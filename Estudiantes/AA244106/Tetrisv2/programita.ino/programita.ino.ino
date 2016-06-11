#define mus 80
#define pau 112

void setup() {
  //bits en forma de pines
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  //se inicializan en silencio
  digitalWrite(8, 1);
  digitalWrite(9, 1);
  digitalWrite(10, 1);
  digitalWrite(11, 1);
}

void loop() {
  // notas de la canción
E(4); B(2); C(2); D(2); E(1); D(1); C(2); B(2);
A(4); A(2); C(2); E(4); D(2); C(2); B(2); E(2); B(2); C(2); D(4); E(4); C(4); A(4); A(2); A(2); B(2); C(2);
D(2); D(4); f(2); A(2); A(1); A(1); G(2); f(2); E(6); C(2); E(2); f(1); E(1); D(2); C(2);
B(4); B(2); C(2); D(4); E(4); C(4); A(4); A(8);
}


//funciones de cada nota
void C(int duracion) { //0
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  delay(duracion*mus);
  sil(duracion);
}

void D(int duracion) { //1
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  delay(duracion*mus);
  sil(duracion);
}

void E(int duracion) { //2
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  delay(duracion*mus);
  sil(duracion);
}

void f(int duracion) { //3
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  delay(duracion*mus);
  sil(duracion);
}

void G(int duracion) { //4
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  delay(duracion*mus);
  sil(duracion);
}

void A(int duracion) { //5
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  delay(duracion*mus);
  sil(duracion);
}

void B(int duracion) { //6
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  delay(duracion*mus);
  sil(duracion);
}

void C_(int duracion) { //7
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  delay(duracion*mus);
  sil(duracion);
}

void A_(int duracion) { //11
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  delay(duracion*mus);
  sil(duracion);
}

void sil(int espera) {
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  delay(espera*pau);
}

