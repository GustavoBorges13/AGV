//SENSORES ULTRASSONICOS
#define echoPin1 2 //PWM F1
#define trigPin1 23 //Digital
#define echoPin2 3 //PWM F2
#define trigPin2 25 //Digital
#define echoPin3 4 //PWM F3
#define trigPin3 27 //Digital
#define echoPin4 5 //PWM F4
#define trigPin4 29 //Digital
#define echoPin5 6 //PWM F5
#define trigPin5 31 //Digital
#define echoPin6 7 //PWM F6
#define trigPin6 33 //Digital
#define echoPin7 8 //PWM F7
#define trigPin7 35 //Digital

long duration, DistanciaCM, S1, S2, S3, S4, S5, S6, S7;

int frente = 41; // IN1
int tras = 43; // IN2
//int buzina = 45; // IN3

void setup()
{
  pinMode(frente, OUTPUT);
  pinMode(tras, OUTPUT);


  digitalWrite(frente, HIGH);
  digitalWrite(tras, HIGH);

  //SENSORES
  pinMode(echoPin1, INPUT_PULLUP);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin2, INPUT_PULLUP);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin3, INPUT_PULLUP);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin4, INPUT_PULLUP);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin5, INPUT_PULLUP);
  pinMode(trigPin5, OUTPUT);
  pinMode(echoPin6, INPUT_PULLUP);
  pinMode(trigPin6, OUTPUT);
  pinMode(echoPin7, INPUT_PULLUP);
  pinMode(trigPin7, OUTPUT);
  Serial.begin(9600);

}

void loop()
{
  
  SensorUltra(trigPin1, echoPin1);
  S1 = DistanciaCM;
  SensorUltra(trigPin2, echoPin2);
  S2 = DistanciaCM;
  SensorUltra(trigPin3, echoPin3);
  S3 = DistanciaCM;
  SensorUltra(trigPin4, echoPin4);
  S4 = DistanciaCM;
  SensorUltra(trigPin5, echoPin5);
  S5 = DistanciaCM;
  SensorUltra(trigPin6, echoPin6);
  S6 = DistanciaCM;
  SensorUltra(trigPin7, echoPin7);
  S7 = DistanciaCM;

  Serial.print("S1 ");
  Serial.print(S1);
  Serial.print(" | ");
  Serial.print("S2 ");
  Serial.print(S2);
  Serial.print(" | ");
  Serial.print("S3 ");
  Serial.print(S3);
  Serial.print(" | ");
  Serial.print("S4 ");
  Serial.print(S4);
  Serial.print(" | ");
  Serial.print("S5 ");
  Serial.print(S5);
  Serial.print(" | ");
  Serial.print("S6 ");
  Serial.print(S6);
  Serial.print(" | ");
  Serial.print("S7 ");
  Serial.println(S7);
  condicaoFRENTE();
}

void SensorUltra(int trigPin, int echoPin) { //BIBLIOTECA
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  DistanciaCM = (duration / 2) / 29.1;
}

void condicaoFRENTE() { //GERAL
  if (S1 <= 100 || S2 <= 170 || S3 <= 100 || S4 <= 100 || S5 <= 170 || S6 <= 170 || S7 <= 100) {
    digitalWrite(frente, HIGH); //STOP
    digitalWrite(tras, LOW);
  } else {
    digitalWrite(tras, HIGH);
    digitalWrite(frente, LOW); //IR PARA FRENTE(ACELERAR)
  }
}
