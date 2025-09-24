---
title: "�ļ�IO/��׼IO"
author: "Zozo"
date: 2025-08-30
draft: true
---

### �ļ�IO��ϵͳ���ü���
- **�ļ�IO�����API����**
  - **���� ��**  ����ϵͳ�ṩ��һ��**�޻���**����ӽ��ײ�Ӳ��������/�������ԭ�� ��ֱ��ͨ�� **ϵͳ���ã��û�̬���ں�̬���л���** ���ں˽��н���
  - **�����ص㣺**  �޻��塢ÿ�ζ�д������ֱ�ӷ���ϵͳ���� ���ں˴���
  - **��������** ==�ļ�������== һ���Ǹ����� �����ڽ�����Ψһ��ʶһ���򿪵��ļ�
    -  `0` - ��׼���루stdin��
    -  `1` - ��׼�����stdout��
    -  `2` - ��׼����stderr��
    [stdin_out_errʾ��](/stdin_out_err_test.c)  
  - **����API**
    - `open()`   [open( )�÷�ʾ��](/unistd_test.c)
    - `close()`   
    - `read()`  [open_read_write_close�÷�ʾ��](/system_call_test.c)
    - `write()`
    - `lseek()`
- **ÿ�ζ�д���漰���û�̬���ں�̬���л� ������ Ч�ʽϵ�** 
- ==�ļ�IO��������==
![�ļ�IO��������ʾ��ͼ](/picture/io2.png)   

### ��׼IO���⺯������
- **��׼IO�����API����**
  - **���壺** c���Ա�׼���ṩ��һ�� **������** ������/������� ���������ļ�IO֮�� ͨ�����û������� **����ϵͳ����**�Ĵ��� �Ӷ����Ч��
  - **�����ص㣺** �����塢�����û��ռ�ά��һ�������� ֻ�������ض�����(�绺�����������з����ֶ�ˢ��)  �Ž�������������ͨ��һ��ϵͳ����д���ں�
  - **��������** ==�ļ�ָ��== һ��ָ�� `FILE` �ṹ���ָ��(��`FILE*`)   `FILE`�ṹ������˹����ļ�����������Ϣ��������Ӧ���ļ���������������ָ�롢��������С�������־��
  - **���ֻ���ģʽ**
    - **ȫ����**��ͨ������**�����ļ�** ֻ�е�`������������`ʱ ��ִ��ʵ�ʵ� I/O ����  ʹ�� `fflush()` ����ǿ��ˢ�»�����
    - **�л���**: ͨ������ **�ն�**��stdout�� ���������з� `\n` ��`��������ʱ` ִ�� I/O ����
    - **�޻���**: �����ַ����л��� ��׼���� `stderr`  ͨ�����޻���� ��ȷ��������Ϣ��**����**�����
  - **����API**
    - `fopen()`     [fopen( )��������](/fopen_test.c)
    - `fclose()`    [fclose�� ����������](/fclose_test.c)
    - `fread()`     [fread�� ����������](/fread_test.c)
    - `fwrite()`    [fwrite�� ����������](/fwrite_test.c)
    - `fprintf()`   [fprintf�� ����������](/fprintf_test.c)
    - `fscanf()`    [fscanf�� ����������](/fscanf_test.c)
    - `fgetc()`     [fgetc�� ����������](/fgetc_test.c)
    - `fputc()`     [fputc�� ����������](/fputc_test.c)
    - `fgets()`     [fgets�� ����������](/fgets_test.c)
    - `fputs()`     [fputs�� ����������](/fputs_test.c)

- ==**��׼IO��������**==
![��׼IO��������ʾ��ͼ](/picture/io1.png)

### ���ߺ������𣺻���

