struct relay{
  int state;
  int port;
} rel = {
  .state = LOW,
  .port = 4
};

struct button{
  int state;
  int port;
}  btn = {
  .state = LOW,
  .port = 5,
};

int toggle_relay(){
  if(rel.state == HIGH){rel.state = LOW;}
  else if(rel.state == LOW){rel.state = HIGH;}
  digitalWrite(rel.port,rel.state);
  return 0;
}

void setup() {
  Serial.begin(9600);
  Serial.write("Starting\n");

  pinMode(rel.port, OUTPUT);
  pinMode(btn.port, INPUT);

}

void loop() {
  btn.state = digitalRead(btn.port);
  if(btn.state == HIGH){
    toggle_relay();
  }
  delay(200);
}
