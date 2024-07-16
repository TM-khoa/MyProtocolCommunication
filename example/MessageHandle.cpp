#include "MessageHandle.h"
#include <iostream>


void HandleMessageCallback(uint8_t *inputBuffer, uint16_t sizeOfInputBuffer, ProtocolID id, bool requestData){
    std::cout << "Receive message event";
}


void HandleMessageError(ProtocolErrorCode err){

}

void PrintFrameData(FrameData fd){
    std::cout << "Virtual send message" <<  std::endl;
    std::cout << "totalLength:" << fd.totalLength << std::endl;
    std::cout << "payload length:" << fd.payloadLength << std::endl;
    std::cout << "protocolID:" << fd.protocolID << std::endl;
    std::cout << "requestData:" << fd.requestData << std::endl;
    std::cout << "crc16:" << fd.crc16 << std::endl;
}

int MessageHandle::SendMessage(ProtocolListID id, bool requestData){
    FrameData fd  = Protocol::MakeFrame(id,requestData);
    PrintFrameData(fd);
    Protocol::ResetFrame();
    return 0;
}

int MessageHandle::SendMessage(void* payload, uint16_t sizeOfPayload, ProtocolListID id){
    FrameData fd  = Protocol::MakeFrame(payload,sizeOfPayload,id);
    PrintFrameData(fd);
    Protocol::ResetFrame();
    return 0;
}

int MessageHandle::ReceiveMessage(){
    std::cout << "virtual receive message";
    return 0;
}