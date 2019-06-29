#include "rotinasInterrupt.h"

/********Funções de Leitura*******************/
// Leitura dos sensores de presença
// Organiza um byte com os sete sensores IR de presença
// NA LAT_ESQ DIAG_ESQ FRENTE_ESQ FRENTE FRENTE_DIR DIAG_DIR LAT_DIR
void lerSensores() {
  bitWrite(sensoresPresenca, 0, !digitalRead(PIN_SP_LDIR));
  bitWrite(sensoresPresenca, 1, !digitalRead(PIN_SP_DDIR));
  bitWrite(sensoresPresenca, 2, !digitalRead(PIN_SP_FDIR));
  bitWrite(sensoresPresenca, 3, !digitalRead(PIN_SP_F));
  bitWrite(sensoresPresenca, 4, !digitalRead(PIN_SP_FESQ));
  bitWrite(sensoresPresenca, 5, !digitalRead(PIN_SP_DESQ));
  bitWrite(sensoresPresenca, 6, !digitalRead(PIN_SP_LESQ));
  bitWrite(sensoresPresenca, 7, 1);
}

void lerDIP() {
  // Função de leitura do DIP Switch
  valorDIP = 0b11111100;
  bitWrite(valorDIP, 0, digitalRead(PIN_DIP2));
  bitWrite(valorDIP, 1, digitalRead(PIN_DIP3));
}

void lerReceptor() {
  noInterrupts();
  deltaT_CH1_Temp = deltaT_CH1;
  deltaT_CH2_Temp = deltaT_CH2;
  deltaT_CH3_Temp = deltaT_CH3;
  interrupts();
}

/***********Pré Rotinas******************/
void frente(int velEsq, int velDir, int tempo) {
  moveRobo(velEsq, velDir);
  delay(tempo);
  moveRobo(0, 0);
}

void cedilha(int velMaior, int velMenor, int tempo, char lado) {
  if (lado == 'D' || lado == 'd')
    moveRobo(velMenor, velMaior);
  else
    moveRobo(velMaior, velMenor);
  delay(tempo);
  moveRobo(0, 0);
}

void gira180(int velE, int velD, int tempo) {
  moveRobo(velE, velD);
  delay(tempo);
  moveRobo(0, 0);
}



/**************Funções de Busca**********/
// Parametros
// velAvanco - velocidade de avanço para quando encontra algo
//
void buscaSimples(int velAvanco, int velAlta, int velMedia, int velBaixa) {
  // Começa verificando o sensor da frente, que é a prioridade
  if (bitRead(sensoresPresenca, 3)) {
    if (flagAvanco < 5000) {
      moveRobo(velAvanco / 5, velAvanco / 5);
      flagAvanco++;
    } else if ((flagAvanco >= 5000) && (flagAvanco < 10000)) {
      moveRobo(velAvanco / 4, velAvanco / 4);
      flagAvanco++;
    } else if ((flagAvanco >= 10000) && (flagAvanco < 15000)) {
      moveRobo(velAvanco / 2, velAvanco / 2);
      flagAvanco++;
    } else if (flagAvanco >= 15000) {
      moveRobo(velAvanco, velAvanco);
      digitalWrite(13, HIGH);
    }
  } else {
    switch (sensoresPresenca) {
      case 0b10000001:
        // Leitura apenas da lateral direita
        moveRobo(velAlta, -velMedia);
        flagAvanco = 0;
        break;
      case 0b10000010:
        // Leitura apenas da diagonal direita
        moveRobo(velMedia, 0);
        flagAvanco = 0;
        break;
      case 0b10000011:
        // Leitura dos sensores diagonal e lateral direita
        moveRobo(velMedia, 0);
        flagAvanco = 0;
        break;
      case 0b10000100:
        // Leitura apenas da frente direita
        moveRobo(velMedia, velBaixa);
        break;
      case 0b10000110:
        // Leitura da diagonal e frente direita
        moveRobo(velMedia, velBaixa);
        break;
      case 0b10000111:
        // Leitura de todos os sensores da direita
        moveRobo(velMedia, velBaixa);
        break;
      case 0b11000000:
        // Leitura apenas da lateral esquerda
        moveRobo(-velMedia, velAlta);
        flagAvanco = 0;
        break;
      case 0b10100000:
        // Leitura apenas da diagonal esquerda
        moveRobo(0, velMedia);
        flagAvanco = 0;
        break;
      case 0b10110000:
        // Leitura dos sensores diagonal e frente esquerda
        moveRobo(0, velMedia);
        break;
      case 0b10010000:
        // Leitura apenas da frente esquerda
        moveRobo(velBaixa, velMedia);
        break;
      case 0b11100000:
        // Leitura da diagonal e lateral esquerda
        moveRobo(velBaixa, velMedia);
        flagAvanco = 0;
        break;
      case 0b11110000:
        // Leitura de todos os sensores da esquerda
        moveRobo(velBaixa, velMedia);
        break;
      case 0b10000000:
        // Leitura de nenhum sensor
        moveRobo(0, 0);
        flagAvanco = 0;
        break;
      default:
        // Caso não mapeado na lógica
        moveRobo(0, 0);
        flagAvanco = 0;
        break;
    }
  }
}

