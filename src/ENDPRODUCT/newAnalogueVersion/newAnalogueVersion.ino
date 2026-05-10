const int buttonOrangePin = 21;
const int buttonRedPin = 19;
const int blueLED_Pin = 16;

int counterPlayer1 = 0;
int counterPlayer2 = 0;

void setup() {
  Serial.begin(115200);

  // PullUp bedeutet: Der Zustand ist standardmäßig 1, wenn gedrückt wird 0 (Logik ist also invers)
  pinMode(buttonOrangePin, INPUT_PULLUP);  // wichtig!
  pinMode(buttonRedPin, INPUT_PULLUP);     // wichtig!
  pinMode(blueLED_Pin, OUTPUT);
}

void loop() {

  /*bool orangePressed = false;
  bool redPressed = false;*/

  // Starte Runde
  digitalWrite(blueLED_Pin, HIGH);
  Serial.println("GO!");
  bool winnerfound = false;

  unsigned long startTime = millis();

  // ⏱ 3 Sekunden Zeitfenster
  while (millis() - startTime < 3000 && !winnerfound) {

    int orange = digitalRead(buttonOrangePin);
    int red = digitalRead(buttonRedPin);


    // Das elseif ist WICHTIG, weil dadurch sichergestellt wird das immer nur einer den Punkt bekommt.

    if (orange == LOW) { // INPUT_PULLUP → LOW = gedrückt
      counterPlayer1++;
      winnerfound = true;
    }

    else if (red == LOW) { // INPUT_PULLUP → LOW = gedrückt
      counterPlayer2++;
      winnerfound = true;
    }
  }

  // 🌐 JSON senden
  Serial.print("{\"scoreOrange\":");
  Serial.print(counterPlayer1);
  Serial.print(",\"scoreRed\":");
  Serial.print(counterPlayer2);
  Serial.println("}");

  // 🔵 LED aus
  digitalWrite(blueLED_Pin, LOW);
  Serial.println("Pause...");

  // ⏳ 5 Sekunden Pause
  delay(5000);
}