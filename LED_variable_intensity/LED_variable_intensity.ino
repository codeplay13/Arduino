int a = 0;
int b = 5;
void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
}
int x = 102;
void loop() {
  // put your main code here, to run repeatedly:
  while(x){
  analogWrite(3, a);
  a += b;
  if((a == 0) || (a == 255)){
    b = -b;
  }
  //delay(1000);
  x--;
  }
}
