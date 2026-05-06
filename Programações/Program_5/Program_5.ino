//SENSORES ULTRASSONICOS
//int echoPin1 = 2; int trigPin1 = 23; //ECHO = PWM(ANALOGICO) - TRIGGER = DIGITAL
//int echoPin2 = 3; int trigPin2 = 25; //ECHO = PWM(ANALOGICO) - TRIGGER = DIGITAL
//int echoPin3 = 4; int trigPin3 = 27; //ECHO = PWM(ANALOGICO) - TRIGGER = DIGITAL
int echoPin4 = 2; int trigPin4 = 23; //ECHO = PWM(ANALOGICO) - TRIGGER = DIGITAL
int echoPin5 = 3; int trigPin5 = 25; //ECHO = PWM(ANALOGICO) - TRIGGER = DIGITAL
int echoPin6 = 4; int trigPin6 = 27; //ECHO = PWM(ANALOGICO) - TRIGGER = DIGITAL
int echoPin7 = 5; int trigPin7 = 29; //ECHO = PWM(ANALOGICO) - TRIGGER = DIGITAL
double duration, DistanciaCM, U1, U2, U3, U4, U5, U6, U7;



//CONTROLE DE MOVIMENTAÇÃO - RELAYS
int frente = 41; // IN1
int tras = 43; // IN2
//int buzina = 45; // IN3



// DADOS da Calibração dos sensores:
// Obtenha esses no esboço de calibração BRANCO/PRETO na programação "Calibracao_Sensor".
// Valores referente aos foto diodos (range minimo e maximo)
int S0 = 44, S1 = 42, S2 = 40, S3 = 38; //SENSOR DE COR 1 - ESQUERDA
int sensorOut = 10;

//Valor de calibração para realizar a conversa... esse valor se aplica para ambos sensores.
//Minimo = valor do branco e máximo = valor do preto.
int redMin = 38, redMax = 57; //Minimo e maximo RED
int greenMin = 51, greenMax = 68; //Minimo e maximo GREEN
int blueMin = 83, blueMax = 65; //Minimo e maximo BLUE

//SENSOR DE COR 2 - DIREITA
int S0_2 = 52, S1_2 = 50, S2_2 = 48, S3_2 = 46; //SENSOR DE COR 2 - DIREITA
int sensorOut_2 = 9;

// Variáveis para medições de largura de pulso de cor:
int redPW = 0, greenPW = 0, bluePW = 0; //Variável de armazenagem do sensor 1
int redPW_2 = 0, greenPW_2 = 0, bluePW_2 = 0; //Variavel de armazenagem do sensor 2

// Variáveis para valores finais de cor:
int redValue, greenValue, blueValue; //Variavel de valor final para cores do sensor 1
int redValue_2, greenValue_2, blueValue_2; //Variavel de valor final para cores do sensor 2



// Variáveis do botão de emergência
const int botao = 49;
int estado = 0;
int pulse = 0;



//MOTOR DE PASSO
// Define os pinos do motor:
int driverPUL = 34;
int driverDIR = 36;
// Cálculo: 360º/400 passos = 0,9º | 1 PASSO EQUIVALE A 0,9 GRAUS
// Variáveis para execução do motor de passo:
// boolean setdir = LOW; Altera o sentido | HIGH --> sentido anti-horário and LOW --> sentido horário
float rotacao = 1.0 / 360; // Define a quantidade de rotações do motor | Regra de três: Exemplo: Para girar 90º - Dividimos 90/360 = 0.25
double revolution = 400 * rotacao; //Precisão escolhida no Driver |
int speed = 1200; // Velocidade do motor, valores menores --> velocidade maior
int count = 0; //  Contador de passos


//SENSOR MAGNETICO
int magnetico_1 = A0; int magnetico_2 = A1; int magnetico_3 = A2; int magnetico_4 = A3; // X-axis-signal
//int magnetico_1 = 3; int magnetico_2 = 4; int magnetico_3 = 5; // Button
float analog_1, analog_2, analog_3, analog_4; // analog_2, analog_3, analog_4;
int digital_1, digital_2, digital_3, digital_4, analog_aux_1, analog_aux_2, analog_aux_3, analog_aux_4; //if digital == 1 or 0

//PID
float erro;
float speed_PID;
int Kp = 50;
int Ki = 25;
int Kd = 25;
float previousError = 0;
float PIDvalue, P, I, D;

/*


  0 0 0 1 ==> -3
  0 0 1 1 ==> -2
  0 0 1 0 ==> -1
  0 0 0 0 ==> 0
  0 1 1 0 ==> 0
  0 1 0 0 ==> 1
  1 1 0 0 ==> 2
  1 0 0 0 ==> 3


*/


