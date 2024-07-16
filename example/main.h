#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdint.h>

typedef enum ProtocolListID {
	PROTOCOL_ID_HANDSHAKE = 1,
	PROTOCOL_ID_1,
	PROTOCOL_ID_2,
	PROTOCOL_ID_3, 
	PROTOCOL_ID_ERROR,
	PROTOCOL_ID_END,
} ProtocolListID;
#endif