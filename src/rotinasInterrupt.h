#include "define.h"

void lerCH1()
{
  if (digitalRead(PIN_CH1))
    tZero_CH1 = micros();
  else
    deltaT_CH1 = micros() - tZero_CH1;
}

void lerCH2()
{
  if (digitalRead(PIN_CH2))
    tZero_CH2 = micros();
  else
    deltaT_CH2 = micros() - tZero_CH2;
}

void lerCH3()
{
  if (digitalRead(PIN_CH3))
    tZero_CH3 = micros();
  else
    deltaT_CH3 = micros() - tZero_CH3;
}