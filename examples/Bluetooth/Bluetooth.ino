#include <BigbotHexa.h>

Bot bot;
int velocidad = 255;
void setup() {
  Serial.begin(9600);

}

void loop() {
//recibir instrucciones por bluetooth
  bot.bluetooth(velocidad);
}
