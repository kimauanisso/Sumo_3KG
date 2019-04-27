#include "rotinasInterrupt.h"

/********Funções de Leitura*******************/
//Leitura dos sensores de presença
//Organiza um byte com os sete sensores IR de presença
// NA LAT_ESQ DIAG_ESQ FRENTE_ESQ FRENTE FRENTE_DIR DIAG_DIR LAT_DIR
void lerSensores()
{
    bitWrite(sensoresPresenca, 0, !digitalRead(PIN_SP_LDIR));
    bitWrite(sensoresPresenca, 1, !digitalRead(PIN_SP_DDIR));
    bitWrite(sensoresPresenca, 2, !digitalRead(PIN_SP_FDIR));
    bitWrite(sensoresPresenca, 3, !digitalRead(PIN_SP_F));
    bitWrite(sensoresPresenca, 4, !digitalRead(PIN_SP_FESQ));
    bitWrite(sensoresPresenca, 5, !digitalRead(PIN_SP_DESQ));
    bitWrite(sensoresPresenca, 6, !digitalRead(PIN_SP_LESQ));
    bitWrite(sensoresPresenca, 7, 1);
}

void lerDIP()
{
    //Função de leitura do DIP Switch
    dip1 = !digitalRead(PIN_DIP1);
    dip2 = !digitalRead(PIN_DIP2);
    dip3 = !digitalRead(PIN_DIP3);
}

/**************Funções de Busca**********/
//Parametros
//      velAvanco - velocidade de avanço para quando encontra algo
//      
void buscaSimples(int velAvanco, int velAlta, int velMedia, int velBaixa)
{
    //Começa verificando o sensor da frente, que é a prioridade
    if(bitRead(sensoresPresenca, 3))
        moveRobo(velAvanco, velAvanco);
    else
    {
        switch (sensoresPresenca)
        {
        case 0b10000001:
            //Leitura apenas da lateral esquerda
            moveRobo(velAlta, -velAlta);
            break;
        case 0b10000010:
            //Leitura apenas da diagonal esquerda
            moveRobo(velMedia, -velMedia);
            break;
        case 0b10000011:
            //Leitura dos sensores diagonal e lateral esquerda
            moveRobo(velMedia, -velMedia);
            break;
        case 0b10000100:
            //Leitura apenas da frente esquerda
            moveRobo(velMedia, velBaixa);
            break;
        case 0b10000110:
            //Leitura da diagonal e frente esquerda
            moveRobo(velMedia, velBaixa);
            break;
        case 0b10000111:
            //Leitura de todos os sensores da esquerda
            moveRobo(velMedia, velBaixa);
            break;        
        default:
            break;
        }        
    }
}

/********Funções de movimentação**********/
//Converte valores de -100 a 100 para o intervalo em microssegundos do sinal de servo
//Parametros velEsq e velDir - velocidades dos motores de -100 a 100
void moveRobo(int velEsq, int velDir)
{
    velEsq = map(velEsq, -100,100,1010, 2013);
    velDir = map(velDir, -100,100,985, 1985);
    motorEsq.writeMicroseconds(velEsq);
    motorDir.writeMicroseconds(velDir);
}

void controlaRobo(uint16_t Ch1, uint16_t Ch2)
{
    int velEsq = map(Ch1, 980, 2010, -100, 100);
    int velDir = map(Ch2, 980, 2010, -100, 100);
    moveRobo(velEsq, velDir);
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