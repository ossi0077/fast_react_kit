#include "LedControl.h"  //dot matrix를 사용하기 위한 라이브러리 호출

#define dataIn 12  //DIN 12번 핀으로 사용
#define cs 11      //CS 11번 핀으로 사용
#define clk 10     //CLK 10번 핀으로 사용
#define Player1 4  //button 핀번호
#define Player2 6  //button 핀번호

LedControl lc = LedControl(dataIn, clk, cs, 1);  //LedControl('DIN핀 번호', 'CLK핀 번호', 'CS핀 번호', 'dot matrix 갯수')

int stateCheck = 0;
bool Matrix_false[8][8] = {
  0,
};
bool MatrixInput_1[8][8] = {
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 0, 1, 0, 0, 0, 0, 1, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 1, 0, 0, 0, 0, 1, 0 },
  { 1, 0, 0, 0, 0, 0, 0, 1 }
};

bool MatrixInput_2[8][8] = {
  { 0, 0, 1, 1, 1, 1, 0, 0 },
  { 0, 1, 0, 0, 0, 0, 1, 0 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 0, 1, 0, 0, 0, 0, 1, 0 },
  { 0, 0, 1, 1, 1, 1, 0, 0 }
};

bool MatrixInput_3[8][8] = {
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 1, 1, 1, 1, 1, 1, 0 },
  { 0, 0, 1, 1, 1, 1, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 }
};

bool MatrixInput_4[8][8] = {
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 0 },
  { 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 }
};

int btnFlg1 = 0;
int btnFlg2 = 0;
int btn1Chk() {
  if (digitalRead(Player1) == 0) {
    btnFlg1 = 1;
    return 0;
  }
  if (btnFlg1 == 1) {
    btnFlg1 = 0;
    return 1;
  }
  return 0;
}

int btn2Chk() {
  if (digitalRead(Player2) == 0) {
    btnFlg2 = 1;
    return 0;
  }
  if (btnFlg2 == 1) {
    btnFlg2 = 0;
    return 1;
  }
  return 0;
}

void MatrixLoop(bool matinput[8][8]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      lc.setLed(0, i, j, matinput[i][j]);
    }
  }
}

void setupfunc() {
  MatrixLoop(MatrixInput_1);
  randomSeed(analogRead(0));
  int randomTime = random(3, 6);
  delay(randomTime * 1000);
  MatrixLoop(MatrixInput_2);
}

void setup() {
  pinMode(Player1, INPUT_PULLUP);
  pinMode(Player2, INPUT_PULLUP);
  lc.shutdown(0, false);  //dot matrix를 깨우는 코드. shutdown('지정할 dotmatrix의 주소', 'false : 깨우기')
  lc.setIntensity(0, 8);  //밝기 설정. setIntensity('지정할 dotmatrix의 주소','밝기값(0~15)')
  lc.clearDisplay(0);     //사용하기 전 초기화. clearDisplay('지정할 dotmatrix의 주소')
}

void loop() {
  if (stateCheck == 1) {
    if (btn1Chk() == 1) {
      stateCheck = 0;
      MatrixLoop(MatrixInput_3);
      delay(1500);
      MatrixLoop(Matrix_false);
    } else if (btn2Chk() == 1) {
      stateCheck = 0;
      MatrixLoop(MatrixInput_4);
      delay(1500);
      MatrixLoop(Matrix_false);
    }
  } else if (stateCheck == 0) {
    if ((btn1Chk() == 1) || (btn2Chk() == 1)) {
      setupfunc();
      stateCheck = 1;
    }
  }
}