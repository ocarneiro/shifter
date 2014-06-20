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

const int intervalo = 2;

String linha0 = "111110000000111111100000000000111100000000001111111110001111100001111000000000";
String linha1 = "110001100000111001110000000001111110000000011111111000001111100001111000000000";
String linha2 = "110001100000111001110000000011100111000000111000000000001111100001111000000000";
String linha3 = "111110000000111111100000000111000011100000011111000000001111100001111000000000";
String linha4 = "110001100000111011111000000111111111110000000001111000001111100001111000000000";
String linha5 = "110000110000111000111100000111000001110000000000111100001111100001111000000000";
String linha6 = "110000110000111000011100000111000001110000011111111100001111100001111111111111";
String linha7 = "111111100000111000001110001111000001111000011111111000001111100001111111111111";

void setup() {
  pinMode(data_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(save_pin,OUTPUT);  
  latch();
  
  pinMode(buzzer,OUTPUT);
//  Serial.begin(9600);
 
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);  
  
}

void enviaColuna(String coluna) {
  for (int pos = 0; pos < coluna.length(); pos++) {
    int valor = coluna.charAt(pos) - '0';
    save(valor);
  }
}

void loop() {
//  avisaQueVai();
/*
  tone(buzzer,550);
  delay(100);
  noTone(buzzer);
  delay(150);
*/
  vai();
/*  
  tone(buzzer,250);
  delay(100);
  noTone(buzzer);
  delay(150);
  
  volta();
*/
}

void avisaQueVai() {  
  tone(buzzer,600);
  delay(20);
  noTone(buzzer);
  delay(100);
  tone(buzzer,600);
  delay(20);
  noTone(buzzer);
  delay(100);
  tone(buzzer,600);
  delay(20);
  noTone(buzzer);
  delay(100);
}

void vai() {
  for (int pos = 0; pos < linha1.length(); pos++) {
    String coluna = "" + String(linha0.charAt(pos));
    coluna += String(linha1.charAt(pos));
    coluna += String(linha2.charAt(pos));
    coluna += String(linha3.charAt(pos));
    coluna += String(linha4.charAt(pos));
    coluna += String(linha5.charAt(pos));
    coluna += String(linha6.charAt(pos));
    coluna += String(linha7.charAt(pos));
    enviaColuna(coluna);
    latch();
//    Serial.println(coluna);
    delay(intervalo);
    
    if (pos == linha1.length()/2) {
        noTone(buzzer);
    }
  }
  
//  tone(buzzer,250);
} 

void volta() {
  for (int pos = linha1.length(); pos > 0;  pos--) {
    String coluna = "" + String(linha0.charAt(pos));
    coluna += String(linha1.charAt(pos));
    coluna += String(linha2.charAt(pos));
    coluna += String(linha3.charAt(pos));
    coluna += String(linha4.charAt(pos));
    coluna += String(linha5.charAt(pos));
    coluna += String(linha6.charAt(pos));
    coluna += String(linha7.charAt(pos));
    enviaColuna(coluna);
    latch();
//    Serial.println(coluna);
    delay(intervalo);
    
    if (pos == linha1.length()/2) {
        noTone(buzzer);
    }
  }  
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

