# 编译器和工具
CC = gcc
RM = rm -f
MKDIR = mkdir -p

# 编译选项
CFLAGS = -Wall -Wextra -O2 -g -fPIC
LIBS = -lm
DLIBS = -ldl

# 目录结构
SRC_DIR = src
INC_DIR = include
LIB_DIR = lib
BUILD_DIR = build
BIN_DIR = bin

# 库信息
LIB_NAME = math
LIBRARY = $(LIB_DIR)/lib$(LIB_NAME).so

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
	@echo "构建完成!"
	@echo "库文件: $(LIBRARY)"
	@echo "可执行文件: $(MAIN_BIN)"

# 创建必要的目录
directories:
	$(MKDIR) $(BUILD_DIR) $(LIB_DIR) $(BIN_DIR)

# 构建动态库（不使用soname）
$(LIBRARY): $(OBJS)
	$(CC) -shared -o $@ $^ $(LIBS)
	@echo "动态库构建完成: $@"

# 编译库的源文件
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 编译主程序
$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 链接生成可执行文件
$(MAIN_BIN): $(MAIN_OBJ) $(LIBRARY)
	$(CC) -o $@ $(MAIN_OBJ) -L$(LIB_DIR) -l$(LIB_NAME) $(DLIBS)
	@echo "可执行文件构建完成: $@"

# 清理构建文件
clean:
	$(RM) -r $(BUILD_DIR) $(LIB_DIR) $(BIN_DIR)
	@echo "清理完成"

# 运行程序
run: $(MAIN_BIN)
	LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH ./$(MAIN_BIN)

# 显示构建信息
info:
	@echo "源文件: $(SRCS)"
	@echo "目标文件: $(OBJS)"
	@echo "库文件: $(LIBRARY)"
	@echo "可执行文件: $(MAIN_BIN)"

# 安装到当前用户目录
install-local: all
	cp $(LIBRARY) $$HOME/lib/
	cp $(INC_DIR)/*.h $$HOME/include/
	@echo "安装到用户目录完成"

.PHONY: all clean run info install-local directories


# # 最简 Makefile
# all: lib/libmath.so bin/calculator

# lib/libmath.so: src/math_basic.c src/math_advanced.c include/mathlib.h
# 	mkdir -p lib build
# 	gcc -fPIC -Iinclude -c src/math_basic.c -o build/math_basic.o
# 	gcc -fPIC -Iinclude -c src/math_advanced.c -o build/math_advanced.o
# 	gcc -shared -o lib/libmath.so build/math_basic.o build/math_advanced.o -lm

# bin/calculator: main.c
# 	mkdir -p bin
# 	gcc -Iinclude -o bin/calculator main.c -Llib -lmath -ldl

# clean:
# 	rm -rf lib build bin

# run:
# 	LD_LIBRARY_PATH=lib ./bin/calculator

# .PHONY: all clean run