/********Funções de movimentação**********/
// Converte valores de -100 a 100 para o intervalo em microssegundos do sinal de
// servo Parametros velEsq e velDir - velocidades dos motores de -100 a 100
void moveRobo(int velEsq, int velDir) {
  velEsq = map(velEsq, -100, 100, 1010, 2013);
  velDir = map(velDir, -100, 100, 1000, 2000);  // 1100, 1800
  motorEsq.writeMicroseconds(velEsq);
  motorDir.writeMicroseconds(velDir);
}

void controlaRobo(uint16_t Ch1, uint16_t Ch2) {
  int velEsq = map(Ch1, 1000, 2000, -100, 100);
  int velDir = map(Ch2, 1000, 2000, -100, 100);
  moveRobo(velEsq, velDir);
}

/*******Funções de controle******/
// void movimentoInicial(void) {
//   switch (valorDIP) {
//     case 0b11111111:
//       // Serial.println("Parado");
//       moveRobo(0, 0);
//       break;
//     case 0b11111110:
//       // Serial.println("Frente");
//       frente(100, 65, 120);
//       break;
//     case 0b11111101:
//       if (deltaT_CH3_Temp > 1800) {
//         // Serial.println("Cedilha Esq");
//         cedilha(95, 55, 180, 'e');
//       } else {
//         // Serial.println("Cedilha Dir");
//         cedilha(95, 65, 170, 'D');
//         //Arrumar dps
//         // moveRobo(0,0);
//         // delay(60);
//         // moveRobo(100, 100);
//         // delay(40);
//       }
//       break;
//     case 0b11111100:
//       // Serial.println("Gira 180");
//       gira180(100, -100, 60);
//       break;
//     default:
//       // Serial.println("Erro");
//       break;
//   }
// }
/********* Funções de controle 2.0 **********/
void movimentoInicial(void) {
  switch (valorDIP) {
    case 0b11111111:
    if (deltaT_CH3_Temp > 1800){
      //Parado
      moveRobo(0, 0);
    }else{
      //Cedilha Fake
      gira180(100,-100,30);
    }
      break;

    case 0b11111110:
      if (deltaT_CH3_Temp > 1800){
        frente(100, 65, 120);
      }else{
        gira180(100, -100, 60);
      }
      break;

    case 0b11111101:
      if (deltaT_CH3_Temp > 1800) {
        // Serial.println("Cedilha Esq");
        cedilha(95, 55, 180, 'e');
      } else {
        // Serial.println("Cedilha Dir");
        cedilha(95, 65, 170, 'D');
        //Arrumar dps
        // moveRobo(0,0);
        // delay(60);
        // moveRobo(100, 100);
        // delay(40);
      }
      break;

    case 0b11111100:
      if (deltaT_CH3_Temp > 1800){
        gira180(100,-100,15);
        delay(20);
        frente(-100,-80,70);

      }else{
        gira180(-100,100,10);
        delay(20);
        //frente(-100,-80,70);
      }
     break;
    default:
      // Serial.println("Erro");
      break;
  }
}

/********Funções de exibição*******/

void exibeSensores() { Serial.println(sensoresPresenca, BIN); }

void exibeDIP() {
  // Função de exibição dos valores do DIP Switch
  Serial.println(valorDIP, BIN);
}

void exibeReceptor(uint16_t CH1, uint16_t CH2, uint16_t CH3) {
  // Função de exibição dos valores lidos do receptor RF
  Serial.print(CH1);
  Serial.print(" ");
  Serial.print(CH2);
  Serial.print(" ");
  Serial.println(CH3);
}