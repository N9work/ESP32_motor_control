#include <Arduino.h>

const int G = 18;
const int R = 21;
const int O = 19;
const int freq = 5000;
const int bit = 8;


void setup() {
 
  ledcAttach(G,freq,bit);  //เซ็ตค่าให้เป็นanalog(pinที่ใช้,ความถี่,บิต)
  ledcAttach(R,freq,bit);
  ledcAttach(O,freq,bit);

}

void loop() {
  Green(); //เรียกฟังก์ชั่นที่พึ่งสร้าง :)
  Orange();
  Red();
}
void  Green(){

    //for(ค่าเริ่มต้น,จุดสิ้นสุด,จำนวนการเพิ่มครั้งละ +หรือ-)
  for(int fade = 0;fade<=255;fade ++){
    ledcWrite(18,fade);
    delay(10); //ดีเลย์ค่าจนกว่าจะครบลูปfor
  }
  delay(500);

  for(int fade = 255;fade>=0;fade --){
    ledcWrite(18,fade);
    delay(10);
  }
  delay(500);
}
void  Orange(){
   
  for(int fade = 0;fade<=255;fade ++){
    ledcWrite(19,fade);
    delay(10); 
  }
  delay(500);

  for(int fade = 255;fade>=0;fade --){ 
    ledcWrite(19,fade);
    delay(10);
  }
  delay(1000);
}
void  Red(){

  for(int fade = 0;fade<=255;fade ++){
    ledcWrite(21,fade);
    delay(10);
  }
  delay(1000);

  for(int fade = 255;fade>=0;fade --){
    ledcWrite(21,fade);
    delay(10);
  }
  delay(1000);
}
