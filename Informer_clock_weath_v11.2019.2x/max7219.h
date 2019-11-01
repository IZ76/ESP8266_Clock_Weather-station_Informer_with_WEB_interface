// MAX7219 commands:
#define CMD_NOOP   0
#define CMD_DIGIT0 1
#define CMD_DIGIT1 2
#define CMD_DIGIT2 3
#define CMD_DIGIT3 4
#define CMD_DIGIT4 5
#define CMD_DIGIT5 6
#define CMD_DIGIT6 7
#define CMD_DIGIT7 8
#define CMD_DECODEMODE  9
#define CMD_INTENSITY   10
#define CMD_SCANLIMIT   11
#define CMD_SHUTDOWN    12
#define CMD_DISPLAYTEST 15
byte scr[136];            // Максимально можно использовать 16 секций 8х8 (NUM_MAX *8 +8)
//======================================================================================================
void sendCmdAll(byte cmd, byte data) {
  digitalWrite(CS_PIN, LOW);
  for(int i = NUM_MAX0 + NUM_MAX1 - 1; i >= 0; i--) {
    shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, cmd);
    shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, data);
  }
  digitalWrite(CS_PIN, HIGH);
}
//======================================================================================================
void refreshAll() {
  byte mask0 = (rotate0 == 270? 0x01 : 0x80);
  byte mask1 = (rotate1 == 270? 0x01 : 0x80);
  for(int c = 0; c < 8; c++) {
    digitalWrite(CS_PIN, LOW);
    for(int i = NUM_MAX0 + NUM_MAX1 - 1; i >= NUM_MAX0; i--) {
      byte bt = 0;
      if(rotate1 == 270) {
        for(int b = 0; b < 8; b++){
          bt <<= 1;
          if(scr[i * 8 + b] & mask1) bt |= 0x01;
        }
        shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, CMD_DIGIT0 + c);
        shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, bt);
      } else if(rotate1 == 90) {
        for(int b = 0; b < 8; b++){
          bt >>= 1;
          if(scr[i * 8 + b] & mask1) bt |= 0x80;
        }
        shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, CMD_DIGIT0 + c);
        shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, bt);
      } else {
        shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, CMD_DIGIT0 + c);
        shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, scr[i * 8 + c]);
      }
    }
    if(rotate1 == 270) mask1 <<= 1;
    if(rotate1 == 90) mask1 >>= 1;
    for(int i = NUM_MAX0 - 1; i >=0; i--) {
      byte bt = 0;
      if(rotate0 == 270) {
        for(int b = 0; b < 8; b++){
          bt <<= 1;
          if(scr[i * 8 + b] & mask0) bt |= 0x01;
        }
        shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, CMD_DIGIT0 + c);
        shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, bt);
      } else if(rotate0 == 90) {
        for(int b = 0; b < 8; b++){
          bt >>= 1;
          if(scr[i * 8 + b] & mask0) bt |= 0x80;
        }
        shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, CMD_DIGIT0 + c);
        shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, bt);
      } else {
        shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, CMD_DIGIT0 + c);
        shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, scr[i * 8 + c]);
      }
    }
    digitalWrite(CS_PIN, HIGH);
    if(rotate0 == 270) mask0 <<= 1;
    if(rotate0 == 90) mask0 >>= 1;
  }
}
//======================================================================================================
void clr(byte zone) {
  for(int i = (zone ? NUM_MAX0 * 8 : 0); i < (zone ? NUM_MAX1 + NUM_MAX0 : NUM_MAX0) * 8; i++) scr[i] = 0;
}
//======================================================================================================
void clrAll() {
  for(int i = 0; i < (NUM_MAX1 + NUM_MAX0) * 8; i++) scr[i] = 0;
}
//======================================================================================================
void scrollLeft(byte zone) {
  for(int i = (zone ? NUM_MAX0 * 8 : 0); i < (zone ? NUM_MAX0 + NUM_MAX1 : NUM_MAX0) * 8 + 7; i++) scr[i] = scr[i + 1];
}
//======================================================================================================
void scrollDown(byte zone) {
  for(int i = (zone ? NUM_MAX0 * 8 : 0); i < (zone ? NUM_MAX0 + NUM_MAX1 : NUM_MAX0) * 8 + 7; i++) scr[i] = scr[i]<<1;
}
//======================================================================================================
void invert(byte zone) {
  for(int i = (zone ? NUM_MAX0 * 8 : 0); i < (zone ? NUM_MAX0 + NUM_MAX1 : NUM_MAX0) * 8; i++) scr[i] =~ scr[i];
}
//======================================================================================================
void initMAX7219() {
  pinMode(DIN_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  sendCmdAll(CMD_DISPLAYTEST, 0);
  sendCmdAll(CMD_SCANLIMIT, 7);
  sendCmdAll(CMD_DECODEMODE, 0);
  sendCmdAll(CMD_INTENSITY, 0);
  sendCmdAll(CMD_SHUTDOWN, 0);
  clrAll();
  refreshAll();
}
