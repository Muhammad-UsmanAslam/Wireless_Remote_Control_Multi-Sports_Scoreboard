#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"

// =============================================================================
// P10 PANEL CONFIGURATION
// Arduino → Panel 1 → Panel 2 → Panel 3 → Panel 4 → Panel 5 → Panel 6
// HUB12 interface, 6 panels chained in a SINGLE ROW = 192x16 pixels
//
// IMPORTANT: The DMD library constructor signature is:
//      DMD(panelsWide, panelsHigh)
// Since all 6 panels are chained horizontally (one row), it must be
// called as DMD(6, 1) — NOT DMD(1, 6). Swapping these two values is
// what was causing garbled / incorrect output across the panels.
// =============================================================================
#define DISPLAYS_WIDE   6   // panels chained left-to-right
#define DISPLAYS_HIGH   1   // panels stacked top-to-bottom

DMD p10(DISPLAYS_WIDE, DISPLAYS_HIGH);

// Each P10 panel module is 32 px wide x 16 px tall.
#define PANEL_PX_WIDE   32
#define TOTAL_WIDTH     (DISPLAYS_WIDE * PANEL_PX_WIDE)   // 192
#define SECTION_WIDTH   (TOTAL_WIDTH / 3)                 // 64 px per pair of panels

// =============================================================================
// BLUETOOTH DATA
// =============================================================================
String gameName     = "GAME NAME";
String team1Name    = "TEAM 1";
String team2Name    = "TEAM 2";
int    score1       = 0;
int    score2       = 0;
String timerStr     = "00:00";
String timerEnabled = "ON";

char buf[100];
byte bufPos = 0;
unsigned long lastCharTime = 0;
const unsigned long MSG_TIMEOUT = 100;

// =============================================================================
// DISPLAY REFRESH (called by Timer1 interrupt)
// =============================================================================
void p10scan() {
  p10.scanDisplayBySPI();
}

// =============================================================================
// PARSE BLUETOOTH COMMAND
// Format: GAME:FOOTBALL|T1:TEAM 1|S1:3|T2:TEAM 2|S2:2|TM:05:30|TS:RUN|TE:ON
// =============================================================================
String getValue(String data, String key, String defaultVal) {
  int start = data.indexOf(key);
  if (start == -1) return defaultVal;
  start += key.length();
  int finish = data.indexOf("|", start);
  if (finish == -1) finish = data.length();
  return data.substring(start, finish);
}

void processCommand(String cmd) {
  if (cmd.length() == 0) return;

  gameName     = getValue(cmd, "GAME:", gameName);
  team1Name    = getValue(cmd, "T1:",   team1Name);
  score1       = getValue(cmd, "S1:",   String(score1)).toInt();
  team2Name    = getValue(cmd, "T2:",   team2Name);
  score2       = getValue(cmd, "S2:",   String(score2)).toInt();
  timerStr     = getValue(cmd, "TM:",   timerStr);
  timerEnabled = getValue(cmd, "TE:",   timerEnabled);

  drawScoreboard();
}

// =============================================================================
// DRAW SCOREBOARD
// Panel 1-2 (X=0-63):    [GAME NAME            00:00]
// Panel 3-4 (X=64-127):  [TEAM 1                   0]
// Panel 5-6 (X=128-191): [TEAM 2                   0]
// =============================================================================
void drawScoreboard() {
  p10.clearScreen(true);
  p10.selectFont(SystemFont5x7);

  char textBuf[24];
  int textWidth;

  // --- Panel 1-2: Game Name + Timer ---
  gameName.toCharArray(textBuf, sizeof(textBuf));
  p10.drawString(0, 0, textBuf, strlen(textBuf), GRAPHICS_NORMAL);

  if (timerEnabled == "ON") {
    timerStr.toCharArray(textBuf, sizeof(textBuf));
    textWidth = strlen(textBuf) * 6;
    p10.drawString(SECTION_WIDTH - textWidth, 0, textBuf, strlen(textBuf), GRAPHICS_NORMAL);
  }

  // --- Panel 3-4: Team 1 + Score ---
  team1Name.toCharArray(textBuf, sizeof(textBuf));
  p10.drawString(SECTION_WIDTH, 0, textBuf, strlen(textBuf), GRAPHICS_NORMAL);

  sprintf(textBuf, "%d", score1);
  textWidth = strlen(textBuf) * 6;
  p10.drawString((SECTION_WIDTH * 2) - textWidth, 0, textBuf, strlen(textBuf), GRAPHICS_NORMAL);

  // --- Panel 5-6: Team 2 + Score ---
  team2Name.toCharArray(textBuf, sizeof(textBuf));
  p10.drawString(SECTION_WIDTH * 2, 0, textBuf, strlen(textBuf), GRAPHICS_NORMAL);

  sprintf(textBuf, "%d", score2);
  textWidth = strlen(textBuf) * 6;
  p10.drawString(TOTAL_WIDTH - textWidth, 0, textBuf, strlen(textBuf), GRAPHICS_NORMAL);
}

// =============================================================================
// SETUP
// =============================================================================
void setup() {
  Serial.begin(9600);

  Timer1.initialize(2000);
  Timer1.attachInterrupt(p10scan);

  p10.clearScreen(true);
  drawScoreboard();
}

// =============================================================================
// MAIN LOOP
// =============================================================================
void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (bufPos < sizeof(buf) - 1) buf[bufPos++] = c;
    lastCharTime = millis();
  }

  if (bufPos > 0 && (millis() - lastCharTime > MSG_TIMEOUT)) {
    buf[bufPos] = '\0';
    String cmd = String(buf);
    cmd.trim();
    processCommand(cmd);
    bufPos = 0;
  }
}
