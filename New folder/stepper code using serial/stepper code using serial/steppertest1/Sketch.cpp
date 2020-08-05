/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include <Stepper.h>
#include <SoftwareSerial.h>
//Beginning of Auto generated function prototypes by Atmel Studio
ISR(TIMMER1_COMPA_vect );
//End of Auto generated function prototypes by Atmel Studio


// change this to the number of steps on your motor
#define STEPS 100
SoftwareSerial mySerial(0, 1);
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper1(STEPS, 2, 3, 4, 5);
Stepper stepper2(STEPS, 6, 7, 8, 9);
Stepper stepper3(STEPS, 10, 11, 12, 44);

int previous1 = 0;
int previous2 = 0;
int previous3 = 0;
ISR(TIMMER1_COMPA_vect)
{ //semding back the angle read by adc port 
  Serial.write(analogRead(A0));
  Serial.write(analogRead(A1));
  Serial.write(analogRead(A2));
  //Serial.write(String(analogRead(A1)), DEC);
  //Serial.write(String(analogRead(A2)), DEC);
 }
void setup() {
 
  sei();
  TCCR1A=0;
  TCCR1B=0;
  TCNT1=0;
  OCR1A=46874;            //12MHZ/(PRESCALER*4HZ)
  TCCR1B |=(1<<WGM12);     //CTC MODE
  TCCR1B |=(1<<CS11) | (1<<CS10); //SET PRESCALER TO 64
  TIMSK1 |=(1<<OCIE1A);      //ENABLLE INTERPT
  Serial.begin(9600);
   // set the speed of the motor to 4 RPMs
  stepper1.setSpeed(4);
  stepper2.setSpeed(4);
  stepper3.setSpeed(4);
  sei();
}

String a="000000000";//initially set all motors to 0 degree
void loop() 
{ 
  if (Serial.available())
  { a = Serial.readString(); 
  }
    String x=a.substring(0,2);
    String y=a.substring(3,5);
    String z=a.substring(6,8); 
  int d1,d2,d3;  
  d1=(x.toInt())*(STEPS/360);
  d2=(y.toInt())*(STEPS/360);
  d3=(z.toInt())*(STEPS/360);
 
  stepper1.step(d1 - previous1);
  stepper2.step(d2 - previous2);
  stepper3.step(d3 - previous3);

  previous1 =d1;
  previous2 =d2;
  previous3 =d3;
}
