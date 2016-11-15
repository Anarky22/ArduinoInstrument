/*#define led 13
#define led2 12
#define led3 11
#define led4 10
#define led5 9
#define led6 8
*/
#define buzzer 3
unsigned long echo = 0;
int ultraSoundSignal = 9; // Ultrasound signal pin
unsigned long ultrasoundValue = 0;

int frequency = 0;

void setup() {

  Serial.begin (9600);

  /*pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  */
  
  pinMode(buzzer, OUTPUT);
  pinMode(ultraSoundSignal,OUTPUT);
}

void loop() {
  pinMode(ultraSoundSignal, OUTPUT); 
  /*necessary for recording an accurate measurement*/

  digitalWrite(ultraSoundSignal, LOW); 
  delayMicroseconds(2); 
  digitalWrite(ultraSoundSignal, HIGH);
  delayMicroseconds(5); 
  digitalWrite(ultraSoundSignal, LOW); 

  /*takes the recorded value and converts to distance*/

  pinMode(ultraSoundSignal, INPUT); 
  digitalWrite(ultraSoundSignal, HIGH);
  echo = pulseIn(ultraSoundSignal, HIGH);
  distance = (echo / 58.138);

  if (distance <= 9.5) {
    //digitalWrite(led, HIGH);
    frequency=262; //C
  }
  else if (distance <= 17) {
    //digitalWrite(led2, HIGH);
    frequency = 277; //C#/D♭
  }
  else if (distance <= 24.5) {
    //digitalWrite(led3, HIGH);
    frequency = 294; //D
  } 
  else if (distance <= 32) {
    //digitalWrite(led4, HIGH);
    frequency = 311; //D#/E♭
  }
  else if (distance <= 39.5) {
    //digitalWrite(led5, HIGH);
    frequency= 330; //E
  }
  else if (distance <= 47) {
    //digitalWrite(led6, HIGH);
    frequency= 349; //F
  }
  else if (distance <= 54.5){
    frequency = 370//F#/G♭
  }
  else if(distance <= 62){
    frequency = 392; //G
  }
  else if(distance <= 69.5){
    frequency =415; //G#/A♭
  }
  else if(distance <= 77){
    frequency = 440; //A
  }
  else if(distance <= 84.5){
    frequency = 466;//A#/B♭
  }
  else if(distance <= 92){
    frequency = 494;//B
  }
  else if(distance <= 99.5){
    frequency = 523;//C
  }

  Serial.print(distance);
  Serial.println(" cm");
  tone(buzzer, sound);

  delay(500);
}
