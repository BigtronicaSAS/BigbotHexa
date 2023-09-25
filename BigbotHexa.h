/*
  BigBotHexa.h - Librería para controlar la plataforma BigBot.
  Creado por Bigtronica en 2023 por Juan Camilo Alvarez .
*/
#ifndef BigbotHexa_h
#define BigbotHexa_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

class Bot : public Servo {
  public:
    Bot();
    bool IR_izquierda();
    bool IR_centro();
    bool IR_derecha();
	void adelante(int velocidad);
	void atras(int velocidad);
	void girar_derecha(int velocidad);
	void girar_izquierda(int velocidad);
	void parar();
	float detectar_obstaculo();
	void pitar(int tiempo);
	void servo(int angulo, int tiempo);
	void inicio();
	void seguidor();
	void obstaculos(int _distance);
	void bluetooth(int velocidad);
  private:
	int pin_IR_izquierda;
	int pin_IR_centro;
	int pin_IR_derecha;
	int MotorA_speed;
    int MotorA_direction;
    int MotorB_speed;
    int MotorB_direction;
	int pin_echo;
	int pin_trigger;
	int pin_buzzer;
	int pin_rx;
	int pin_tx;
	bool bandera_inicializar;
	SoftwareSerial *BT;
	  
};

#endif