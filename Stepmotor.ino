/*usar define para dar um nome a um valor constante. Como por exemplo, ao mencionar dirPin, o compilador irá substituir todas as referencias a esta constante pelo valor que eu definir
  que no caso são os pinos, exemplo o pino 5 (CLK+). */
#define dirPin 5 // CW- >> 5  || Este é o controle da direção. Para ser usado deve se inserir o digitalWrite(pulsoPin, "HiGH ou LOW"); HIGH = SENTIDO ... , LOW = SENTIDO...
#define pulsoPin 6 // CLK-/CLK >> 7   || Este é os dados do pulsos que controla a velocidade da rotação. Altere os dados "delayMicroseconds(Valor);", sendo que o valor minimo é de
//1000 delayMicroseconds podendo ser usado até os 900 (menor que isso pode haver ruidos mais altos e faz com que o motor de passo nao funcione corretamente -> não gira) e o valor máximo é
//de aproximadamente 25000 delayMicroseconds, se for mais do que isso pode haver variações de velocidade e /ruído.
#define pulsosPorRevolution 400 // Aqui é a quantidades de pulsos que o motor dá 1 ciclo completo.

//400 steps = 360°
// 1° = 1,111111111111111 stepsmotors
//90° = 100 steps
double grau = 1.111111111111111;

void setup() {
  // Declarando os pinos do motor de passo (saidas)
  pinMode(pulsoPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
//16000
  digitalWrite(dirPin, HIGH);
  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < grau * 1080; i++) { //incrementa de 1 em 1 até que chegue no angulo/rotação desejado... 1grau * (o angulo para girar).
    // These four lines result in 1 step:
    digitalWrite(pulsoPin, HIGH);
    delayMicroseconds(900);
    digitalWrite(pulsoPin, LOW);
    delayMicroseconds(900);
  }
  delay(2000);
  digitalWrite(dirPin, HIGH);
  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < grau * 1080; i++) { //incrementa de 1 em 1 até que chegue no angulo/rotação desejado... 1grau * (o angulo para girar).
    // These four lines result in 1 step:
    digitalWrite(pulsoPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(pulsoPin, LOW);
    delayMicroseconds(2000);
  }
  delay(2000);
  digitalWrite(dirPin, HIGH);
  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < grau * 720; i++) { //incrementa de 1 em 1 até que chegue no angulo/rotação desejado... 1grau * (o angulo para girar).
    // These four lines result in 1 step:
    digitalWrite(pulsoPin, HIGH);
    delayMicroseconds(10000);
    digitalWrite(pulsoPin, LOW);
    delayMicroseconds(10000);
  }
  delay(2000);
  digitalWrite(dirPin, HIGH);
  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < grau * 360; i++) { //incrementa de 1 em 1 até que chegue no angulo/rotação desejado... 1grau * (o angulo para girar).
    // These four lines result in 1 step:
    digitalWrite(pulsoPin, HIGH);
    delayMicroseconds(15000);
    digitalWrite(pulsoPin, LOW);
    delayMicroseconds(15000);
  }
  delay(2000);
  digitalWrite(dirPin, HIGH);
  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < grau * 720; i++) { //incrementa de 1 em 1 até que chegue no angulo/rotação desejado... 1grau * (o angulo para girar).
    // These four lines result in 1 step:
    digitalWrite(pulsoPin, HIGH);
    delayMicroseconds(5000);
    digitalWrite(pulsoPin, LOW);
    delayMicroseconds(5000);
  }
  delay(2000);
}
 /* digitalWrite(dirPin, LOW);
  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < grau * 180; i++) {
    // These four lines result in 1 step:
    digitalWrite(pulsoPin, HIGH);
    delayMicroseconds(900);
    digitalWrite(pulsoPin, LOW);
    delayMicroseconds(900);
  }
  delay(2000);
} */
