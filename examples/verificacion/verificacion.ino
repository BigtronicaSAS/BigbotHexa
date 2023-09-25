#include <BigbotHexa.h>

Bot bot;
void setup() {

}

void loop() {
  bot.adelante(255);  //la plataforma debe avanzar durante un segundo
  delay(1000);
  bot.parar();        //la plataforma debe parar por un segundo
  delay(1000);
  bot.atras(255);     //la plataforma debe retroceder por un segundo
  delay(1000);
  bot.parar();        //la plataforma debe parar por un segundo
  delay(1000);
  bot.girar_derecha(255);  //la plataforma debe girar a la derecha
  delay(1000);
  bot.girar_izquierda(255);  //la plataforma debe girar a la izquierda
  delay(1000);

  //la plataforma debe avanzar hasta que encuentre un obstáculo, luego pitar y girar a la derecha
  while (bot.detectar_obstaculo()>10){
    bot.adelante(255);
  }
  bot.parar();
  bot.pitar(1000);
  bot.girar_derecha(255);
  delay(500);

}
