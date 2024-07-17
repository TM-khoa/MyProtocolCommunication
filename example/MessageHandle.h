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
    uint8_t* GetHandshakeCode(){return (uint8_t*)_handshakeCode;}
    void SetHandshake(bool handshake){_isHandshake = handshake;}
    bool GetHandshakeStatus(){return _isHandshake;}
    void SetSendingStatus(bool isSending) {_isSending = isSending;}
    bool GetSendingStatus(){return _isSending;}
    int RequestHandshake(){
        if(_isSending == true) return 1;
        Protocol::SendRequestHandshakeCode((uint8_t*)_handshakeCode,sizeof(_handshakeCode),PROTOCOL_ID_HANDSHAKE);
        _isSending = true;
        return 0;
    }

    int ResponseHandshake(){
        if(_isSending == true) return 1;
        Protocol::SendResponseHandshakeCode((uint8_t*)_handshakeCode,sizeof(_handshakeCode),PROTOCOL_ID_HANDSHAKE);
        _isSending = true;
        return 0;
    }

    private:
	uint8_t _rxBuf[50];
	uint8_t _txBuf[50];
    const uint8_t _handshakeCode[8] = {0x12,0x34,0x56,0x78,0x90,0xab,0xcd,0xef};
    bool _isHandshake = false;
    bool _isSending = false;

};

#endif