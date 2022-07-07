// INCLUSÃO DE BIBLIOTECAS
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// DEFINIÇÕES
#define endereco  0x27 // Endereços comuns: 0x27, 0x3F
#define colunas   16
#define linhas    2

// INSTANCIANDO OBJETOS
LiquidCrystal_I2C lcd(endereco, colunas, linhas);


// definindo caracteres

int position = 7;


byte eye1[8] = {
0b00000,
0b01110,
0b11111,
0b11111,
0b11111,
0b11111,
0b01110,
0b00000
};

byte eye2[8] = {
0b00000,
0b01110,
0b11111,
0b11111,
0b11111,
0b10001,
0b01110,
0b00000
};

byte eye3[8] = {
0b00000,
0b01110,
0b11111,
0b11111,
0b10101,
0b10001,
0b01110,
0b00000
};

byte eye4[8] = {
0b00000,
0b01110,
0b11111,
0b10101,
0b10101,
0b10001,
0b01110,
0b00000
};


byte eye[8] = {
0b00000,
0b01110,
0b10001,
0b10101,
0b10101,
0b10001,
0b01110,
0b00000
};

byte nose[8] = {
0b00000,
0b00000,
0b00000,
0b00100,
0b00100,
0b00100,
0b00000,
0b00000
};

byte mouth[8] = {
0b00000,
0b00000,
0b00000,
0b00000,
0b10001,
0b01110,
0b00000,
0b00000
};

//definindo constantes
const int MIN_POSITION = 0;
const int MAX_POSITION = 13;
const float MAX_BRIGHT = 800;

void createChar(){
lcd.createChar(0, eye);
lcd.createChar(1, nose);
lcd.createChar(2, mouth);
lcd.createChar(3, eye1);
lcd.createChar(4, eye2);
lcd.createChar(5, eye3);
lcd.createChar(6, eye4);
}

void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    createChar();
    lcd.setCursor(3,0);
    lcd.print("Hello World!");
    delay(1000);
    lcd.clear();
    lcd.print("Hora de levantar!");
    delay(1000);
    lcd.setCursor(position,0);
    blinkEye(position);
}


bool LeftIsBright(int left_eye, int right_eye){
if(left_eye > right_eye)
return true;
else
return false;
}
bool RightIsBright(int left_eye, int right_eye){
if(right_eye > left_eye)
return true;
else
return false;
}
bool isBright(int left_eye, int right_eye){
if (left_eye > 500 and right_eye > 500){
return true;
}
else
return false;
}

float calBrightPerCent(int Bright)
{
float res;
res = Bright / MAX_BRIGHT;
Serial.println(res*10-8);
return (res*10)-8.5;
}

int goToLeft(int position, int left_bright){

if(position > (MIN_POSITION - calBrightPerCent(left_bright)) ){
position--;
return position;
}
else
return position;
}
int goToRight(int position, int right_bright){
if(position < (MAX_POSITION + calBrightPerCent(right_bright)) ){
position++;
return position;
}
else
return position;
}



void renderFace(int position){
lcd.clear();
lcd.setCursor(position,0);
lcd.write((uint8_t)0);
lcd.write((uint8_t)1);
lcd.write((uint8_t)0);
lcd.setCursor(position + 1,1);
lcd.write((uint8_t)2);
}


void renderEye(int position) {
delay(500);
lcd.clear();
lcd.setCursor(position,0);
lcd.write((uint8_t)3);
lcd.write((uint8_t)1);
lcd.write((uint8_t)3);
lcd.setCursor(position + 1,1);
lcd.write((uint8_t)2);

delay(200);

lcd.clear();
lcd.setCursor(position,0);

lcd.write((uint8_t)4);
lcd.write((uint8_t)1);
lcd.write((uint8_t)4);
lcd.setCursor(position + 1,1);
lcd.write((uint8_t)2);

delay(200);

lcd.clear();
lcd.setCursor(position,0);

lcd.write((uint8_t)5);
lcd.write((uint8_t)1);
lcd.write((uint8_t)5);
lcd.setCursor(position + 1,1);
lcd.write((uint8_t)2);

delay(200);

lcd.clear();
lcd.setCursor(position,0);

lcd.write((uint8_t)6);
lcd.write((uint8_t)1);
lcd.write((uint8_t)6);
lcd.setCursor(position + 1,1);
lcd.write((uint8_t)2);
}

void renderCloseEye(){
lcd.clear();
lcd.setCursor(7,0);
lcd.print(">-<");
}

void blinkEye(int position){
lcd.clear();
delay(100);
lcd.setCursor(position,0);
renderEye(position);

}

void loop() {
int left_eye = analogRead(A0);
int right_eye = analogRead(A1);
if(LeftIsBright(left_eye,right_eye))
{
position = goToLeft(position,left_eye);
renderFace(position);

}
else if(RightIsBright(left_eye,right_eye)){
position = goToRight(position,right_eye);
renderFace(position);


}else if(isBright(left_eye,right_eye)){
renderCloseEye();
}
else{
if(position < 7)
renderFace(position ++);
else if(position > 7)
renderFace(position --);
else
renderFace(position);
}
delay(1000);
}
