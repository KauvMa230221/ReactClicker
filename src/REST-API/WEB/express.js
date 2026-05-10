
// Verbesserte Version:
const express = require("express");
const { SerialPort } = require("serialport");
const { ReadlineParser } = require("@serialport/parser-readline");

const app = express();

//let currentData = { score: 0 };
let currentData = {
  scoreOrange: 0,
  scoreRed: 0,
};

let port = null;
let parser = null;

// 🔍 Funktion zum Verbinden
function connectSerial() {
  console.log("Versuche Serial-Verbindung...");

  try {
    port = new SerialPort({
      path: "COM4", // anpassen!
      baudRate: 115200,
      autoOpen: false, // ❗ wichtig
    });

    port.open((err) => {
      if (err) {
        console.log("Kein Gerät gefunden:", err.message);
        return;
      }

      console.log("Serial verbunden!");

      parser = port.pipe(new ReadlineParser({ delimiter: "\n" }));

      /*parser.on("data", line => {
        try {
          const data = JSON.parse(line);
          currentData = data;
          console.log("Empfangen:", data);
        } catch {
          console.log("Ungültige Daten:", line);
        }
      });*/
      parser.on("data", (line) => {
        try {
          const data = JSON.parse(line);

          currentData.scoreOrange = data.scoreOrange;
          currentData.scoreRed = data.scoreRed;

          console.log("Orange:", data.scoreOrange);
          console.log("Red:", data.scoreRed);
        } catch {
          console.log("Fehler:", line);
        }
      });

      port.on("close", () => {
        console.log("Serial getrennt!");
      });
    });
  } catch (e) {
    console.log("Fehler beim Öffnen:", e.message);
  }
}

// 🔁 Versuche alle 3 Sekunden neu zu verbinden
setInterval(() => {
  if (!port || !port.isOpen) {
    connectSerial();
  }
}, 3000);

// 🌐 API
app.get("/data", (req, res) => {
  res.json(currentData);
});

// 🌐 Webseite
app.get("/", (req, res) => {
  res.sendFile(__dirname + "/index.html");
});

// 🚀 Server starten
app.listen(3000, () => {
  console.log("Server läuft auf http://localhost:3000");
});
