//Barra sem pot
//Ilumina uma barra de LED's (B210SR) para testes, sem potenciometro para controle
//Utiliza um shift register (74HC595 ou 595)
//Licenca: Apache 2.0 (use como quiser)
//http://www.apache.org/licenses/LICENSE-2.0.html
//Copyright 2014 Otavio Carneiro (carneiro.blog.br)

const int data_pin = 0; //DS (pino 14 no 595)    - ligado com um resistor de 300R
const int latch_pin = 1; //STCP (pino 12 no 595) - ligado com um resistor de 300R
const int save_pin = 2; //SHCP (pino 11 no 595)  - ligado com um resistor de 300R
//o pino 13 (OE - pause) foi ligado ao GND diretamente
//o pino 10 (MR - Nreset) foi ligado ao VCC com um resistor de 1k

const int led9 = 3;
const int led10 = 4;

//sequencia de valores a serem exibidos pela barra de leds, representados por 1 (aceso) e 0 (apagado)
int valores[] = {
                   0,   //B0000000000, 
                   1,   //B0000000001,  //2**0 = 1
                   3,   //B0000000011,  //2**1 = 2 + 1 = 3
                   7,   //B0000000111,  //2**2 = 4 + 3 = 7
                   15,  //B0000001111,  //2**3 = 8 + 7 = 15
                   31,  //B0000011111, 
                   63,  //B0000111111, 
                   127, //B0001111111, 
                   255, //B0011111111,
                   511, //B0111111111,
                   1023 //B1111111111 = 10 bits acesos
                 };

void setup() {
  pinMode(data_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(save_pin,OUTPUT);  
  latch();
  pinMode(led9, OUTPUT);
  pinMode(led10, OUTPUT);
}

void loop() {
  int pausa = 200;
  for(int saida = 0; saida <= 10; saida++) {
    acendeBarra(valores[saida]);
    delay(pausa);
  }
  
  for(int saida = 10; saida >= 0; saida--) {
    acendeBarra(valores[saida]);
    delay(pausa);
  }
  
}


//acende leds a partir de um inteiro que representa bits acesos ou apagados
void acendeBarra(int valor) {
    //utiliza o shift register para os 8 primeiros bits
    for(int pos_atual = 7; pos_atual >= 0; pos_atual--) {
      setData(bit_aceso(valor, pos_atual));
      save();
    }
    latch();
    digitalWrite(led9, bit_aceso(valor, 8));
    digitalWrite(led10, bit_aceso(valor, 9));
} 

//retorna verdadeiro se o bit na posicao "indice" for 1. 
boolean bit_aceso(int valor, int indice)
{
    return (valor & (1 << indice)) != 0;
}

//envia um valor no pino data
void setData(int value) {
  digitalWrite(data_pin, value);
}

//salva o dado no 595
void save() {
  digitalWrite(save_pin, HIGH);
  digitalWrite(save_pin, LOW);
}

//libera a exibicao dos dados gravados
void latch() {
  digitalWrite(latch_pin, HIGH);
  digitalWrite(latch_pin, LOW);
}
