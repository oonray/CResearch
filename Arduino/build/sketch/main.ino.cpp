#include <Arduino.h>
#line 1 "g:\\OneDrive - Noroff Education AS\\R&D\\CResearch\\Arduino\\Transistior\\main.ino"
#line 1 "g:\\OneDrive - Noroff Education AS\\R&D\\CResearch\\Arduino\\Transistior\\main.ino"
int out = 8;

#line 3 "g:\\OneDrive - Noroff Education AS\\R&D\\CResearch\\Arduino\\Transistior\\main.ino"
void setup();
#line 10 "g:\\OneDrive - Noroff Education AS\\R&D\\CResearch\\Arduino\\Transistior\\main.ino"
void loop();
#line 3 "g:\\OneDrive - Noroff Education AS\\R&D\\CResearch\\Arduino\\Transistior\\main.ino"
void setup() {
  // put your setup code here, to run once:
  pinMode(out, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(out,HIGH);
  delay(200);
  digitalWrite(out,LOW);
  delay(1000);

}
