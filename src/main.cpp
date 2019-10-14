#include "rotinasRobo.h"

// Eleven
// Branch eleven

void setup() {
  Serial.begin(9600);
  // Configuração dos Motores
  motorDir.attach(PIN_MOT_DIR, 1000, 2000);
  motorEsq.attach(PIN_MOT_ESQ, 1000, 2000);

  // Configuração Módulo de Start
  pinMode(PIN_START, INPUT);

  // Configuração dos Sensores
  pinMode(PIN_SP_LDIR, INPUT_PULLUP);
  pinMode(PIN_SP_DDIR, INPUT_PULLUP);
  pinMode(PIN_SP_FDIR, INPUT_PULLUP);
  pinMode(PIN_SP_F, INPUT_PULLUP);
  pinMode(PIN_SP_FESQ, INPUT_PULLUP);
  pinMode(PIN_SP_DESQ, INPUT_PULLUP);
  pinMode(PIN_SP_LESQ, INPUT_PULLUP);
  // Configuração DIP Switch
  pinMode(PIN_DIP1, INPUT_PULLUP);
  pinMode(PIN_DIP2, INPUT_PULLUP);
  pinMode(PIN_DIP3, INPUT_PULLUP);
  // Configuração interrupts do receptor
  attachInterrupt(PIN_CH1, lerCH1, CHANGE);
  attachInterrupt(PIN_CH2, lerCH2, CHANGE);
  attachInterrupt(PIN_CH3, lerCH3, CHANGE);
  delay(2000);
  lerReceptor();
  controlaRobo(deltaT_CH1_Temp, deltaT_CH2_Temp);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  lerReceptor();
  // exibeReceptor(deltaT_CH1_Temp, deltaT_CH2_Temp, deltaT_CH3_Temp);
  if (deltaT_CH3_Temp < 1900 && deltaT_CH3_Temp > 1100) {
    controlaRobo(deltaT_CH1_Temp, deltaT_CH2_Temp);
    // exibeReceptor(deltaT_CH1_Temp, deltaT_CH2_Temp, deltaT_CH3_Temp);
  } else {
    lerDIP();
    movimentoInicial();
    while (deltaT_CH3_Temp > 1800 || deltaT_CH3_Temp < 1200) {
      controlaRobo(deltaT_CH1_Temp, deltaT_CH2_Temp);
      lerSensores();  
      if (bitRead(sensoresPresenca, 3)) {
        if (flagAvanco < 5000) {
          moveRobo(20, 20);
          flagAvanco++;
        } else if ((flagAvanco >= 5000) && (flagAvanco < 10000)) {
          moveRobo(30, 30);
          flagAvanco++;
        } else if ((flagAvanco >= 10000) && (flagAvanco < 15000)) {
          moveRobo(50, 50);
          flagAvanco++;
        } else if (flagAvanco >= 15000) {
          moveRobo(100, 100);
          digitalWrite(13, HIGH);
        }
      } else flagAvanco = 0;
     } 
     moveRobo(0,0);
    }
 }