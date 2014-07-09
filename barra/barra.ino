//Barra
//Ilumina uma barra de LED's (B210SR) a partir de um valor de um potenciometro
//Utiliza um shift register (74HC595 ou 595)
//Licenca: Apache 2.0 (use como quiser)
//http://www.apache.org/licenses/LICENSE-2.0.html
//Copyright 2014 Otavio Carneiro (carneiro.blog.br)

const int data_pin = 2; //DS (pino 14 no 595)    - ligado com um resistor de 300R
const int latch_pin = 3; //STCP (pino 12 no 595) - ligado com um resistor de 300R
const int save_pin = 4; //SHCP (pino 11 no 595)  - ligado com um resistor de 300R
//o pino 13 (OE - pause) foi ligado ao GND diretamente
//o pino 10 (MR - Nreset) foi ligado ao VCC com um resistor de 1k

const int pot = A0; //Potenciometro conectado ao pino analogico A0

//sequencia de valores a serem exibidos pela barra de leds, representados por 1 (aceso) e 0 (apagado)
int valores[] = {
                   0,   //B00000000, 
                   1,   //B00000001,  //2**0 = 1
                   3,   //B00000011,  //2**1 = 2 + 1 = 3
                   7,   //B00000111,   //2**2 = 4 + 3 = 7
                   15,  //B00001111,  //2**3 = 8 + 7 = 15
                   31,  //B00011111, 
                   63,  //B00111111, 
                   127, //B01111111, 
                   255  //B11111111
                 };
  


void setup() {
  pinMode(data_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(save_pin,OUTPUT);  
  latch();
  pinMode(pot, INPUT);
  Serial.begin(9600);  //debug
}

void loop() {
  int leitura = analogRead(pot) ;
  int saida = map(leitura, 0, 1023, 8, 0);
  acendeBarra(valores[saida]);
  Serial.println(String(leitura) + " -> " + String(saida)); //debug
  delay(500);
}


//acende leds a partir de um inteiro que representa bits acesos ou apagados
void acendeBarra(int valor) {
    for(int pos_atual = 7; pos_atual >= 0; pos_atual--) {
      setData(bit_aceso(valor, pos_atual));
      save();
    }
    latch();
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
