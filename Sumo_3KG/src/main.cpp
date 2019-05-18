#include "rotinasRobo.h"

void setup()
{
  Serial.begin(9600);
  //Configuração dos Motores
  motorDir.attach(PIN_MOT_DIR, 1000, 2000);
  motorEsq.attach(PIN_MOT_ESQ, 1000, 2000);
  // motorDir.writeMicroseconds(1500);
  // motorEsq.writeMicroseconds(1500);
  // delay(200);

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
  delay(2000);
  lerReceptor();
  controlaRobo(deltaT_CH1_Temp, deltaT_CH2_Temp);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop()
{
  lerReceptor();
  if (deltaT_CH3_Temp < 1900  && deltaT_CH3_Temp > 1100)
  {
    controlaRobo(deltaT_CH1_Temp, deltaT_CH2_Temp);
    //exibeReceptor(deltaT_CH1_Temp, deltaT_CH2_Temp, deltaT_CH3_Temp);
  }
  else
  {
    lerDIP();
    delay(4800);
    //exibeDIP();
    switch (valorDIP)
    {
    case 0b11111111:
      //Serial.println("Parado");
      moveRobo(0, 0);
      break;
    case 0b11111110:
      //Serial.println("Frente");
      frente(100, 65, 140);
      break;
    case 0b11111101:
      if (deltaT_CH3_Temp > 1800)
      {
        //Serial.println("Cedilha Esq");
        cedilha(100, 40, 235, 'D');
      }
      else
      {
        //Serial.println("Cedilha Dir");
        cedilha(100, 65, 180, 'e');
      }
      break;
    case 0b11111100:
      //Serial.println("Gira 180");
      gira180(100, -100, 120);
      break;
    default:
      //Serial.println("Erro");
      break;
    }

    while (deltaT_CH3_Temp > 1800 || deltaT_CH3_Temp < 1200)
    {
      lerReceptor();
      lerSensores();
      buscaSimples(100, 70, 50, 30); //(0, 70, 50, 30);
      //exibeSensores();
    }
  }
}