- **������**
  - **���壺** ��������һ��Ԥ�����ڴ��������������ڴ�������е���ʱ����תվ���򡰵ȴ�����
  - **Ŀ�ģ�** 
    - **����ϵͳ���ã����Ч��**
      - ϵͳ�����ǰ���Ĳ��� ����Ҫ���û�̬�л����ں�̬ ִ��������л����� �����������л��Ŀ���Զ�������û��ռ��ڴ��в������ݵĿ���
      - �����������С���߼��������ϳ�һ�δ��������� �Ӷ��������ϵͳ���õĴ���
    - **Э���ٶȲ��죨ƽ����������**
      - `CPU vs ����/����:` CPU �������ݵ��ٶȣ����뼶��ԶԶ���ڴ��̻������д���ݵ��ٶȣ����뼶�������û�л����������ٵ� CPU �����ò�Ƶ���صȴ����ٵ� I/O �豸�������Դ�˷ѡ��������� CPU ���Կ��ٵؽ����ݡ��ӡ�����������Ȼ�����ȥ�������������ɻ�����������������豸�򽻵���
    - **�ṩ��ݵĲ���**
      - ������ʹ�� `����`��`���ж�ȡ`�ȸ߼�������Ϊ���ܣ���Ϊ��Щ�����������û��ռ�Ļ�������������ɣ�������ÿ�ζ��ͷ��ں�
  - **�û�������:** �ɱ�׼I/O�⣨��glibc�����û��ռ�ά�� �����`FILE�ṹ��`���������Ļ�����
  - **�ں˻�����:** �ɲ���ϵͳ�ں�ά�� ������ͨ�� `write()` ϵͳ���ý����ں˺󣬲���������д��Ӳ�� �ں˻Ὣ������Լ��Ļ��������棨Page Cache���� ���ʵ���ʱ�����绺��������һ��ʱ��󡢻���� `sync()/fsync()`����д����� ����Ϊ��**����������̵Ķ�д����**

  - **��� ��ʹʹ���޻���� �ļ�I/O(write)  ����Ҳֻ�Ǵ��û��ռ俽�������ں˿ռ� �������������� Ҫȷ����������д����� ��Ҫ���� fsync(fd)**

- **�����������ƣ���ݲֿ�**
����һ�����Ϲ�����������̣�

- **û�л��������޻���I/O����** ���Աÿ�����һ����Ʒ�������̿����͵���ҡ�����һ�����ٻ��������һ�������ǳ���Ч����Ϊ�󲿷�ʱ�䶼������·�ϣ�ϵͳ���ÿ�������
  - ��Ӧ��ÿ�ε��� `write()` ֻд1���ֽڵ��ļ� �ͻᷢ��һ��ϵͳ���á�
- **�л�������������I/O����** ���Ա���������ͳ�һ����Ʒ ���Ѷ����Ʒ�ռ������زֿ�(������)�� ֱ����
  1. �ֿ�����ˣ�������������
  2. ���ߵ���һ��Ĺ̶�����ʱ�䣨ǿ��ˢ�£��� `fflush()`����
  3. ������һ���Ӽ��Ķ����������̷������������з�`\n` �л���ģʽ����
    ��ʱ�����ſ�һ�˳����Ѳֿ������е���Ʒһ�����͵��ּ����ģ��ںˣ���
  - ��Ӧ������ `fputc()` ��Σ��ַ��ȱ������ڴ滺���������ض������²ŷ���һ�� `write()` ϵͳ���ã�����������д���ںˡ�
��������زֿ⡱���ǻ���������ͨ���������������ϵͳ���ô����� ���������������Ч�� 

- ==�ļ�I/O����׼I/O�����������ں˹�ϵͼ==
```mermaid
graph TD
    A[Ӧ�ó���] --> B[��׼I/O�⺯��]
    A --> C[�ļ�I/Oϵͳ����]
    
    B --> D[�û��ռ仺����]
    D --> C
    
    C --> E[�ں˿ռ�]
    
    E --> F[�ں˻�����<br>Page Cache]
    F --> G[����Ӳ��<br>����/�豸]
    
    B --> H[FILE* �ļ�ָ��]
    C --> I[int �ļ�������]

            style B fill:#e1f5fe
            style C fill:#ffebee
            style D fill:#f3e5f5
            style F fill:#fff3e0   
```
- ==��������==
![���������Ա�ͼ](/picture/io4.png) 

- ==����ת����ϵ==
![����ת����ϵͼ](/picture/io3.png) 

### ϵͳ����
- **ϵͳ����**��Ӧ�ó��������ϵͳ�ں�֮��ı�̽ӿ� �û�����ͨ��ϵͳ���������ں�Ϊ��ִ����Ȩ���� ���ļ����������̹�������ͨ�ŵ�
  - �û������޷�ֱ��ִ����Ȩָ��
  - ��Ҫͨ��ϵͳ���ýӿ������ں˴���
    - ���磺�û�������ֱ�Ӷ�д����
    - ����ͨ�� `open()`, `read()`, `write()` ��ϵͳ����
- **CPU��Ȩ����**
![ CPU��Ȩ���� ](/picture/io5.png) 

- **ϵͳ���ù�������**
```mermaid
sequenceDiagram
    participant App as Ӧ�ó���
    participant LibC as C��׼��
    participant Kernel as �ں�

    Note over App, Kernel: 1. �û��ռ�׼��
    App->>LibC: ���ÿ⺯��(��fwrite)
    LibC->>LibC: ׼��ϵͳ���ò���
    
    Note over App, Kernel: 2. ����ϵͳ����
    LibC->>Kernel: ִ��syscallָ��<br>����writeϵͳ����
    Note right of Kernel: �л����ں�̬
    
    Note over App, Kernel: 3. �ں˴���
    Kernel->>Kernel: ��֤�����Ϸ���
    Kernel->>Kernel: ִ��ʵ�ʵ��ļ�д�����
    Kernel->>Kernel: ׼������ֵ
    
    Note over App, Kernel: 4. �����û��ռ�
    Kernel->>LibC: ���ؽ��
    Note right of Kernel: �л����û�̬
    LibC->>App: ������ֵ������
```

