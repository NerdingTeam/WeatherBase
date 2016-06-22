#include <ArdusatSDK.h>
#include "thermo.h"
#include "DHT.h"
#include "vcc.h"
#include <VirtualWire.h>


void setup()
{
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    //vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
}


void loop()
{
  dhtPacket newPacket;
  vccPacket newVcc;

    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
  //  Serial.println(read_Vcc());

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	int i;

        digitalWrite(13, true); // Flash a light to show received good message
	// Message with a good checksum received, dump it.

	  if(buf[0]==0)
    {
      memcpy(&newPacket,buf,sizeof(newPacket));
      Serial.println(newPacket.temperature);
    }
    else
    {
      memcpy(&newVcc,buf,sizeof(newVcc));
      Serial.println(newVcc.millivolts);

    }

        digitalWrite(13, false);
    }
}
