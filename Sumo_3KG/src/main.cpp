#include"rotinasRobo.h"

void setup()
{
  Serial.begin(9600);
  //Configuração dos Motores
  motorDir.attach(PIN_MOT_DIR);
  motorEsq.attach(PIN_MOT_ESQ);
  motorDir.writeMicroseconds(1500);
  motorEsq.writeMicroseconds(1500);
  //Configuração dos Sensores 
  pinMode(PIN_SP_LDIR, INPUT_PULLUP);
  pinMode(PIN_SP_DDIR, INPUT_PULLUP);
  pinMode(PIN_SP_FDIR, INPUT_PULLUP);
  pinMode(PIN_SP_F, INPUT_PULLUP);
  pinMode(PIN_SP_FESQ, INPUT_PULLUP);
  pinMode(PIN_SP_DESQ, INPUT_PULLUP);
  pinMode(PIN_SP_LESQ, INPUT_PULLUP);
  //Configuração DIP Switch 
  pinMode(PIN_DIP1, INPUT_PULLUP);
  pinMode(PIN_DIP2, INPUT_PULLUP);
  pinMode(PIN_DIP3, INPUT_PULLUP);
  //Configuração interrupts do receptor
  attachInterrupt(PIN_CH1, lerCH1, CHANGE);
  attachInterrupt(PIN_CH2, lerCH2, CHANGE);
  attachInterrupt(PIN_CH3, lerCH3, CHANGE);
}

void loop()
{
  static uint16_t deltaT_CH1_Temp, deltaT_CH2_Temp, deltaT_CH3_Temp;
  noInterrupts();
  deltaT_CH1_Temp = deltaT_CH1;
  deltaT_CH2_Temp = deltaT_CH2;
  deltaT_CH3_Temp = deltaT_CH3;
  interrupts();

  motorDir.writeMicroseconds(deltaT_CH1_Temp);
  motorEsq.writeMicroseconds(deltaT_CH2_Temp);
  
  //lerDIP();
  //lerSensores();
  //exibeSensores();
  //exibeDIP();
  exibeReceptor(deltaT_CH1_Temp, deltaT_CH2_Temp, deltaT_CH3_Temp);
}