### ��̬��
- ��̬�⣨Shared Library������**��������ʱ����̬���صĴ����**�����������Թ���ͬһ�ݿ�������ڴ��еĸ���
- **��̬�������**
  - **��ʡ�ڴ�**��������̹���ͬһ�ݴ���
  - **��ʡ���̿ռ�**��������ÿ����ִ���ļ��а��������
  - **���ڸ���**�����¿��������±������г���
  - **����ʱ����**�����Զ�̬���غ�ж��
- **��̬��Ĵ�����ʹ��**
 - **���ļ�����������**
    - `-l<name>  �� ���� lib<name>.so����̬�⣩�� lib<name>.a����̬�⣩`
      ���� -lmylib �������������ң�
      - ��̬��: libmylib.so�����ȣ�
      - ��̬��: libmylib.a�������̬�ⲻ���ڣ�
  - **������̬��**
    ```bash
        # ����Ϊλ���޹ش���
        gcc -fPIC -c helper1.c helper2.c
        # ������̬��
        gcc -shared -o libmylib.so helper1.o helper2.o

        # ����һ�����
        gcc -fPIC -shared -o libmylib.so helper1.c helper2.c
    ```
  - **�������Ӷ�̬��**
    ```bash
        # ����ʱ���Ӷ�̬��
        gcc -o myapp main.c -L. -lmylib

        # ����ǰ��Ҫ���ÿ�·��
        export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
        ./myapp
    ```
    ![�������](/picture/io6.png)
  - **ʾ��˵��** 
  �����������ļ��� 
    ```t
    .
    ������ main.c
    ������ libmylib.so    # �����Ҫ���ӵĿ�
    ```
    ִ�������
    ```bash
    gcc -o myapp main.c -L. -lmylib
    ```
    �������᣺
    - �ڵ�ǰĿ¼��.���в���
    - �ҵ� libmylib.so����Ϊ -lmylib �� lib + mylib + .so��
    - �������ӵ���ִ���ļ� myapp ��
  - **��Ҫ��ʾ**
    - ˳�����Ҫ���������˳���Ӱ����Ž���
    ```bash
        # ��ȷ��˳�������Ŀ���ں���
        gcc main.o -lmyapp -lmylib  # myapp ���� mylib
    ``` 
    - ·�����ȼ�: `-L` ָ����·��������ϵͳ·��
    - �汾����: �����Ҫ�ض��汾������ֱ��ָ���ļ�����
    ```bash
        gcc -o myapp main.c /path/to/libmylib.so.1.2.3
    ``` 
   **-lmylib ��ʾ������Ϊ mylib �Ŀ⣬ʵ�ʲ��ҵ��ļ��� libmylib.so���� libmylib.a��**
- **��̬����һ���**
  - ������·��
    ```bash
        # �鿴Ĭ������·��  verbose:�������������ϸ������Ϣ SEARCH_DIR: ֻ��ʾ���� "SEARCH_DIR" ����
        ld --verbose | grep SEARCH_DIR

        # �鿴ϵͳ������
        cat /etc/ld.so.conf
        ls /etc/ld.so.conf.d/

        # ���¿⻺��
        sudo ldconfig
    ``` 
  - ������������
    ```bash
        # ��ʱ��ӿ�·��
        export LD_LIBRARY_PATH=/path/to/libs:$LD_LIBRARY_PATH

        # ����Ԥ���ؿ�
        export LD_PRELOAD=/path/to/libdebug.so

        # ���ÿ������
        export LD_DEBUG=libs  # ������Ϣ
    ```
    ![�������1](/picture/io7.png)
    ![�������1](/picture/io8.png)
  - �汾����
    ```bash
        # 1. �������汾�ŵĹ����
        gcc -shared -Wl,-soname,libmylib.so.1 -o libmylib.so.1.0.0 helper.c
        # 2. �������汾�ŷ�������
        ln -sf libmylib.so.1.0.0 libmylib.so.1
        # 3. ����ͨ�÷�������
        ln -sf libmylib.so.1 libmylib.so
    ```
    ![�������2](/picture/io9.png)
    ![�������3](/picture/io10.png)
