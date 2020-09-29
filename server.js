// server.js
// where your node app starts

const express = require("express");
const app = express();

app.use(express.static("public"));

app.get("/", (request, response) => {
  response.sendFile(__dirname + "/views/index.html");
});

// listen for requests :)
const listener = app.listen(process.env.PORT, () => {
  console.log("Application Port" + listener.address().port);
});

const bluetooth = require('node-bluetooth');
const device = new bluetooth.DeviceINQ();
device.listPairedDevices(console.log);
