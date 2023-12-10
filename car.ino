#define dira 8
#define dirb 10
#define pwma 9
#define pwmb 11

#define triggerDepan 12
#define echoDepan 13
#define triggerKanan 4
#define echoKanan 5
#define triggerKiri 6
#define echoKiri 7

// long durationDepan, jarakDepan, durationKanan, jarakKanan, durationKiri, jarakKiri;
long durationDepan, durationKanan, durationKiri; // deklarasi variable

// fungsi kendali motor kiri
void motorKiri(int a) {
  if (a >= 0) {
    digitalWrite(dira, 0);  // putar motor berlawanan arah jarum jam
    analogWrite(pwma, a);   // setting kecepatannya sesuai dengan nilai parameter a
  } else if (a < 0) {
    digitalWrite(dira, 1);  // putar motor berlawanan arah jarum jam
    analogWrite(pwma, a + 255); // untuk memastikan nilai pwm nya tetap bernilai positif
  }
}

// fungsi kendali motor kanan
void motorKanan(int b) {
  if (b >= 0) {
    digitalWrite(dirb, 0);
    analogWrite(pwmb, b);
  } else if (b < 0) {
    digitalWrite(dirb, 1);
    analogWrite(pwmb, b + 255);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(dira, OUTPUT);
  pinMode(dirb, OUTPUT);

  pinMode(triggerDepan, OUTPUT);
  pinMode(echoDepan, INPUT);

  pinMode(triggerKanan, OUTPUT);
  pinMode(echoKanan, INPUT);

  pinMode(triggerKiri, OUTPUT);
  pinMode(echoKiri, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.print("Front : ");
  // Serial.println(funcDistanceFront());
  // Serial.print("Left : ");
  // Serial.println(funcDistanceLeft());
  // Serial.print("Right : ");
  // Serial.println(funcDistanceRight());
  // delay(200);
  if (funcDistanceFront() > 15) {
    motorKanan(-255);
    motorKiri(255);
    // Serial.println("Maju");
  } else if (funcDistanceFront() < 15 && funcDistanceLeft() < 15 && funcDistanceRight() < 15) {
    motorKanan(100);
    motorKiri(-100);
    // Serial.println("Mundur");
  } else {
    if (funcDistanceLeft() > funcDistanceRight()) {
      motorKanan(-255);
      motorKiri(0);
      // Serial.println("Kanan");
    } else {
      motorKanan(0);
      motorKiri(255);
      // Serial.println("Kiri");
    }
  }
}

int funcDistanceFront() { // fungsi untuk mengambil jarak sensor depan
  digitalWrite(triggerDepan, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerDepan, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerDepan, LOW);
  durationDepan = pulseIn(echoDepan, HIGH);
  // jarakDepan = (durationDepan / 2) / 29.1;
  return (durationDepan / 2) / 29.1;
}

int funcDistanceRight() { // fungsi untuk mengambil jarak sensor kanan
  digitalWrite(triggerKanan, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerKanan, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerKanan, LOW);
  durationKanan = pulseIn(echoKanan, HIGH);
  // jarakKanan = (durationKanan / 2) / 29.1;
  return (durationKanan / 2) / 29.1;
}

int funcDistanceLeft() { // fungsi untuk mengambil jarak sensor kiri
  digitalWrite(triggerKiri, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerKiri, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerKiri, LOW);
  durationKiri = pulseIn(echoKiri, HIGH);
  // jarakKiri = (durationKiri / 2) / 29.1;
  return (durationKiri / 2) / 29.1;
}
