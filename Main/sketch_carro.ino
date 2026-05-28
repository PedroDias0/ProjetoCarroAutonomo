#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// ===== ULTRASSÓNICO FRENTE =====
#define TRIG_FRENTE 13
#define ECHO_FRENTE 34

// ===== ULTRASSÓNICO DIREITA =====
#define TRIG_DIR 12
#define ECHO_DIR 35

// ===== ULTRASSÓNICO ESQUERDA =====
#define TRIG_ESQ 17
#define ECHO_ESQ 16

int distanciaParar = 25;
int distanciaLateral = 12;

// ===== SENSORES IR =====
#define SENSOR_LINHA_ESQ 4
#define SENSOR_LINHA_DIR 15
#define LINHA_PRETA HIGH

// ===== DRIVER ESQUERDO =====
#define IN1 25
#define IN2 26
#define IN3 27
#define IN4 14
#define ENA 33
#define ENB 32

// ===== DRIVER DIREITO =====
#define IN5 18
#define IN6 19
#define IN7 21
#define IN8 22
#define ENC 23
#define END 5

int rapido = 200;
bool primeiroObstaculo = true;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_CARRO");

  pinMode(TRIG_FRENTE, OUTPUT);
  pinMode(ECHO_FRENTE, INPUT);
  pinMode(TRIG_DIR, OUTPUT);
  pinMode(ECHO_DIR, INPUT);
  pinMode(TRIG_ESQ, OUTPUT);
  pinMode(ECHO_ESQ, INPUT);

  pinMode(SENSOR_LINHA_ESQ, INPUT);
  pinMode(SENSOR_LINHA_DIR, INPUT);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT); pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT); pinMode(IN8, OUTPUT);

  ledcAttach(ENA, 1000, 8);
  ledcAttach(ENB, 1000, 8);
  ledcAttach(ENC, 1000, 8);
  ledcAttach(END, 1000, 8);

  parar();
  delay(1000);
}

void loop() {
  autonomo();
}

long medirDistancia(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duracao = pulseIn(echo, HIGH, 30000);

  if (duracao == 0) return 999;

  long distancia = duracao * 0.034 / 2;

  if (distancia < 5) return 999;
  if (distancia > 300) return 999;

  return distancia;
}

void autonomo() {
  long frenteDist = medirDistancia(TRIG_FRENTE, ECHO_FRENTE);
  delay(40);
  long direitaDist = medirDistancia(TRIG_DIR, ECHO_DIR);
  delay(40);
  long esquerdaDist = medirDistancia(TRIG_ESQ, ECHO_ESQ);
  delay(40);

  int linhaEsq = digitalRead(SENSOR_LINHA_ESQ);
  int linhaDir = digitalRead(SENSOR_LINHA_DIR);

  Serial.print("F: ");
  Serial.print(frenteDist);
  Serial.print(" | E: ");
  Serial.print(esquerdaDist);
  Serial.print(" | D: ");
  Serial.print(direitaDist);
  Serial.print(" | IR_E: ");
  Serial.print(linhaEsq);
  Serial.print(" | IR_D: ");
  Serial.print(linhaDir);
  Serial.print(" | Primeiro: ");
  Serial.println(primeiroObstaculo);

  if (linhaEsq == LINHA_PRETA && linhaDir != LINHA_PRETA) {
    parar();
    delay(100);
    tras();
    delay(200);
    direita();
    delay(300);
    parar();
    delay(100);
  }

  else if (linhaDir == LINHA_PRETA && linhaEsq != LINHA_PRETA) {
    parar();
    delay(100);
    tras();
    delay(200);
    esquerda();
    delay(300);
    parar();
    delay(100);
  }

  else if (linhaEsq == LINHA_PRETA && linhaDir == LINHA_PRETA) {
    frente();
  }

  else if (frenteDist <= distanciaParar) {
    parar();
    delay(150);
    tras();
    delay(300);
    parar();
    delay(100);

    if (primeiroObstaculo) {
      esquerda();
      delay(850);
      primeiroObstaculo = false;
    } else {
      if (esquerdaDist > direitaDist) {
        esquerda();
        delay(850);
      } else {
        direita();
        delay(850);
      }
    }

    parar();
    delay(100);
  }

  else if (esquerdaDist <= distanciaLateral) {
    direita();
    delay(250);
    parar();
    delay(50);
  }

  else if (direitaDist <= distanciaLateral) {
    esquerda();
    delay(250);
    parar();
    delay(50);
  }

  else {
    frente();
  }
}

void velEsquerda(int v) {
  ledcWrite(ENA, v);
  ledcWrite(ENB, v);
}

void velDireita(int v) {
  ledcWrite(ENC, v);
  ledcWrite(END, v);
}

void esquerdaFrente() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void esquerdaTras() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void direitaFrente() {
  digitalWrite(IN5, HIGH); digitalWrite(IN6, LOW);
  digitalWrite(IN7, HIGH); digitalWrite(IN8, LOW);
}

void direitaTras() {
  digitalWrite(IN5, LOW); digitalWrite(IN6, HIGH);
  digitalWrite(IN7, LOW); digitalWrite(IN8, HIGH);
}

void frente() {
  velEsquerda(rapido);
  velDireita(rapido);
  esquerdaFrente();
  direitaFrente();
}

void tras() {
  velEsquerda(rapido);
  velDireita(rapido);
  esquerdaTras();
  direitaTras();
}

void direita() {
  velEsquerda(rapido);
  velDireita(rapido);
  esquerdaTras();
  direitaFrente();
}

void esquerda() {
  velEsquerda(rapido);
  velDireita(rapido);
  esquerdaFrente();
  direitaTras();
}

void parar() {
  velEsquerda(0);
  velDireita(0);

  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  digitalWrite(IN5, LOW); digitalWrite(IN6, LOW);
  digitalWrite(IN7, LOW); digitalWrite(IN8, LOW);
}