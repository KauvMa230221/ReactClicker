const express = require("express");
const cors = require("cors");
const { SerialPort } = require("serialport");
const { ReadlineParser } = require("@serialport/parser-readline");

const app = express();
const PORT = 3001;

app.use(cors());
app.use(express.json());


const port = new SerialPort({
  path: "COM3", 
  baudRate: 115200,
});

const parser = port.pipe(new ReadlineParser({ delimiter: "\n" }));

let latestResult = null;

// Listen for Arduino response
parser.on("data", (data) => {
  console.log("Arduino Response:", data);
  latestResult = data.trim();
});

// Start reaction game
app.post("/start", (req, res) => {
  latestResult = null;

  port.write("START\n", (err) => {
    if (err) {
      return res.status(500).json({ error: "Failed to start Arduino" });
    }

    res.json({ message: "Game started" });
  });
});

// Get latest result
app.get("/result", (req, res) => {
  if (latestResult) {
    res.json({ reactionTime: latestResult });
  } else {
    res.json({ reactionTime: null });
  }
});

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});