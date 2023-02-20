#include <Servo.h>


#define MAX_DEGREE 180
#define MIN_DEGREE 0

#define MAX_JOYSTICK 1000
#define MIN_JOYSTICK 0

#define MAX_DELTA 1
#define MIN_DELTA -1

#ifndef A0
# define A0 0
# define A1 1
# define A2 2
# define A3 3
# define A4 4
# define A5 5
#endif

#ifndef D2
# define D2 2
# define D3 3
# define D5 5
# define D6 6
# define D7 7
# define D8 8
#endif


float clampf(float min, float value, float max) {
  if (value > max) return max;
  if (value < min) return min;
  return value;
}


float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


//#pragma pack(push, 0)
//struct WServo {
//  Servo serv;
//
//  int spd;
//  int dir;
//
//  int ap;
//  int dp;
//
//  float mod;
//  short pos;
//
//  WServo(short ini, short spd, short dir, short ap, short dp, float mod = 1) :
//    serv(Servo()), spd(spd), dir(dir), ap(ap), dp(dp), mod(mod), pos(ini)
//  {
//    Serial.println(1);
//    serv.attach(dp);
////    serv.write(ini);
//  }
//  void update(void) {
//    float input = analogRead(ap);
//    input = mapf(input, MIN_JOYSTICK, MAX_JOYSTICK, MIN_DELTA, MAX_DELTA);
//    pos = (short)clampf(MIN_DEGREE, pos + (spd * input * dir * mod), MAX_DEGREE);
//    serv.write(pos);
//  }
//};


Servo servo_base;
Servo servo_hand_0;
Servo servo_hand_1;
Servo servo_hand_2;
Servo servo_claw;

float speed = 2;
float threshold = 0.3;
float delta;

float sb_pos;
short sb_dir = -1;
float sb_mod = 1;

float sh0_pos;
short sh0_dir = -1;
float sh0_mod = 1;

float sh1_pos;
short sh1_dir = -1;
float sh1_mod = 0.7;

float sh2_pos;
short sh2_dir = -1;
float sh2_mod = 1;

float sc_pos;
short sc_dir = 1;
float sc_mod = 1;


void setup(void) {
  Serial.begin(9600);

  servo_base.attach(D2);
  servo_base.write(93);
  
  servo_hand_0.attach(D3);
  servo_hand_0.write(93);
  
  servo_hand_1.attach(D5);
  servo_hand_1.write(93);
  
  servo_hand_2.attach(D6);
  servo_hand_2.write(93);
  
  servo_claw.attach(D7);
  servo_claw.write(120);
}

#define SERV_UPDATE(serv, AP, pos, spd, dir, mod) \
  do { \
    float delta = analogRead(AP); \
    delta = clampf(MIN_JOYSTICK, delta, MAX_JOYSTICK); \
    delta = mapf(delta, MIN_JOYSTICK, MAX_JOYSTICK, MIN_DELTA, MAX_DELTA); \
    delta = round(delta * 10.0) / 10.0; \
    pos = clampf(MIN_DEGREE, pos + (spd * delta * dir * mod), MAX_DEGREE); \
    serv.write((int)pos); \
  } while(0)

void loop(void) {

  SERV_UPDATE(servo_base, A0, sb_pos, speed, sb_dir, sb_mod);
  SERV_UPDATE(servo_hand_0, A2, sh0_pos, speed, sh0_dir, sh0_mod);
  SERV_UPDATE(servo_hand_1, A2, sh1_pos, speed, sh1_dir, sh1_mod);
  SERV_UPDATE(servo_hand_2, A3, sh2_pos, speed, sh2_dir, sh2_mod);
  SERV_UPDATE(servo_claw, A1, sc_pos, speed, sc_dir, sc_mod);

  // Base
//  delta = analogRead(A0);
//  delta = clampf(MIN_JOYSTICK, delta, MAX_JOYSTICK);
//  delta = mapf(delta, MIN_JOYSTICK, MAX_JOYSTICK, MIN_DELTA, MAX_DELTA);
//  delta = round(delta * 10.0) / 10.0;
//  pos = clampf(MIN_DEGREE, pos + (speed * delta * direction * mod), MAX_DEGREE);
//  servo_base.write((int)pos);
 

//  // Hand 0
//  delta = analogRead(A2);
//  delta = mapf(delta, MIN_JOYSTICK, MAX_JOYSTICK, MIN_DELTA, MAX_DELTA);
//  hand_0_x = clampf(MIN_DEGREE, hand_0_x + (speed * delta * -direction), MAX_DEGREE);
//  servo_hand_0.write((int)hand_0_x);
//  delta = 0;
//
//  // Hand 1
//  delta = analogRead(A2);
//  delta = mapf(delta, MIN_JOYSTICK, MAX_JOYSTICK, MIN_DELTA, MAX_DELTA);
//  hand_1_x = clampf(MIN_DEGREE, hand_1_x + (speed * delta * -direction * 0.75), MAX_DEGREE);
//  servo_hand_1.write((int)hand_1_x);
//  delta = 0;
//
//
//  // Hand 2
//  delta = analogRead(A4);
//  delta = mapf(delta, MIN_JOYSTICK, MAX_JOYSTICK, MIN_DELTA, MAX_DELTA);
//  hand_1_x = clampf(MIN_DEGREE, hand_1_x + (speed * delta * -direction * 0.75), MAX_DEGREE);
//  servo_hand_1.write((int)hand_1_x);
//  delta = 0;
//
//  Serial.print("pos: ");
//  Serial.println(pos);
  
  delay(10);
}
