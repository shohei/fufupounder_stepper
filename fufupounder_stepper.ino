#include <SPI.h>
#include <MsTimer2.h>

// ピン定義。
#define PIN_SPI_MOSI 11
#define PIN_SPI_MISO 12
#define PIN_SPI_SCK 13
#define PIN_SPI_SS 10
#define PIN_BUSY 9

void setup()
{
  delay(1000);
  pinMode(PIN_SPI_MOSI, OUTPUT);
  pinMode(PIN_SPI_MISO, INPUT);
  pinMode(PIN_SPI_SCK, OUTPUT);
  pinMode(PIN_SPI_SS, OUTPUT);
  pinMode(PIN_BUSY, INPUT);
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);
  Serial.begin(9600);
  digitalWrite(PIN_SPI_SS, HIGH);
 
  L6470_resetdevice(); //残留コマンドの削除とリセット 
  L6470_setup();  //L6470を設定
  
  MsTimer2::set(100, fulash);
  MsTimer2::start();
  delay(2000);
  
  //L6470_move(1,160000);
  //L6470_busydelay(5000); 
  //L6470_run(0,94000);
  //L6470_run(0,10000);
  //delay(6000);
  //L6470_softstop();
  //L6470_busydelay(5000);
  //L6470_goto(0x6789);
  //L6470_busydelay(5000);
  //L6470_run(0,0x4567);
  //L6470_run(1,94000);
  //delay(1000);
  //L6470_hardhiz();
}

void loop(){
//  rotateTest();
  //testDrive();
  L6470_run(0,30000);
//  delay(5000);
//  L6470_softstop();
//  L6470_busydelay(500);
//  L6470_run(1,30000);
//  delay(5000);
}

void rotateTest(){
  L6470_move(1,16000);  
  L6470_hardhiz(); //回転急停止、保持トルクなし
  L6470_move(0,16000);  
  L6470_hardhiz(); //回転急停止、保持トルクなし  
}

void testDrive(){
  L6470_run(0,300000);
  delay(5000);
  L6470_softstop();
  L6470_busydelay(500);
  L6470_run(1,300000);
  delay(5000);
  L6470_softstop();
  L6470_busydelay(500);  
}

void L6470_setup(){
//L6470_setparam_acc(0x40); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
L6470_setparam_acc(0x08A); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
//L6470_setparam_dec(0x40); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
L6470_setparam_acc(0x08A); //default 0x08A (12bit) (14.55*val+14.55[step/s^2])
//L6470_setparam_maxspeed(0x40); //default 0x041 (10bit) (15.25*val+15.25[step/s])
//L6470_setparam_maxspeed(0xFFFFFF); //default 0x041 (10bit) (15.25*val+15.25[step/s])
// When half step // L6470_setparam_maxspeed(0x5C); //default 0x041 (10bit) (15.25*val+15.25[step/s])
L6470_setparam_maxspeed(0xFFFFFF); //default 0x041 (10bit) (15.25*val+15.25[step/s])
L6470_setparam_minspeed(0x00); //default 0x000 (1+12bit) (0.238*val[step/s])
L6470_setparam_fsspd(0xff); //default 0x027 (10bit) (15.25*val+7.63[step/s])
//L6470_setparam_fsspd(0x3ff); //default 0x027 (10bit) (15.25*val+7.63[step/s])
//L6470_setparam_fsspd(0x027); //default 0x027 (10bit) (15.25*val+7.63[step/s])
L6470_setparam_kvalhold(0x80); //default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvalrun(0xd0); //default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvalacc(0x80); //default 0x29 (8bit) (Vs[V]*val/256)
L6470_setparam_kvaldec(0x60); //default 0x29 (8bit) (Vs[V]*val/256)

//L6470_setparam_stepmood(0x03); //default 0x07 (1+3+1+3bit)
L6470_setparam_stepmood(0x07); //default 0x07 (1+3+1+3bit)
}

void fulash(){
  Serial.print("0x");
  Serial.print( L6470_getparam_abspos(),HEX);
  Serial.print("  ");
  Serial.print("0x");
  Serial.println( L6470_getparam_speed(),HEX);
}



