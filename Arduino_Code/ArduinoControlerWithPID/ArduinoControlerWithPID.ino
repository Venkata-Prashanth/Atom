#include <ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/Twist.h>

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


#define rightKp       0.23280                   //right pid proportionality constant
#define rightKi       4.90759                   //right pid integral constant
#define rightKd       0.0                       //right pid derivative constant

/*-------------Time variables-----------*/

#define LoopTime  100                          //Looptime in millisecond
const byte noCommLoopMax = 30;                    //number of main loops the robot will execute without communication before stopping
unsigned int noCommLoops = 0;                     //main loop without communication counter
unsigned long currentMillis = 0.0;
unsigned long prevMillis = 0.0;

/*-------------Robot-specific constants-----------*/
const double wheelDiameter = 0.195;               //Wheel radius, in m
const double wheelbase = 0.267;                   //Wheelbase, in m
const double encoderRes = 980.0;                  //Encoder ticks or counts per rotation
const double max_speed = 1.49;                    //Max speed in m/s {(2*PI*r*RPM)/60}
const float Pi = 3.141593;

double velLinearReq = 0.0,  velAngularReq = 0.0;    // Desired Linear and angular Velocities of robot in m/s and rad/s

class motor
{
private:
  uint8_t _pwmPin,_dirPin, _encA,_encB;
  double Kp = 0.0,Ki = 0.0,Kd = 0.0,error = 0.0,errorIntegral = 0.0 , errorDifferential = 0.0, errorPrev =0.0;
public:
  motor(uint8_t pwmPin , uint8_t dirPin, uint8_t encA , uint8_t encB, double kp ,double ki, double kd);
  double rpmActual = 0.0, speedActual = 0.0 ,rpmCmd = 0.0 , pwmValue=0.0; 
  volatile long encoderPos = 0; 
  void intialize();
  void setSpeed(int Value);
  void pidCompute();
  void calActualRpm();
};
motor::motor(uint8_t pwmPin , uint8_t dirPin , uint8_t encA , uint8_t encB, double kp ,double ki, double kd)
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
  pwmValue = (Kp*error)+(Ki*errorIntegral)+(Kd*errorDifferential);
  errorPrev = error;
  errorIntegral = constrain(errorIntegral ,-255,255);
}
void motor::calActualRpm(){
  rpmActual = ((encoderPos/encoderRes)*(1000/LoopTime)*60);
  speedActual = (rpmActual*Pi*wheelDiameter)/60;
  encoderPos = 0;  
}
motor motorLeft(leftPWMPin, leftDirPin, leftEncA ,leftEncB,leftKp,leftKi,leftKd);
motor motorRight(rightPWMPin,rightDirPin,rightEncA,rightEncB,rightKp,rightKi,rightKd);


ros::NodeHandle nh;

//Callback function for Subscribed cmd_vel topic from ROS
void cmd_vel_callback( const geometry_msgs::Twist& cmd_vel){ 
  noCommLoops = 0;                                                    
  velLinearReq = cmd_vel.linear.x;                                     
  velAngularReq = cmd_vel.angular.z;
  motorLeft.rpmCmd = ((velLinearReq + (velAngularReq*(wheelbase/2)))*60)/(Pi*wheelDiameter);
  motorRight.rpmCmd= ((velLinearReq - (velAngularReq*(wheelbase/2)))*60)/(Pi*wheelDiameter);
}
ros::Subscriber<geometry_msgs::Twist> cmd_vel("cmd_vel", cmd_vel_callback); //create a subscriber to ROS topic for cmd_vel commands (will execute "cmd_vel_callback" function when receiving data)
geometry_msgs::Vector3Stamped speed_msg;                                //create a "speed_msg" ROS message
ros::Publisher speed_pub("speed", &speed_msg);                          //create a publisher to ROS topic "speed" using the "speed_msg" type

void setup() {
  nh.initNode();                              //init ROS node
  nh.getHardware()->setBaud(57600);           //set baud for ROS serial communication
  nh.subscribe(cmd_vel);                      //suscribe to ROS topic for velocity commands
  nh.advertise(speed_pub);                    // publish speed in ROS topic
  motorLeft.intialize();
  motorRight.intialize();
  attachInterrupt(digitalPinToInterrupt(rightEncA), rightEncoderCallback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightEncB), rightEncoderCallback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(leftEncA), leftEncoderCallback, CHANGE);
  attachInterrupt(digitalPinToInterrupt(leftEncB), leftEncoderCallback, CHANGE);
}

void loop() {
  nh.spinOnce();
  if((millis()-prevMillis) >= LoopTime)   
  {                                                                           // enter timed loop
    prevMillis = millis();
    motorLeft.calActualRpm();
    motorRight.calActualRpm();
    motorRight.pidCompute();
    motorLeft.pidCompute();
    if (noCommLoops >= noCommLoopMax) {
      motorLeft.setSpeed(0);
      motorRight.setSpeed(0);
    }
    else {
      motorLeft.setSpeed((int)motorLeft.pwmValue);
      motorRight.setSpeed((int)motorRight.pwmValue);
    }
    noCommLoops++;
    if (noCommLoops == 65535){
      noCommLoops = noCommLoopMax;
    }
    publishSpeed(LoopTime);   //Publish odometry on ROS topic
  }
}

//Publish function for odometry, uses a vector type message to send the data (message type is not meant for that but that's easier than creating a specific message type)
void publishSpeed(double time) {
  speed_msg.header.stamp = nh.now();              //timestamp for odometry data
  speed_msg.vector.x = motorLeft.speedActual;     //left wheel speed (in m/s)
  speed_msg.vector.y = motorRight.speedActual;    //right wheel speed (in m/s)
  speed_msg.vector.z = time/1000;                 //looptime, should be the same as specified in LOOPTIME (in s)
  speed_pub.publish(&speed_msg);
  nh.spinOnce();
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
  
  
