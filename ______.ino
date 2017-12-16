#include <Adafruit_NeoPixel.h>//include声明函数
#include <Wire.h>//调用收发数据所使用的库函数
#include "I2Cdev.h"
#include <U8glib.h>//关于oled屏幕引用函数的声明
#include <SHT2x.h>
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);      //说明oled型号
#define INTERVAL_LCD             20             //定义OLED刷新时间间隔  
 #define setFont_L u8g.setFont(u8g_font_7x13)
#define setFont_M u8g.setFont(u8g_font_fixed_v0r)
#define setFont_S u8g.setFont(u8g_font_fixed_v0r)
#define setFont_SS u8g.setFont(u8g_font_fub25n)//关于时间频率可能少了东西
#define temp1    25
#define temp2    30
#define temp3    32
 
float sensor_tem;//float定义基本数据单精度常量
void colorSet(uint32_t);
void TemRead();

void setup() {
  Serial.begin(9600);//初始化串口通信，并设置波特率9600
  Wire.begin(); 
}
 
void loop() {
  TemRead();//调用自定义函数
  
  if (sensor_tem <= temp1)//if判断语句
    {u8g.firstPage();
    do {
        setFont_S;
        u8g.setPrintPos(4, 16);
        u8g.print("please wear a cotton-padded");
        u8g.setPrintPos(4, 26);
        u8g.print("temperature:");
        u8g.setPrintPos(4, 36);
        u8g.print(sensor_tem);
    }while( u8g.nextPage() );}

 
  else if (sensor_tem > temp1 && sensor_tem <= temp2)//三个逻辑运算符，>表示大于，&&表示逻辑关系“与”，<=表示大于等于
   { u8g.firstPage();
    do {
        setFont_S;
        u8g.setPrintPos(4, 16);
        u8g.print("please wear a long sleeved coat" );
        u8g.setPrintPos(4, 26);
        u8g.print("temperature:");
        u8g.setPrintPos(4, 36);
        u8g.print(sensor_tem);
    }while( u8g.nextPage() );}

 
  else if (sensor_tem > temp2 && sensor_tem <= temp3)
   { u8g.firstPage();
    do {
        setFont_S;
        u8g.setPrintPos(4, 16);
        u8g.print("please wear a long sleeved shirt");
        u8g.setPrintPos(4, 26);
        u8g.print("temperature:");
        u8g.setPrintPos(4, 36);
        u8g.print(sensor_tem);
    }while( u8g.nextPage() );}

  else if(sensor_tem>temp3)
   { u8g.firstPage();
    do {
        setFont_S;
        u8g.setPrintPos(4, 16);
        u8g.print("please wear a T-shirt");
        u8g.setPrintPos(4, 26);
        u8g.print("temperature:");
        u8g.setPrintPos(4, 36);
        u8g.print(sensor_tem);
    }while( u8g.nextPage() );}

}
 
void TemRead()
{
  sensor_tem = SHT2x.readT();//把获得的温度值赋给变量sensor_tem
  Serial.println(sensor_tem);//将数据从Arduino传递到PC且单独占据一行，此数据可在串口监视器中看到
  Serial.print("--");   
  Serial.println(SHT2x.readRH());
  delay(100);
}
