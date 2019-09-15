void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  delay(100);

  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  //delay();

  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  delay(100);

  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  //delay(100);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(100);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  //delay();
}