- **ʹ�ù��ߺ͵���**
  - **�������**
    ```bash
        # �鿴���������Ŀ�
        ldd myapp

        # �鿴���еķ���
        nm -D libmylib.so

        # �鿴���ű�
        objdump -T libmylib.so

        # �鿴����Ϣ
        readelf -d libmylib.so
    ```
  - **���Զ�̬��**
    ```bash
        # ���õ��Ի�������
        export LD_DEBUG=files  # ��ʾ�ļ�����
        export LD_DEBUG=bindings  # ��ʾ���Ű�
        export LD_DEBUG=libs    # ��ʾ������
        export LD_DEBUG=all     # ��ʾ������Ϣ

        # ���г���鿴������Ϣ
        ./myapp
    ```
- **��̬������ʾ��**
  - **Ŀ¼�ṹ**
    - ���д������ļ�
        -  main.c �������ļ� [main.cʾ��](/Dynamic_library_test/main.c)
        -  src/   ���Դ��   [srcԴ��ʾ��1](/Dynamic_library_test/src/math_advanced.c)
        -  inlcude/   ���ͷ�ļ� [includeͷ�ļ�ʾ��](/Dynamic_library_test/include/Dmathlib.h)
        -  Makefile  �����ļ�   [Makefile�ļ�ʾ��](/Dynamic_library_test/Makefile)
    ![Ŀ¼�ṹʾ��ͼ](/picture/io14.png) 


### ��̬��
- ��̬�⣨Static Library������**����ʱ���������ӵ���ִ���ļ���**�Ŀ⡣��������ʱ����Ҫ�ⲿ�Ŀ��ļ�
  - **��̬����ص㣺**
    - ��չ��: .a (Archive)
    - ���ӷ�ʽ: ����ʱ��̬����
    - ����ʱ: ����Ҫ�ⲿ����
    - �ļ���С: ��ִ���ļ��ϴ�
    - ����: ��Ҫ���±������
  - **��̬��Ĵ�����ʹ��**
    - **������̬��**
    ```bash
        # ����ΪĿ���ļ�
        gcc -c helper1.c helper2.c

        # ������̬��
        ar rcs libmylib.a helper1.o helper2.o

        # �鿴������
        ar -t libmylib.a
    ``` 
    - **ʹ�þ�̬��**
    ```bash
        # �������Ӿ�̬��
        gcc -o myapp main.c -L. -lmylib

        # ����ֱ��ָ�����ļ�
        gcc -o myapp main.c libmylib.a
    ```
    - **��̬�⹤�����** 
      - **av����**
        ```bash
            # ������̬��
            ar rcs libmylib.a file1.o file2.o

            # ����ļ������п�
            ar r libmylib.a newfile.o

            # ɾ�����е��ļ�
            ar d libmylib.a oldfile.o

            # ��ȡ���е��ļ�
            ar x libmylib.a file1.o

            # �鿴������
            ar -t libmylib.a
        ``` 
      - **ranlib����**
        ```bash
            # Ϊ��̬�ⴴ���������������ӣ�
            ranlib libmylib.a

            # ar��sѡ���Ѿ������������
            # ar rcs �ȼ��� ar rc + ranlib
        ```
- **��̬���붯̬��Ա�**
![��̬���붯̬��Ա�](/picture/io11.png) 

