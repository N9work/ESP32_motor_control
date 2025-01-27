#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

int led_G = 18;
int led_O = 19;
int led_R = 21;

const int freq = 5000;
const int bit = 8;

int Status;
const char* ssid = "Switch";
const char* password = "12345678";

WebServer server(80);

void Control_Page() {
  // HTML go tee nee na ja
  String html = R"rawliteral(
<!DOCTYPE html>
<html>

<head>

    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <title>Light Toggle</title>
</head>

<style>
    /* From Uiverse.io by varoonrao */ 
.checkbox-con {
 margin: 10px;
 display: center;
 align-items: center;
 color: white;
}

.checkbox-con input[type="checkbox"] {
 appearance: none;
 width: 48px;
 height: 27px;
 border: 2px solid #ff0000;
 border-radius: 20px;
 background: #f1e1e1;
 position: relative;
 box-sizing: border-box;
}

.checkbox-con input[type="checkbox"]::before {
 content: "";
 width: 14px;
 height: 14px;
 background: rgba(234, 7, 7, 0.5);
 border: 2px solid #ea0707;
 border-radius: 50%;
 position: absolute;
 top: 0;
 left: 0;
 transform: translate(13%, 15%);
 transition: all 0.3s ease-in-out;
}

.checkbox-con input[type="checkbox"]::after {
 position: absolute;
 top: 0;
 left: 20px;
}

.checkbox-con input[type="checkbox"]:checked {
 border: 2px solid #02c202;
 background: #e2f1e1;
}

.checkbox-con input[type="checkbox"]:checked::before {
 background: rgba(2, 194, 2, 0.5);
 border: 2px solid #02c202;
 transform: translate(133%, 13%);
 transition: all 0.3s ease-in-out;
}

.checkbox-con input[type="checkbox"]:checked::after {
 position: absolute;
 top: 5px;
 left: 5px;
}

.checkbox-con label {
 margin-left: 10px;
 cursor: pointer;
 user-select: none;
 align-items: center;
}
html,body{
    height: 100%;
    margin:0;
    display: grid;
    place-content: center;
    align-items: center;
    background-color: aquamarine;
}

</style>
<body style="text-align: center;">
    <h1 style="color:black;">Light Toggle wibwub</h1>
    <h1>แดง</h1>
    <div class="checkbox-con">
        <input id="Red_toggle" type="checkbox">
    </div>
    <h1>ส้ม</h1>
    <div class="checkbox-con">
        <input id="Orange_toggle" type="checkbox">
    </div>
    <h1>เขว</h1>
    <div class="checkbox-con">
        <input id="Green_toggle" type="checkbox">
    </div>
    <script>
        document.getElementById("Red_toggle").addEventListener("change", function (e) {
            fetch(`/Red_toggle?State=${e.target.checked ? 1 : 0}`);
        });

        document.getElementById("Orange_toggle").addEventListener("change", function (e) {
            fetch(`/Orange_toggle?State=${e.target.checked ? 1 : 0}`);
        });

        document.getElementById("Green_toggle").addEventListener("change", function (e) {
            fetch(`/Green_toggle?State=${e.target.checked ? 1 : 0}`);
        });
    </script>
</body>

</html>

  )rawliteral";
  server.send(200, "text/html", html);
}
void Red_toggle() {
  if (server.hasArg("State")) {
    int state = server.arg("State").toInt();
    if (state == 1) {
      for (int fade = 0; fade <= 255; fade++) {
        ledcWrite(led_R, fade);  // ควบคุม LED สีแดง
        delay(1);
      }
    } else {
      for (int fade = 255; fade >= 0; fade--) {
        ledcWrite(led_R, fade);
        delay(1);
      }
    }
    server.send(200, "text/plain", "OK");
  }
}
void Orange_toggle() {
  if (server.hasArg("State")) {
    int state = server.arg("State").toInt();
    if (state == 1) {
      for (int fade = 0; fade <= 255; fade++) {
        ledcWrite(led_O, fade);  // ควบคุม LED สีแดง
        delay(1);
      }
    } else {
      for (int fade = 255; fade >= 0; fade--) {
        ledcWrite(led_O, fade);
        delay(1);
      }
    }
    server.send(200, "text/plain", "OK");
  }
}

void Green_toggle() {
  if (server.hasArg("State")) {
    int state = server.arg("State").toInt();
    if (state == 1) {
      for (int fade = 0; fade <= 255; fade++) {
        ledcWrite(led_G, fade);  // ควบคุม LED สีแดง
        delay(1);
      }
    } else {
      for (int fade = 255; fade >= 0; fade--) {
        ledcWrite(led_G, fade);
        delay(1);
      }
    }
    server.send(200, "text/plain", "OK");
  }
}


void setup() {
    // ตั้งพินเด้อ
    ledcAttach(led_R, freq, bit);
    // ตั้งพินเด้อ

    ledcAttach(led_O, freq, bit);
    // ตั้งพินเด้อ
    ledcAttach(led_G, freq, bit);

    // ตั้งให้ตัวบอร์ดเป็นตัวกระจาย wifi(Access Point)
    WiFi.softAP(ssid, password);
    Serial.println("Access Point Created Laew");
    Serial.print("IP ADDRESS: ");
    Serial.println(WiFi.softAPIP());  //show ip address in serial:)

    // เอาฟังก์ชั่นที่สร้างมาเข้ามาในเว็บ
    server.on("/", Control_Page);
    server.on("/Red_toggle", Red_toggle);
    server.on("/Orange_toggle", Orange_toggle);
    server.on("/Green_toggle", Green_toggle);

    server.begin();
}

void loop() {
    server.handleClient();
}
