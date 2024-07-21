#include "MessageHandle.h"
#include <iostream>


void PrintFrameData(FrameData fd){
    
    // ép kiểu int để cout in ra dạng số thay vì ký tự ASCII
    // std::cout << "\t" << "totalLength:" << (int)fd.totalLength << std::endl;
    // std::cout << "\t" << "protocolID:" << (int)fd.protocolID << std::endl;
    // std::cout << "\t" << "requestData:" << (int)fd.requestData << std::endl;
    // std::cout << "\t" << "payload length:" << (int)fd.payloadLength << std::endl;
    // std::cout << "\t" << "crc16:0x" << std::hex << fd.crc16 << std::endl;
}

/**
 * @brief Gửi yêu cầu dữ liệu từ bên nhận
 * @param id Mã nhận dạng khung truyền
 * @param requestData true nếu yêu cầu bên nhận phản hồi thông tin
 * @return 
 */
int MessageHandle::SendMessage(ProtocolListID id, bool requestData){
    if(_isSending == true) return 1;
    FrameData fd  = Protocol::MakeFrame(id,requestData);
    std::cout << "Virtual send message" <<  std::endl;
    PrintFrameData(fd);
    _isSending = true;
    return 0;
}

/**
 * @brief Gửi payload đến bên nhận 
 * @param payload Con trỏ trỏ tới dữ liệu cần gửi
 * @param sizeOfPayload Kích thước dữ liệu
 * @param id Mã nhận dạng khung truyền
 * @return 0 nếu gửi thành công, 1 nếu đang bận
 */
int MessageHandle::SendMessage(void* payload, uint16_t sizeOfPayload, ProtocolListID id){
    if(_isSending == true) return 1;
    FrameData fd  = Protocol::MakeFrame(payload,sizeOfPayload,id);
    std::cout << "Virtual send message" <<  std::endl;
    PrintFrameData(fd);
    _isSending = true;
    return 0;
}



int MessageHandle::HandleReceiveMessage(){
    std::cout << "Virtual receive message" << std::endl;
    FrameData fd = Protocol::DecodeFrameAndCheckCRC();
    PrintFrameData(fd);
    return 0;
}