
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
#include <Arduino.h>
// #include <iostream>
// #include <vector>
// #include <sstream>
// #include <Ticker.h>
// #include <cstring>
// #include<string>

// #include <BLEDevice.h>
// #include <BLEServer.h>
// #include <BLEUtils.h>
// #include <BLE2902.h>

using namespace std;

#include <seq_ESP32.h>

char buffer[20];

extern SeqEntry seqList[NumSeqs];     //list of up to 20?
extern Stage_Spec seq_step[2];    //[0] is RED; [1] is IR
extern uint16_t numbersequences;
extern Parse_Return p_ret;


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
        Serial.println(rxValue.c_str());

        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }

        Serial.println();  // just a CR; LF
        //methinks all above can be done with printf. ???? abc

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
  using namespace std;
  defSeq();   //this loads up the sequences
 
  //seqList[0].seqnum
  Serial.println("Starting.......");
  
  
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
  cout << ("Waiting a client connection to notify...") << endl;
}

void loop() {
int seq_n = 0, step_n =0 ;    //debug, run through them all, see if blows up
int nloops = numbersequences;
nloops = 2;
for (seq_n = 1; seq_n< nloops; seq_n++){
step_n = -1;    //fake out first time
cout<<"time since start (ms) = " <<millis();
cout <<"\tseq num ="<<seq_n<<"\tseq name: " << seqList[seq_n].seqname<<endl;

 while ((step_n >0)||(step_n < 0))    //step_n = -1 is first time, set to zero in parse_exec_seq
 {
  // cout<<"\ntime since start (ms) = " <<millis();
  // cout <<"\tsequence num ="<<seq_n<<"seq name" << seqList[seq_n].seqname<<endl;
  step_n = parse_exec_seq(seq_n,step_n); //returns 0 if finished
  out_p_ret();
  delay(p_ret.out_time*100);
 }
 
//  delay(5000);
} //END DEBUG WHILE
 while (1);
// delay(2000);

//   }
while(1);  //debug hang up
  
  if (deviceConnected) {
    
    // scale.power_up();
    //digitalWrite(ledPin, HIGH);
    // scalerdg = (int)((scale.get_units(numSamples))*10);
    //scale.power_down();
    //digitalWrite(ledPin, LOW);
    //itoa(scalerdg,txString,10);

    
//    pCharacteristic->setValue(&fakeValue, 1); // To send the integer value
//    pCharacteristic->setValue("Hello!"); // Sending a test message
    // pCharacteristic->setValue(txString);
    for (int i = 0; i <NumSeqs; i++) {
    pCharacteristic->setValue(seqList[i].seqname.c_str());
    pCharacteristic->notify(); // Send the value to the app!
    Serial.print("*** ");
    Serial.print(seqList[i].seqname.c_str());
    Serial.println(" ***");
    //scalerdg++;
    delay(500);  
    }
    cout<<"\n\ntime since start (ms) = " <<millis();
    cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n\n";
    
        
    // pCharacteristic->notify(); // Send the value to the app!
    // Serial.print("*** Sent Value: ");
    // Serial.print(txString);
    // Serial.println(" ***");
    // scalerdg++;
    // delay(1000);

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
