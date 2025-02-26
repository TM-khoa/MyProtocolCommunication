CXX = g++
CC = gcc
CXXFLAGS = -Wall -g
CFLAGS = -Wall -g
OBJ_DIR = output
SRCDIR = example # phần tử hiện tại của SRCDIR là example
SRCDIR += Protocol # thêm một phần tử mới là Protocol, tương đương SRCDIR := example Protocol
CPP_SRC = $(wildcard $(SRCDIR)/*.cpp)
C_SRC = $(wildcard $(SRCDIR)/*.c)
INC_SRC = $(wildcard $(SRCDIR)/*.h)

# foreach var, list, text
# var: SRCDIR
# list: $(SRCDIR), $() liệt kê các phần tử trong SCRDIR
# text: $(wildcard $(SRCDIR)/*.cpp) -> tìm tất cả các file có đuôi .cpp trong từng phần tử SRCDIR
CPP_FILES := $(foreach SRCDIR, $(SRCDIR), $(CPP_SRC))
C_FILES := $(foreach SRCDIR, $(SRCDIR), $(C_SRC))
HEADER_FILES := $(foreach SRCDIR, $(SRCDIR), $(INC_SRC))
CPP_OBJ := $(notdir $(CPP_FILES)) # Bỏ đi đường dẫn tới các file .cpp này
# Thay thế các đuôi .cpp hiện tại của biến CPP_OBJ thành đuôi .o
CPP_OBJ := $(subst .cpp,.o, $(CPP_OBJ))

C_OBJ := $(notdir $(C_FILES)) # Bỏ đi đường dẫn tới các file .cpp này
# Thay thế các đuôi .cpp hiện tại của biến CPP_OBJ thành đuôi .o
C_OBJ := $(subst .c,.o, $(C_OBJ))
OBJ_FILES = $(CPP_OBJ) $(C_OBJ)
PATH_OBJ := $(foreach OBJ_FILES,$(OBJ_FILES),$(OBJ_DIR)/$(OBJ_FILES))


vpath %.cpp $(CPP_SRC) # Tìm kiếm dependency có đuôi .cpp ở đường dẫn này
vpath %.c $(C_SRC) # Tìm kiếm dependency có đuôi .c ở đường dẫn này
vpath %.h $(INC_SRC) # Tìm kiếm dependency có đuôi .h ở đường dẫn này

MyProtocol: $(OBJ_FILES)
	$(CXX) $(PATH_OBJ) -o $@

%.o: %.cpp $(HEADER_FILES)
# Tạo đường dẫn chứa file object, -p chỉ thị nếu đã có đường dẫn rồi thì không tạo thêm nữa
	@mkdir -p $(OBJ_DIR) 
	$(CXX) -c $(CXXFLAGS) -I $(SRCDIR) $< -o $(OBJ_DIR)/$@

%.o: %.c   $(HEADER_FILES)
	$(CC) -c $(CFLAGS) -I $(SRCDIR) $< -o $(OBJ_DIR)/$@

.PHONY: clean	
clean:
	@rm -r $(OBJ_DIR)
	@rm *.exe
print-%:
# $@ lúc ban đầu sẽ là print- + đối số truyền vào, sau đó thay thế print- thành NULL 
# -> chỉ còn lại đối số truyền vào (ví dụ $@ = print-a -> $@ = a)
# dấu $ ngoài cùng dùng để lấy tham chiếu tới đối số truyền vào (ví dụ $a)

	@echo $($(subst print-,,$@))
