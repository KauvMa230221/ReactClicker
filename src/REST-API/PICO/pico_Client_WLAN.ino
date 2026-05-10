#include <WiFi.h>


// TCP-Verbindung kombiniert mit der Spielelogik:

// WLAN-Daten
const char* ssid = "DEIN_WLAN";
const char* password = "DEIN_PASSWORT";

// Server-IP (dein PC!)
const char* server = "192.168.0.100";

WiFiClient client;

// Pins
const int buttonOrangePin = 21;
const int ledOrangePin = 20;

const int buttonRedPin = 19;
const int ledRedPin = 18;

const int blueLED_Pin = 16;

// Zustände
int buttonOrangeState = 0;
int buttonRedState = 0;

// Timer
unsigned long lastCycle = 0;
unsigned long lastSend = 0;

bool blueOn = false;
unsigned long blueStart = 0;

int counter = 0;

void setup() {
  Serial.begin(115200);

  pinMode(ledOrangePin, OUTPUT);
  pinMode(buttonOrangePin, INPUT);

  pinMode(ledRedPin, OUTPUT);
  pinMode(buttonRedPin, INPUT);

  pinMode(blueLED_Pin, OUTPUT);

  // WLAN verbinden
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Verbinde WLAN...");
  }

  Serial.println("WLAN verbunden!");
}

void loop() {

  // Buttons lesen
  buttonOrangeState = digitalRead(buttonOrangePin);
  buttonRedState = digitalRead(buttonRedPin);

  // LEDs folgen Buttons
  digitalWrite(ledOrangePin, buttonOrangeState);
  digitalWrite(ledRedPin, buttonRedState);

  unsigned long now = millis();

  // 🟦 Spiel-Logik (alle 5 Sekunden startet ein 3s Fenster)
  if (!blueOn && now - lastCycle >= 5000) {
    blueOn = true;
    blueStart = now;
    lastCycle = now;

    digitalWrite(blueLED_Pin, HIGH);
    Serial.println("GO!");
  }

  // Während blau an ist → prüfen ob gedrückt
  if (blueOn) {

    // Wenn Button gedrückt → Punkt
    if (buttonOrangeState == HIGH || buttonRedState == HIGH) {
      counter++;
      Serial.print("Treffer! Score: ");
      Serial.println(counter);

      blueOn = false;
      digitalWrite(blueLED_Pin, LOW);
    }

    // Nach 3 Sekunden automatisch aus
    if (now - blueStart >= 3000) {
      blueOn = false;
      digitalWrite(blueLED_Pin, LOW);
      Serial.println("Zeit vorbei!");
    }
  }

  // 🌐 Alle 5 Sekunden Daten an Server senden
  if (now - lastSend >= 5000) {
    lastSend = now;

    if (client.connect(server, 3000)) {

      String url = "/update?orange=" + String(buttonOrangeState) +
                   "&red=" + String(buttonRedState) +
                   "&score=" + String(counter);

      client.println("GET " + url + " HTTP/1.1");
      client.println("Host: " + String(server));
      client.println("Connection: close");
      client.println();

      Serial.print("Gesendet: ");
      Serial.println(url);

    } else {
      Serial.println("Server nicht erreichbar");
    }

    client.stop();
  }
}