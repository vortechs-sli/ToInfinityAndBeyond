
// Calling the lieberries
#include <IRremote.h>
#include <IRremoteInt.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Motor on port M1: right side of bridge
Adafruit_DCMotor *bridgeMotor1 = AFMS.getMotor(1);
// Motor on port M2: left side of bridge
Adafruit_DCMotor *bridgeMotor2 = AFMS.getMotor(1);

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
bool pressTwo = false;
int motor1 = 0;
int motor2 = 0;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  
  AFMS.begin();  // create with the default frequency 1.6KHz

  // Starting the motors:  

  // Set the speed to start, from 0 (off) to 255 (max speed)
  bridgeMotor1->setSpeed(100);
  bridgeMotor1->run(FORWARD);
  // turn on motor   
  bridgeMotor1->run(RELEASE);

  // Set the speed to start, from 0 (off) to 255 (max speed)
  bridgeMotor2->setSpeed(100);
  bridgeMotor2->run(FORWARD);
  // turn on motor
  bridgeMotor2->run(RELEASE);
}

void loop() {
  
  if (irrecv.decode(&results)) 
  {
    switch(results.value){

// Lowering bridge
      case 0xFF18E7:
        motor1 = 1;
        motor2 = 1;
        Serial.println("received 2");
        break;

// Raising bridge
      case 0xFF4AB5:
        motor1 = -1;
        motor2 = -1;
        Serial.println("received 8");
        break;

// Stop bridge movement
    case 0xFF38C7:
    motor1 = 0;
    motor2 = 0;
    Serial.println("received 5");
    break;
    
    irrecv.resume();


  

 
  } 
  
  } else {
    // no output
    motor1 = 0;
    motor2 = 0;
  }

  // MOTOR 1
  if (motor1 == 1)
  {
    bridgeMotor1->run(FORWARD);
  }

  else if (motor1 == 0)
  {
    bridgeMotor1->run(RELEASE);
  }

  else if (motor1 == -1)
  {
   bridgeMotor1->run(BACKWARD); 
  }
  delay (150);


  // MOTOR 2
  if (motor2 == 1)
  {
    bridgeMotor2->run(FORWARD);
  }

  else if (motor2 == 0)
  {
    bridgeMotor2->run(RELEASE);
  }

  else if (motor2 == -1)
  { 
    bridgeMotor2->run(BACKWARD);
  }
  delay (150);

}
