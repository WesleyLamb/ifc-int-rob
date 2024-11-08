// Projeto 30: Robo que acompanha uma linha

#define lights 9
int LDR1, LDR2, LDR3; // valores dos sensores

// deslocamentos (offsets) de calibração 
int leftOffset = 0, rightOffset = 0 , centre = 0;

// pinos para a velocidade e direção do motor 
int speed1 = 3, speed2 = 11, direction1 = 12, direction2 = 13;

// velocidade inicial e deslocamento da rotação
int startSpeed = 70, rotate = 30;

// limiar do sensor
int threshold = 5;

// velocidades iniciais dos motores esquerdo e direito
int left = startSpeed, right = startSpeed;

// Rotina de calibração do sensor
void calibrate() {

  // executa 10 vezes, para obter uma média
  for (int x = 0; x < 10; x++) { 
    // acende as luzes
    digitalWrite(lights, HIGH); 

    delay(100);

    // lê os 3 sensores
    LDR1 = analogRead(0);
    LDR2 = analogRead(1);
    LDR3 = analogRead(2);

    leftOffset = leftOffset + LDR1; // adiciona o valor do sensor da esquerda ao total 
    centre = centre + LDR2; // adiciona o valor do sensor do centro ao total
    rightOffset = rightOffset + LDR3; // adiciona o valor do sensor da direita ao total

    delay(100);
    digitalWrite(lights, LOW); // apaga as luzes
    delay(100);
  }

  // obtém a média para cada sensor
  leftOffset = leftOffset / 10;
  rightOffset = rightOffset / 10;
  centre = centre / 10;

  // calcula os deslocamentos para os sensores esquerdo e direito
  leftOffset = centre - leftOffset;
  rightOffset = centre - rightOffset;
}

void setup() {

  // define os pinos dos motores como saldas
  pinMode(lights, OUTPUT); // luzes
  pinMode(speed1, OUTPUT);
  pinMode(speed2, OUTPUT);
  pinMode(direction1, OUTPUT);
  pinMode(direction2, OUTPUT);

  // calibra os sensores
  calibrate();
  delay(3000);
  digitalWrite(lights, HIGH); // acende as luzes 
  delay(100);

  // define a direção do motor para frente
  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, HIGH);

  // define a velocidade de ambos os motores
  analogWrite(speed1, left);
  analogWrite(speed2, right);
}

void loop() {

  // utiliza a mesma velocidade em ambos os motores
  left = startSpeed;
  right = startSpeed;

  // lé os sensores e adiciona os deslocamentos
  LDR1 = analogRead(0) + leftOffset;
  LDR2 = analogRead(1);
  LDR3 = analogRead(2) + rightOffset;

  // se LDR1 for maior do que o sensor do centro limiar, vire para a direita
  if (LDR1 > (LDR2+threshold)) {
    left = startSpeed + rotate;
    right = startSpeed - rotate;
  }

  // se LDR3 for maior do que o sensor do centro limiar, vire para a esquerda
  if (LDR3 > (LDR2+threshold)) { 
    left = startSpeed - rotate;
    right = startSpeed + rotate;
  }

  // Envia os valores de velocidade para os motores
  analogWrite(speed1, left);
  analogWrite(speed2, right);
}