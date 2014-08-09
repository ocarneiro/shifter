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
int valores[] = {511,1023,768,768,768,768,768,768,0, //L
                 512,768,960,240,124,110,99,110,124,240,960,768,512,0, //A
                 1022,1022,546,546,546,546,806,886,1022,476,0,0,0, //B
                 1023,32,32,32,32,32,32,1023,0, //H
                 384,640,640,672,672,448,0, //a
                 448,544,544,544,544,544,0, //c
                 1023,128,320,544,0, //k
                 448,672,672,672,160,192,0, //e
                 960,32,32,0,0,0,0,0 //r
                 };
//verifica quantos inteiros formam a mensagem
int qtde_valores = sizeof(valores) / sizeof(int); 

void setup() {
  pinMode(data_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(save_pin,OUTPUT);  
  latch();
  pinMode(led9, OUTPUT);
  pinMode(led10, OUTPUT);
}

void loop() {
  //int pausa = 2;  //200 eh lento demais... 50 tb... 20 idem... 2 tambem
  int micro_pausa = 15; //300 eh muito
  for(int saida = 0; saida <= qtde_valores; saida++) {
    acendeBarra(valores[saida]);
    //delay(pausa);
    delayMicroseconds(micro_pausa);
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
