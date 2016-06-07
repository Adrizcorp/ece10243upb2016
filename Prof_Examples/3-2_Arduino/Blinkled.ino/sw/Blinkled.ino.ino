
void setup() {
  // set up the LCD's number of columns and rows:
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(8, 0);
  digitalWrite(9, 0);
  digitalWrite(10, 0);

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");
}

void loop() {
   
  digitalWrite(9, !digitalRead(9));
  Serial.println("Hola Dindos\n");
  delay(100);
}
