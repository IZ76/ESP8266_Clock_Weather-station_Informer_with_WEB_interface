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
byte scr[NUM_MAX * 8 + 8];
//======================================================================================================
void sendCmd(int addr, byte cmd, byte data) {
  digitalWrite(CS_PIN, LOW);
  for(int i = NUM_MAX - 1; i >= 0; i--) {
    shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, i == addr ? cmd : 0);
    shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, i == addr ? data : 0);
  }
  digitalWrite(CS_PIN, HIGH);
}
//======================================================================================================
void sendCmdAll(byte cmd, byte data) {
  digitalWrite(CS_PIN, LOW);
  for(int i = NUM_MAX - 1; i >= 0; i--) {
    shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, cmd);
    shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, data);
  }
  digitalWrite(CS_PIN, HIGH);
}
//======================================================================================================
void refresh(int addr) {
  for(int i = 0; i < 8; i++)
    sendCmd(addr, i + CMD_DIGIT0, scr[addr * 8 + i]);
}
//======================================================================================================
void refreshAllRot270() {
  byte mask = 0x01;
  for(int c = 0; c < 8; c++){
    digitalWrite(CS_PIN, LOW);
    for(int i = NUM_MAX - 1; i >= 0; i--) {
      byte bt = 0;
      for(int b = 0; b < 8; b++){
        bt <<= 1;
        if(scr[i * 8 + b] & mask) bt |= 0x01;
      }
      shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, CMD_DIGIT0 + c);
      shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, bt);
    }
    digitalWrite(CS_PIN, HIGH);
    mask <<= 1;
  }
}
//======================================================================================================
void refreshAllRot90() {
  byte mask = 0x80;
  for(int c = 0; c < 8; c++){
    digitalWrite(CS_PIN, LOW);
    for(int i = NUM_MAX - 1; i >= 0; i--) {
      byte bt = 0;
      for(int b = 0; b < 8; b++){
        bt >>= 1;
        if(scr[i * 8 + b] & mask) bt |= 0x80;
      }
      shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, CMD_DIGIT0 + c);
      shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, bt);
    }
    digitalWrite(CS_PIN, HIGH);
    mask >>= 1;
  }
}
//======================================================================================================
void refreshAll() {
  if(rotate == 270) {
    refreshAllRot270();
  } else if(rotate == 90) {
    refreshAllRot90();
  } else {
    for(int c = 0; c < 8; c++){
      digitalWrite(CS_PIN, LOW);
      for(int i = NUM_MAX - 1; i >= 0; i--){
        shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, CMD_DIGIT0 + c);
        shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, scr[i * 8 + c]);
      }
    digitalWrite(CS_PIN, HIGH);
    }
  }
}
//======================================================================================================
void clr() {
  for(int i = 0; i < NUM_MAX * 8; i++) scr[i] = 0;
}
//======================================================================================================
void scrollLeft() {
  for(int i = 0; i < NUM_MAX * 8 + 7; i++) scr[i] = scr[i + 1];
}
//======================================================================================================
void invert() {
  for(int i = 0; i < NUM_MAX * 8; i++) scr[i] =~ scr[i];
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
  clr();
  refreshAll();
}
