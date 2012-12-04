/*
  LightningTimer
  Counts down from 3 minutes with audible and visible alerts.

  - 5 second countdown with beeps and white flash.
  - 2 minutes solid green.
  - beep and 30 seconds solid yellow
  - beep and 20 second flashing yellow
  - beep and 7 seconds flashing red
  - 3 seconds flashing red with beep
  - infinite loop on siren beep and blue/red flash.

  Based on Blink, which is in the public domain.
  Beep routine from http://tronixstuff.wordpress.com/2012/03/19/simone-the-numerical-memory-game/
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
static int red = 13;
static int green = 9;
static int blue = 10;

static int beep = 11;

void led_toggle(int led) {
  digitalWrite(led, !digitalRead(led));
}

void piezoBeep(int type) // used to make beeps
{
  long duration=250000;
  int freq;
  switch(type)
  {
    case 1:
      freq = 600;
      break;
    case 2:
      freq = 700;
      break;
    case 3:
      freq = 800;
      break;
    case 4:
      freq = 900;
      break;
    case 5:
      freq = 1000;
      break;
    case 6:
      freq = 1100;
      break;
    case 7:
      freq = 1200;
      break;
    case 8:
      freq = 1300;
      break;
  }

  int period = (1.0 / freq) * 1000000;
  long elapsed_time = 0;
  while (elapsed_time < duration) {
    digitalWrite(11,HIGH);
    delayMicroseconds(period / 2);
    digitalWrite(11, LOW);
    delayMicroseconds(period / 2);
    elapsed_time += (period);
  }
}

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  pinMode(beep, OUTPUT);
  
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  int i = 0;
  
  // Blink white five times.
  for(i = 0; i < 5; i++) {
   
    led_toggle(red);
    led_toggle(green);
    led_toggle(blue);
    piezoBeep(i + 3);
    delay (500);
    led_toggle(red);
    led_toggle(green);
    led_toggle(blue);
    delay (500);
  }
 
  // Count down 2 minutes on green.
  led_toggle(green);
  for (i = 0; i < 120; i++) {
    delay(1000);
  }
  
  piezoBeep(8);
  
  // 30 seconds on yellow.
  digitalWrite(green, HIGH);
  led_toggle(red);
  for(i = 0; i < 30; i++) {
    delay(1000);
  }
  
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
  piezoBeep(8);
  
  // 20 seconds flashing yellow.
  for (i = 0; i < 20; i++) {
    led_toggle(green);
    led_toggle(red);
    delay(500);
    led_toggle(green);
    led_toggle(red);
    delay(500);
  }

  piezoBeep(8);
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
  
  // 10 seconds flashing red.
  for (i = 0; i < 10; i++) {
    if (i > 7) {
      piezoBeep(i - 1);
    }
    led_toggle(red);
    delay(250);
    led_toggle(red);
    delay(250);
    led_toggle(red);
    delay(250);
    led_toggle(red);
    delay(250);
  }

  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(blue, LOW);
  
  // flash white slowly and beep!
  // Blink white five times.
  for(;;) {
    piezoBeep(8);
    led_toggle(red);
    led_toggle(blue);
    delay (250);

    piezoBeep(1);
    led_toggle(red);
    led_toggle(blue);
    delay (250);
  }
  
}
