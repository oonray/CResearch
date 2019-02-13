# 1 "g:\\OneDrive - Noroff Education AS\\R&D\\CResearch\\Arduino\\Transistior\\main.ino"
# 1 "g:\\OneDrive - Noroff Education AS\\R&D\\CResearch\\Arduino\\Transistior\\main.ino"
int out = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(out, 0x1);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(out,0x1);
  delay(200);
  digitalWrite(out,0x0);
  delay(1000);

}
