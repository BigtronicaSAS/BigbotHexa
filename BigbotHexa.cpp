#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "BigbotHexa.h"


Bot::Bot(){
  pin_IR_izquierda = 3;
  pin_IR_centro = 6;
  pin_IR_derecha = 5;
  pin_echo = 8;
  pin_trigger = 7;
  pin_buzzer = 4;
  MotorA_speed = 10;
  MotorA_direction = 12;
  MotorB_speed = 11;
  MotorB_direction = 13;
  pin_rx = 1;
  pin_tx = 0;
  Serial.begin(9600);
  pinMode(pin_IR_izquierda, INPUT);
  pinMode(pin_IR_centro, INPUT);
  pinMode(pin_IR_derecha, INPUT);
  pinMode(pin_echo, INPUT);
  pinMode(pin_trigger, OUTPUT);
  pinMode(pin_buzzer, OUTPUT);
  pinMode(MotorA_direction , OUTPUT);
  pinMode(MotorA_speed , OUTPUT);
  pinMode(MotorB_speed ,OUTPUT);
  pinMode(MotorB_direction , OUTPUT);
  digitalWrite(pin_trigger, LOW);
  digitalWrite(pin_buzzer, LOW);
  BT = new SoftwareSerial(pin_rx, pin_tx);

}

bool Bot::IR_izquierda(){
  return digitalRead(pin_IR_izquierda);
}
bool Bot::IR_centro(){
  return digitalRead(pin_IR_centro);
}
bool Bot::IR_derecha(){
  return digitalRead(pin_IR_derecha);
}

void Bot::girar_derecha(int velocidad){

  digitalWrite(MotorA_direction, HIGH);
  digitalWrite(MotorB_direction, LOW);
  analogWrite(MotorA_speed, (velocidad));
  analogWrite(MotorB_speed, (velocidad));
	
}

void Bot::girar_izquierda(int velocidad){
  digitalWrite(MotorA_direction, LOW);
  digitalWrite(MotorB_direction, HIGH);
  analogWrite(MotorA_speed, (velocidad));
  analogWrite(MotorB_speed, (velocidad));
}

void Bot::adelante(int velocidad){
  digitalWrite(MotorA_direction, HIGH);
  digitalWrite(MotorB_direction, HIGH);
  analogWrite(MotorA_speed, (velocidad));
  analogWrite(MotorB_speed, (velocidad));
}

void Bot::atras(int velocidad){
  digitalWrite(MotorA_direction, LOW);
  digitalWrite(MotorB_direction, LOW);
  analogWrite(MotorA_speed, (velocidad));
  analogWrite(MotorB_speed, (velocidad));
}

void Bot::parar(){
  analogWrite(MotorA_speed, 0);
  analogWrite(MotorB_speed, 0);
}

float Bot::detectar_obstaculo(){
	digitalWrite(pin_trigger, LOW);
	delayMicroseconds(2);
	digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);
	float distancia = pulseIn(pin_echo, HIGH)*0.034/2;
	Serial.println(distancia);
	if (distancia == 0){
		Serial.println("Conecte el sensor");
	}else{
		return distancia;		
	}
	
}

void Bot::pitar(int tiempo){
	digitalWrite(pin_buzzer, HIGH);
	delay(tiempo);
	digitalWrite(pin_buzzer, LOW);
}

void Bot::servo(int angulo, int tiempo){
  attach(9);
  write(angulo);
  delay(tiempo);
}

void Bot::bluetooth(int velocidad){
int mensaje = 10;
BT->begin(9600);

	if(BT->available()){
		pitar(10);
		mensaje = BT->read();
		Serial.println(mensaje);
		if (mensaje == 49){
			adelante(velocidad);
			
		}
		if (mensaje == 48){
			atras(velocidad);
			
		}
		if (mensaje == 50){
			girar_izquierda(velocidad);
		}
		if (mensaje == 51){
			girar_derecha(velocidad);
		}
		if (mensaje == 52){
			parar();
		}
		if (mensaje == 53){
			pitar(500);
		}

	}
	}

void Bot::inicio(){
  servo(90, 1000);
  Serial.begin(9600);
}


void Bot::obstaculos(int _distance){
  delay(50);
  int distance = detectar_obstaculo();
  if(distance < _distance){
    parar();
    servo(10, 600);
    int servoReadRight = detectar_obstaculo();
    servo(170, 600);
    int servoReadLeft = detectar_obstaculo();
    servo(90, 600);
    if (servoReadLeft > servoReadRight) {
        girar_izquierda(255);
      } else {
        girar_derecha(255);
      }
  } else if (distance >= _distance) {
      adelante(255);
    }
}

void Bot::seguidor(){
  Serial.print(IR_izquierda());
  Serial.print(IR_centro());
  Serial.print(IR_derecha());
  Serial.println("");
  
if (IR_centro() == 0 and IR_derecha() == 1 and IR_izquierda()==1){
  adelante(255);
}

if (IR_izquierda() == 0){
  girar_izquierda(0);
  girar_derecha(255);
}

if (IR_derecha() == 0){
  girar_izquierda(255);
  girar_derecha(0);
}
}