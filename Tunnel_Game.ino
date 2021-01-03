#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <DFRobotDFPlayerMini.h>

#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5
#define LED5 6
#define LED6 7
#define LED7 8
#define LED8 0
SoftwareSerial mySoftwareSerial(11, 9); // tx rx
int trigPin = 12;    // Trigger
int echoPin = 13;    // Echo

#define button1 A0
#define button2 A1
#define button3 A2
#define button4 A3
#define button5 A4
#define button6 A5
#define button7 10
//#define button8 11



long duration, cm, inches;
int prev = 10; 
int turn_on = 10;


DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);


void setup() {


  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(button6, INPUT);
  pinMode(button7, INPUT);
  //pinMode(button8, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  randomSeed(analogRead(0));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  myDFPlayer.volume(30);
  power_on();
  all_off();
  delay(2000);

}

void loop()
{

  while(turn_on == prev)
  {
    turn_on = random(1,8);
  }
  prev = turn_on;

  digitalWrite(turn_on + 1, HIGH);
  play_sound(turn_on, 2000);


  while (true) //while the button is not pressed run this while loop
  {

    int check = check_button_press(turn_on);
    if (check == 1)
    {
      wrong();
      all_off();
      delay(1000);
      digitalWrite(turn_on + 1, HIGH);
      play_sound(turn_on, 2000);
    }
    else if (check == 2)
    {
      play_sound(turn_on, 2000);
      break;
    }

    if (dis_sensor() && dis_sensor()&& dis_sensor() && dis_sensor() && dis_sensor())
    {
        standup();
        all_off();
        digitalWrite(turn_on + 1, HIGH);
        play_sound(turn_on, 2000);
      
    }


  }


  right();
  digitalWrite(turn_on + 1, LOW);


}

void power_on()
{

  all_off();
  play_sound(13, 0);

  digitalWrite(LED1, HIGH);
  delay(500);
  digitalWrite(LED2, HIGH);
  delay(500);
  digitalWrite(LED3, HIGH);
  delay(500);
  digitalWrite(LED4, HIGH);
  delay(500);
  digitalWrite(LED5, HIGH);
  delay(500);
  digitalWrite(LED6, HIGH);
  delay(500);
  digitalWrite(LED7, HIGH);
  delay(500);
  digitalWrite(LED8, HIGH);
  delay(500);

  play_sound(13, 0);
  all_off();
  delay(500);
  all_on();
  delay(500);
  all_off();
  delay(500);
  all_on();
  delay(500);
  all_off();
  delay(500);



}

void right()
{

  delay(500);
  all_on();
  play_sound(11, 0);

  delay(250);
  all_off();


  delay(250);
  all_on();
  play_sound(11, 0);

  delay(250);
  all_off();

  delay(1200);

}


void wrong()
{
  play_sound(12, 0);

  for (int i = 0; i <= 2; i++)
  {
    all_on();
    delay(250);
    all_off();
    delay(250);
  }


}

int check_button_press(int x)
{
  if (digitalRead(button1) == LOW )
  {
    if (x != 1)
      return 1;
    else
      return 2;
  }

  if (digitalRead(button2) == LOW )
  {
    if (x != 2)
      return 1;
    else
      return 2;
  }

  if (digitalRead(button3) == LOW )
  {
    if (x != 3)
      return 1;
    else
      return 2;
  }

  if (digitalRead(button4) == LOW )
  {
    if (x != 4)
      return 1;
    else
      return 2;
  }

  if (digitalRead(button5) == LOW )
  {
    if (x != 5)
      return 1;
    else
      return 2;
  }

  if (digitalRead(button6) == LOW )
  {
    if (x != 6)
      return 1;
    else
      return 2;
  }

  if (digitalRead(button7) == LOW )
  {
    if (x != 7)
      return 1;
    else
      return 2;
  }
//
//  if (digitalRead(button8) == LOW )
//  {
//    if (x != 8)
//      return 1;
//    else
//      return 2;
//  }
  return 0;

}



void standup()
{
  
  
  all_off();
  //play_sound(power_down, 10000)
  // power down noise?
  // please stand up!

  // so when the sensors detects the magtenic it pass through it, so have
  // to wait until it passes backl through
  while (true)
  {
    //if it equals high then it went back up and stood up
    if (!dis_sensor())
    {
      break;
    }

  }
  return;


}

//Helper function

void all_on()
{
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
  digitalWrite(LED6, HIGH);
  digitalWrite(LED7, HIGH);
  digitalWrite(LED8, HIGH);

}


void all_off()
{

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  digitalWrite(LED8, LOW);

}

boolean dis_sensor()
{

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
  inches = (duration / 2) / 74; // Divide by 74 or multiply by 0.0135

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  return (inches > 500);

}

void play_sound(int song, long del)
{
  myDFPlayer.playMp3Folder(song);
  delay(del); 
}
