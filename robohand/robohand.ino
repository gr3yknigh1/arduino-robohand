#include <Servo.h>

#define MAX_DEGREE 180
#define MAX_CLAW_DEGREE 120
#define MIN_DEGREE 0

#define MAX_JOYSTICK 1000
#define MIN_JOYSTICK 0

#define MAX_DELTA 1
#define MIN_DELTA -1

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


Servo servo_base;
Servo servo_hand_0;
Servo servo_hand_1;
Servo servo_hand_2;
Servo servo_claw;

float speed = 4;
float threshold = 0.6;
float delta;

float sb_pos;
float sb_mod = -1;

float sh0_pos;
float sh0_mod = -1;

float sh1_pos;
float sh1_mod = -0.7;

float sh2_pos;
float sh2_mod = -1;

float sc_pos;
float sc_mod = 1;


void setup(void) {
  Serial.begin(9600);

  servo_base.attach(D2);
  servo_hand_0.attach(D3);
  servo_hand_1.attach(D5);
  servo_hand_2.attach(D6);
  servo_claw.attach(D7);
  
  servo_base.write(93);
  servo_hand_0.write(93);
  servo_hand_1.write(93);
  servo_hand_2.write(93);
  servo_claw.write(130); // 150 - max, 140 - mid, 120 - min
}


#define SERV_UPDATE(__servo, __analogPin, __position, __speed, __modifier, __minDegree, __maxDegree, __threshold) \
  do { \
    float delta = analogRead(__analogPin); \
    delta = clampf(MIN_JOYSTICK, delta, MAX_JOYSTICK); \
    delta = mapf(delta, MIN_JOYSTICK, MAX_JOYSTICK, MIN_DELTA, MAX_DELTA); \
    delta = round(delta * 10.0) / 10.0; \
    if (abs(delta) <= __threshold) \
      delta = 0; \
    if (delta != 0) \
      delta = delta > 0 ? 1 : -1; \
    Serial.println(delta); \
    __position = clampf(__minDegree, __position + (__speed * delta * __modifier), __maxDegree); \
    __servo.write((int)__position); \
  } while(0)


void loop(void) {
  SERV_UPDATE(servo_base, A0, sb_pos, speed, sb_mod, MIN_DEGREE, MAX_DEGREE, threshold);
  SERV_UPDATE(servo_hand_0, A2, sh0_pos, speed, sh0_mod, MIN_DEGREE, MAX_DEGREE, threshold);
  SERV_UPDATE(servo_hand_1, A2, sh1_pos, speed, sh1_mod, MIN_DEGREE, MAX_DEGREE, threshold);
  SERV_UPDATE(servo_hand_2, A3, sh2_pos, speed, sh2_mod, MIN_DEGREE, MAX_DEGREE, threshold);
  SERV_UPDATE(servo_claw, A1, sc_pos, speed, sc_mod, 120, 150, threshold);
  delay(10);
}
