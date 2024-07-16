#include "MessageHandle.h"
#include <iostream>



void PrintFrameData(FrameData fd){
    
    // ép kiểu int để cout in ra dạng số thay vì ký tự ASCII
    std::cout << "totalLength:" << (int)fd.totalLength << std::endl;
    std::cout << "protocolID:" << (int)fd.protocolID << std::endl;
    std::cout << "requestData:" << (int)fd.requestData << std::endl;
    std::cout << "payload length:" << (int)fd.payloadLength << std::endl;
    std::cout << "crc16:0x" << std::hex << fd.crc16 << std::endl;
}

int MessageHandle::SendMessage(ProtocolListID id, bool requestData){
    FrameData fd  = Protocol::MakeFrame(id,requestData);
    std::cout << "Virtual send message" <<  std::endl;
    PrintFrameData(fd);
    Protocol::ResetFrame();
    return 0;
}

int MessageHandle::SendMessage(void* payload, uint16_t sizeOfPayload, ProtocolListID id){
    FrameData fd  = Protocol::MakeFrame(payload,sizeOfPayload,id);
    std::cout << "Virtual send message" <<  std::endl;
    PrintFrameData(fd);
    return 0;
}

int MessageHandle::HandleReceiveMessage(){
    std::cout << "Virtual receive message" << std::endl;
    FrameData fd = Protocol::DecodeFrameAndCheckCRC();
    PrintFrameData(fd);
    return 0;
}