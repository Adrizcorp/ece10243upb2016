
#define DO 0
#define RE 1
#define MI 2
#define FA 3
#define SOL 4
#define LA 5
#define SI 6
#define DO2 7
#define SILENCE 255
void set_output(unsigned char in)
{
  int i=0;  
  int corriemiento=0;
  for(i=8; i==15; i++){
      corriemiento = (1<<(i-8));
       digitalWrite(i, in & corriemiento );
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
  set_output(SILENCE);

  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");
}

void loop() {
  set_output(DO);
  delay(400);
  set_output(RE);
  delay(400);
  set_output(MI);
  delay(400);
  set_output(FA);
  delay(400);
  set_output(SOL);
  delay(400);
  set_output(LA);
  delay(400);
  set_output(SI);
  delay(400);
  set_output(DO2);
  delay(400);
}
