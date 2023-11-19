
/*-------------Motor pin  variables-----------*/

#define leftPWMPin    46                   //PWM signal pin to Motordriver
#define leftDirPin    45                   //Direction pin if LOW CW if Hight Rotates CCW
#define leftEncA      18                   //Blue wire Sensor A
#define leftEncB      19                   //Purple Wire Sensor B

#define rightPWMPin   44                   //PWM signal pin to Motordriver
#define rightDirPin   43                   //Direction pin if LOW CW if Hight Rotates CCW
#define rightEncA      3                   //Blue wire Sensor A
#define rightEncB      2                   //Purple Wire Sensor B

/*-------------PID Constants-----------*/

#define leftKp        0.23280                //left pid proportionality constant
#define leftKi        4.90759                //left pid integral constant
#define leftKd        0.0                     //left pid derivative constant


#define rightKp       0.23280                   //left pid proportionality constant
#define rightKi       4.90759                   //left pid integral constant
#define rightKd       0.0                       //left pid derivative constant


/*-------------Time variables-----------*/

#define LOOPTIME 100                            //Looptime in millisecond
const byte noCommLoopMax = 10;                  //number of main loops the robot will execute without communication before stopping
unsigned int noCommLoops = 0;                   //main loop without communication counter
unsigned long currentMillis;
unsigned long prevMillis;

/*-------------Robot-specific constants-----------*/
const double wheelDiameter = 0.195;               //Wheel radius, in m
const double wheelbase = 0.450;                   //Wheelbase, in m
const double encoderRes = 980.0;                  //Encoder ticks or counts per rotation
const double max_speed = 1.49;                    //Max speed in m/s {(2*PI*r*RPM)/60}


double velLinearReq= 0.0,  velAngularReq = 0.0;    // Desired Linear and angular Velocities of robot in m/s and rad/s
int count=0, flag = 0;
class motor
{
private:
  uint8_t _pwmPin,_dirPin, _encA,_encB;
  float Kp = 0.0,Ki = 0.0,Kd = 0.0,error = 0.0,errorIntegral = 0.0 , errorDifferential = 0.0, errorPrev =0.0,u=0.0;
  
public:
  motor(uint8_t pwmPin , uint8_t dirPin , uint8_t encA , uint8_t encB , float kp ,float ki, float kd);
  float rpmActual = 0.0 ,rpmCmd = 0.0 , pwmValue=0.0; 
  volatile long encoderPos = 0; 
  void intialize();
  void setSpeed(int Value);
  void pidCompute();
  void calActualRpm();
};

motor::motor(uint8_t pwmPin , uint8_t dirPin , uint8_t encA , uint8_t encB,float kp ,float ki, float kd)
{
  _pwmPin = pwmPin;
  _dirPin = dirPin;
  _encA = encA;
  _encB = encB;
  Kp = kp;
  Ki = ki;
  Kd = kd;
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
  // Make sure the pmm values is in limits is within the limit.
  Value = constrain(Value, -254, 254);
  if (Value >= 0) {
    analogWrite(_pwmPin, Value);
    digitalWrite(_dirPin, LOW);
  } 
  else {
    analogWrite(_pwmPin, -Value);
    digitalWrite(_dirPin, HIGH);
  }
}

void motor::pidCompute(){
  error = rpmCmd - rpmActual;
  errorIntegral = errorIntegral + error*(0.1);
  errorDifferential = (error-errorPrev)/(0.1);
  u = (Kp*error)+(Ki*errorIntegral)+(Kd*errorDifferential);
  errorPrev = error;
  pwmValue =u;
  errorIntegral = constrain(errorIntegral,-255,255);
}

void motor::calActualRpm(){
  if(abs(encoderPos)<10){
    rpmActual=0;
  }
  else{
    rpmActual = ((encoderPos/encoderRes)*(1000/LOOPTIME)*60); 
  }
  encoderPos = 0;  
}

motor motorLeft(leftPWMPin, leftDirPin, leftEncA ,leftEncB,leftKp,leftKi,leftKd);
motor motorRight(rightPWMPin,rightDirPin,rightEncA,rightEncB,rightKp,rightKi,rightKd);



void setup() {
  Serial.begin(9600);
  motorLeft.intialize();
  motorRight.intialize();

  attachInterrupt(digitalPinToInterrupt(rightEncA), rightEncoderCallback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightEncB), rightEncoderCallback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(leftEncA), leftEncoderCallback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(leftEncB), leftEncoderCallback, CHANGE);
}

void loop() {
  if (millis() - prevMillis >= LOOPTIME){
    prevMillis =millis();
    if(flag == 0){
      delay(10000);
      flag = 1;
    }
    if(count<50)
    {
     motorRight.rpmCmd = 75;
     motorLeft.rpmCmd = 75; 
    }
    else if(count<70)
    {
      motorLeft.rpmCmd = 0;
      motorRight.rpmCmd = 0; 
    }
    else if(count <120)
    {
      motorLeft.rpmCmd = -75;
      motorRight.rpmCmd = -75;
    }
    else
    {
      motorLeft.rpmCmd = 0;
      motorRight.rpmCmd = 0;
    }
    motorLeft.calActualRpm();
    motorRight.calActualRpm();
    motorLeft.pidCompute();
    motorRight.pidCompute();
    motorRight.setSpeed((int)motorRight.pwmValue);
    motorLeft.setSpeed((int)motorLeft.pwmValue);
    Serial.print(motorLeft.rpmCmd);
    Serial.print(",");
    Serial.print(motorLeft.rpmActual);
    Serial.print(",");
    Serial.print(motorRight.rpmActual);
    Serial.print(",");
    Serial.print(motorLeft.pwmValue);
    Serial.print(",");
    Serial.println(motorRight.pwmValue);
    count++;
  }
}
void leftEncoderCallback() {
  static int8_t lookup_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static uint8_t leftEncoderVal = 0;
    
  leftEncoderVal = leftEncoderVal << 2;
  leftEncoderVal = leftEncoderVal | ((PIND & 0b1100) >> 2);
 
  motorLeft.encoderPos = motorLeft.encoderPos + lookup_table[leftEncoderVal & 0b1111];
}

void rightEncoderCallback() {
  static int8_t lookup_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static uint8_t rightEncoderVal = 0;
    
  rightEncoderVal = rightEncoderVal << 2;
  rightEncoderVal = rightEncoderVal | ((PINE & B00110000) >> 4);
 
  motorRight.encoderPos = motorRight.encoderPos + lookup_table[rightEncoderVal & 0b1111];
}

  
