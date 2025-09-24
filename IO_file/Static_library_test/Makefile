# 编译器和工具
CC = gcc
AR = ar
RM = rm -f
MKDIR = mkdir -p

# 编译选项
CFLAGS = -Wall -Wextra -O2 -g
ARFLAGS = rcs

# 目录结构
SRC_DIR = src
INC_DIR = include
LIB_DIR = lib
BUILD_DIR = build
BIN_DIR = bin

# 库信息
LIB_NAME = math
LIBRARY = $(LIB_DIR)/lib$(LIB_NAME).a

# 源文件
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# 主程序
MAIN_SRC = main.c
MAIN_OBJ = $(BUILD_DIR)/main.o
MAIN_BIN = $(BIN_DIR)/calculator

# 头文件路径
INCLUDES = -I$(INC_DIR)

# 默认目标
all: directories $(LIBRARY) $(MAIN_BIN)

# 创建必要的目录
directories:
	$(MKDIR) $(BUILD_DIR) $(LIB_DIR) $(BIN_DIR)

# 构建静态库
$(LIBRARY): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
	@echo "静态库构建完成: $@"

# 编译库的源文件
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 编译主程序
$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 链接生成可执行文件
$(MAIN_BIN): $(MAIN_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $< -L$(LIB_DIR) -l$(LIB_NAME)
	@echo "可执行文件构建完成: $@"

# 清理构建文件
clean:
	$(RM) -r $(BUILD_DIR) $(LIB_DIR) $(BIN_DIR)
	@echo "清理完成"

# # 安装到系统目录（可选）
# install: all
# 	cp $(LIBRARY) /usr/local/lib/
# 	cp $(INC_DIR)/*.h /usr/local/include/
# 	cp $(MAIN_BIN) /usr/local/bin/
# 	@echo "安装完成"

# # 卸载
# uninstall:
# 	$(RM) /usr/local/lib/lib$(LIB_NAME).a
# 	$(RM) /usr/local/include/mathlib.h
# 	$(RM) /usr/local/bin/calculator
# 	@echo "卸载完成"

# 显示构建信息
info:
	@echo "源文件: $(SRCS)"
	@echo "目标文件: $(OBJS)"
	@echo "库文件: $(LIBRARY)"
	@echo "可执行文件: $(MAIN_BIN)"

# 运行程序
run: $(MAIN_BIN)
	./$(MAIN_BIN)

# 调试版本
debug: CFLAGS += -DDEBUG -O0
debug: all

# 静态分析
check: CFLAGS += -fsanitize=address -fsanitize=undefined
check: all

# 声明伪目标
.PHONY: all clean info run debug check directories