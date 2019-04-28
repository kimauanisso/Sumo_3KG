#include "rotinasRobo.h"

void setup()
{
  Serial.begin(9600);
  //Configuração dos Motores
  motorDir.attach(PIN_MOT_DIR, 1000, 2000);
  motorEsq.attach(PIN_MOT_ESQ, 1000, 2000);
  //motorDir.writeMicroseconds(1500);
  //motorEsq.writeMicroseconds(1500);
  //delay(1000);

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
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop()
{
  static uint16_t deltaT_CH1_Temp, deltaT_CH2_Temp, deltaT_CH3_Temp;
  noInterrupts();
  deltaT_CH1_Temp = deltaT_CH1;
  deltaT_CH2_Temp = deltaT_CH2;
  deltaT_CH3_Temp = deltaT_CH3;
  interrupts();

  if (deltaT_CH3_Temp < 1800)
  {
    controlaRobo(deltaT_CH1_Temp, deltaT_CH2_Temp);
    //exibeReceptor(deltaT_CH1_Temp, deltaT_CH2_Temp, deltaT_CH3_Temp);
  }
  else
  {
    lerSensores();
    buscaSimples(velAvanco, velAlta, velMedia, velBaixa);//(0, 80, 50, 30);
    //exibeSensores();
  }

  //lerDIP();

  //exibeDIP();
}