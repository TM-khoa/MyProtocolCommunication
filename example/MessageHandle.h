#ifndef _MESSAGE_HANDLE_H
#define _MESSAGE_HANDLE_H
#include "main.h"
#include "../Protocol/Protocol.h"

extern uint8_t targetBufferToSendReceiveMesg[100];

void HandleMessageCallback(uint8_t *inputBuffer, uint16_t sizeOfInputBuffer, ProtocolID id, bool requestData);
void HandleMessageError(ProtocolErrorCode err);
class MessageHandle : public Protocol
{
    public :
    MessageHandle(){
        Protocol::RegisterStorageBuffer(_txBuf, sizeof(_txBuf), _rxBuf, sizeof(_rxBuf));
        Protocol::RegisterReceivedCallbackEvent(&HandleMessageCallback);
        Protocol::RegisterErrorEvent(&HandleMessageError);
    }
    ~MessageHandle(){

    }
    virtual int  SendMessage(ProtocolListID id, bool requestData);
    virtual int SendMessage(void* payload, uint16_t sizeOfPayload, ProtocolListID id);
    virtual int ReceiveMessage();


    private:
        uint8_t _rxBuf[50];
		uint8_t _txBuf[50];
};

#endif