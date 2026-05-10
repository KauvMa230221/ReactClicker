const int buttonOrangePin = 21;
const int buttonRedPin = 19;

int counter = 0;

void setup() {
  Serial.begin(115200);

  pinMode(buttonOrangePin, INPUT);
  pinMode(buttonRedPin, INPUT);
}

void loop() {
  int orange = digitalRead(buttonOrangePin);
  int red = digitalRead(buttonRedPin);

  if (orange == HIGH || red == HIGH) {
    counter++;

    // Daten als JSON senden
    Serial.print("{\"score\":");
    Serial.print(counter);
    Serial.println("}");
    
    delay(300); // Entprellen + Spam vermeiden
  }
}