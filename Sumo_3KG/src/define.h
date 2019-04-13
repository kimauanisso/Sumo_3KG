#ifndef define
#define define

#include <Arduino.h>
#include <Servo.h>

/************Definição de pinos*************/
//Receptor
#define PIN_CH1 A0
#define PIN_CH2 A1
#define PIN_CH3 A2
//Sensores de Presença
#define PIN_SP_F 9
#define PIN_SP_FDIR 7
#define PIN_SP_FESQ 11
#define PIN_SP_DDIR 8
#define PIN_SP_DESQ 10
#define PIN_SP_LDIR 6
#define PIN_SP_LESQ 12
//DIP Switch
#define PIN_DIP1 4
#define PIN_DIP2 3
#define PIN_DIP3 2
//Sensores de Linha
#define PIN_SL_DIR A5
#define PIN_SL_ESQ A6
//Motores 
#define PIN_MOT_DIR A4
#define PIN_MOT_ESQ A3

//Definição de variáveis da leitura do receptor
//deltaT -> Tamanho do pulso do sinal de Servo do receptor
//tZero_CH1 -> Guarda o tempo inicial de leitura do sinal do receptor
volatile uint16_t deltaT_CH1, deltaT_CH2, deltaT_CH3;
uint16_t tZero_CH1, tZero_CH2, tZero_CH3;

//Variáveis dos motores
Servo motorDir;
Servo motorEsq;

//Variáveis de sensores e outros inputs
uint8_t dip1, dip2, dip3; //variáveis do DIP Switch
uint8_t sensoresPresenca; //variável que armazena o estado de todos os sensores de presença

#endif