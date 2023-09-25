

#include <BigbotHexa.h>


Bot bot;
int delayMillis = 1000;

void setup() {
Serial.begin(9600);
}

void loop() {

  for (int angulo = 0; angulo <= 180; angulo += 10) {
    bot.servo(angulo, delayMillis);
  }
}                         

 