#include <Servo.h>
#define midRange 115

Servo rudder;
Servo prop_l;
Servo prop_r;

void blink() { // blinks onboard LED
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
}

void wait() { // waits until potentiometer crosses midpoint. WARNING: may need to adjust values depending on pot. resistance and connected pins
  if (analogRead(A2) > 500) {
    while (analogRead(A2) > 500) {}
  } else {
    while (analogRead(A2) < 500) {}
  }

  blink();
}

void setup() {
  // for blink()
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);

  rudder.attach(3); // rudder signal is pin 3
  prop_l.attach(5); // left propeller signal is pin 5
  prop_r.attach(9); // right propeller signal is pin 9

  // for wait(). WARNING: may need to adjust write value depending on pot. resistance and connected pins
  pinMode(A0, OUTPUT);
  analogWrite(A0, 1023);
  pinMode(A2, INPUT);

  prop_l.write(1280); // left propeller high throttle
  prop_r.write(1280); // right propeller high throttle
  wait(); // waits for knob to turn

  prop_l.write(800); // left propeller low throttle
  prop_r.write(800); // right propeller low throttle
  wait(); // waits for knob to turn

  prop_l.write(1280); // left propeller high speed
  prop_r.write(1280); // right propeller high speed

  rudder.write(midRange); // set rudder position to middle
}

void loop() {
  delay(2000); // waits 2 seconds
  rudder.write(midRange - 22); // sets rudder to middle position minus 22 degrees
  delay(2000); // waits 2 seconds
  rudder.write(midRange + 22); // sets rudder to middle position plus 22 degrees
}
