#include <AFMotor.h>

// Inicializa os motores
AF_DCMotor motorEsquerdo(4); // Motor esquerdo conectado ao M4
AF_DCMotor motorDireito(3);  // Motor direito conectado ao M3

// Define os pinos dos sensores de linha
const int sensorEsquerdo = 0;  // Sensor esquerdo no pino digital 2
const int sensorMeio = 1;      // Sensor central no pino digital 3
const int sensorDireito = 2;   // Sensor direito no pino digital 4

// Define a velocidade dos motores
const int VELOCIDADE_NORMAL = 150; // Velocidade padrão
const int VELOCIDADE_CURVA_INF = 75;  // Velocidade ajustada para curvas
const int VELOCIDADE_CURVA_SUP = 200;  // Velocidade ajustada para curvas
const int limitadorAnalogico = 500;

#define SEGUINDO_RETO 0
#define VIRANDO_DIREITA 1
#define VIRANDO_ESQUERDA 2
int ultimoEstado = SEGUINDO_RETO;

void setup() {
  delay(3000);
  // Configura os pinos dos sensores como entrada
  pinMode(sensorEsquerdo, INPUT);
  pinMode(sensorMeio, INPUT);
  pinMode(sensorDireito, INPUT);

  // Inicializa a comunicação serial para depuração
  Serial.begin(9600);
//  Serial.println("Carrinho Seguidor de Linha Iniciado");
}

void loop() {
  // Lê os valores dos sensores
  int leituraEsquerdo = analogRead(sensorEsquerdo);
  int leituraMeio = analogRead(sensorMeio);
  int leituraDireito = analogRead(sensorDireito);

  // Depuração
  Serial.print("E: ");
  Serial.print(leituraEsquerdo);
  Serial.print(" | M: ");
  Serial.print(leituraMeio);
  Serial.print(" | D: ");
  Serial.println(leituraDireito);

  // Controle do carrinho  
  if (leituraMeio > limitadorAnalogico) {
    // Linha preta detectada pelo sensor do meio
    ultimoEstado = SEGUINDO_RETO;
    andarFrente();
  } else if (leituraEsquerdo > limitadorAnalogico) {
    // Linha preta detectada pelo sensor esquerdo
    ultimoEstado = VIRANDO_ESQUERDA;
    curvaEsquerda();
  } else if (leituraDireito > limitadorAnalogico) {
    // Linha preta detectada pelo sensor direito
    ultimoEstado = VIRANDO_DIREITA;
    curvaDireita();
  } else {
    switch (ultimoEstado) {
      case SEGUINDO_RETO:
        andarFrente();
        break;
      case VIRANDO_ESQUERDA:
        curvaEsquerda();
        break;
      case VIRANDO_DIREITA:
        curvaDireita();
        break; 
    }
    
    // Nenhum sensor detecta a linha preta
//    parar();
  }

  delay(50); // Pequena pausa para leitura estável dos sensores
}

void andarFrente() {
  motorEsquerdo.setSpeed(VELOCIDADE_NORMAL);
  motorDireito.setSpeed(VELOCIDADE_NORMAL);
  motorEsquerdo.run(FORWARD);
  motorDireito.run(BACKWARD);
}

void curvaEsquerda() {
  motorEsquerdo.setSpeed(VELOCIDADE_CURVA_INF); // Aumenta a velocidade da roda esquerda
  motorDireito.setSpeed(VELOCIDADE_CURVA_SUP); // Mantém a velocidade da roda direita
  motorEsquerdo.run(FORWARD);
  motorDireito.run(BACKWARD);
}

void curvaDireita() {
  motorEsquerdo.setSpeed(VELOCIDADE_CURVA_SUP); // Mantém a velocidade da roda esquerda
  motorDireito.setSpeed(VELOCIDADE_CURVA_INF);  // Aumenta a velocidade da roda direita
  motorEsquerdo.run(FORWARD);
  motorDireito.run(BACKWARD);
}

void parar() {
  motorEsquerdo.run(RELEASE);
  motorDireito.run(RELEASE);
}
