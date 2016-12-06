#define buzzer 9
unsigned long echo = 0;
int echoPin=11;
int ultraSoundSignal = 10; // Ultrasound signal pin
unsigned long ultrasoundValue = 0;
double distance = 0;
int frequency = 0;
const int recordButton=7, playButton=4, dropButton=13, raiseButton=12, muteButton=3;
int note[] = {262, 294, 330, 349, 392, 440, 494, 523};
int octave = 2;
int sound_duration[100], sound_frequency[100], order=0; // arrays for looping mechanism
  unsigned long previousTime=0, elapsedTime=0; 

void setup() {

  Serial.begin (9600);


  pinMode(dropButton, INPUT);
  pinMode(raiseButton, INPUT);
  pinMode(muteButton, INPUT);
  
  pinMode(playButton, INPUT);
  pinMode(recordButton, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ultraSoundSignal,OUTPUT);
}

void loop() {
  getDistance(); //sets global variable distance to the distance in cm
  //getOctave(); //Checks to see if octave is changedM
  getNote(); //sets global variable frequency to the correct note's frequency in hertz


   if(digitalRead(dropButton) == LOW )
  {
      note[0] = 262/2;
    note[1] = 294/2;
    note[2] = 330/2;
    note[3] = 349/2;
    note[4] = 392/2;
    note[5] = 440/2;
    note[6] = 494/2;
    note[7] = 523/2;
  }
  /*else{
    note[0] = 262;note[1] = 294;note[2] = 330;note[3] = 349;note[4] = 392;note[5] = 440;note[6] = 494;note[7] = 523;
  }*/
  

  else if(digitalRead(raiseButton) == LOW )
  {
     note[0] = 262*2;
    note[1] = 294*2;
    note[2] = 330*2;
    note[3] = 349*2;
    note[4] = 392*2;
    note[5] = 440*2;
    note[6] = 494*2;
    note[7] = 523*2;
  }
  else if(digitalRead(raiseButton) == HIGH && digitalRead(dropButton) == HIGH){
    note[0] = 262;
    note[1] = 294;
    note[2] = 330;
    note[3] = 349;
    note[4] = 392;
    note[5] = 440;
    note[6] = 494;
    note[7] = 523;
  }
  if (digitalRead(playButton)==LOW)
   {
    noTone(buzzer);
    play();
   }
  else
  {
    if(distance > 48)
    noTone(buzzer);
    else
    tone(buzzer, frequency);
  }
  
  if (digitalRead(recordButton)==LOW){
    record();
    sound_frequency[order]=frequency;
  }
   
  if (digitalRead(muteButton)==LOW)
  {
    reset();
  }
  

  
  Serial.print(distance);
  Serial.println(" cm");
  //delay(100);
}

void getDistance(){
    pinMode(ultraSoundSignal, OUTPUT); 
  
  digitalWrite(ultraSoundSignal, LOW); 
  delayMicroseconds(2); 
  digitalWrite(ultraSoundSignal, HIGH);
  delayMicroseconds(5); 
  digitalWrite(ultraSoundSignal, LOW); 

  /*takes the recorded value and converts to distance*/

  pinMode(echoPin, INPUT); 
  echo = pulseIn(echoPin, HIGH);
  distance = (echo / 58.138);
}

void getNote(){
  if (distance <= 11.5/2) {
    frequency=note[0]; //C
  }
  else if (distance <= 21/2+1) {
    frequency = note[1]; //C#/D♭
  }
  else if (distance <= 30.5/2+2) {
    frequency = note[2]; //D
  } 
  else if (distance <= 40/2+4) {
    frequency = note[3]; //D#/E♭
  }
  else if (distance <= 49.5/2+6) {
    frequency= note[4]; //E
  }
  else if (distance <= 59/2+8) {
    frequency= note[5]; //F
  }
  else if (distance <= 68.5/2+10){
    frequency = note[6];//F#/G♭
  }
  else if(distance <= 78/2+12){
    frequency = note[7]; //G
  }
  else{
    frequency = 0;
  }


} 

void getOctave(){
  if(digitalRead(dropButton) == LOW && octave >= 3)
  {
    Serial.println("DOWN DOWN DOWN");
    for(int i = 0; i < 8; i++)
    {
      note[i]=note[i]/2.0;
    }
    octave--;
  }
  

  if(digitalRead(raiseButton) == LOW && octave <= 5)
  {
        Serial.println("UP UP UP UP UP");
    for(int i = 0; i < 8; i++)
    {
      note[i]=note[i]*2.0;
    }
    octave++;
  }
}

void record()
{
  Serial.println(sound_frequency[order]);
  Serial.println(frequency);
  if(sound_frequency[order]!=frequency)
  {
    sound_duration[order]=millis() - previousTime;
    previousTime = millis();

    order++;
  }

  sound_frequency[order]=frequency;
  Serial.println(order);
}
void play()
{
  for(int i=1;i<50;i++)
  {
    sound_duration[0]=0;
    Serial.print(sound_frequency[i]);
    Serial.print("                    ");
    Serial.println(sound_duration[i]);
    tone(buzzer, sound_frequency[i], sound_duration[i]);
    delay(sound_duration[i]);
    if(sound_duration[i]==0)
    {
      break;
    }
  }
}
void reset()
{
  Serial.println("RESET RESET RESET");
  order=0;
  memset(sound_frequency,0,sizeof(sound_frequency));
  memset(sound_duration,0,sizeof(sound_duration));
}
