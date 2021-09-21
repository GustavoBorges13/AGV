
//SENSOR DE COR 1 -ESQUERDA
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

//SENSOR DE COR 2 - DIREITA
#define S0_2 22
#define S1_2 24
#define S2_2 26
#define S3_2 28
#define sensorOut_2 9

// DADOS da Calibração dos sensores:
// Obtenha esses no esboço de calibração BRANCO/PRETO na programação "Calibracao_Sensor".
int redMin_2 = 25; // Red minimum value
int redMax_2 = 280; // Red maximum value
int greenMin_2 = 30; // Green minimum value
int greenMax_2 = 330; // Green maximum value
int blueMin_2 = 24; // Blue minimum value
int blueMax_2 = 280; // Blue maximum value

int redMin = 25; // Red minimum value
int redMax = 226; // Red maximum value
int greenMin = 25; // Green minimum value
int greenMax = 220; // Green maximum value
int blueMin = 21; // Blue minimum value
int blueMax = 181; // Blue maximum value

// Variáveis para medições de largura de pulso de cor:
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

int redPW_2 = 0;
int greenPW_2 = 0;
int bluePW_2 = 0;

// Variáveis para valores finais de cor:
int redValue;
int greenValue;
int blueValue;

int redValue_2;
int greenValue_2;
int blueValue_2;

// Cálculo:
// 360º/400 passos = 0,9º
// 1 PASSO EQUIVALE A 0,9 GRAUS
// Define os pinos do motor:
int driverPUL = 3;
int driverDIR = 2;

// Variáveis para execução do motor de passo:
int count = 0; //  Contador de passos
// boolean setdir = LOW; Altera o sentido | HIGH --> sentido anti-horário and LOW --> sentido horário
float rotacao = 1.0 / 360; // Define a quantidade de rotações do motor | Regra de três: Exemplo: Para girar 90º - Dividimos 90/360 = 0.25
double revolution = 400 * rotacao; //Precisão escolhida no Driver |
int speed = 1000; // Velocidade do motor, valores menores --> velocidade maior

//#define indutivo 10

// Funções:
void setup() {
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT); // Set Sensor output as input

  pinMode(S0_2, OUTPUT);
  pinMode(S1_2, OUTPUT);
  pinMode(S2_2, OUTPUT);
  pinMode(S3_2, OUTPUT);
  pinMode(sensorOut_2, INPUT); // Set Sensor output as input

  // Sensor Indutivo
  //pinMode (indutivo, INPUT_PULLUP);

  // Set Frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S0_2, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(S1_2, LOW);

  // Setup Serial Monitor
  Serial.begin(9600);

  // Definindo as portas do arduino como saídas:
  pinMode (driverPUL, OUTPUT);
  pinMode (driverDIR, OUTPUT);
}

void loop() {
  // Ler valor do vermelho:
  redPW = getRedPW();
  redPW_2 = getRedPW_2();
  // Mapa - valores de 0-255
  redValue = map(redPW, redMin, redMax, 255, 0);
  redValue_2 = map(redPW_2, redMin_2, redMax_2, 255, 0);
  // Delay para estabilizar o sensor:

  // Ler valor do verde:
  greenPW = getGreenPW();
  greenPW_2 = getGreenPW_2();
  // Mapa - valores de 0-255
  greenValue = map(greenPW, greenMin, greenMax, 255, 0  );
  greenValue_2 = map(greenPW_2, greenMin_2, greenMax_2, 255, 0  );
  // Delay para estabilizar o sensor:

  // Ler valor vermelho
  bluePW = getBluePW();
  bluePW_2 = getBluePW_2();
  // Mapa - valores de 0-255
  blueValue = map(bluePW, blueMin, blueMax, 255, 0);
  blueValue_2 = map(bluePW_2, blueMin_2, blueMax_2, 255, 0);
  // Delay para estabilizar o sensor:

  // Print output to Serial Monitor
  Serial.print(" Red = ");
  Serial.print(redValue);
  Serial.print(" -- ");
  Serial.print(redValue_2);
  Serial.print(" Green = ");
  Serial.print(greenValue);
  Serial.print(" -- ");
  Serial.print(greenValue_2);
  Serial.print(" Blue = ");
  Serial.print(blueValue);
  Serial.print(" -- ");
  Serial.println(blueValue_2);



  /* //COR BRANCAAA BRANCO BRANCO BRANCO
    if (redValue >= 240 && greenValue >= 240 && blueValue >= 240) {
     while (count <= revolution) {
       digitalWrite (driverDIR, HIGH);
       // Executando "revolution" passos:
       digitalWrite(driverDIR, HIGH);
       digitalWrite(driverPUL, HIGH);
       delayMicroseconds(speed);
       digitalWrite(driverPUL, LOW);
       delayMicroseconds(speed);
       count = count + 1;
     }
    }
    count = 0; */

  //PRETO
  if (redValue <= 100 && greenValue <= 70 && blueValue <= 70) {
    for (int count = 0; count <= revolution * 20; count++) {
      digitalWrite(driverDIR, HIGH);
      digitalWrite(driverPUL, HIGH);
      delayMicroseconds(speed);
      digitalWrite(driverPUL, LOW);
      delayMicroseconds(speed);
    }
  }
  //PRETO
  if (redValue_2 <= 100 && greenValue_2 <= 70 && blueValue_2 <= 70) {
    for (int count = 0; count <= revolution * 20; count++) {
      digitalWrite(driverDIR, LOW);
      digitalWrite(driverPUL, HIGH);
      delayMicroseconds(speed);
      digitalWrite(driverPUL, LOW);
      delayMicroseconds(speed);
    }
  }
}
// Function to read Red Pulse Widths
int getRedPW() {

  // Set sensor to read Red only
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);

  // Return the value
  return PW;
}

int getRedPW_2() {

  // Set sensor to read Red only
  digitalWrite(S2_2, LOW);
  digitalWrite(S3_2, LOW);

  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut_2, LOW);

  // Return the value
  return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
  // Set sensor to read Green only
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);

  // Return the value
  return PW;
}

// Function to read Green Pulse Widths
int getGreenPW_2() {
  // Set sensor to read Green only
  digitalWrite(S2_2, HIGH);
  digitalWrite(S3_2, HIGH);

  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut_2, LOW);

  // Return the value
  return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {

  // Set sensor to read Blue only
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);

  // Return the value
  return PW;
}

int getBluePW_2() {

  // Set sensor to read Blue only
  digitalWrite(S2_2, LOW);
  digitalWrite(S3_2, HIGH);

  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut_2, LOW);

  // Return the value
  return PW;
}
