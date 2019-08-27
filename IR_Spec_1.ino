#define BUZZER 6
#define SIGNAL_PIN A0

int distance =0;
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   pinMode(BUZZER,OUTPUT);
   pinMode(SIGNAL_PIN,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int volt = map(analogRead(A0),0,1023,0,5000);
  distance = (27.61/ (volt- 0.1696))*1000;
  
  
  if (distance <=20)
  {
   tone(BUZZER,600);
   delay(500);
   noTone(BUZZER);
   delay(500);
  }
  else
  {
    delay(500);
  }
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}
