#define MY_DEBUG
#define MY_RADIO_RFM95
#define MY_RFM95_IRQ_PIN 26
#define MY_RFM95_RST_PIN 14

#define MY_NODE_ID 9
#define MY_REPEATER_FEATURE
//#define MY_TRANSPORT_WAIT_READY_MS 5000
#define MY_REPEATER_FEATURE

#define ServoPin  13
#define ANGLE 110

#include <MySensors.h>
#include <Servo.h>

MyMessage porteMsg(2, V_STATUS);

Servo servo1;

void before() {
  servo1.attach(ServoPin);
  porte(ANGLE);  // Porte ouverte au démarrage
}

void setup() {
  // put your setup code here, to run once:
  //WiFi.mode(WIFI_STA);
  //WiFi.begin(ssid, password);

  send(porteMsg.set(true));
}

void presentation() {
  sendSketchInfo("Poulailler", "1.0");
  present(2, S_BINARY, "porte");
}

void loop() {
  // put your main code here, to run repeatedly:

}

void receive(const MyMessage &message) {
  if (message.getType() == V_STATUS) {
    if (message.getSensor() == 2) {
      if (message.getBool()) {
        // Ouvre la porte
        porte(ANGLE);
      }
      else {
        // Ferme la porte
        for (int posDegrees = ANGLE; posDegrees >= 0; posDegrees--) {
          servo1.write(posDegrees);
          delay(40);
        }
      }
    }
  }
}

void porte (int angle) {
          for (int posDegrees = 0; posDegrees <= angle; posDegrees++) {
          servo1.write(posDegrees);
          delay(40);
        }
}
