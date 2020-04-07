
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
  Serial.println("can you do this??");
  
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
 parse_exec_seq(1,2);
//   for (int j = 0; j <=numbersequences; j++){ 
//   Serial.printf("\n\ntime since start (ms) = %lu\n",millis());  
//   cout << "sequence number  = "<<j << " name = "<<seqList[j].seqname <<endl;
//   string my_str = seqList[j].seqdetail;
//   my_str.erase(remove(my_str.begin(), my_str.end(),' '),my_str.end());    //removes extra spaces.
// 	vector<string> seq_cmd;

// 	stringstream s_stream(my_str); //create string stream from the string
	
// 	while(s_stream.good()){
//     string substr;
// 		getline(s_stream, substr, ','); //get first string delimited by comma
//   	seq_cmd.push_back(substr);
// 	}
 
	
// 	for(int i = 0; i<seq_cmd.size(); i++){ //print all splitted strings
//     if(seq_cmd.at(i).size() >0){    //avoid problems with a null sequence (,, or trailing comma)
//       uint16_t freq = get_num (seq_cmd, i);
//       uint16_t sclr = get_clr (seq_cmd, i);
//       //FIXME: change freq to num for clarity 
//       if(seq_cmd.at(i)[0]=='p'){
//           cout<< "It is a power cmd; power =  "<< freq << " color = " << sclr<< endl;
//           if (sclr == RED) REDstep.step_power = freq;
//           else if (sclr == IR) IRstep.step_power = freq;          
//           else cout<< "Unknown Color: "<< seq_cmd.at(i)[1] <<endl;

//          }
//          if(seq_cmd.at(i)[0]=='f'){     

          
//          cout<< "It is a freq cmd; freq =  "<< freq << " color = " << sclr<< endl;

//           if (sclr == RED) REDstep.step_freq = freq;
//           else if (sclr == IR) IRstep.step_freq = freq;
//           else cout<< "Unknown color: "<< seq_cmd.at(i)[1] <<endl;
//           cout << "RED freq = " << REDstep.step_freq << " IR freq = " << IRstep.step_freq << endl;

//          }
      
//     }

    
		
// 	}

//   // delay(2000);

//   }
while(1);
  
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

    Serial.println("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n\n");
    
        
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
