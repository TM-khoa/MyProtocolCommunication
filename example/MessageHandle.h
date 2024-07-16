#ifndef _MESSAGE_HANDLE_H
#define _MESSAGE_HANDLE_H
#include "main.h"
#include "../Protocol/Protocol.h"
                                                                                                         


typedef void (*pReceiveCallback)(FrameData fd);
typedef void (*pErrorCallback)(ProtocolErrorCode err);
class MessageHandle : public Protocol
{           
    public :
	MessageHandle(void (*pReceiveCallback)(FrameData fd), void (*pErrorCallback)(ProtocolErrorCode err)){        
        Protocol::RegisterStorageBuffer(_txBuf, sizeof(_txBuf), _rxBuf, sizeof(_rxBuf));
        Protocol::RegisterReceivedCallbackEvent(pReceiveCallback);
        Protocol::RegisterErrorEvent(pErrorCallback);
    }
    ~MessageHandle(){

    }
    virtual int SendMessage(ProtocolListID id, bool requestData);
    virtual int SendMessage(void* payload, uint16_t sizeOfPayload, ProtocolListID id);
    virtual int HandleReceiveMessage();


    private:
	uint8_t _rxBuf[50];
	uint8_t _txBuf[50];
};

#endif