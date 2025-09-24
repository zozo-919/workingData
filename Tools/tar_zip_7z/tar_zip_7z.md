### 压缩工具
- ==**tar**==
  - **压缩**
    1. 创建 .tar.gz 文件（最常用）
        ```bash
            # 将 file1.txt, dir2 打包并压缩成 archive.tar.gz
            tar -zcvf archive.tar.gz file1.txt dir2/
            # 过程： 先打包成 archive.tar，再用 gzip 压缩成 archive.tar.gz
        ```
    
    2. 创建 .tar.bz2 文件 (压缩率更高 更慢)
        ```bash
            tar -cjvf archive.tar.bz2 file1.txt dir2/ 
        ```

    3. 创建 .tar.xz 文件 (压缩率最高 最慢)
        ```bash
            tar -cJvf archive.tar.xz file1.txt dir2/ 
        ```
  - **解压**
    1. 解压 .tar.gz 文件
        ```bash
            # 解压到当前目录
            tar -xzvf archive.tar.gz
            # 解压到指定目录 /path/to/target
            tar -xzvf archive.tar.gz -C /path/to/target
        ``` 
    2. 解压 .tar.bz2 文件
        ```bash
            tar -xjvf archive.tar.bz2
        ```
    3. 解压 .tar.xz 文件
        ```bash
            tar -xJvf archive.tar.xz
        ```
    4. 解压普通的 .tar 文件（仅打包，未压缩）
        ```bash
            tar -xvf archive.tar
        ```
    5. 查看 不解压
        ```bash
            # 查看 .tar.gz 文件内容
            tar -tzvf archive.tar.gz
            # 查看 .tar.bz2 文件内容
            tar -tjvf archive.tar.bz2
        ```       

- ==**zip**==
  - **安装**：
    ```bash
        sudo apt update && sudo apt install zip unzip
    ```
  - **压缩**
   1. 压缩单个文件
        ```bash
            zip archive.zip file1.txt
        ```
   2. 压缩多个文件和目录
        ```bash
            zip archive.zip file1.txt file2.jpg directory/
        ```
   3. 递归压缩目录
        ```bash
            zip -r archive.zip my_directory/
        ```
   4. 压缩当前目录下所有文件
        ```bash
            zip archive.zip *
        ```
   5. 高压缩率（但速度较慢）
        ```bash
            zip -9 -r archive.zip my_directory/
            # -9 表示最高压缩级别（1-9) 9为最高
        ```
   6. 加密压缩（设置密码）
        ```bash
            zip -e -r secure.zip my_directory/
            # -e 选项会提示你输入密码
        ``` 
  - **解压**
    1. 解压到当前目录
    ```bash
        unzip archive.zip
    ```
    2. 解压到指定目录
    ```bash
        unzip archive.zip -d /path/to/target_directory
    ```
    3. 查看压缩包内容 （不解压）
    ```bash
        unzip -l archive.zip
    ```
    4. 安静模式解压 （不显示输出信息）
    ```bash
        unzip -q archive.zip
    ```
    5. 覆盖解压 （不提示直接覆盖已存在文件）
    ```bash
        unzip -o archive.zip
    ```
    6. 解压加密ZIP文件
    ```bash
        unzip secure.zip
        # 系统会提示输入密码
    ```     
- ==**7z**==
  - **安装**
    ```bash
        sudo apt update && sudo apt install p7zip-full p7zip-rar
    ```
  - **压缩**
    1. 基本压缩
    ```bash
        7z a archive.7z file1.txt
    ```
    2. 压缩多个文件和目录
    ```bash
        7z a archive.7z file1.txt dir1/ file2.jpg
    ```
    3. 递归压缩目录
    ```bash
        7z a archive.7z my_directory/
    ```
    4. 最高压缩级别
    ```bash
        7z a -mx=9 archive.7z my_directory/
        # -mx=9 表示极限压缩
    ```
    5. 加密压缩
    ```bash
        7z a -p密码 archive.7z my_directory/
        # 或者
        7z a -p archive.7z my_directory/
        # 会提示输入密码
    ```
    6. 加密文件名
    ```bash
        7z a -p密码 -mhe=on archive.7z my_directory/
        # -mhe=on 同时加密文件名
    ``` 
  - **解压**
    1. 解压到当前目录
    ```bash
        7z x archive.7z
    ```
    2. 解压到指定目录
    ```bash
        7z x archive.7z -o/path/to/target
        # 或者
        7z x archive.7z -o"path/to/target"
    ```
    3. 安静模式解压
    ```bash
        7z x -y archive.7z
        # -y 对所有提示回答"是"
    ```
    4. 解压加密的7Z文件
    ```bash
        7z x -p密码 archive.7z
        # 或者
        7z x -p archive.7z
    ```
    5. 解压特定文件 
    ```bash
        7z x archive.7z specific_file.txt
    ```
  - **查看和管理压缩包** 
    1. 列出压缩包内容
    ```bash
        7z l archive.7z
    ```
    2. 测试压缩包完整性
    ```bash
        7z t archive.7z
    ```
    3. 添加文件到现有压缩包
    ```bash
        7z u archive.7z new_file.txt
    ```
    4. 从压缩包中删除文件
    ```bash
        7z d archive.7z file_to_remove.txt
    ```
  - **支持的其他格式**
    ```bash
        # 压缩为 zip 格式
        7z a archive.zip files/

        # 解压 rar 文件
        7z x archive.rar

        # 解压 tar.gz 文件
        7z x archive.tar.gz

        # 解压 iso 镜像
        7z x image.iso
    ```   

- ==**unar解压工具 （自动处理编码）**==
  - **安装unar**
  ```bash
    sudo apt update && sudo apt install unar
  ```
  1. **基本解压** 
    ```bash
        # 解压到当前目录
        unar filename.zip
        # 解压多个文件
        unar file1.rar file2.zip
    ```
  2. **指定输出目录**
    ```bash
        unar -o ~/Downloads/ file.zip
    ```
  3. **强制覆盖已存在文件**  
    ```bash
        unar -f file.zip
    ```
  4. **指定编码**
    ```bash
        # 尝试特定编码
        unar -e GB18030 file.zip
    ```
  5. **解压后保留压缩文件的时间戳**
    ```bash
        unar -D file.zip
    ```
  6. **密码解压**
    ```bash
        unar -p mypassword encrypted.zip
    ``` 

  - **批量解压下载的文件**
    ```bash
    #!/bin/bash        
    find downloads/ -name "*.zip" -o -name "*.rar" -o -name "*.7z" | while read file; do
        unar "$file" -o extracted/
    done
        # 解压 downloads/ 目录下的所有压缩文件
    ```
  
    - **查看压缩包内容** 
    ```bash
        lsar file.zip
    ```
    - **查看详细信息**
    ```bash
        lsar -l file.zip 
    ```