//Observação: 

//MOTOR DE PASSO (DIREÇÃO)
#define dirPin 21
#define pulsoPin 20
#define pulsosPorRevolution 200

//SENSORES ULTRASSONICOS
#define trigPin1 2
#define echoPin1 3
#define trigPin2 4
#define echoPin2 5
#define trigPin3 8
#define echoPin3 9
#define trigPin4 10 //E
#define echoPin4 11 //E
#define trigPin5 12 //D
#define echoPin5 13 //D
//SENSOR ULTRASSONICO NOVO
#define trig6 13  //Pino 9 do Arduino será a saída de trigger
#define echo6 12 //Pino 8 do Arduino será a entrada de echo
void trigPulse();  //Função que gera o pulso de trigger
float pulse;     //Variável que armazena o tempo de duração do echo
float dist_cm;   //Variável que armazena o valor da distância em centímetros

long duration, DistanciaCM, FRENTE1, FRENTE2, FRENTE3, DIREITA, ESQUERDA, FRENTE4;

//RELES
int buzina = 23; // VAZIO | IN1
int vazio = 37; // BUZINA | IN2
int tras = 29; // (Marcha) TRAS | IN3
int frente = 27; // (Marcha) FRENTE | IN4

//Variaveis
//boolean status1 = false;

void setup()
{
  Serial.begin(9600);

  //RELES
  pinMode(frente, OUTPUT);
  pinMode(tras, OUTPUT);
  pinMode(buzina, OUTPUT);
  pinMode(vazio, OUTPUT);

  //SENSORES
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(trigPin5, OUTPUT);
  pinMode(echoPin5, INPUT);

  //Motor de passo
  pinMode(pulsoPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  /* Condições iniciais */
  //LOW = ACIONAR || HIGH = DESATIVAR
  digitalWrite(frente, HIGH); // DESLIGADO
  digitalWrite(tras, HIGH);   // DESLIGADO
  digitalWrite(buzina, HIGH); // DESLIGADO
  digitalWrite(vazio, HIGH);  // DESLIGADO

  //sensor novo
  pinMode(trig6, OUTPUT);   //Pino de trigger será saída digital
  pinMode(echo6, INPUT);    //Pino de echo será entrada digital
  digitalWrite(trig6, LOW); //Saída trigger inicia em nível baixo

  
  //INICIALIZAÇAO TEMPO
  delay(2000);
}

void loop()
{
  SensorUltra(trigPin1, echoPin1);
  FRENTE1 = DistanciaCM;
  SensorUltra(trigPin2, echoPin2);
  FRENTE2 = DistanciaCM;
  SensorUltra(trigPin3, echoPin3);
  FRENTE3 = DistanciaCM;
  
  trigPulse();                 //Aciona o trigger do módulo ultrassônico
  pulse = pulseIn(echo6, HIGH, 200000); //Mede o tempo em que o pino de echo fica em nível alto
  dist_cm = pulse/58.82;       //Valor da distância em centímetros 
  FRENTE4 = dist_cm;
  
  // 340m/s
  // 34000cm/s
  /*
       100000 us - 17000 cm/s
            x us - 1cm
          1E6
     x = -----
         17E3
  */ 
  Serial.println(dist_cm);     //Imprime o valor na serial
delay (200);
  Serial.print("MEIO: ");
  Serial.print(FRENTE1);
  Serial.print(" | ");
  Serial.print("ESQUERDA: ");
  Serial.print(FRENTE2);
  Serial.print(" | ");
  Serial.print("DIRETA: ");
  Serial.println(FRENTE3);

  condicaoFRENTE();
}

void SensorUltra(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  DistanciaCM = (duration / 2) / 29.1;
  /*
    Divide-se por dois porque sai e volta, pelo que o tempo seria o dobro do de uma viagem de ida. O 29,1
    é a velocidade do som (que é 343,5 m/s => 1 / 0,03435 = 29,1). Portanto, note-se que o resultado é em
    CM, não em polegadas. Provavelmente, poderia descobrir o resultado olhando para a folha de dados do
    sensor ou simplesmente obter muitas amostras relativas à duração da distância (medir-se-ia a distância
    manualmente) e obter uma equação que é muito semelhante.
  */
  //CONDIÇÕES - obs: 250 cm é o maximo que o sensor ultra consegue ler.
}

void condicaoFRENTE() { //GERAL
  if (FRENTE1 <= 150 || FRENTE2 <= 100 || FRENTE3 <= 100 || FRENTE4 <= 100 ) {
    //Serial.println("DETECTOU ALGO NA FRENTE"); //AVISAR
    digitalWrite(frente, HIGH); //STOP
    digitalWrite(tras, LOW);
  } else {
    digitalWrite(tras, HIGH);
    digitalWrite(frente, LOW); //IR PARA FRENTE(ACELERAR)
  }
}

void trigPulse()
{
  digitalWrite(trig6, HIGH);  //Pulso de trigger em nível alto
  delayMicroseconds(10);     //duração de 10 micro segundos
  digitalWrite(trig6, LOW);   //Pulso de trigge em nível baixo
}
