int length = 74; // the number of notes
char notes[] = "bshhsbaggabbaabshhsbaggabagg abgabsbgabsbagadbshhsbaggabagg "; // a space represents a rest
int beats[] = { 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3,1,4,4,2,2,2,2,2,2,2,2,2,2,3,1,4,2,4,2,2,2,1,1,2,2,2,1,1,2,2,2,2,4,4,2,2,2,2,2,2,2,2,2,2,3,1,4,4};
int tempo = 100;
//do sostenido es s, re sostenido es h, fa sostenido es t
//sol sostenido es y, la sostenido es u
void playTone(int tones) {
  switch (tones){
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

//do sostenido es s, re sostenido es h, fa sostenido es t
//sol sostenido es y, la sostenido es u
void playNote(char note) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b','s','h','t','y','u', 'C',' '};
  int tones[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

  // play the tone corresponding to the note name
  for (int i = 0; i < 14; i++) {
    if (names[i] == note) {
      playTone(tones[i]);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < length; i++) {    
    playNote(notes[i]);
    // pause between notes
    delay(beats[i] * tempo); 
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(tempo); 
  }
}
