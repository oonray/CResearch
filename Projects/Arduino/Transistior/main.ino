int out = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(out, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(out,HIGH);
}