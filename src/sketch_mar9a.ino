const int buttonOrangePin = 21;  // Orange
const int ledOrangePin = 20;    // Orange

const int buttonRedPin = 19; // Red
const int ledRedPin = 18; // Red

const int blueLED_Pin = 16; 

// variables will change:
int buttonOrangeState = 0;  // Orange
int buttonRedState = 0;  // Red


void setup() {
  // Orange
  pinMode(ledOrangePin, OUTPUT);
  pinMode(buttonOrangePin, INPUT);

  // Red
  pinMode(ledRedPin, OUTPUT);
  pinMode(buttonRedPin, INPUT);

  // Blue:
  pinMode(blueLED_Pin, OUTPUT);

  // Für Kommandozeilenausgabe:
  Serial.begin(115200);
}

void loop() {
  // read the state of the pushbutton value:
  buttonOrangeState = digitalRead(buttonOrangePin);
  buttonRedState = digitalRead(buttonRedPin);

  digitalWrite(ledOrangePin, buttonOrangeState);
  digitalWrite(ledRedPin, buttonRedState);

  /*
  // Orange:
  if (buttonOrangeState == HIGH) {
    // turn LED on:
    digitalWrite(blueLED_Pin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(blueLED_Pin, LOW);  // Schaltet nicht komplett aus (Warum?)
  }

  // Red:
  if (buttonRedState == HIGH) {
    // turn LED on:
    digitalWrite(blueLED_Pin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(blueLED_Pin, LOW); // Schaltet nicht komplett aus (Warum?)
  }*/



  unsigned long startTime = millis();
  int counter = 0;

  // Wiederhole das Ganze insgesamt 15 Sekunden lang
  while (true) {

    // LED an für 3 Sekunden
    digitalWrite(blueLED_Pin, HIGH);
    delay(3000);

  
    if(buttonOrangeState == HIGH || buttonRedState == HIGH){
      digitalWrite(blueLED_Pin, HIGH);
      counter++;
      Serial.println(counter);
    }


    // LED aus für 5 Sekunden
    digitalWrite(blueLED_Pin, LOW);
    delay(5000);
  }

  // Nach 15 Sekunden sicher ausschalten
  digitalWrite(blueLED_Pin, LOW);

  // Stoppt das Programm dauerhaft
  while (true) {
  }
}

// TODO: Create the connection to the Rest-API