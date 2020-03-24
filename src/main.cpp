#include <Arduino.h>


#include <Arduino.h>
// #include <rpm_tst_include.h>

/*
    Video: https://www.youtube.com/watch?v=oCMOYS71NIU
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini

   Create a BLE server that, once we receive a connection, will send periodic notifications.
   The service advertises itself as:    6E400001-B5A3-F393-E0A9-E50E24DCCA9E
   Has a characteristic of: 6E400002-B5A3-F393-E0A9-E50E24DCCA9E - used for receiving data with "WRITE" 
   Has a characteristic of: 6E400003-B5A3-F393-E0A9-E50E24DCCA9E - used to send data with  "NOTIFY"

   The design of creating the BLE server is:
   1. Create a BLE Server
   2. Create a BLE Service
   3. Create a BLE Characteristic on the Service
   4. Create a BLE Descriptor on the characteristic
   5. Start the service.
   6. Start advertising.

   In this example rxValue is the data received (only accessible inside that function).
   And txValue is the data to be sent, in this example just a byte incremented every second. 
*/
/*
This is an adaptation the squeezer project
*/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

char buffer[20];

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
//int txValue = 0;
int fakeValue = 0;
int scalerdg = 0;


// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");

        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }

        Serial.println();  // just a CR; LF
        //methinks all above can be done with printf. ????

        // Do stuff based on the command received from the app
        if (rxValue.find("A") != -1) { 
          Serial.print("Turning ON!");
          // digitalWrite(ledPin, HIGH);
        }
        else if (rxValue.find("B") != -1) {
          Serial.print("Turning OFF!");
          // digitalWrite(ledPin, LOW);
        }

        Serial.println();
        Serial.println("*********");
      }
    }
};

void setup() {
  Serial.begin(115200);
  // pinMode(ledPin, OUTPUT);
//  pinMode(FastPin, OUTPUT);
//  digitalWrite(FastPin, LOW);    //default t0 10 sps

  // 
  // scale.power_up();   //for debug

  
  Serial.println("Starting.......");

  // scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Serial.print("warm it up with 100 read average: \t\t");
  // Serial.println(scale.read_average(100));       // print the average of 100 readings from the ADC
  // scale.set_scale();
  
  // scale.tare();                // reset the scale to 0
  // scale.set_scale(9631.f);                      // better guess--against CAMRY; see the README for details
  
  Serial.println("After setting up the scale:");
  char txString[12];
  int scalerdg =0;
//  while (1){
////    scalerdg = (int)((scale.get_units(numSamples))*10);
////    //scale.power_down();
////    //digitalWrite(ledPin, LOW);
////    itoa(scalerdg,txString,10);
//    Serial.println(scale.get_units(10));
//  
//  }

//  Serial.print("100 read average: \t\t");
//  Serial.println(scale.read_average(100));       // print the average of 20 readings from the ADC

  
  
  Serial.print("print the average of 1 slow readings after tare\t");
//  scale.power_up();   //for debug
  // Serial.println(scale.get_units(1));   // print the average of 20 readings from the ADC minus the tare weight, set with tare()
//  scale.power_down();   //for debug
//  digitalWrite(FastPin, HIGH);
//  Serial.print("print the average of 10 fast readings after tare\t");
//  Serial.println(scale.get_units(10));   // print the average of 20 readings from the ADC minus the tare weight, set with tare()
//}

  // Create the BLE Device
  Serial.println("Now Set Up the BLE Device");
  BLEDevice::init("FYE LightPad (TM)"); // Give it a name
  Serial.println("After Set up BLE Device v3");
  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TX,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
                      
  pCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_RX,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}

void loop() {
  char txString[12];

  
  if (deviceConnected) {
    
    // scale.power_up();
    //digitalWrite(ledPin, HIGH);
    // scalerdg = (int)((scale.get_units(numSamples))*10);
    //scale.power_down();
    //digitalWrite(ledPin, LOW);
    itoa(scalerdg,txString,10);
    
//    pCharacteristic->setValue(&fakeValue, 1); // To send the integer value
//    pCharacteristic->setValue("Hello!"); // Sending a test message
    pCharacteristic->setValue(txString);
        
    pCharacteristic->notify(); // Send the value to the app!
    Serial.print("*** Sent Value: ");
    Serial.print(txString);
    Serial.println(" ***");
    scalerdg++;
    delay(1000);

    // You can add the rxValue checks down here instead
    // if you set "rxValue" as a global var at the top!
    // Note you will have to delete "std::string" declaration
    // of "rxValue" in the callback function.
//    if (rxValue.find("A") != -1) { 
//      Serial.println("Turning ON!");
//      digitalWrite(LED, HIGH);
//    }
//    else if (rxValue.find("B") != -1) {
//      Serial.println("Turning OFF!");
//      digitalWrite(LED, LOW);
//    }
  }
//  delay(1000);
}
