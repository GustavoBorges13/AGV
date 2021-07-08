/*usar define para dar um nome a um valor constante. Como por exemplo, ao mencionar dirPin, o compilador irá substituir todas as referencias a esta constante pelo valor que eu definir
  que no caso são os pinos, exemplo o pino 5 (CLK+). */
#define dirPin 5 // CW- >> 5  || Este é o controle da direção. Para ser usado deve se inserir o digitalWrite(pulsoPin, "HiGH ou LOW"); HIGH = SENTIDO ... , LOW = SENTIDO...
#define pulsoPin 6 // CLK-/CLK >> 7   || Este é os dados do pulsos que controla a velocidade da rotação. Altere os dados "delayMicroseconds(Valor);", sendo que o valor minimo é de
//1000 delayMicroseconds podendo ser usado até os 900 (menor que isso pode haver ruidos mais altos e faz com que o motor de passo nao funcione corretamente -> não gira) e o valor máximo é
//de aproximadamente 25000 delayMicroseconds, se for mais do que isso pode haver variações de velocidade e /ruído.
#define pulsosPorRevolution 200 // Aqui é a quantidades de pulsos que o motor dá 1 ciclo completo.


//Definindo a pinagem do relé
const int FRENTE (7);
const int RE (8);
const int buzina (4);
const int rele4sobrando (4);
const int IR = 9;

void setup() {
  // Declarando os pinos do motor de passo (saidas)
  pinMode(pulsoPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(FRENTE, OUTPUT);
  pinMode(RE, OUTPUT);
  pinMode(buzina, OUTPUT);
  pinMode(rele4sobrando, OUTPUT);
  pinMode(IR, INPUT);

  //condição inicial dos reles.
  //digitalWrite(FRENTE, HIGH);
  digitalWrite(RE, HIGH);
  digitalWrite(buzina, HIGH);
  digitalWrite(rele4sobrando, HIGH);

}


void loop() {
  if (digitalRead(IR) == HIGH) { //SENSOR DESLIGADO
    digitalWrite(FRENTE, LOW); {
      delayMicroseconds(3000);
    }
  } else {
    (digitalRead(IR) != HIGH); { //SENSOR LIGADO
      digitalWrite(FRENTE, HIGH); //VEICULO PARA
      delay(1000);
    }
  }
}
/*digitalWrite(dirPin, HIGH);
  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < pulsosPorRevolution; i++) {
  // These four lines result in 1 step:
  digitalWrite(pulsoPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(pulsoPin, LOW);
  delayMicroseconds(1000);
  }

  delay(2000);

  // Set the spinning direction counterclockwise:
  digitalWrite(dirPin, LOW);

  // Spin the stepper motor 1 revolution quickly:
  for (int i = 0; i < pulsosPorRevolution; i++) {
  // These four lines result in 1 step:
  digitalWrite(pulsoPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(pulsoPin, LOW);
  delayMicroseconds(1000);
  }

  delay(2000);
  }*/
/*digitalWrite(FRENTE, LOW); {
  delay(3000);
  }
  digitalWrite(FRENTE, HIGH);
  delay(2000);
  digitalWrite(RE, HIGH); {
  delay(3000);
  }
  digitalWrite(RE, LOW);
  delay(2000);
  }*/
