### ѹ������
- ==**tar**==
  - **ѹ��**
    1. ���� .tar.gz �ļ�����ã�
        ```bash
            # �� file1.txt, dir2 �����ѹ���� archive.tar.gz
            tar -zcvf archive.tar.gz file1.txt dir2/
            # ���̣� �ȴ���� archive.tar������ gzip ѹ���� archive.tar.gz
        ```
    
    2. ���� .tar.bz2 �ļ� (ѹ���ʸ��� ����)
        ```bash
            tar -cjvf archive.tar.bz2 file1.txt dir2/ 
        ```

    3. ���� .tar.xz �ļ� (ѹ������� ����)
        ```bash
            tar -cJvf archive.tar.xz file1.txt dir2/ 
        ```
  - **��ѹ**
    1. ��ѹ .tar.gz �ļ�
        ```bash
            # ��ѹ����ǰĿ¼
            tar -xzvf archive.tar.gz
            # ��ѹ��ָ��Ŀ¼ /path/to/target
            tar -xzvf archive.tar.gz -C /path/to/target
        ``` 
    2. ��ѹ .tar.bz2 �ļ�
        ```bash
            tar -xjvf archive.tar.bz2
        ```
    3. ��ѹ .tar.xz �ļ�
        ```bash
            tar -xJvf archive.tar.xz
        ```
    4. ��ѹ��ͨ�� .tar �ļ����������δѹ����
        ```bash
            tar -xvf archive.tar
        ```
    5. �鿴 ����ѹ
        ```bash
            # �鿴 .tar.gz �ļ�����
            tar -tzvf archive.tar.gz
            # �鿴 .tar.bz2 �ļ�����
            tar -tjvf archive.tar.bz2
        ```       

- ==**zip**==
  - **��װ**��
    ```bash
        sudo apt update && sudo apt install zip unzip
    ```
  - **ѹ��**
   1. ѹ�������ļ�
        ```bash
            zip archive.zip file1.txt
        ```
   2. ѹ������ļ���Ŀ¼
        ```bash
            zip archive.zip file1.txt file2.jpg directory/
        ```
   3. �ݹ�ѹ��Ŀ¼
        ```bash
            zip -r archive.zip my_directory/
        ```
   4. ѹ����ǰĿ¼�������ļ�
        ```bash
            zip archive.zip *
        ```
   5. ��ѹ���ʣ����ٶȽ�����
        ```bash
            zip -9 -r archive.zip my_directory/
            # -9 ��ʾ���ѹ������1-9) 9Ϊ���
        ```
   6. ����ѹ�����������룩
        ```bash
            zip -e -r secure.zip my_directory/
            # -e ѡ�����ʾ����������
        ``` 
  - **��ѹ**
    1. ��ѹ����ǰĿ¼
    ```bash
        unzip archive.zip
    ```
    2. ��ѹ��ָ��Ŀ¼
    ```bash
        unzip archive.zip -d /path/to/target_directory
    ```
    3. �鿴ѹ�������� ������ѹ��
    ```bash
        unzip -l archive.zip
    ```
    4. ����ģʽ��ѹ ������ʾ�����Ϣ��
    ```bash
        unzip -q archive.zip
    ```
    5. ���ǽ�ѹ ������ʾֱ�Ӹ����Ѵ����ļ���
    ```bash
        unzip -o archive.zip
    ```
    6. ��ѹ����ZIP�ļ�
    ```bash
        unzip secure.zip
        # ϵͳ����ʾ��������
    ```     
- ==**7z**==
  - **��װ**
    ```bash
        sudo apt update && sudo apt install p7zip-full p7zip-rar
    ```
  - **ѹ��**
    1. ����ѹ��
    ```bash
        7z a archive.7z file1.txt
    ```
    2. ѹ������ļ���Ŀ¼
    ```bash
        7z a archive.7z file1.txt dir1/ file2.jpg
    ```
    3. �ݹ�ѹ��Ŀ¼
    ```bash
        7z a archive.7z my_directory/
    ```
    4. ���ѹ������
    ```bash
        7z a -mx=9 archive.7z my_directory/
        # -mx=9 ��ʾ����ѹ��
    ```
    5. ����ѹ��
    ```bash
        7z a -p���� archive.7z my_directory/
        # ����
        7z a -p archive.7z my_directory/
        # ����ʾ��������
    ```
    6. �����ļ���
    ```bash
        7z a -p���� -mhe=on archive.7z my_directory/
        # -mhe=on ͬʱ�����ļ���
    ``` 
  - **��ѹ**
    1. ��ѹ����ǰĿ¼
    ```bash
        7z x archive.7z
    ```
    2. ��ѹ��ָ��Ŀ¼
    ```bash
        7z x archive.7z -o/path/to/target
        # ����
        7z x archive.7z -o"path/to/target"
    ```
    3. ����ģʽ��ѹ
    ```bash
        7z x -y archive.7z
        # -y ��������ʾ�ش�"��"
    ```
    4. ��ѹ���ܵ�7Z�ļ�
    ```bash
        7z x -p���� archive.7z
        # ����
        7z x -p archive.7z
    ```
    5. ��ѹ�ض��ļ� 
    ```bash
        7z x archive.7z specific_file.txt
    ```
  - **�鿴�͹���ѹ����** 
    1. �г�ѹ��������
    ```bash
        7z l archive.7z
    ```
    2. ����ѹ����������
    ```bash
        7z t archive.7z
    ```
    3. ����ļ�������ѹ����
    ```bash
        7z u archive.7z new_file.txt
    ```
    4. ��ѹ������ɾ���ļ�
    ```bash
        7z d archive.7z file_to_remove.txt
    ```
  - **֧�ֵ�������ʽ**
    ```bash
        # ѹ��Ϊ zip ��ʽ
        7z a archive.zip files/

        # ��ѹ rar �ļ�
        7z x archive.rar

        # ��ѹ tar.gz �ļ�
        7z x archive.tar.gz

        # ��ѹ iso ����
        7z x image.iso
    ```   

- ==**unar��ѹ���� ���Զ�������룩**==
  - **��װunar**
  ```bash
    sudo apt update && sudo apt install unar
  ```
  1. **������ѹ** 
    ```bash
        # ��ѹ����ǰĿ¼
        unar filename.zip
        # ��ѹ����ļ�
        unar file1.rar file2.zip
    ```
  2. **ָ�����Ŀ¼**
    ```bash
        unar -o ~/Downloads/ file.zip
    ```
  3. **ǿ�Ƹ����Ѵ����ļ�**  
    ```bash
        unar -f file.zip
    ```
  4. **ָ������**
    ```bash
        # �����ض�����
        unar -e GB18030 file.zip
    ```
  5. **��ѹ����ѹ���ļ���ʱ���**
    ```bash
        unar -D file.zip
    ```
  6. **�����ѹ**
    ```bash
        unar -p mypassword encrypted.zip
    ``` 

  - **������ѹ���ص��ļ�**
    ```bash
    #!/bin/bash        
    find downloads/ -name "*.zip" -o -name "*.rar" -o -name "*.7z" | while read file; do
        unar "$file" -o extracted/
    done
        # ��ѹ downloads/ Ŀ¼�µ�����ѹ���ļ�
    ```
  
    - **�鿴ѹ��������** 
    ```bash
        lsar file.zip
    ```
    - **�鿴��ϸ��Ϣ**
    ```bash
        lsar -l file.zip 
    ```