/* Programação para controlar o Motor de Passo NEMA 42 com Driver 2DM2280.
   Projeto: AGV (Veículo Guiado Automaticamente)
   Parceria: HPE Automotores Ltda do Brasil / Unidade Integrada SESI SENAI Catalão
   Gestão: Sr. Edenilson Ducatti, Sra. Luzia Juana, Sr. André Machado e Sra. Aliana Dias e Arley Gon.
   Corpo Técnico: Arley Gonçalves, Alcione Borges, Bruna Lays, Maycon Lima, Edir Macedo, Gustavo Borges e Gabriel Henrique.
*/

// Define os pinos do sensor de cor:
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Calibração dos valores:
// Obtenha esses no esboço de calibração BRANCO/PRETO na programação "Calibracao_Sensor".
int redMin = 13; // Red minimum value
int redMax = 186; // Red maximum value
int greenMin = 13; // Green minimum value
int greenMax = 190; // Green maximum value
int blueMin = 12; // Blue minimum value
int blueMax = 152; // Blue maximum value

// Variáveis para medições de largura de pulso de cor:
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

// Variáveis para valores finais de cor:
int redValue;
int greenValue;
int blueValue;

// Cálculo:
// 360º/400 passos = 0,9º
// 1 PASSO EQUIVALE A 0,9 GRAUS
// Define os pinos do motor:
int driverPUL = 3;
int driverDIR = 2;

// Variáveis para execução do motor de passo:
int count = 0;                   //  Contador de passos
// boolean setdir = LOW;            // Altera o sentido | HIGH --> sentido anti-horário and LOW --> sentido horário
float rotacao = 0.125;               // Define a quantidade de rotações do motor | Regra de três: Exemplo: Para girar 90º - Dividimos 90/360 = 0.25
double revolution = 400 * rotacao; // Precisão escolhida na configuração do Driver
int speed = 1000;                // Velocidade do motor: valores menores --> velocidade maior | valores maiores --> velocidade menor

int buzzer = 22;

#define indutivo 10

// Funções:
void setup() {
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Sensor Indutivo
  pinMode (indutivo, INPUT_PULLUP);

  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

  // Set Frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Setup Serial Monitor
  Serial.begin(38400);

  // Definindo as portas do arduino como saídas:
  pinMode (driverPUL, OUTPUT);
  pinMode (driverDIR, OUTPUT);

  pinMode(buzzer, OUTPUT);
}

void step() {
  // Definindo 1 passo:
  digitalWrite(driverPUL, HIGH);
  delayMicroseconds(speed);
  digitalWrite(driverPUL, LOW);
  delayMicroseconds(speed);
}

void loop() {
  // Ler valor do vermelho:
  redPW = getRedPW();
  // Mapa - valores de 0-255
  redValue = map(redPW, redMin, redMax, 255, 0);
  // Delay para estabilizar o sensor:
  delay(200);

  // Ler valor do verde:
  greenPW = getGreenPW();
  // Mapa - valores de 0-255
  greenValue = map(greenPW, greenMin, greenMax, 255, 0);
  // Delay para estabilizar o sensor:
  delay(200);

  // Ler valor vermelho
  bluePW = getBluePW();
  // Mapa - valores de 0-255
  blueValue = map(bluePW, blueMin, blueMax, 255, 0);
  // Delay para estabilizar o sensor:
  delay(200);

  // Print output to Serial Monitor
  Serial.print(" Red = ");
  Serial.print(redValue);
  Serial.print(" Green = ");
  Serial.print(greenValue);
  Serial.print(" Blue = ");
  Serial.println(blueValue);

  //Green: VERDE VERDE VERDE VERDE VERDE VERDE VERDE VERDE VERDE
  if (redValue <= 100 && greenValue >= 150 && blueValue <= 120) {
    while (count <= revolution) {
      digitalWrite (driverDIR, HIGH);
      // Executando "revolution" passos:
      step();
      count = count + 1;
    }
    delay (2000);
    while (digitalRead(indutivo) == LOW) {
      digitalWrite (driverDIR, LOW);
      // Executando "revolution" passos:
      step();
    }
  }
  count = 0;

  //Vermelho: VERMELHO VERMELHO VERMELHO VERMELHO VERMELHO VERMELHO
  if (redValue >= 150 && greenValue <= 120 && blueValue <= 120) {
    while (count <= revolution) {
      digitalWrite (driverDIR, LOW);
      // Executando "revolution" passos:
      step();
      count = count + 1;
    }
    delay (2000);
    while (digitalRead(indutivo) == LOW) {
      digitalWrite (driverDIR, HIGH);
      // Executando "revolution" passos:
      step();
    }
  }
  count = 0;
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
