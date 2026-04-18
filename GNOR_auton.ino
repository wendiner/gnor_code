// GNOR_auton.ino
// by wendiner, 2026
// GNU General Public License v3.0
//
// Auton code for the 2026 Spring Great Navel Orange Race
// Ran on an Arduino Uno R3
// 
// Wiring guide:
// 3: rudder signal cable
// 5: propeller(s) signal cable
// 7: input to button or pot
// 8: output from above
// A4: MPU6050 SDA pin
// A5: MPU6050 SCL pin

#include <Servo.h>

int midRange = 115; // rudder midpoint

Servo rudder;
Servo prop;

void blink() { // blinks onboard LED
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Button pressed!");
}

void wait() { // waits until potentiometer crosses midpoint. WARNING: may need to adjust values depending on pot. resistance and connected pins
  if (digitalRead(8) == 1) {
    while (digitalRead(8) == 1) {}
  } else while (digitalRead(8) != 1) {}

  blink();
}

void setup() {
  // for blink()
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);

  rudder.attach(3); // rudder signal is pin 3
  prop.attach(5); // propeller signal is 5

  rudder.write(midRange); // put server in middle position

  // for wait(). WARNING: may need to adjust write value depending on pot. resistance and connected pins
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  digitalWrite(7, HIGH);

  prop.write(1900); // throttle high
  wait(); // waits for user input

  prop.write(800); // throttle low
  wait(); // waits for user input

  prop.write(1200); // this signal is ignored by ESCs
  delay(1000);
  
  prop.write(800); // start low
  for (int i = 0; i < 110; i++) { // rapidly go to full speed
    prop.write(800 + i * 10);
    delay(50);
  }

  delay(7000); // go straight for 7 seconds

  prop.write(800); // stop
}

void loop() {

}
