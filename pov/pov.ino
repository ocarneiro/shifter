//POV
//Para uso com um shift register (74HC595 ou 595)
//Licenca: Apache 2.0 (use como quiser)
//http://www.apache.org/licenses/LICENSE-2.0.html
//Copyright 2014 Otavio Carneiro (carneiro.blog.br)

const int data_pin = 2; //DS (pino 14 no 595)    - ligado com um resistor de 300R
const int latch_pin = 3; //STCP (pino 12 no 595) - ligado com um resistor de 300R
const int save_pin = 4; //SHCP (pino 11 no 595)  - ligado diretamente
//o pino 13 (OE - pause) foi ligado ao GND diretamente
//o pino 10 (MR - Nreset) foi ligado ao VCC com um resistor de 1k
const int buzzer = 11; //buzzer ligado a um resistor de 300R

String linha0 = "00001111000111000000100000000";
String linha1 = "00001000100100100001010000000";
String linha2 = "00001000100100100010001000000";
String linha3 = "00001111000111000010001000000";
String linha4 = "00001000100100100011111000000";
String linha5 = "00001000010100-10010001000000";
String linha6 = "00001000010100010010001000000";
String linha7 = "00001111100100011010001000000";

String linhaTeste1 = "11100011";
String linhaTeste2 = "00011100";
String linhaTeste3 = "10100011";

void setup() {
  pinMode(data_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(save_pin,OUTPUT);  
  latch();
  
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  
}

void enviaLinha(String linha) {
  for (int pos = 0; pos < linha.length(); pos++) {
    int valor = linha.charAt(pos) - '0';
    save(valor);
  }
}

void loop() {
  enviaLinha(linhaTeste1);
  latch();
  delay(1000);
  enviaLinha(linhaTeste2);
  latch();
  delay(1000);
  enviaLinha(linhaTeste3);
  latch();
  delay(1000);  
/*  
  delay(1000);
  Serial.println("De novo...");
  delay(1000);
*/  
/*  
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
*/
} 

//envia um valor no pino data
void setData(int value) {
  digitalWrite(data_pin, value);
}

//salva um valor especificado no 595
void save(int valor) {
  setData(valor);
  save();
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

void buzz() {
  tone(buzzer,1500);
  tone(buzzer,500);
  noTone(buzzer);
}
