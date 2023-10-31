const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" type="text/css" href="styles.css"> <!-- 在styles.css文件中定义样式 -->
</head>
<body>
  <h1>ESP8266 NodeMCU Web Server Controlled Servo Motor</h1>
  <br><br>
  <div class="slidecontainer">
    <input type="range" min="220" max="400" value="310" class="slider" id="myRange">
    <p>PWM signal: <span id="demo"></span></p>
    <br><br>
    <div class="buttons">
      <button class="btn" data-status="1">Stop</button>
      <button class="btn" data-status="2">Forward</button>
      <button class="btn" data-status="3">Downward</button>
      <button class="btn" data-status="4">CW Rotation</button>
      <button class="btn" data-status="5">CCW Rotation</button>
      <button class="btn" data-status="6">Test Mode</button>
      <button class="btn" data-status="7">Task 1</button>
    </div>
    <label><span id="isiStatusSER1"></span></label>
  </div>
  
  <script src="script.js"></script> <!-- 引用单独的JavaScript文件 -->
</body>
</html>

<script>
document.addEventListener("DOMContentLoaded", function() {
  var slider = document.getElementById("myRange");
  var output = document.getElementById("demo");
  var buttons = document.querySelectorAll(".btn");

  output.innerHTML = slider.value;

  slider.addEventListener("input", function() {
    output.innerHTML = this.value;
    sendData(this.value);
  });

  buttons.forEach(function(button) {
    button.addEventListener("click", function() {
      var status = this.getAttribute("data-status");
      sendData2(status);
    });
  });

  function sendData(pos) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        console.log(this.responseText);
      }
    };
    xhttp.open("GET", "setPOS?servoPOS=" + pos, true);
    xhttp.send();
  }

  function sendData2(status) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("isiStatusSER1").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "setSER1?;SERstate1=" + status, true);
    xhttp.send();
  }
});
</script>
     <br><br><br><br>
     
     

  </body>

</html>
)=====";