- **��̬������ʾ��**
  - **Ŀ¼�ṹ**
    - ���д������ļ�
        -  main.c �������ļ� [main.cʾ��](/Static_library_test/main.c)
        -  src/   ���Դ��   [srcԴ��ʾ��](/Static_library_test/src/mathlib.c)
        -  inlcude/   ���ͷ�ļ� [includeͷ�ļ�ʾ��](/Static_library_test/include/mathlib.h)
        -  Makefile  �����ļ�   [Makefile�ļ�ʾ��](/Static_library_test/Makefile)
    ![Ŀ¼�ṹʾ��ͼ](/picture/io12.png) 
    - **Makefile�ļ�����**
    �� [Makefile�ļ�ʾ��](/Static_library_test/Makefile) Ϊ�ο�
      - **�������͹���**    ���峣�õĹ�����������޸ĺ�ά��
        ```bash
            # CC��C ������
            CC = gcc
            
            # AR����̬��������
            AR = ar
            
            # RM��ɾ���ļ�����
            RM = rm -f

            # MKDIR������Ŀ¼����
            MKDIR = mkdir -p
        ```
      - **����ѡ��**    ���ñ���ʹ��ѡ��
        ```bash
            # CFLAGS����������־  -Wall -Wextra����ʾ���о���  -O2���Ż�����2  -g������������Ϣ
            CFLAGS = -Wall -Wextra -O2 -g
            
            # ARFLAGS����̬����ѡ��  r���滻�����ļ� c�������⣨��������ڣ� s�������������൱�� ranlib��
            ARFLAGS = rcs
        ```
      - **Ŀ¼�ṹ**    ������ĿĿ¼�ṹ�����ִ�����֯����
        ```bash
            # ָ��Դ����Ŀ¼ - src
            SRC_DIR = src
            
            # ָ��ͷ�ļ�Ŀ¼ - include
            INC_DIR = include
            
            # �Զ����� ���ļ����Ŀ¼ lib
            LIB_DIR = lib
            
            # �Զ����� �м��ļ�Ŀ¼ - build 
            BUILD_DIR = build
            
            # �Զ����� ��ſ�ִ���ļ� - bin
            BIN_DIR = bin
        ```
      - **����Ϣ** ���������ƺ�·��
        ```bash
            # ָ����Ļ���������Ϊmath
            LIB_NAME = math 
            
            # ָ�������Ŀ�·�� lib/libmath.a
            LIBRARY = $(LIB_DIR)/lib$(LIB_NAME).a
        ```
      - **Դ�ļ�**  �Զ�����Դ�ļ������ɶ�Ӧ��Ŀ���ļ��б�
        ```bash
            # �ҵ����� src/*.c �ļ�
            SRCS = $(wildcard $(SRC_DIR)/*.c)
            
            # �� .c �ļ�·��ת��Ϊ .o �ļ�·��  ���磺src/math.c �� build/math.o
            OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

        ```
      - **������**  ���������������ļ�
        ```bash
            # ��Դ�ļ�
            MAIN_SRC = main.c
            
            # ��Ŀ���ļ�·��
            MAIN_OBJ = $(BUILD_DIR)/main.o
            
            # ���տ�ִ���ļ�·��
            MAIN_BIN = $(BIN_DIR)/calculator
        ```
      - **ͷ�ļ�·��**  ����ͷ�ļ�����·��
        ```bash
            # -Iinclude �� ���߱������� include Ŀ¼�в���ͷ�ļ�
            INCLUDES = -I$(INC_DIR)
        ```
      - **Ĭ��Ŀ��**    ����Ĭ�Ϲ���Ŀ��
        ```bash
            # ������ϵ���ȴ���Ŀ¼ �� ������ �� ������ִ���ļ�
            all: directories $(LIBRARY) $(MAIN_BIN)

            # ִ�� make �� make all ʱ��˳��ִ����ЩĿ��
        ```
      - **������Ҫ��Ŀ¼**  �������������Ŀ¼
        ```bash
            # ���� build/ lib/ bin/ Ŀ¼  ȷ�����Ŀ¼���ڣ������ļ��Ҳ���·���Ĵ���
            directories:
                $(MKDIR) $(BUILD_DIR) $(LIB_DIR) $(BIN_DIR)
        ```
      - **������̬��**  ������̬��Ĺ���
        ```bash
            # $@��Ŀ���ļ���lib/libmath.a��  $^�����������ļ������е� .o �ļ��� 
            $(LIBRARY): $(OBJS)
                $(AR) $(ARFLAGS) $@ $^
                @echo "��̬�⹹�����: $@"
        ```
      - **������Դ�ļ�**  ����Դ�ļ�ΪĿ���ļ���ģʽ����
        ```bash
            # %��ͨ�����ƥ���ļ���     $<����һ�������ļ���.c �ļ��� $@��Ŀ���ļ���.o �ļ���
            # ���磺src/math.c �� build/math.o
            $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
                $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
            
            # build/math.o: src/math.c
            #   gcc -Wall -Wextra -O2 -g -Iinclude -c math.c -o math.o    
        ```
      - **����������**  �����������ļ�
        ```bash
            # �����Ĺ�������Ϊ�������� src Ŀ¼��
            $(MAIN_OBJ): $(MAIN_SRC)
                $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

            # build/main.o: main.c
            #   gcc  -Wall -Wextra -O2 -g -Iinclude -c main.c main.o
        ```
      - **�������ɿ�ִ���ļ�**  �����������տ�ִ���ļ�
        ```bash
            # $<����һ�������ļ���build/main.o��  -Llib��ָ��������·��  -lmath������ libmath.a ��
            $(MAIN_BIN): $(MAIN_OBJ) $(LIBRARY)
                $(CC) $(CFLAGS) -o $@ $< -L$(LIB_DIR) -l$(LIB_NAME)
                @echo "��ִ���ļ��������: $@"

            # build/calculator: build/main.o lib/libmath.a
            #   gcc -Wall -Wextra -O2 -g -o calculator main.o -Llib -lmath
        ```
      - **�������ļ�**    �����������ɵ��ļ�
        ```bash
            # ɾ�� build��lib��bin Ŀ¼��������
            clean:
                $(RM) -r $(BUILD_DIR) $(LIB_DIR) $(BIN_DIR)
                @echo "�������"
        ```
      - **��ʾ������Ϣ**
        ```bash
            # ��ʾ��Ŀ�ṹ��Ϣ�����ڵ���
            info:
                @echo "Դ�ļ�: $(SRCS)"
                @echo "Ŀ���ļ�: $(OBJS)"
                @echo "���ļ�: $(LIBRARY)"
                @echo "��ִ���ļ�: $(MAIN_BIN)"
        ```
      - **���г���**
        ```bash
            # ���������г���
            run: $(MAIN_BIN)
                ./$(MAIN_BIN)
        ```
      - **���԰汾**    �������԰汾
        ```bash
            # -DDEBUG: ���� DEBUG ��     -O0�������Ż������ڵ���
            debug: CFLAGS += -DDEBUG -O0
            debug: all
        ```
      - **��̬����**    ��������̬�����İ汾
        ```bash
            # �ڴ�������δ������Ϊ���
            check: CFLAGS += -fsanitize=address -fsanitize=undefined
            check: all
        ```
      - **����αĿ��**  ������ЩĿ�겻��ʵ���ļ� ��ֹ��ͬ���ļ���ͻ ȷ����ЩĿ�����Ǳ�ִ��
        ```bash
            # ����αĿ��
            .PHONY: all clean info run debug check directories
        ```

