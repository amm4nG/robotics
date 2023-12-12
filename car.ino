#define in1MotorKanan 8
#define in3MotorKiri 10
#define in2MotorKanan 9
#define in4MotorKiri 11

const int speedMotorKanan = 1;
const int speedMotorKiri = 3;


#define triggerDepan 12
#define echoDepan 13
#define triggerKanan 4
#define echoKanan 5
#define triggerKiri 6
#define echoKiri 7

int ledGreen = 2;  // lampu indikator hijau
int theta = 15; // jarak yang dijadikan pembanding

// long durationDepan, jarakDepan, durationKanan, jarakKanan, durationKiri, jarakKiri;
long durationDepan, durationKanan, durationKiri;  // deklarasi variable

void setup() {
  Serial.begin(9600);  // mulai pembacaan pada serial monitor

  pinMode(in1MotorKanan, OUTPUT);
  pinMode(in3MotorKiri, OUTPUT);

  pinMode(triggerDepan, OUTPUT);
  pinMode(echoDepan, INPUT);

  pinMode(triggerKanan, OUTPUT);
  pinMode(echoKanan, INPUT);

  pinMode(triggerKiri, OUTPUT);
  pinMode(echoKiri, INPUT);

  pinMode(ledGreen, OUTPUT);
}

// bool status = true;
void loop() {
  digitalWrite(ledGreen, HIGH); // lampu hijau nyala
  int dFront = funcDistanceFront(); // ambil jarak sensor depan
  int dLeft = funcDistanceLeft(); // ambil jarak sensor kiri
  int dRight = funcDistanceRight(); // ambil jarak sensor kanan

  if(dFront>theta){
    turnForward(255);
  }else if(dRight>theta){ 
    turnRight(255);
  }else if(dLeft>theta){
    turnLeft(255);
  }else{
    turnBackward(255);
  }

  // if(dFront>theta && status){
  //   turnForward(255);
  // }else if(dRight>theta){ 
  //   turnRight(255);
  //   status = true;
  // }else if(dLeft>theta){
  //   turnLeft(255);
  //   status = true;
  // }else{
  //   turnBackward(255);
  //   status = false;
  // }

}

void turnRight(int v) {
  // motor kanan mundur
  digitalWrite(in1MotorKanan, 1); //searah putaran jarum jam dilihat dari dalam
  digitalWrite(in2MotorKanan, 0);
  analogWrite(speedMotorKanan, v); 

  // motor kiri maju
  digitalWrite(in3MotorKiri, 1); //searah putaran jarum jam dilihat dari dalam
  digitalWrite(in4MotorKiri, 0);
  analogWrite(speedMotorKiri, v); 
}

void turnLeft(int v) { 
  // motor kanan maju
  digitalWrite(in1MotorKanan, 0); //berlawanan arah putaran jarum jam dilihat dari dalam
  digitalWrite(in2MotorKanan, 1);
  analogWrite(speedMotorKanan, v); 

  // motor kiri mundur
  digitalWrite(in3MotorKiri, 0); //berlawanan arah putaran jarum jam dilihat dari dalam
  digitalWrite(in4MotorKiri, 1);
  analogWrite(speedMotorKiri, v);
}

void turnForward(int v) {
  // motor kanan maju
  digitalWrite(in1MotorKanan, 0); //berlawanan arah putaran jarum jam dilihat dari dalam
  digitalWrite(in2MotorKanan, 1);
  analogWrite(speedMotorKanan, v); 

  // motor kiri maju
  digitalWrite(in3MotorKiri, 1); //searah putaran jarum jam dilihat dari dalam
  digitalWrite(in4MotorKiri, 0);
  analogWrite(speedMotorKiri, v); 
}

void turnBackward(int v) {
  // motor kanan mundur
  digitalWrite(in1MotorKanan, 1); //searah putaran jarum jam dilihat dari dalam
  digitalWrite(in2MotorKanan, 0);
  analogWrite(speedMotorKanan, v); 

  // motor kiri mundur
  digitalWrite(in3MotorKiri, 0); //berlawanan arah putaran jarum jam dilihat dari dalam
  digitalWrite(in4MotorKiri, 1);
  analogWrite(speedMotorKiri, v);
}

int funcDistanceFront() {  // fungsi untuk mengambil jarak sensor depan
  digitalWrite(triggerDepan, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerDepan, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerDepan, LOW);
  durationDepan = pulseIn(echoDepan, HIGH);
  // jarakDepan = (durationDepan / 2) / 29.1;
  return (durationDepan / 2) / 29.1;
}

int funcDistanceLeft() {  // fungsi untuk mengambil jarak sensor kanan
  digitalWrite(triggerKanan, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerKanan, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerKanan, LOW);
  durationKanan = pulseIn(echoKanan, HIGH);
  // jarakKanan = (durationKanan / 2) / 29.1;
  return (durationKanan / 2) / 29.1;
}

int funcDistanceRight() {  // fungsi untuk mengambil jarak sensor kiri
  digitalWrite(triggerKiri, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerKiri, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerKiri, LOW);
  durationKiri = pulseIn(echoKiri, HIGH);
  // jarakKiri = (durationKiri / 2) / 29.1;
  return (durationKiri / 2) / 29.1;
}
