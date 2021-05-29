//al_belov tpms reader for mca t.me/al_belov with f-mods help =)


#include <splash.h>
#include <can.h>
#include <mcp2515.h>
#include <Wire.h>
#include <SPI.h>

#include <Adafruit_GFX.h> 
//#include <Adafruit_SSD1306.h> //ligrary for Arduino // Библиотека экрана для платы arduino на чипе atmega 
#include <ESP_SSD1306.h> //this library for ESP8266 and others, for atmega328 use prev //библиотека экрана для esp8266
#define OLED_RESET                      16
ESP_SSD1306 display(OLED_RESET);




float fl = 0; //front left tire pressure //переменная давления в левом переднем колесе
float fr = 0; //ront right //в правом переднем
float rr = 0; //rear right // правом заднем
float rl = 0; //rear left  // левом заднем
float a1; // a1-b4 - служебные пеерменные для формулы, если кто-то хочет сделать код короче, можете использовать меньше, но мне и так сойдет
float b1;
float a2;
float b2;
float a3;
float b3;
float a4;
float b4;
struct can_frame canMsg1; //
struct can_frame canMsg2;
struct can_frame canMsg3;
struct can_frame canMsg4;
struct can_frame canans;
MCP2515 mcp2515(D3);                 // SPI CS Pin D3  //куда подключен CS пин преобразователя
 



void setup()   
{                
  
  SPI.begin();                       //инициализируем связь по протоколу SPI
  Serial.begin(9600);                //инициализируем последовательную связь со скоростью 9600 бод 
  
  mcp2515.reset();                          
  mcp2515.setBitrate(CAN_125KBPS,MCP_8MHZ); //устанавливаем скорость CAN 125 кбит/с и частоту кварца 8 МГц //set can speed and quartz oscillator frequency
  mcp2515.setConfigMode();
  mcp2515.setFilterMask(MCP2515::MASK0, false, 0x7FF); //masks work with this lib only like this, don't ask me why //маски работают только так с этой библиотекой, не спрашивайте, почему
  mcp2515.setFilter(MCP2515::RXF0, false, 0x72E);
  mcp2515.setFilter(MCP2515::RXF1, false, 0x72E);
  mcp2515.setFilterMask(MCP2515::MASK1, false, 0x7FF);
  mcp2515.setFilter(MCP2515::RXF2, false, 0x72E);
  mcp2515.setFilter(MCP2515::RXF3, false, 0x72E);
  mcp2515.setFilter(MCP2515::RXF4, false, 0x72E);
  mcp2515.setFilter(MCP2515::RXF5, false, 0x72E);
  mcp2515.setNormalMode();
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); // Указываем адрес дисплея //set display address
  
  canMsg1.can_id  = 0x726; 
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x03;
  canMsg1.data[1] = 0x22;
  canMsg1.data[2] = 0x28;
  canMsg1.data[3] = 0x13;
  canMsg1.data[4] = 0x00;
  canMsg1.data[5] = 0x00;
  canMsg1.data[6] = 0x00;
  canMsg1.data[7] = 0x00;

  canMsg2.can_id  = 0x726;
  canMsg2.can_dlc = 8;
  canMsg2.data[0] = 0x03;
  canMsg2.data[1] = 0x22;
  canMsg2.data[2] = 0x28;
  canMsg2.data[3] = 0x14;
  canMsg2.data[4] = 0x00;
  canMsg2.data[5] = 0x00;
  canMsg2.data[6] = 0x00;
  canMsg2.data[7] = 0x00;

  canMsg3.can_id  = 0x726;
  canMsg3.can_dlc = 8;
  canMsg3.data[0] = 0x03;
  canMsg3.data[1] = 0x22;
  canMsg3.data[2] = 0x28;
  canMsg3.data[3] = 0x15;
  canMsg3.data[4] = 0x00;
  canMsg3.data[5] = 0x00;
  canMsg3.data[6] = 0x00;
  canMsg3.data[7] = 0x00;

  canMsg4.can_id  = 0x726;
  canMsg4.can_dlc = 8;
  canMsg4.data[0] = 0x03;
  canMsg4.data[1] = 0x22;
  canMsg4.data[2] = 0x28;
  canMsg4.data[3] = 0x16;
  canMsg4.data[4] = 0x00;
  canMsg4.data[5] = 0x00;
  canMsg4.data[6] = 0x00;
  canMsg4.data[7] = 0x00;


  
  Serial.println("void end");
 
}


void loop() {
display.clearDisplay();
Serial.println(" ");
Serial.println(" ");
Serial.println(" ");
  
//front left start
   mcp2515.sendMessage(&canMsg1);
   delay(100);
   if (mcp2515.readMessage(&canans) == MCP2515::ERROR_OK) {
    
     if (canans.data[3] == 19) {
            Serial.print("fl pressure ");
      a1 = canans.data[4];
      b1 = canans.data[5];
      
      fl = (((a1*256)+b1+22)/3)/100;
      Serial.println(fl);
      }  
    else {
     Serial.println("no fl tire data");
    }
     
    }
    
       else {
     Serial.println("no fl message recieved");
    }
    
//front left end

//front right start
   mcp2515.sendMessage(&canMsg2);
   delay(100);
   if (mcp2515.readMessage(&canans) == MCP2515::ERROR_OK) {
    
     if (canans.data[3] == 20) {
            Serial.print("fr pressure ");
      a2 = canans.data[4];
      b2 = canans.data[5];
      
      fr = (((a2*256)+b2+22)/3)/100;
      Serial.println(fr);
      }  
    else {
     Serial.println("no fr tire data");
    }
     
    }
    
       else {
     Serial.println("no fr message recieved");
    }
   
//front right end

//rear left start
   mcp2515.sendMessage(&canMsg3);
   delay(100);
   if (mcp2515.readMessage(&canans) == MCP2515::ERROR_OK) {
    
     if (canans.data[3] == 21) {
            Serial.print("rl pressure ");
      a3 = canans.data[4];
      b3 = canans.data[5];
      
      rl = (((a3*256)+b3+22)/3)/100;
      Serial.println(rl);
      }  
    else {
     Serial.println("no rl tire data");
    }
     
    }
    
       else {
     Serial.println("no rl message recieved");
    }
   
//rear left end

//rear right start
   mcp2515.sendMessage(&canMsg4);
   delay(100);
   if (mcp2515.readMessage(&canans) == MCP2515::ERROR_OK) {
    
     if (canans.data[3] == 22) {
            Serial.print("rr pressure ");
      a4 = canans.data[4];
      b4 = canans.data[5];
      
      rr = (((a4*256)+b4+22)/3)/100;
      Serial.println(rr);
      }  
    else {
     Serial.println("no rr tire data");
    }
     
    }
    
       else {
     Serial.println("no rr message recieved");
    }
   
//rear right end

 display.clearDisplay();
  // Показать текст
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(fl);
  display.setCursor(65,0);
  display.println(fr);
  display.setCursor(0,15);
  display.println(rl);
  display.setCursor(65,15);
  display.println(rr);
  display.display();
  delay(4000);





Serial.println("loop end");
}