### GCC���ӿ�ԭ��
- **���ӵĻ�������** �� �����ǽ����Ŀ���ļ���.o���Ϳ��ļ���.a/.so���ϲ���һ����ִ���ļ������Ĺ���
- **���ӵ���Ҫ����** ��
  - ���Ž������ҵ�ÿ�����ŵĶ���
  - �ض�λ�������������붨���ַ����
  - ��ַ���䣺Ϊ��������ݷ������յ�ַ
- **��������������**
```mermaid
graph TD
    A[Դ����] --> B[����]
    B --> C[Ŀ���ļ� .o]
    C --> D[������]
    E[��̬�� .a] --> D
    F[��̬�� .so] --> D
    D --> G[��ִ���ļ�]
    
    style C fill:#e1f5fe
    style E fill:#f3e5f5
    style F fill:#fff3e0
    style G fill:#c8e6c9
```
- **���Ž�������**
  - �������ͣ�
    - ������ţ�������������ʵ�ʶ���
    - ���÷��ţ��������á�����ʹ��
    - δ������ţ�������δ����ķ���
  - ���Ž����㷨
    ```c
        // ������ά���������ϣ�
        δ�������ż��� = {����δ����ķ���}
        �Ѷ�����ż��� = {}
        ��ǰĿ���ļ����� = {}

        foreach (�����ļ�) {
            if (��Ŀ���ļ�) {
                ������ż��뵱ǰ����
                �������е�δ�������
            }
            if (�ǿ��ļ�) {
                ֻ��ȡ�ܽ�����ǰδ������ŵĳ�Ա
            }
        }

        if (δ�������ż��� != ��) {
            ����: undefined reference
        }
    ```
- **��̬��������ϸ����**
���農̬��Ľṹ���£� 
    ```t
        libmath.a
        ������ math_basic.o
        ��   ������ add (����)
        ��   ������ subtract (����) 
        ��   ������ multiply (����, δ����)
        ������ math_advanced.o
            ������ multiply (����)
            ������ power (����)
            ������ factorial (����)
    ```
���ӹ���ʾ��:
```bash
    # ���� main.o �е����� add() �� multiply()
    gcc main.o -L. -lmath -o program
```
������ִ�в���:
  - �� main.o ���뵱ǰ����
    - δ�������: add, multiply
  - ���� libmath.a��
    - ���� math_basic.o���ṩ add����Ҫ multiply
    - ��ȡ math_basic.o������δ�������: multiply
    - ���� math_advanced.o���ṩ multiply
    - ��ȡ math_advanced.o�����з��Ž������
  - ���Կ��������޹ص�Ŀ���ļ�

- **��̬��������ϸ����**
����ʱ��
```bash
    gcc -shared -fPIC -o libmath.so math_basic.c math_advanced.c
    gcc main.o -L. -lmath -o program
``` 
������������
  1. ��¼��Ҫ libmath.so
  2. �ڿ�ִ���ļ��д��� .dynamic ��
  3. ��ӷ����ض�λ��Ϣ
