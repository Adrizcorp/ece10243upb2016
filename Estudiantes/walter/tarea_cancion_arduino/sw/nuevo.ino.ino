
#define c4 0
#define d4 1
#define e4 2
#define f4 3
#define g4 4
#define a4 5
#define b4 6
#define c5 7
#define d5 8
#define e5 9
#define f5 10
#define g5 11
#define a5 12
#define b5 13

#define SILENCE 255
void set_output(unsigned char in)
{
  switch (in){
    case 1:
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
    break;
    case 2:
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
    break;
    case 3:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
    break;
    case 4:
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
    break;
    case 5:
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
    break;
    case 6:
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
    break;
    case 7:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
    break;
    case 8:
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
    break;
    case 9:
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
    break;
    case 10:
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
    break;
    case 11:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
    break;
    case 12:
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
    break;
    case 13:
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
    break;
    default:
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
    break;
  }
}


void setup() {
  
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
 

  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");
}

;
  


void loop() {
  set_output(a4);
  delay(500);
  set_output(SILENCE);
  delay(10);
  set_output(a4);
  delay(500);
  set_output(SILENCE);
  delay(10);
  set_output(a4);
  delay(500);
  set_output(SILENCE);
  delay(10);
  set_output(f4);
  delay(350);
  set_output(SILENCE);
  delay(10);
  set_output(c5);
  delay(150);
  set_output(SILENCE);
  delay(10);
  set_output(a4);
  delay(500);
  set_output(SILENCE);
  delay(10);
  set_output(f4);
  delay(350);
  set_output(SILENCE);
  delay(10);
  set_output(c5);
  delay(150);
  set_output(SILENCE);
  delay(10);
  set_output(a4);
  delay(1000);
  set_output(SILENCE);
  delay(10);
  set_output(e5);
  delay(500);
  set_output(SILENCE);
  delay(10);
  set_output(e5);
  delay(500);
  set_output(SILENCE);
  delay(10);
  set_output(e5);
  delay(500);
  set_output(SILENCE);
  delay(10);
  set_output(f5);
  delay(350);
  set_output(SILENCE);
  delay(10);
  set_output(c5);
  delay(150);
  set_output(SILENCE);
  delay(10);
  set_output(g4);
  delay(500);
  set_output(SILENCE);
  delay(10);
  set_output(f4);
  delay(350);
  set_output(SILENCE);
  delay(10);
  set_output(c5);
  delay(150);
  set_output(SILENCE);
  delay(10);
  set_output(a4);
  delay(1000);
  set_output(SILENCE);
  delay(10);
  
  
}
