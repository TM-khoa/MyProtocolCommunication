# Giới thiệu

Đây là dự án cá nhân (Do It Yourself) để test giao thức mô phỏng hoạt động truyền dữ liệu giữa hai thiết bị vi điều khiển, hoặc giữa vi điều khiển và máy tính, phục vụ cho mục đích giao tiếp point-to-point.

# Hướng dẫn sử dụng
_*Lưu ý*_: Hướng dẫn này áp dụng trên hệ điều hành Window
Tải [GNU Make](https://www.gnu.org/software/make/) ( phiên bản hiện tại đang thử nghiệm là 3.81).

+ Sau khi cài đặt GNU Make, xác định đường dẫn trỏ tới GNU Make (ví dụ như cài đặt mặc định là C:\Program Files (x86)\GnuWin32\binmake.exe) và thêm vào Enviroment Variables.
+ Sau khi thêm đường dẫn GNU Make vào Enviroment Variables, mở Command line (hoặc Powershell) và nhập lệnh __*make --version*__. Nếu cài đặt thành công thì sẽ hiển thị như sau:
```
GNU Make 3.81                                                                                              
Copyright (C) 2006  Free Software Foundation, Inc.                                                              
This is free software; see the source for copying conditions.                                                   
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A                                             
PARTICULAR PURPOSE.                                                                                             
This program built for i386-pc-mingw32  
```

Tải [MinGW64 cho Window x64](https://sourceforge.net/projects/mingw-w64/)

Cài đặt GDB server từ MinGW64 (tùy chọn cài đặt để debug).

Tùy chọn cài đặt Text Editor [Visual Studio Code](https://code.visualstudio.com/) và cài đặt extension C/C++ trên Visual Studio Code.

Thực hiện clone project về máy:
```
git clone https://github.com/TM-khoa/MyProtocolCommunication.git

```
- Vào thư mục chứa project và gọi lệnh __*make*__:
```
cd MyProtocolCommunication
make
```

Output sau khi chạy lệnh __*make*__ thành công:
```
g++ -c -Wall -g -I example  Protocol  example/main.cpp -o output/main.o
g++: warning: Protocol: linker input file unused because linking not done
g++ -c -Wall -g -I example  Protocol  example/MessageHandle.cpp -o output/MessageHandle.o
g++: warning: Protocol: linker input file unused because linking not done
g++ -c -Wall -g -I example  Protocol  Protocol/Protocol.cpp -o output/Protocol.o
g++: warning: Protocol: linker input file unused because linking not done
gcc -c -Wall -g -I example  Protocol  Protocol/CRC16.c -o output/CRC16.o
gcc: warning: Protocol: linker input file unused because linking not done
g++ output/main.o output/MessageHandle.o output/Protocol.o output/CRC16.o -o MyProtocol
```

Lúc này máy tính sẽ sinh ra file MyProtocol.exe. Thực hiện chạy file .exe:
```
.\MyProtocol.exe
Kết quả 
--->
********************TEST HANDSHAKE*********************
Device 1 is requesting handshake from device 2
Sending complete
Receive complete
Virtual receive message
Device2 matched handshake code, connection established, in protocol mode
Device2 response handshake code
Sending complete
Receive complete
Virtual receive message
Device1 matched handshake code, connection established, in protocol mode
Device1 connection established
********************CONNECTION ESTABLISHED*********************
**********************BEGIN COMMUNICATION***********************
Virtual send message
Device 1 send value 'a'
Sending complete
Receive complete
Virtual receive message
Event: Device2 get message
Device2 get value a is: 20
**********************NEXT TRANSFER***********************
Virtual send message
Device 2 send value 'b'
Sending complete
Receive complete
Virtual receive message
Event: Device1 get message
Device1 get value b is: 15.23
**********************NEXT TRANSFER***********************
Virtual send message
Device 1 request structure data
Sending complete
Receive complete
Virtual receive message
Event: Device2 get message
Virtual send message
Device2 response value dataTest
Sending complete
Receive complete
Virtual receive message
Event: Device1 get message
Device1 get dataTest is:
        --> a: -34000
        --> b: -58.33
        --> c: Test String
```

Để xóa các file .o và .exe. Gọi lệnh __*make clean*__.

# Giải thích ví dụ

Giả sử có hai thiết bị lần lượt là Device1 và Device2

Ví dụ thực hiện các công việc sau:

## 1. Thực hiện bắt tay
- Kết quả sau khi thực hiện bắt tay:
```
********************TEST HANDSHAKE*********************
Device 1 is requesting handshake from device 2
Sending complete
Receive complete
Virtual receive message
Device2 matched handshake code, connection established, in protocol mode
Device2 response handshake code
Sending complete
Receive complete
Virtual receive message
Device1 matched handshake code, connection established, in protocol mode
Device1 connection established
********************CONNECTION ESTABLISHED*********************
```
- Thiết bị 1 gửi mã bắt tay cho thiết bị 2, nếu mã khớp với mã bắt tay trong thiết bị 2 thì thiết bị 2 xác nhận trong chế độ bắt tay
- Nếu thiết bị 1 có yêu cầu phản hồi mã bắt tay từ thiết bị 2, thì sau khi xác nhận bắt tay thành công, thiết bị 2 sẽ gửi mã phản hồi về thiết bị 1
- Thiết bị 1 cũng sẽ thực hiện giải mã tương tự, lần này thiết bị 2 không có yêu cầu phải phản hồi mã bắt tay, do đó thiết bị 1 sau khi bắt tay thành công thì kết thúc quá trình bắt tay
- Vì mục đích của ví dụ là giả lập quá trình giao tiếp. Bằng cách sử dụng tính năng hàm ảo (__*virtual*__) của C++ để tạo ra một phương thức giao tiếp ảo (__SendMessage__ in ra thông báo __"Virtual send message"__ và __ReceiveMessage__ in ra thông báo __"Virtual receive message"__). Người dùng chỉ cần ghi đè (__override__) các phương thức ảo theo mong muốn để sử dụng 
## 2. Thiết bị 1 gửi số nguyên dương 8 bit cho thiết bị 2
- Kết quả giao tiếp:
```
**********************BEGIN COMMUNICATION***********************
Virtual send message
Device 1 send value 'a'
Sending complete
Receive complete
Virtual receive message
Event: Device2 get message
Device2 get value a is: 20
```

- Thiết bị 1 gửi giá trị a = 20 cho thiết bị 2, nếu thiết bị 2 giải mã thành công thì sẽ in ra giá trị a nhận được là 20
- Nếu quá trình giải mã thành công thì sẽ in ra thông báo:
`Event: Device2 get message`
- Nếu quá trình giải mã xảy ra lỗi thì sẽ in ra thông báo lỗi:
`
Event: Device2 error message event found
`

## 3. Thiết bị 2 gửi số thực 32 bit cho thiết bị 1

- Kết quả giao tiếp:
```
**********************NEXT TRANSFER***********************
Virtual send message
Device 2 send value 'b'
Sending complete
Receive complete
Virtual receive message
Event: Device1 get message
Device1 get value b is: 15.23
```

- Thiết bị 2 gửi giá trị b = 15.23 cho thiết bị 1, nếu thiết bị 1 giải mã thành công thì sẽ in ra giá trị b nhận được là 15.23
- Nếu quá trình giải mã thành công thì sẽ in ra thông báo:
`Event: Device1 get message`
- Nếu quá trình giải mã xảy ra lỗi thì sẽ in ra thông báo lỗi:
`Event: Device1 error message event found`

## 4. Thiết bị 1 yêu cầu một cấu trúc dữ liệu từ thiết bị 2
- Kết quả giao tiếp:
```
**********************NEXT TRANSFER***********************
Virtual send message
Device 1 request structure data
Sending complete
Receive complete
Virtual receive message
Event: Device2 get message
Virtual send message
Device2 response value dataTest
Sending complete
Receive complete
Virtual receive message
Event: Device1 get message
Device1 get dataTest is:
        --> a: -34000
        --> b: -58.33
        --> c: Test String
```
- Thiết bị 1 gửi yêu cầu thiết bị 2 phản hồi một cấu trúc dữ liệu TestDataStructure_t gồm 3 trường:
    + Trường kiểu dữ liệu int 'a'
    + Trường kiểu dữ liệu float 'b'
    + Trường kiểu dữ liệu mảng char 'c'
- Sau khi nhận được yêu cầu từ thiết bị 1, thiết bị 2 sẽ tự tạo ra biến thuộc kiểu TestDataStructure_t (phục vụ cho mục đích demo), đóng gói và gửi về thiết bị 1


# Chế độ bắt tay (Handshake) (Tùy chọn)

Chế độ này là tùy chọn, người dùng có thể thực hiện nếu mong muốn

Trước khi bắt đầu giao tiếp, cả hai thiết bị cần phải thực hiện bắt tay bằng cách gửi một mã được quy định sẵn trước do người dùng quy định. Nếu không vào chế độ bắt tay thì thông tin nhận được sẽ không giải mã (cho dù bên gửi đã gửi đúng cấu trúc giao thức)

__*Lưu ý*__: Thư viện Protocol chỉ có nhiệm vụ đóng gói và giải mã khung truyền dữ liệu, không quyết định kết quả chế độ bắt tay. Người dùng cần thao tác xử lý dữ liệu dựa vào kết quả nhận được do thư viện Protocol giải mã

# Hướng dẫn sử dụng

### 1. Khởi tạo
Thư viện Protocol yêu cầu 2 con trỏ hàm cho việc thông báo nhận dữ liệu và thông báo giải mã khung truyền dữ liệu xảy ra lỗi:
```
typedef void (*pProtocolCpltCallback)(FrameData fd); // dùng để thông báo đã giải mã gói tin thành công và đợi người dùng xử lý

typedef void (*pProtocolErrorCallback)(ProtocolErrorCode err);// dùng để thông báo lỗi
```

Người dùng cần viết hàm xử lý tương ứng với 2 con trỏ hàm trên, ví dụ:
```
void Device1GetData(FrameData fd); // Thiết bị 1 nhận được gói tin
void Device2GetData(FrameData fd); // Thiết bị 2 nhận được gói tin
void Device1GetError(ProtocolErrorCode err) // Thiết bị 1 thông báo lỗi giải mã
void Device2GetError(ProtocolErrorCode err) // Thiết bị 2 thông báo lỗi giải mã
```

Ngoài ra thư viện Protocol yêu cầu cung cấp bộ đệm phục vụ cho truyền và nhận dữ liệu. Người dùng thực hiện cung cấp địa chỉ con trỏ và kích thước bộ đệm truyền và nhận thông qua phương thức __Protocol::RegisterStorageBuffer__. Bộ đệm có thể dùng cấp phát động hoặc khởi tạo ngay từ ban đầu. 

__Ví dụ__:
```
Protocol protocol1;
uint8_t txBuffer[100] = {0};
uint8_t rxBuffer[100] = {0};
int main(void){
    protocol1.RegisterStorageBuffer(txBuffer, sizeof(txBuffer), rxBuffer, sizeof(rxBuffer));
    protocol1.RegisterReceivedCallbackEvent(&Device1GetData);
    protocol1.RegisterErrorEvent(&Device1GetError);
}
```

Có thể tạo ra một class MessageHandle kế thừa từ class Protocol với hàm dựng nhận con trỏ hàm pProtocolCpltCallback và pProtocolErrorCallback:

```
class MessageHandle : public Protocol
{
    public :
	MessageHandle(void (*pReceiveCallback)(FrameData fd), void (*pErrorCallback)(ProtocolErrorCode err)){        
        Protocol::RegisterStorageBuffer(_txBuf, sizeof(_txBuf), _rxBuf, sizeof(_rxBuf));
        Protocol::RegisterReceivedCallbackEvent(pReceiveCallback);
        Protocol::RegisterErrorEvent(pErrorCallback);
    } 
};

```

### Truyền dữ liệu

1. Sử dụng phương thức __Protocol::MakeFrame__ với payload do người dùng cung cấp để tạo ra khung truyền và được chứa trong bộ đệm txBuffer

2. Người dùng gọi hàm xuất dữ liệu ra ngoại vi để gửi khung truyền chứa trong bộ đệm txBuffer, trong ví dụ sử dụng phương thức ảo __MessageHandle::SendMessage__. Người dùng thực hiện override phương thức này với API điều khiển ngoại vi của vi điều khiển. Trong ví dụ thì phương thức ảo sẽ đóng gói khung truyền và bật cờ _isSending = true trong class __MessageHandle__ để cho phép gửi.


3. Trong ví dụ sử dụng hàm __SimulatePeripheralSendMessage__ để mô phỏng việc truyền dữ liệu với một thanh ghi ngoại vi periphBuffer. Kiểm tra điều kiện cho phép gửi __MessageHandle::GetSendingStatus__ và thực hiện đưa thông tin từ bộ đệm txBuffer ra ngoài testBuffer để bên nhận copy khung truyền từ testBuffer vào bộ đệm nhận rxBuffer

### Nhận dữ liệu
1. Byte đầu tiên nhận được trong rxBuffer cho biết tổng chiều dài cần thiết để chứa khung truyền. Dùng phương thức __Protocol::SetTotalLength()__ để thông báo cho class Protocol về chiều dài khung truyền, sau đó thực hiện nhận tiếp các byte còn lại vào rxBuffer cho đến khi đủ chiều dài khung truyền

2. Sau khi nhận đầy đủ khung truyền, gọi phương thức __Protocol::DecodeFrameAndCheckCRC()__ để kiểm tra mã CRC16 và giải mã khung truyền. Sau khi giải mã thành công sẽ tự động gọi tới con trỏ hàm thông báo sự kiện nhận do người dùng cung cấp ban đầu, nếu giải mã sai thì sẽ gọi tới con trỏ hàm thông báo lỗi 

3. Trong ví dụ cung cấp phương thức ảo __MessageHandle::HandleReceiveMessage()__ để nhận và giải mã khung truyền. Người dùng thực hiện override phương thức này theo mong muốn.

4. Hàm __SimulatePeripheralReceiveMessage__ mô phỏng nhận dữ liệu testBuffer đưa vào bộ đệm ngoại vi periphBuffer và copy lần lượt từng byte vào rxBuffer

## Mã lỗi

PROTOCOL_ERR_OK: Không có lỗi

PROTOCOL_ERR_FEATURE_NOT_SUPPORT: Không hỗ trợ tính năng

PROTOCOL_ERR_ID_NOT_FOUND: Không tìm thấy mã nhận dạng (ProtocolID) phù hợp

PROTOCOL_ERR_NULL_CALLBACK_FUNCTION: Người dùng không đăng ký hàm xử lý tương ứng với con trỏ hàm pProtocolCpltCallback hoặc pProtocolErrorCallback

PROTOCOL_ERR_CRC_FAIL: Mã CRC do bên gửi không khớp

PROTOCOL_ERR_FRAME_ERROR: Lỗi khung truyền

PROTOCOL_ERR_OUT_OF_BUFFER_SIZE: Khung truyền vượt quá kích thước bộ đệm truyền nhận

PROTOCOL_ERR_REFERENCE_PAYLOAD_NOT_FOUND: Người dùng không đăng ký đối số truyền vào

PROTOCOL_ERR_PAYLOAD_NOT_RECOGNIZE: Kích thước payload không khớp với kích thước đã quy định

PROTOCOL_ERR_STORE_BUFFER_IS_NULL: Không tìm thấy bộ đệm chứa dữ liệu

PROTOCOL_ERR_END: Không dùng