����ʱ��
```bash
    ./program
```
��̬������������
  1. ��ȡ .dynamic �Σ�������Ҫ libmath.so
  2. ������·����LD_LIBRARY_PATH, /etc/ld.so.conf �ȣ�
  3. ���� libmath.so ���ڴ�
  4. ���з����ض�λ
  5. ִ�г���

### Linux����ϵͳ���ض�̬��
- **��̬���ص�����ܹ�**
```mermaid
graph TD
    A[��ִ���ļ�] --> B[�ں� execve]
    B --> C[�û��ռ�]
    C --> D[��̬������ ld-linux.so]
    D --> E[����������]
    E --> F[�����ض�λ]
    F --> G[����ִ��]
    
    style D fill:#e1f5fe
    style E fill:#fff3e0
    style F fill:#f3e5f5
```
- **��ִ���ļ��еĶ�̬��Ϣ**
�鿴��̬����Ϣ��
```bash
    readelf -d /bin/ls

    # ���ʾ����
    Dynamic section at offset 0x1e28 contains 27 entries:
    Tag        Type                         Name/Value
    0x0000000000000001 (NEEDED)             Shared library: [libselinux.so.1]
    0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
    0x000000000000000c (INIT)               0x400520
    0x000000000000000d (FINI)               0x4012d4
    0x0000000000000019 (INIT_ARRAY)         0x601e18
    0x000000000000001b (INIT_ARRAYSZ)       8 (bytes)
``` 
�ؼ���̬��ǩ��
  - NEEDED����Ҫ�Ĺ����
  - RPATH��������·��
  - RUNPATH������ʱ������·��
  - INIT����ʼ��������ַ
  - FINI����ֹ������ַ
- **��̬������ (ld-linux.so)**
��λ��̬��������
```bash
    # �鿴��ִ���ļ�ʹ�õĶ�̬������
    readelf -l /bin/ls | grep interpreter

    # ���ʾ����
    [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]
```

��̬��������ְ��
  - �������������Ĺ����
  - ���з����ض�λ
  - ִ�г�ʼ������
  - ������Ȩ����������ڵ�

- **������·������**
����·�����ȼ���
```mermaid
graph LR
    A[DT_RPATH<br>����ʱָ��] --> B[LD_LIBRARY_PATH<br>��������]
    B --> C[DT_RUNPATH<br>����ʱ·��]
    C --> D[��������<br>/etc/ld.so.cache]
    D --> E[Ĭ��·��<br>/lib, /usr/lib]
    
    style A fill:#e1f5fe
    style B fill:#fff3e0
```
ʵ������˳��
  - ��ִ���ļ��� RPATH��������ڣ�
  - LD_LIBRARY_PATH ��������
  - ��ִ���ļ��� RUNPATH��������ڣ�
  - /etc/ld.so.cache �����ļ�
  - Ĭ��ϵͳ·����/lib, /usr/lib

- **�����ļ��ع���**
�׶�1���ں˴���
```bash
    # ��ִ�� ./program ʱ��
    execve("./program", argv, envp)
        ��
    �ں˼���ļ���ʽ��ELF��
        ��
    ���س���ε��ڴ�
        ��
    ���ö�̬������·��
        ��
    �������̲�������̬������
```
�׶�2����̬��������ʼ��
```bash
    // ld-linux.so �ĳ�ʼ������
    1. ����������ض�λ��Ϣ
    2. �����쳣����
    3. ��ȡ�����в����ͻ�������
    4. ��ʼ���ڲ����ݽṹ
```

�׶�3������������
```bash
    // �ݹ��������������
    foreach (NEEDED entry in executable) {
        �ݹ���ؿ⼰������
        ά���Ѽ��ؿ���б�
        ���汾������
    }
```

�׶�4�������ض�λ
```bash
    // ���Ž������ض�λ
    foreach (relocation entry) {
        ���ҷ��Ŷ��壨�����м��صĿ��У�
        ����ҵ������µ�ַ����
        ���δ�ҵ��������ʹ���ӳٰ�
    }
```

�׶�5����ʼ��ִ��
```bash
    // ִ�г�ʼ������
    �������п�� .init ����
    ���ó���� main ����
    ������������...
```

- **�ӳٰ�** (PLT/GOT)
�������ӱ� (PLT) ��ȫ��ƫ�Ʊ� (GOT)��
```mermaid
graph LR
    A[������ú���] --> B[PLT��Ŀ]
    B --> C[��һ�ε���] --> D[GOTָ���������]
    B --> E[��������] --> F[GOTָ��ʵ�ʺ���]
    D --> G[��̬����������]
    G --> H[����GOT]
    H --> I[��ת��ʵ�ʺ���]
```

�ӳٰ󶨵����ƣ�
  - �����ٶȿ죺����Ҫ������ʱ�������з���
  - �ڴ��Ч��ֻ����ʵ��ʹ�õĺ���
  - �������ã���һ�ε��ú�ֱ����ת

