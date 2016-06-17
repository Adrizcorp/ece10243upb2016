#define Ab4 0
#define A4 1
#define B4 2
#define C5 3
#define E5 4
#define Ab5 5
#define A5 6
#define B5 7
#define D5 8
#define C6 9
#define D6 10
#define E6 11
#define F6 12
#define G6 13
#define A6 14
#define SINAU 255

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
        case 14:
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
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

void loop() {
    set_output(E5);
  delay(125);
  set_output(E6);
  delay(500);
  set_output(B5);
  delay(250);
  set_output(C6);
  delay(250);
  set_output(D6);
  delay(250);  
  set_output(E6);
  delay(125);  
  set_output(D6);
  delay(125);  
  set_output(C6);
  delay(250);
  set_output(B5);
  delay(250);
  set_output(A5);
  delay(500);
  set_output(A5);
  delay(250);
  set_output(C6);
  delay(250);
  set_output(E6);
  delay(500);
  set_output(D6);
  delay(250);
  set_output(C6);
  delay(250);
  set_output(B5);
  delay(750);
  set_output(C6);
  delay(250);
  set_output(D6);
  delay(500);
  set_output(E6);
  delay(500);
  set_output(C6);
  delay(500);
  set_output(A5);
  delay(500);
  set_output(A5);
  delay(500);
  set_output(SINAU); 
  delay(250);
  set_output(D6);
  delay(500);
  set_output(F6);
  delay(250);
  set_output(A6);
  delay(500);
  set_output(G6);
  delay(250);
  set_output(F6);
  delay(250);
  set_output(E6);
  delay(750);
  set_output(C6);
  delay(250);
  set_output(E6);
  delay(500);
  set_output(D6);
  delay(250);
  set_output(C6);
  delay(250);
  set_output(B5);
  delay(500);
  set_output(B5);
  delay(250);
  set_output(C6);
  delay(250);
  set_output(D6);
  delay(500);
  set_output(E6);
  delay(500);
  set_output(C6);
  delay(500);
  set_output(A5);
  delay(500);
  set_output(A5);
  delay(500);
  set_output(SINAU); 
  delay(500);
  set_output(E6);
  delay(500);
  set_output(B5);
  delay(250);
  set_output(C6);
  delay(250);
  set_output(D6);
  delay(250);
  set_output(E6);
  delay(125);
  set_output(D6);
  delay(125);
  set_output(C6);
  delay(250);
  set_output(B5);
  delay(250);
  set_output(A5);
  delay(500);
  set_output(A5);
  delay(250);
  set_output(C6);
  delay(250);
  set_output(E6);
  delay(500);
  set_output(D6);
  delay(250);
  set_output(C6);
  delay(250);
  set_output(B5);
  delay(750);
  set_output(C6);
  delay(250);
  set_output(D6);
  delay(500);
  set_output(E6);
  delay(500);
  set_output(C6);
  delay(500);
  set_output(A5);
  delay(500);
  set_output(A5);
  delay(500);
  set_output(SINAU); 
  delay(250);
  set_output(D6);
  delay(500);
  set_output(F6);
  delay(250);
  set_output(A6);
  delay(500);
  set_output(G6);
  delay(250);
  set_output(F6);
  delay(250);
  set_output(E6);
  delay(750);
  set_output(C6);
  delay(250);
  set_output(E6);
  delay(500);
  set_output(D6);
  delay(250);
  set_output(C6);
  delay(250);
  set_output(B5);
  delay(500);
  set_output(B5);
  delay(250);
  set_output(C6);
  delay(250);
  set_output(D6);
  delay(500);
  set_output(E6);
  delay(500);
  set_output(C6);
  delay(500);
  set_output(A5);
  delay(500);
  set_output(A5);
  delay(500);
  set_output(SINAU);   
  delay(500);
  set_output(E5);
  delay(1000);
  set_output(C5);
  delay(1000);
  set_output(D5);
  delay(1000);
  set_output(B4);
  delay(1000);
  set_output(C5);
  delay(1000);
  set_output(A4);
  delay(1000);
  set_output(Ab4);
  delay(1000);
  set_output(B4);
  delay(1000);
  set_output(E5);
  delay(1000);
  set_output(C5);
  delay(1000);
  set_output(D5);
  delay(1000);
  set_output(B4);
  delay(1000);
  set_output(C5);
  delay(500);
  set_output(E5);
  delay(500);
  set_output(A5);
  delay(1000);
  set_output(A5);
  delay(2000);
  set_output(E5);
  delay(1000);
  set_output(C5);
  delay(1000);
  set_output(D5);
  delay(1000);
  set_output(B4);
  delay(1000);
  set_output(C5);
  delay(1000);
  set_output(A4);
  delay(1000);
  set_output(Ab4);
  delay(1000);
  set_output(B4);
  delay(1000);
  set_output(E5);
  delay(1000);
  set_output(C5);
  delay(1000);
  set_output(D5);
  delay(1000);
  set_output(B4);
  delay(1000);
  set_output(C5);
  delay(500);
  set_output(E5);
  delay(50);
  set_output(A5);
  delay(1000);
  set_output(Ab5);
  delay(2000);
}

