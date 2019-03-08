/*
 Name:		SClb_Arduino_DMXEthernet.h
 Created:	08-Mar-19 19:00:06
Author:	statuscue
 Editor:	http://hes.od.ua
*/

/*
	Copyright 2019-2019 by Yevhen Mykhailov
	Art-Net(TM) Designed by and Copyright Artistic Licence Holdings Ltd.
*/

#ifndef _SClb_Arduino_DMXEthernet_h
#define _SClb_Arduino_DMXEthernet_h

#include <Udp.h>
#include <Arduino.h>
#include <inttypes.h>

#define RESULT_NONE 0
#define RESULT_DMX_RECEIVED 1
#define RESULT_PACKET_COMPLETE 2

#define DMX_UNIVERSE_SIZE 512

#define NO_HTP_IS_SINGLE_SENDER 1


class SClb_Arduino_DMXEthernet {

public:
	/*!
	* @brief UDP port used by protocol
	*/
	virtual uint16_t dmxPort(void);

	/*!
	* @brief universe for sending and receiving dmx
	* @discussion First universe is zero for Art-Net and one for sACN E1.31.
	* @return universe 0/1-255
	*/
	virtual uint8_t universe(void);
	/*!
	* @brief set universe for sending and receiving
	* @discussion First universe is zero for Art-Net and one for sACN E1.31.
	* @param u universe 0/1-255
	*/
	virtual void    setUniverse(uint8_t u);
	/*!
	 * @brief enables double buffering of received DMX data, merging from two sources
	 * @discussion enableHTP allocates three 512 byte data buffers A, B, and Merged.
							 when a DMX packet is received, the data is copied into A or b
							 based on the IP address of the sender.  The highest level
							 for each slot is written to the merged HTP buffer.
							 Read the data from the HTP buffer using getHTPSlot(n).
							 enableHTP() is not available on an ATmega168, ATmega328, or
							 ATmega328P due to RAM size.
	 */
	virtual void    enableHTP(void);

	/*!
	* @brief number of slots (aka addresses or channels)
	* @discussion Should be minimum of ~24 depending on actual output speed.  Max of 512.
	* @return number of slots/addresses/channels
	*/
	virtual int  numberOfSlots(void);
	/*!
	* @brief set number of slots (aka addresses or channels)
	* @discussion Should be minimum of ~24 depending on actual output speed.  Max of 512.
	* @param slots 1 to 512
	*/
	virtual void setNumberOfSlots(int n);
	/*!
	* @brief get level data from slot/address/channel
	* @param slot 1 to 512
	* @return level for slot (0-255)
	*/
	virtual uint8_t  getSlot(int slot);
	/*!
	* @brief get level data from slot/address/channel when merge/double buffering is enabled
	* @discussion You must call enableHTP() once after the constructor before using getHTPSlot()
	* @param slot 1 to 512
	* @return level for slot (0-255)
	*/
	virtual uint8_t  getHTPSlot(int slot);
	/*!
	* @brief set level data (0-255) for slot/address/channel
	* @param slot 1 to 512
	* @param level 0 to 255
	*/
	virtual void     setSlot(int slot, uint8_t value);
	/*!
	* @brief direct pointer to dmx buffer uint8_t[]
	* @return uint8_t* to dmx data buffer
	*/
	virtual uint8_t* dmxData(void);

	/*!
	* @brief read UDP packet
	* @return 1 if packet contains dmx
	*/
	virtual uint8_t readDMXPacket(UDP* eUDP);

	/*!
	* @brief read contents of packet from _packet_buffer
	* @discussion _packet_buffer should already contain packet payload when this is called
	* @param eUDP pointer to UDP object
	* @param packetSize size of received packet
	* @return 1 if packet contains dmx
	*/
	virtual uint8_t readDMXPacketContents(UDP* eUDP, int packetSize);

	/*!
	 * @brief send the contents of the _packet_buffer to the address to_ip
	 */
	virtual void    sendDMX(UDP* eUDP, IPAddress to_ip);
};

#endif // ifndef SClb_Arduino_DMXEthernet_H

