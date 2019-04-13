#include "rotinasInterrupt.h"


void lerSensores()
{
    bitWrite(sensoresPresenca, 0, digitalRead(PIN_SP_LDIR));
    bitWrite(sensoresPresenca, 1, digitalRead(PIN_SP_DDIR));
    bitWrite(sensoresPresenca, 2, digitalRead(PIN_SP_FDIR));
    bitWrite(sensoresPresenca, 3, digitalRead(PIN_SP_F));
    bitWrite(sensoresPresenca, 4, digitalRead(PIN_SP_FESQ));
    bitWrite(sensoresPresenca, 5, digitalRead(PIN_SP_DESQ));
    bitWrite(sensoresPresenca, 6, digitalRead(PIN_SP_LESQ));
    bitWrite(sensoresPresenca, 7, 1);
}

void lerDIP()
{
    //Função de leitura do DIP Switch
    dip1 = !digitalRead(PIN_DIP1);
    dip2 = !digitalRead(PIN_DIP2);
    dip3 = !digitalRead(PIN_DIP3);
}

/********Funções de exibição*******/

void exibeSensores()
{
    Serial.println(sensoresPresenca, BIN);
}

void exibeDIP()
{
    //Função de exibição dos valores do DIP Switch
    Serial.print(dip1);
    Serial.print(" ");
    Serial.print(dip2);
    Serial.print(" ");
    Serial.println(dip3);
}

void exibeReceptor(uint16_t CH1, uint16_t CH2, uint16_t CH3)
{
    //Função de exibição dos valores lidos do receptor RF
    Serial.print(CH1);
    Serial.print(" ");
    Serial.print(CH2);
    Serial.print(" ");
    Serial.println(CH3);
}