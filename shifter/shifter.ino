//Shifter
//Teste de shift register (74HC595 ou 595)
//Licenca: Apache 2.0 (use como quiser)
//http://www.apache.org/licenses/LICENSE-2.0.html
//Copyright 2014 Otavio Carneiro (carneiro.blog.br)

const int data_pin = 2; //DS (pino 14 no 595)    - ligado com um resistor de 300R
const int latch_pin = 3; //STCP (pino 12 no 595) - ligado com um resistor de 300R
const int save_pin = 4; //SHCP (pino 11 no 595)  - ligado diretamente
//o pino 13 (OE - pause) foi ligado ao GND diretamente
//o pino 10 (MR - Nreset) foi ligado ao VCC com um resistor de 1k

void setup() {
  pinMode(data_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(save_pin,OUTPUT);  
  latch();
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

void loop() {  
  setData(HIGH);
  save();
  save();
  save();
  save();
//  delay(10);
  latch();
  delay(1000);
  setData(LOW);
  save();
  save();
  save();
  save();
//  delay(10);
  latch();
  delay(1000);  
} 