void setup() {
  Serial.begin(9600);

  //SENSORES MAGNETICOS
  pinMode (magnetico_1, INPUT); pinMode (magnetico_2, INPUT); pinMode (magnetico_3, INPUT); pinMode (magnetico_4, INPUT);

  //SENSORES ULTRASSONICOS
  //pinMode(echoPin1, INPUT_PULLUP); pinMode(trigPin1, OUTPUT); //U1
  //pinMode(echoPin2, INPUT_PULLUP); pinMode(trigPin2, OUTPUT); //U2
  //pinMode(echoPin3, INPUT_PULLUP); pinMode(trigPin3, OUTPUT); //U3
  pinMode(echoPin4, INPUT_PULLUP); pinMode(trigPin4, OUTPUT); //U4
  pinMode(echoPin5, INPUT_PULLUP); pinMode(trigPin5, OUTPUT); //U5
  pinMode(echoPin6, INPUT_PULLUP); pinMode(trigPin6, OUTPUT); //U6
  pinMode(echoPin7, INPUT_PULLUP); pinMode(trigPin7, OUTPUT); //U7


  //SENSORES DE COR
  pinMode(S0, OUTPUT); pinMode(S1, OUTPUT); pinMode(S2, OUTPUT); pinMode(S3, OUTPUT); //Define as saídas do sensor.
  pinMode(sensorOut, INPUT); pinMode(sensorOut_2, INPUT); //Define a saída do sensor 1 e 2 como entrada
  pinMode(S0_2, OUTPUT); pinMode(S1_2, OUTPUT); pinMode(S2_2, OUTPUT); pinMode(S3_2, OUTPUT); pinMode(sensorOut_2, INPUT); //Define as saídas do sensor 2.
  digitalWrite(S0, HIGH); digitalWrite(S0_2, HIGH); digitalWrite(S1, LOW); digitalWrite(S1_2, LOW); //Define a frequencia de escala dos sensores para 20%.


  //SENSOR INDUTIVO
  //pinMode (indutivo, INPUT_PULLUP);


  // Botão de emergência
  pinMode(botao, INPUT_PULLUP);


  //SAÍDAS DO CONTROLE DE NAVEGAÇÃO (MOTOR)
  pinMode (driverPUL, OUTPUT);
  pinMode (driverDIR, OUTPUT);


  //SAÍDAS DO CONTROLE DE MOVIMENTAÇÃO (RELAYS)
  pinMode(frente, OUTPUT); pinMode(tras, OUTPUT);
  digitalWrite(frente, HIGH); digitalWrite(tras, HIGH); //estado antes de iniciar.
  //HIGH = DESLIGADO | LOW = LIGADO

}

void loop() {
  //SensorUltra(trigPin1, echoPin1); U1 = DistanciaCM;
  //SensorUltra(trigPin2, echoPin2); U2 = DistanciaCM;
  //SensorUltra(trigPin3, echoPin3); U3 = DistanciaCM;
  SensorUltra(trigPin4, echoPin4); U4 = DistanciaCM;
  SensorUltra(trigPin5, echoPin5); U5 = DistanciaCM;
  SensorUltra(trigPin6, echoPin6); U6 = DistanciaCM;
  SensorUltra(trigPin7, echoPin7); U7 = DistanciaCM;

  //Serial.print("S1 "); Serial.print(U1); Serial.print(" | ");
  //Serial.print("S2 "); Serial.print(U2); Serial.print(" | ");
  //Serial.print("S3 "); Serial.print(U3); Serial.print(" | ");
  /*
    Serial.print("S4 "); Serial.print(U4); Serial.print(" | ");
    Serial.print("S5 "); Serial.print(U5); Serial.print(" | ");
    Serial.print("S6 "); Serial.print(U6); Serial.print(" | ");
    Serial.print("S7 "); Serial.println(U7);*/

  if (digitalRead(botao) == 1) {
    pulse++;
    if (pulse % 2 == 0) {
      estado = 1;
      Serial.println("Ligado!");
    }
    if (pulse % 2 == 1) {
      estado = 0;
      Serial.println("Desligado!");
    }
    while (digitalRead(botao) == 1) {}
  }

  leitura_sensores();
  calculatePID ();
  seguidor_linha();
}


void leitura_sensores() {
  analog_1 = analogRead (magnetico_1);
  analog_2 = analogRead (magnetico_2);
  analog_3 = analogRead (magnetico_3);
  analog_4 = analogRead (magnetico_4);

  //PID
  if (analog_1 > 504 && analog_2 > 508 && analog_3 > 518 && analog_4 <= 525) {
    erro = -3;
  } else if (analog_1 > 504 && analog_2 > 508 && analog_3 <= 518 && analog_4 <= 525) {
    erro = -2;
  } else if (analog_1 > 504 && analog_2 > 508 && analog_3 <= 518 && analog_4 > 525) {
    erro = -1;
  } else if (analog_1 > 504 && analog_2 > 508 && analog_3 > 518 && analog_4 > 525) {
    erro = 0;
  } else if (analog_1 > 504 && analog_2 <= 508 && analog_3 <= 518 && analog_4 > 525) {
    erro = 0;
  } else if (analog_1 > 504 && analog_2 <= 508 && analog_3 > 518 && analog_4 > 525) {
    erro = 1;
  } else if (analog_1 <= 504 && analog_2 <= 508 && analog_3 > 518 && analog_4 > 525) {
    erro = 2;
  } else if (analog_1 <= 504 && analog_2 > 508 && analog_3 > 518 && analog_4 > 525) {
    erro = 3;
  }

  Serial.print(analog_1); // print analog value
  Serial.print(" ");
  Serial.print(analog_2); // print analog value
  Serial.print(" ");
  Serial.print(analog_3); // print analog value
  Serial.print(" ");
  Serial.println(analog_4);
}

