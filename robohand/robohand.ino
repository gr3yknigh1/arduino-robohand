#include <Servo.h>


#define MAX_DEGREE 180
#define MAX_CLAW_DEGREE 120
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

g
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

bool sc_is_open = false;


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
  servo_claw.write(130); // 150 - max, 140 - mid, 120 - min
}


#define SERV_UPDATE(serv, AP, pos, spd, dir, mod, min_degree, max_degree) \
  do { \
    float delta = analogRead(AP); \
    delta = clampf(MIN_JOYSTICK, delta, MAX_JOYSTICK); \
    delta = mapf(delta, MIN_JOYSTICK, MAX_JOYSTICK, MIN_DELTA, MAX_DELTA); \
    delta = round(delta * 10.0) / 10.0; \
    pos = clampf(min_degree, pos + (spd * delta * dir * mod), max_degree); \
    serv.write((int)pos); \
  } while(0)


void loop(void) {
  SERV_UPDATE(servo_base, A0, sb_pos, speed, sb_dir, sb_mod, MIN_DEGREE, MAX_DEGREE);
  SERV_UPDATE(servo_hand_0, A2, sh0_pos, speed, sh0_dir, sh0_mod, MIN_DEGREE, MAX_DEGREE);
  SERV_UPDATE(servo_hand_1, A2, sh1_pos, speed, sh1_dir, sh1_mod, MIN_DEGREE, MAX_DEGREE);
  SERV_UPDATE(servo_hand_2, A3, sh2_pos, speed, sh2_dir, sh2_mod, MIN_DEGREE, MAX_DEGREE);
  SERV_UPDATE(servo_claw, A1, sc_pos, speed, sc_dir, sc_mod, MIN_DEGREE, MAX_DEGREE);
  delay(10);
}
