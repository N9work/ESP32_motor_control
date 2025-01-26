#include <WiFi.h>
#include <WebServer.h>

// voltage
#define R_ENA 32
#define L_ENB 14

//motor L
#define MR_IN1 27
#define MR_IN2 26

//motor R
#define ML_IN3 25
#define ML_IN4 33

int spA = 255;
int spB = 255;

const char* ssid = "";          // เปลี่ยนเป็นชื่อ Wi-Fi ของคุณ
const char* password = "12345678";  // เปลี่ยนเป็นรหัสผ่าน Wi-Fi ของคุณ

// สร้างเซิร์ฟเวอร์
WebServer server(80);

void handleRoot() {
  // HTML หน้าเว็บสำหรับควบคุมมอเตอร์
  String html = R"rawliteral(
<!DOCTYPE html>
<html
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no" >
    <link href="https://fonts.cdnfonts.com/css/8bit-wonder"rel="stylesheet">
   
   
    <style>
        .arrows {
            font-size: 65px;
            color: AliceBlue;
        }

        .circularArrows {
            font-size: 80px;
            color: Cornsilk;
        }

        td {
            background-color: rgb(252, 155, 9);
            border-radius: 35%;
            box-shadow: 5px 5px #aa3e04;
        }

        td:active {
            transform: translate(5px, 5px);
            box-shadow: none;
        }

        .noselect {
            -webkit-touch-callout: none;
            -webkit-user-select: none;
            -khtml-user-select: none;
            -moz-user-select: none;
            -ms-user-select: none;
            user-select: none;
            touch-action: manipulation;
        }
        .card {
        background-color: #5aa8a7;
        padding: 4px;
        border-radius: 25px;
        box-shadow: 0 12px 20px rgba(0, 0, 0, 0.2);
        max-width: 500px;
        margin: auto;
        }
        body{
        background-image: url(https://m.media-amazon.com/images/I/61RvZIDo-uL.jpg);
        background-size: cover;
        background-repeat: no-repeat;
        -webkit-background-size: 100%;
        -moz-background-size: 100%;
        -o-background-size: 100%;
        background-size: 100% 100%;
        }
        font{
            font-family: '8BIT WONDER', sans-serif;
        }
    </style>
</head>

<body class="noselect" align="center">
    <h1 style="color: rgb(252, 20, 20);text-align:center;font-family: '8BIT WONDER';">AGV &#127942;&#127949;&#127950;&#128168;  </h1>
    <h2 style="color: rgb(252, 20, 20);text-align:center;font-family: '8BIT WONDER';font-size: 20px"> Web Controller &#128377;&#128377; </h2>
    <h3 style="color: rgb(76, 23, 250);text-align:center;font-family: '8BIT WONDER'">Wi-Fi &#128732; Mode</h2>

    <h4 style="color: rgb(255, 0, 0);text-align:center;font-family: '8BIT WONDER'">&#128677; LET'S GOO!</h4>
    <div class="card">
        <table id="mainTable" style="width:330px;margin:auto;table-layout:fixed;" CELLSPACING=15>
            <tr>
                <td></td>
                <td ontouchstart="fetch('/forward')" ontouchend="fetch('/stop')"><span class="arrows">&#8679;</span></td>
                <td </td>
            </tr>
            <tr>
                <td ontouchstart="fetch('/left')" ontouchend="fetch('/stop')"><span class="arrows">&#8678;</span></td>
                <td style="background-color:white;box-shadow:none"><span class="arrows"> &#128526;</span></td>
                <td ontouchstart="fetch('/right')" ontouchend="fetch('/stop')"><span class="arrows">&#8680;</span></td>
            </tr>
            <tr>
                <td </td>
                <td ontouchstart="fetch('/backward')" ontouchend="fetch('/stop')"><span class="arrows">&#8681;</span></td>
                <td </td>
            </tr>
        
        </table>
</body>    
</html>
  )rawliteral";
  server.send(200, "text/html", html);
}

void forward() {
  analogWrite(R_ENA, spB);
  digitalWrite(MR_IN1, 1);
  digitalWrite(MR_IN2, 0);

  // wheel R
  analogWrite(L_ENB, spA);
  digitalWrite(ML_IN3, 1);
  digitalWrite(ML_IN4, 0);
}
void backward() {
  analogWrite(R_ENA, spB);
  digitalWrite(MR_IN1, 0);
  digitalWrite(MR_IN2, 1);

  // wheel R
  analogWrite(L_ENB, spA);
  digitalWrite(ML_IN3, 0);
  digitalWrite(ML_IN4, 1);
}
void left() {
  analogWrite(R_ENA, spB);
  digitalWrite(MR_IN1, 1);
  digitalWrite(MR_IN2, 0);

  // wheel R
  analogWrite(L_ENB, spA);
  digitalWrite(ML_IN3, 0);
  digitalWrite(ML_IN4, 1);
}
void right() {
  analogWrite(R_ENA, spB);
  digitalWrite(MR_IN1, 0);
  digitalWrite(MR_IN2, 1);

  // wheel R
  analogWrite(L_ENB, spA);
  digitalWrite(ML_IN3, 1);
  digitalWrite(ML_IN4, 0);
}
void stop() {
  analogWrite(R_ENA, spB);
  digitalWrite(MR_IN1, 0);
  digitalWrite(MR_IN2, 0);

  // wheel R
  analogWrite(L_ENB, spA);
  digitalWrite(ML_IN3, 0);
  digitalWrite(ML_IN4, 0);
}

void setup() {
  Serial.begin(115200);

  pinMode(R_ENA, OUTPUT);
  pinMode(L_ENB, OUTPUT);

  pinMode(MR_IN1, OUTPUT);
  pinMode(MR_IN2, OUTPUT);
  pinMode(ML_IN3, OUTPUT);
  pinMode(ML_IN4, OUTPUT);

  // ตั้งค่า ESP32 เป็น Access Point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Created!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // ตั้งค่าการทำงานของ Web Server
  server.on("/", handleRoot);     // หน้าเว็บหลัก
  server.on("/forward", forward); // เดินหน้า
  server.on("/backward", backward); // ถอยหลัง
  server.on("/left", left); // ถอยหลัง
  server.on("/right", right); // ถอยหลัง
  server.on("/stop", stop); // ถอยหลัง

  server.begin(); // เริ่มต้น Web Server
  Serial.println("Web Server Started!");
}

void loop() {
  // delay(2000);
  server.handleClient(); 
}

