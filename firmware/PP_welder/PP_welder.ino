#include "max6675.h"

int SOpin = 5; //пины подключения термопары
int CSpin = 4;
int SCKpin = 3;

MAX6675 thermocouple(SCKpin, CSpin, SOpin);

int vccPin = 2;  //пин для питания датчика
int relayPin = 6; //пин реле
boolean flag = 1; //флажок для запоминания положения реле

int max_temp = 450; //максимальная температура
int min_temp = 400; //минимальная температура


void setup() {
  Serial.begin(9600);
  pinMode(vccPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(vccPin, HIGH); //дать питание на датчик
  digitalWrite(relayPin, HIGH); //дать питание на реле (реле - обратное, при включении надо подать на него высокий сигнал)

  delay(500); //ждем стабилизации чипа MAX
}

void loop() {
  float temp = thermocouple.readCelsius();  //получить температуру с датчика, в градусах Цельсия
  Serial.print("Temperature = ");
  Serial.println(temp);

  if (temp < max_temp && flag == 1) { //если температура ниже max
    digitalWrite(relayPin, LOW);  //включить нагреватель
  }

  if (temp > max_temp && flag == 1) { //если температура превысила max
    digitalWrite(relayPin, HIGH);  //выключить нагреватель
    flag = 0;
  }

  if (temp < min_temp && flag == 0) { //если температура ниже min
    flag = 1;
  }

  delay(300); //задержка измерения
}
