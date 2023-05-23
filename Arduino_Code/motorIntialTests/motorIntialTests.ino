/*-------------Motor pin  variables-----------*/

#define leftPWMPin    46                   //PWM signal pin to Motordriver
#define leftDirPin    45                   //Direction pin if LOW CW if Hight Rotates CCW
#define leftEncA      18                   //Blue wire Sensor A
#define leftEncB      19                   //Purple Wire Sensor B

#define rightPWMPin   44                   //PWM signal pin to Motordriver
#define rightDirPin   43                   //Direction pin if LOW CW if Hight Rotates CCW
#define rightEncA      3                   //Blue wire Sensor A
#define rightEncB      2                   //Purple Wire Sensor B

/*-------------Robot-specific constants-----------*/
const double wheelDiameter = 0.195;               //Wheel radius, in m
const double wheelbase = 0.450;                   //Wheelbase, in m when connected with Carriage "0.450", Only Pioneer robot "0.267"
const double encoderRes = 980.0;                  //Encoder ticks or counts per rotation
const double max_speed = 1.49;                    //Max speed in m/s {(2*PI*r*RPM)/60}

/*-------------Time variables-----------*/

#define LOOPTIME 100                            //Looptime in millisecond
const byte noCommLoopMax = 10;                  //number of main loops the robot will execute without communication before stopping
unsigned int noCommLoops = 0;                   //main loop without communication counter
unsigned long currentMillis;
unsigned long prevMillis;
int count = 0 , pwmRamp = 0;
class motor
{
private:
  uint8_t _pwmPin,_dirPin, _encA,_encB; 
public:
  motor(uint8_t pwmPin , uint8_t dirPin , uint8_t encA , uint8_t encB);
  float rpmActual = 0.0, pwmValue=0.0; 
  volatile long encoderPos = 0; 
  void intialize();
  void setSpeed(int Value);
  void calActualRpm();
}; 

motor::motor(uint8_t pwmPin , uint8_t dirPin , uint8_t encA , uint8_t encB)
{
  _pwmPin = pwmPin;
  _dirPin = dirPin;
  _encA = encA;
  _encB = encB;
}

void motor::intialize(){
  //Intialising Pins 
  pinMode(_pwmPin, OUTPUT);
  pinMode(_dirPin,OUTPUT);
  pinMode(_encA,INPUT_PULLUP);
  pinMode(_encB,INPUT_PULLUP);

  //Setting all output pins to low
  digitalWrite(_pwmPin,LOW);
  digitalWrite(_dirPin,LOW);
}

void motor::setSpeed(int Value){
  Value = constrain(Value, -245, 254);              // Make sure the pmm values is in limits
  if (Value >= 0) {
    analogWrite(_pwmPin, Value);
    digitalWrite(_dirPin, LOW);
  } 
  else {
    analogWrite(_pwmPin, -Value);
    digitalWrite(_dirPin, HIGH);
  }
}

void motor::calActualRpm(){
  if(abs(encoderPos)<10){                           //to stop reacting if there is only small movement.
    rpmActual=0;
  }
  else{
    rpmActual = ((encoderPos/encoderRes)*(1000/LOOPTIME)*60); 
  }
  encoderPos = 0;  
}


motor motorLeft(leftPWMPin, leftDirPin, leftEncA ,leftEncB);
motor motorRight(rightPWMPin,rightDirPin,rightEncA,rightEncB);


void setup() {
  Serial.begin(57600);
  motorLeft.intialize();
  motorRight.intialize();
  attachInterrupt(digitalPinToInterrupt(rightEncA), rightEncoderACallback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightEncB), rightEncoderBCallback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(leftEncA), leftEncoderACallback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(leftEncB), leftEncoderBCallback, CHANGE);
}

void loop() {
    //Uncomment and Comment required function 
    //displayEncoderCounts();   //
    displayRPM();
}

//Function to print number of Encoder counts
//Rotate the wheel by hand to check whether encoder count
void displayEncoderCounts(){  
    Serial.print("Right Encoder: ");                        
    Serial.print(motorRight.encoderPos);
    Serial.print(",");
    Serial.print("Left Encoder: ");
    Serial.println(motorLeft.encoderPos); 
}

//Function to print rpm of the motors for specific PWM value and LOOPTIME
//Set a PWM to make the motor rotate 
void displayRPM(){
  if (millis() - prevMillis >= LOOPTIME){
    prevMillis =millis();
    if (count >=20){
      if (pwmRamp == 255 || pwmRamp == -255){
        pwmRamp = -pwmRamp;
      }
      else{
        pwmRamp += 5;
      }
      count = 0;
    }
  motorLeft.setSpeed(pwmRamp);
  motorRight.setSpeed(pwmRamp);
  motorLeft.calActualRpm();
  motorRight.calActualRpm();
  motorLeft.encoderPos= 0;
  motorRight.encoderPos= 0;
  count++;
  Serial.print("Right Motor RPM: ");                        
  Serial.print(motorRight.rpmActual);
  Serial.print(",");
  Serial.print("Left Motor RPM: ");
  Serial.println(motorLeft.rpmActual);
  }
}

//Encoder Interrupt Service routines(Interrupt call back Functions)

/*-------------Left Encoder---------------*/
void leftEncoderACallback(){  
  // look for a low-to-high on channel A
  if (digitalRead(leftEncA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(leftEncB) == LOW) {  
      motorLeft.encoderPos += 1;         // CW
    } 
    else {
      motorLeft.encoderPos -= 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(leftEncB) == HIGH) {   
      motorLeft.encoderPos += 1;          // CW
    } 
    else {
      motorLeft.encoderPos -= 1;          // CCW
    }
  }
}

void leftEncoderBCallback(){  
  // look for a low-to-high on channel B
  if (digitalRead(leftEncB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(leftEncA) == HIGH) {  
      motorLeft.encoderPos += 1;         // CW
    } 
    else {
      motorLeft.encoderPos -= 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(leftEncA) == LOW) {   
      motorLeft.encoderPos += 1;          // CW
    } 
    else {
      motorLeft.encoderPos -= 1;          // CCW
    }
  }
}

/*-------------Right Encoder---------------*/

void rightEncoderACallback(){  
  // look for a low-to-high on channel A
  if (digitalRead(rightEncA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(rightEncB) == LOW) {  
      motorRight.encoderPos -= 1;         // CW
    } 
    else {
      motorRight.encoderPos += 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(rightEncB) == HIGH) {   
      motorRight.encoderPos -= 1;          // CW
    } 
    else {
      motorRight.encoderPos += 1;          // CCW
    }
  }
}

void rightEncoderBCallback(){  
  // look for a low-to-high on channel B
  if (digitalRead(rightEncB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(rightEncA) == HIGH) {  
      motorRight.encoderPos -=  1;         // CW
    } 
    else {
      motorRight.encoderPos +=  1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(rightEncA) == LOW) {   
      motorRight.encoderPos -= 1;          // CW
    } 
    else {
      motorRight.encoderPos += 1;          // CCW
    }
  }
}
