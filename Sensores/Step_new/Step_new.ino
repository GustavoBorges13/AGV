/* Programação para controlar o Motor de Passo NEMA 42 com Driver 2DM2280.
   Projeto: AGV (Veículo Guiado Automaticamente)
   Parceria: HPE Automotores Ltda do Brasil / Unidade Integrada SESI SENAI Catalão
   Gestão: Sr. Edenilson Ducatti, Sra. Luzia Juana, Sr. André Machado e Sra. Aliana Dias e Arley Gon.
   Corpo Técnico: Arley Gonçalves, Alcione Borges, Bruna Lays, Maycon Lima, Edir Macedo, Gustavo Borges e Gabriel Henrique.
*/
//LEGENDA://
// int = conversão (número inteiro)
// boolean = tipo de dados
// float = conversão (número quebrado)
// double = tipo de dados
// void setup = tipo de dados
// setup = sketch
// pinMode = entradas e saídas digitais
// loop = sketch
// digitalWrite = entradas e saídas digitais
// delayMicroseconds = funções temporizadoras
// if = estruturas de controle
// else = estruturas de controle

// Cálculo:
// 360º/400 passos = 0,9º 
// 1 PASSO EQUIVALE A 0,9 GRAUS

// Defining pins:
int driverPUL = 3; 
int driverDIR = 2;

// Variables:
int count = 0;                        // Contador de passos
boolean setdir = LOW;                // HIGH --> sentido anti-horário and LOW --> sentido horário
float revolutions = 1.0;              // Define a quantidade de revoluções --> rotações do motor
double revolution = 400*revolutions;  // Precisão escolhida no Driver
int speed = 2500;                     // Velocidade do motor, valores menores --> velocidade maior
                                      //valores maiores --> velocidade menor            
// Functions
void setup() {
  // Definindo as portas do arduino como saídas:
  pinMode (driverPUL,OUTPUT);
  pinMode (driverDIR,OUTPUT);
}

void step(){
  // Definindo 1 passo:
  digitalWrite(driverDIR,setdir);
  digitalWrite(driverPUL,HIGH);
  delayMicroseconds(speed);
  digitalWrite(driverPUL,LOW);
  delayMicroseconds(speed);
}

void loop() {
  // Executando "revolution" passos:
  step();
  if (count>=revolution){exit(0);} //condição verdadeira
  else {count = count + 1;}       // Condição falsa --> conta os passos de 1 em 1 
}
