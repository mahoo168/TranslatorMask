#include "BLEDevice.h"
#include "Free_Fonts.h"
#include "SPI.h"
#include "TFT_eSPI.h"

static String DEVICE_NAME = "TranslatorMask";
static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
static BLEUUID    charUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8");
BLECharacteristic *pCharacteristic;   // キャラクタリスティック
bool deviceConnected = false;           // デバイスの接続状態
bool bInAlarm  = false;                 // デバイス異常判定

TFT_eSPI tft = TFT_eSPI();
String displayStr = "";

//SET UP BLE /////////////////////////////////
//callback for server 
class functionServerCallBacks : public BLEServerCallbacks{
  void onConnect(BLEServer* pServer){
    Serial.println("BLE CONNECTED");
  }
  void onDisconnect(BLEServer* pServer){
    
    Serial.println("BLE DISCONNECTED");
  }
};
//callback for characteristic
class functionCharaCallBacks : public BLECharacteristicCallbacks{
  void onRead(BLECharacteristic* pCharacteristic){
    Serial.println("read");
  }
  void onWrite(BLECharacteristic* pCharacteristic){
    std::string str = pCharacteristic->getValue();
    displayStr = str.c_str();
    for(int i = 0; i < str.length(); i++){
      Serial.print(str[i]);
    }
     Serial.println("");
  }
};
//setup
void setupBLE(){
  BLEDevice::init("TRANSLATOR MASK");
  //Create server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new functionServerCallBacks());
  //Create service
  BLEService *pService = pServer->createService(serviceUUID);
  //Create characteristics
  pCharacteristic = pService->createCharacteristic(charUUID, 
                              BLECharacteristic::PROPERTY_READ   |
                              BLECharacteristic::PROPERTY_WRITE  |
                              BLECharacteristic::PROPERTY_NOTIFY |
                              BLECharacteristic::PROPERTY_INDICATE);
  pCharacteristic->setCallbacks(new functionCharaCallBacks);
 
  //Start service
  pService->start();
  //Start advertising
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}


//////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  tft.begin();
  tft.setRotation(1);
  tft.setFreeFont(FF18);
  
  setupBLE();
}

void loop() {
  // put your main code here, to run repeatedly:
  tft.fillScreen(TFT_BLACK);
  tft.drawString("TEST WRITING",10,10);
  tft.drawString(displayStr,10,50);
  delay(1000);
}
