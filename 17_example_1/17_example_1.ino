#include <Servo.h>

// Arduino pin assignment

#define PIN_POTENTIOMETER 0 // Potentiometer at Pin A3
// Add IR Sensor Definition Here !!!
#define PIN_SERVO 10
#define PIN_LED 9

#define _DUTY_MIN 553  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1476 // servo neutral position (90 degree)
#define _DUTY_MAX 2399 // servo full counter-clockwise position (180 degree)

#define _DIST_MIN 100.0
#define _DIST_MAX 250.0
#define LOOP_INTERVAL 50   // Loop Interval (unit: msec)

#define _EMA_ALPHA 0.5
Servo myservo;
unsigned long last_loop_time;   // unit: msec
float dist_ema, dist_prev = 0;
void setup()
{
  pinMode(PIN_LED, OUTPUT);
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  dist_prev = _DIST_MIN;
  Serial.begin(57600);
}

void loop()
{
  unsigned long time_curr = millis();
  int a_value;
  float dist_raw,duty;
  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  // Remove Next line !!!
  a_value = analogRead(PIN_POTENTIOMETER);
  // Read IR Sensor value !!!
  // Convert IR sensor value into distance !!!
  // we need distance range filter here !!!
  // we need EMA filter here !!!

  // map distance into duty
  dist_raw = (6762.0/(a_value-9)-4.0)*10.0;
  if (dist_raw < _DIST_MIN){
    dist_raw = dist_prev;
    dist_ema = dist_raw * _EMA_ALPHA + dist_ema * (1-_EMA_ALPHA);
    duty = _DUTY_MIN + (float)(_DUTY_MAX - _DUTY_MIN) /(float)(_DIST_MAX - _DIST_MIN) * (dist_ema - _DIST_MIN);
    myservo.writeMicroseconds(duty);
    digitalWrite(PIN_LED, 1);
  } else if (dist_raw > _DIST_MAX){
    dist_raw = dist_prev;
    dist_ema = dist_raw * _EMA_ALPHA + dist_ema * (1-_EMA_ALPHA);
    duty = _DUTY_MIN + (float)(_DUTY_MAX - _DUTY_MIN) /(float)(_DIST_MAX - _DIST_MIN) * (dist_ema - _DIST_MIN);
    myservo.writeMicroseconds(duty);
    digitalWrite(PIN_LED, 1);
  } else{
    dist_prev = dist_raw;
    dist_ema = dist_raw * _EMA_ALPHA + dist_ema * (1-_EMA_ALPHA);
    duty = _DUTY_MIN + (float)(_DUTY_MAX - _DUTY_MIN) /(float)(_DIST_MAX - _DIST_MIN) * (dist_ema - _DIST_MIN);    
    myservo.writeMicroseconds(duty);
    digitalWrite(PIN_LED, 0);
  }
  // myservo.writeMicroseconds(duty);

  // print IR sensor value, distnace, duty !!!
  Serial.print("Min:"); Serial.print(_DIST_MIN);
  Serial.print(",IR:"); Serial.print(a_value);
  Serial.print(",dist:"); Serial.print(dist_raw);
  Serial.print(",ema:");  Serial.print(dist_ema);
  Serial.print(",servo:");  Serial.print(duty);
  Serial.print(",MAX:");  Serial.print(_DIST_MAX);
  Serial.println("");
}
