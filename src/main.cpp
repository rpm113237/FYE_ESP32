
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

using namespace std;

#include <seq_ESP32.h>
#define LED 2   //On Boaard LED
#define PWR_DAC1 25   //two dacs, GPIO25 and GPIO26
#define PWR_DAC0 26   //two dacs, GPIO25 and GPIO26
#define IR_sel   19   //selects IR
#define RED_sel  21   //selects RED
#define LED_out_pin   18   //selects channel for PWM out
#define LEDChannel  0 //use PWM Channel 0

int LEDfreq = 10, LEDres = 8;   //TODO for debug

void setup_LED_io(void)
{
  pinMode (IR_sel, OUTPUT);
  pinMode (RED_sel, OUTPUT);
  pinMode (LED_out_pin, OUTPUT);
  ledcAttachPin(LED_out_pin, LEDChannel);

  // task_parse.start();



  // ledcSetup(LEDChannel, LEDfreq, LEDres);
  // ledcAttachPin(LED, LEDChannel);

}


// const int LEDfreq = 40;
// const int LEDChannel = 0;
// const int LEDres = 8; //Resolution 8, 10, 12, 15

char buffer[20];

// Global variables preceded by g_
extern SeqEntry seqList[NumSeqs];     //list of up to 20?
extern Stage_Spec seq_step[2];    //[0] is RED; [1] is IR
extern uint16_t g_numbersequences;
extern Parse_Return p_ret;
extern int g_seq_n, g_step_n, g_time_scale;    //global seq and step

std::string rxValue;

// Ticker timer1(printMessage, 0, 1);
Ticker task_parse(seq_exec, 1000, MILLIS);    //interval will be change
// Ticker timer3(printCountdown, 1000, 5);
// Ticker timer4(blink, 500);
// Ticker timer5(printCountUS, 100, 0, MICROS_MICROS);


BLECharacteristic *pCharacteristic;
bool deviceConnected = false;



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
      // std::string rxValue = pCharacteristic->getValue();
      rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        // cout<<"Receive: "<<rxValue.c_str()<<endl;
        

        // Do stuff based on the command received from the app
        if (rxValue.find("A") != -1) { 
          cout<<"Turning ON!  \n";
          // digitalWrite(ledPin, HIGH);
        }
        else if (rxValue.find("B") != -1) {
          cout<< ("Turning OFF!\n");
          // digitalWrite(ledPin, LOW);
        }

        // Serial.println();
        // Serial.println("*********");
      }
    }
};

void setup() {
  Serial.begin(115200);
  using namespace std;
  defSeq();   //this loads up the sequences

  // task_parse.start();
 
  //seqList[0].seqnum
  Serial.println("Starting.......");
  pinMode (LED, OUTPUT);

  //on board led; testing
  ledcSetup(LEDChannel, LEDfreq, LEDres);
  ledcAttachPin(LED, LEDChannel);

  // 
  
  
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

void LEDStart(int duty){
//*****for testing with on board LED
//rewrite for real deal--minor
  ledcSetup(LEDChannel, p_ret.out_freq, LEDres);
  ledcWrite(LEDChannel, duty);
//     dacWrite(DAC1, id);
//     delay(100);


}

void seq_exec () {
//if called with g_stepn = 0, no active sequence; pause
  
   if ((g_step_n > 0)||(g_step_n ==-1)) g_step_n = parse_exec_seq(g_seq_n,g_step_n); // parse_exec_seq returns 0 if finished
   if (g_step_n >0)
   {
     cout<<"g_step_n = "<<g_step_n<<"\t";
     LEDStart(127);   //change the 127 to macro ??
     out_p_ret(); //debug
     task_parse.interval((p_ret.out_time*1000)/g_time_scale) ;
     task_parse.start();
    }
    if (g_step_n == 0){   //just turned zero, not called if zero
      task_parse.interval(1); // call back in 1 ms; see if anything to do (i.e g+tetp_n = -1)  
      LEDStart(0); //zero percent; real world set also set DAC to zero????
      // cout<<"g_step_n = "<<g_step_n<<"\t";
    }                                    
  


}

void loop() {


ledcWrite(LEDChannel, 102);

g_step_n = -1;    //fake out first time
g_seq_n = 0;
task_parse.start();
while (g_step_n != 0) task_parse.update();
cout<<"fell through"<<endl;
while(1); //debug hang up

// cout<<"time since start (ms) = " <<millis();
// cout <<"\tseq num ="<<g_seq_n<<"\tseq name: " << seqList[g_seq_n].seqname<<endl;

 
  
  if (deviceConnected) {
    

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

}
