
#define DO 0
#define RE 1
#define MI 2
#define FA 3
#define SOL 4
#define LA 5
#define SI 6
#define SOLs 7
#define LAs 8
#define DOh 9
#define DOsh 10
#define REsh 11
#define MIh 12
#define FAh 13
#define REh 14
#define SOLh 15
#define SOLsh 16
#define LAh 17
#define FAsh 18
#define SILENCE 255
void set_output(unsigned char in)
{
  int i=0;  
  int corriemiento=0;
  for(i=8; i==25; i++){
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
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  
  set_output(SILENCE);

  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");
}

void loop() {
  set_output(FA);
  delay(250);
  set_output(SOLs);
  delay(500);
  set_output(FA);
  delay(350);
  set_output(LA);
  delay(125);
  set_output(DOh);
  delay(500);
  set_output(LA);
  delay(375);
  set_output(DOh);
  delay(125);
  set_output(MIh);
  delay(650);
  
  delay(500);
 
  set_output(FA);
  delay(250);
  set_output(SOLs);
  delay(500);
  set_output(FA);
  delay(350);
  set_output(DOh);
  delay(500);
  set_output(LA);
  delay(375);
  set_output(FA);
  delay(250);
  set_output(DOh);
  delay(500);
  set_output(LA);
  delay(375);
  delay(650);

  set_output(LA);
  delay(500);
  set_output(LA);
  delay(500);
  set_output(LA);
  delay(500);
  set_output(FA);
  delay(350);
  set_output(DOh);
  delay(150);
  set_output(LA);
  delay(500);
  set_output(FA);
  delay(350);
  set_output(DOh);
  delay(150);
  set_output(LA);
  delay(650);
  delay(500);

  set_output(MIh);
  delay(500);
  set_output(MIh);
  delay(500);
  set_output(MIh);
  delay(500);
  set_output(FAh);
  delay(350);
  set_output(DOh);
  delay(150);
  set_output(SOLs);
  delay(500);
  set_output(FA);
  delay(350);
  set_output(DOh);
  delay(150);
  set_output(LA);
  delay(650);
  delay(500);
  set_output(LAh);
  delay(500);
  set_output(LA);
  delay(300);
  set_output(LA);
  delay(150);
  set_output(LAh);
  delay(500);
  set_output(SOLsh);
  delay(325);
  set_output(SOLh);
  delay(175);
  set_output(FAsh);
  delay(125);
  set_output(FAh);
  delay(125);
  set_output(FAsh);
  delay(250);
  
  delay(325);

  
  set_output(LAs);
  delay(250);
  set_output(REsh);
  delay(500);
  set_output(REh);
  delay(325);
  set_output(DOsh);
  delay(175);
  set_output(DOh);
  delay(125);
  set_output(SI);
  delay(125);
  set_output(DOh);
  delay(250);

   delay(350);

 
  
  
  
    

  
}