- **��ʼ������ֹ**
��ʼ��˳��
```c
    // ��ʼ����������˳��
    1. ��̬����������ĳ�ʼ��
    2. ����������� .init ������������ȣ�
    3. ������� .init ����
    4. main() ����
```

��ֹ˳��
```c
    // ��ֹ��������˳�򣨳����˳�ʱ��
    1. main() ��������
    2. ���п�� .fini ����������
    3. �����˳�
```

- **ʵ�ʼ��ع���ʾ��**
�鿴��ϸ���ع��̣�
```bash
    # ���õ��Ի�������
    export LD_DEBUG=all
    ./program

    # ����ֻ�鿴�����
    export LD_DEBUG=libs
    ./program
```

�������ʾ����
```bash
    linux-vdso.so.1 (0x00007ffd45bd3000)
    libmath.so => ./lib/libmath.so (0x00007f8a1b2d4000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f8a1b0d3000)
    /lib64/ld-linux-x86-64.so.2 (0x00007f8a1b4d8000)
```

- **������������**
���Ի���������
```bash
    # ��ʾ���е�����Ϣ
    export LD_DEBUG=all

    # ֻ��ʾ�������Ϣ
    export LD_DEBUG=libs

    # ��ʾ���Ž���
    export LD_DEBUG=symbols

    # ��ʾ�ض�λ��Ϣ
    export LD_DEBUG=reloc

    # ������ļ�
    export LD_DEBUG_OUTPUT=debug.log
```

������ػ���������
```bash
    # �����ӳٰ󶨣������������з��ţ�
    export LD_BIND_NOW=1

    # ���ÿ������
    export LD_LINUX_LOADER=/path/to/ld-linux.so

    # Ԥ���ؿ⣨���ȼ��أ�
    export LD_PRELOAD=/path/to/libdebug.so
```

- **ϵͳ����**
�����ļ���
```bash
    # ϵͳ������
    /etc/ld.so.conf        # �������ļ�
    /etc/ld.so.conf.d/     # ����Ŀ¼
    /etc/ld.so.cache       # ���������Ļ���

    # ���»���
    sudo ldconfig
```

������ƣ�
```bash
    # �鿴��������
    ldconfig -p | grep libmath

    # �ؽ�����
    sudo ldconfig -v
```

- **��ȫ����**
��ȫ���ԣ�
```bash
    # SUID�������LD_LIBRARY_PATH
    chmod u+s program      # ����SUIDλ
    ./program              # ��ʱLD_LIBRARY_PATH��Ч

    # ��ȫ����ģʽ
    export LD_SECURE_LOAD=1  # ֻ���α�׼·��
```

��ȫ©��������
```bash
    # ��ֹ���Žٳ�
    export LD_DYNAMIC_WEAK=0  # ���������Ÿ���

    # �ڴ汣��
    export LD_BIND_NOT=1      # ʹGOTֻ��
```

- **�����Ż�**
Ԥ�����Ż���
```bash
    # ��������ʱ�ض�λ
    sudo prelink -amR

    # ���Ԥ����״̬
    prelink -p
```

���Ż����ɣ�
```bash
    # ʹ�÷��Ű汾����
    gcc -shared -Wl,--version-script=mapfile -o libmath.so math.c

    # �Ż���˳�򣨳��ÿ��ȼ��أ�
    export LD_LIBRARY_PATH=/opt/fastlibs:$LD_LIBRARY_PATH
```

- **�����ų�**
����������ϣ�
```bash
    # ��������
    ldd program

    # �鿴ȱʧ�ķ���
    nm -D program | grep UND

    # �����ͻ
    LD_DEBUG=libs ./program 2>&1 | grep conflict

    # �鿴���ع���
    strace -e open,mmap ./program
```

������
```bash
    # ����: cannot open shared object file
    # ���: ���LD_LIBRARY_PATH��ʹ��ldconfig

    # ����: symbol not found
    # ���: ����汾�ͷ��ŵ���

    # ����: version mismatch
    # ���: ���±����ʹ�ü��ݰ汾
```

- **ʵ�ʰ������Զ�������**
������ʹ���Զ���·���Ŀ�
```bash
    # ����ʱָ��rpath
    gcc -o program main.c -L./lib -lmath -Wl,-rpath,'$ORIGIN/lib'

    # ����ʱ��������LD_LIBRARY_PATH
    ./program
```

���������Կ��������
```bash
    # ��ϸ����
    export LD_DEBUG=files
    export LD_DEBUG_OUTPUT=debug.log
    ./program

    # �����������
    grep "loading file" debug.log
```