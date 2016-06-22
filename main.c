#include <SPI.h>
#include <Ethernet.h>

const int powerPIN = A0;

byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};

EthernetServer server(23);
EthernetClient client;

bool ACTIVATED = false;

void setup() {

  pinMode( powerPIN , OUTPUT );

  Serial.begin(9600);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for (;;)
      ;
  }

}

void loop() {

  client = server.available();

  if (client) {
    client.println("Toggling MODEM POWER");
    Serial.println("Toggling MODEM Power");

  if (ACTIVATED == false) {
    client.println(" PIN 13 -> HIGH ");
    digitalWrite( powerPIN , HIGH ); // TURN POWERTAIL ON 
    ACTIVATED = true;
  }
  else {
    client.println(" PIN 13 -> LOW");
    digitalWrite( powerPIN, LOW ); // TURN POWERTAIL OFF
    ACTIVATED = false;
  }
      
    client.stop();
  }

  switch ( Ethernet.maintain() ) {

    case 1:
      Serial.println("Error: renewed fail");
      break;
    case 2:
      Serial.println("Renewed success");
      break;
    case 3:
      Serial.println("Error: rebind fail");
      break;
    case 4:
      Serial.println("Rebind success");
      break;
    default:
      break;

  }
  
}
