//definition
var BLE_DEVICE_NAME = "TRANSLATOR MASK";

window.SpeechRecognition = window.webkitSpeechRecognition || window.SpeechRecognition;
const recognition = new window.SpeechRecognition();

var inputText = document.getElementById("inputText");
var outputText = document.getElementById("outputText");

var srcLan = "ja";
var dstLan = "en";

//setup
recognition.lang = 'ja-JP';
recognition.interimResults = true;
recognition.continuous = true;

//for GAS translation
var url = "https://script.google.com/macros/s/AKfycbzpaJ6qzfcVPRaYbyw6___w_eIBSbPLwJyM0AkNhR0neS4WjI8/exec";
function translate(data) {
  fetch(url, {
    method: "POST",
    body: JSON.stringify(data),
  })
  .then((res) => {
    if(res.ok){
      return res.text();
    }else{
      console.error(res.status);
    }
  }).then((result) => {
    var data = result.slice(10,-1);
    outputText.textContent = JSON.parse(data).message;
  }).catch((err) => console.error(err));
}

//this event will be called when speech finish
recognition.onresult = (event) => {
  for(var i = 0; i < event.results[0].length; i++){
     inputText.textContent = event.results[0][i].transcript;
  }
  
  var text = inputText.textContent;
  var data = {message: text, souce:srcLan, target:dstLan};
  translate(data);
}

//main function start
recognition.start();