void calculatePID () {
  P = erro;
  I = I + erro;
  D = erro - previousError;
  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
  previousError = erro;
}


void seguidor_linha() {

  if (estado == 1 && U4 >= 90 && U5 >= 90 && U6 >= 90 && U7 >= 90) { //COMPARA O BOTÃO E SENSORES ULTRASSONICOS.
    if (erro == 0) {
      digitalWrite(tras, HIGH); //DESATIVA A MARCHA DE IR PARA TRÁS.
      digitalWrite(frente, LOW); //vai para frente

      //CORREÇAÃO PARA DIREITA, ERROS > 0
    } else if (erro == 1) {
      speed_PID = speed - PIDvalue;
      if (speed_PID < 900) {
        speed_PID = 900;
      }
      for (int count = 0; count <= revolution * 100; count++) {
        digitalWrite(driverDIR, LOW); //CORRIGE PARA DIREITA
        digitalWrite(driverPUL, HIGH);
        delayMicroseconds(speed_PID);
        digitalWrite(driverPUL, LOW);
        delayMicroseconds(speed_PID);
      }
    } else if (erro == 2) {
      speed_PID = speed - PIDvalue;
      if (speed_PID < 900) {
        speed_PID = 900;
      }
      for (int count = 0; count <= revolution * 100; count++) {
        digitalWrite(driverDIR, LOW); //CORRIGE PARA DIREITA
        digitalWrite(driverPUL, HIGH);
        delayMicroseconds(speed_PID);
        digitalWrite(driverPUL, LOW);
        delayMicroseconds(speed_PID);
      }
    } else if (erro == 3) {
      speed_PID = speed - PIDvalue;
      if (speed_PID < 800) {
        speed_PID = 800;
      }
      for (int count = 0; count <= revolution * 225; count++) {
        digitalWrite(driverDIR, LOW); //CORRIGE PARA DIREITA
        digitalWrite(driverPUL, HIGH);
        delayMicroseconds(speed_PID);
        digitalWrite(driverPUL, LOW);
        delayMicroseconds(speed_PID);
      }
    }

    //CORREÇÃO PARA ESQUERDA, ERROS < 0
    if (erro == -1) {
      speed_PID = speed + PIDvalue;
      if (speed_PID < 900) {
        speed_PID = 900;
      }
      for (int count = 0; count <= revolution * 100; count++) {
        digitalWrite(driverDIR, HIGH); //CORRIGE PARA ESQUERDA
        digitalWrite(driverPUL, HIGH);
        delayMicroseconds(speed_PID);
        digitalWrite(driverPUL, LOW);
        delayMicroseconds(speed_PID);
      }
    } else if (erro == -2) {
      speed_PID = speed + PIDvalue;
      if (speed_PID < 900) {
        speed_PID = 900;
      }
      for (int count = 0; count <= revolution * 100; count++) {
        digitalWrite(driverDIR, HIGH); //CORRIGE PARA ESQUERDA
        digitalWrite(driverPUL, HIGH);
        delayMicroseconds(speed_PID);
        digitalWrite(driverPUL, LOW);
        delayMicroseconds(speed_PID);
      }
    } else if (erro == -3) {
      speed_PID = speed + PIDvalue;
      if (speed_PID < 800) {
        speed_PID = 800;
      }
      for (int count = 0; count <= revolution * 225; count++) {
        digitalWrite(driverDIR, HIGH); //CORRIGE PARA ESQUERDA
        digitalWrite(driverPUL, HIGH);
        delayMicroseconds(speed_PID);
        digitalWrite(driverPUL, LOW);
        delayMicroseconds(speed_PID);
      }
    }
  }

  if (estado == 1 && (U4 < 90 || U5 < 90 || U6 < 90 || U7 < 90)) {
    digitalWrite(frente, HIGH);
    digitalWrite(tras, LOW);
    delay(2000);
    Serial.print(estado);
    Serial.println("Parado!");
  }

  if (estado == 0) {
    digitalWrite(frente, HIGH);
    //digitalWrite(tras, LOW);
    //delay(1000);
    Serial.print(estado);
    Serial.println("Parado!");
  }
}

void SensorUltra(int trigPin, int echoPin) { //BIBLIOTECA
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  // DistanciaCM = (duration / 2) / 29.1;
  DistanciaCM = (340 * (duration / 2) / 1000000) * 100;
}
