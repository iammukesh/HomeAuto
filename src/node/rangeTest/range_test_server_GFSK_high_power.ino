// rf22_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing server
// with the RF22 class. RF22 class does not provide for addressing or reliability.
// It is designed to work with the other example rf22_client

#include <SPI.h>
#include <RF22.h>

// Singleton instance of the radio
RF22 rf22;


void setup() 
{
  Serial.begin(9600);
  rf22.setTxPower(RF22_TXPOW_17DBM);
  rf22.setModemConfig(RF22::GFSK_Rb2Fd5);
  if (!rf22.init())
    Serial.println("RF22 init failed");
  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
  Serial.println("ROLE: SERVER");
}

void loop()
{
  if (rf22.available())
  {
    // Should be a message for us now   
    uint8_t buf[RF22_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf22.recv(buf, &len))
    {
      Serial.print("Received data: ");
      Serial.println(buf[0]);
      
      // Send a reply
   //   uint8_t data[] = "And hello back to you";
      rf22.send(buf, sizeof(buf));
      rf22.waitPacketSent();
      Serial.println("Sent a reply");
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}

