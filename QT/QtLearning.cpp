
June::study::QtLearning() {

    qt系统提供的类头文件 无.h后缀
    qt一个类对应一个头文件 类名和头文件名一致

    .pro文件 {

        .pro工程文件 由qmake自动生成用于生产Makefile的配置文件

        .pro示例: {
            QT       += core gui        // 引入core和gui模块

            greaterThan(QT_MAJOR_VERSION, 4): QT += widgets          // 如果Qt版本大于4 那么引入widgets模块

            CONFIG += c++17     // c++17标准

            # You can make your code fail to compile if it uses deprecated APIs.
            # In order to do so, uncomment the following line.
            #DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

            /* 要编译的源文件列表 */
            SOURCES += \
                main.cpp \
                zozowidget.cpp

            /* 要编译的头文件列表 */
            HEADERS += \
                zozowidget.h

            # Default rules for deployment.
            qnx: target.path = /tmp/$${TARGET}/bin          // qnx平台的部署路径
            else: unix:!android: target.path = /opt/$${TARGET}/bin   // unix平台的部署路径
            !isEmpty(target.path): INSTALLS += target       // 安装目标文件到指定路径
        }

        .pro文件的规则:

            1.注释
                    从'#'开始 到该行结束

            2.模块引入
                    QT += 模块名    表示当前项目引入Qt哪些模块

                    引入模块简单理解为'引入C/C++头文件搜索路径' 如果没引入对应模块就使用该头文件的话会报错说找不到该头文件
                    当然不必要的模块还是别引入 因为引入模块不仅仅是引入头文件搜索路径那么简单 还包括引入连接的库等一系列操作 会让程序变臃肿

            3. 模板变量告诉qmake为这个应用程序生成哪种makefile 下面是可供使用的选择 TEMPLATE = app

                    app - 建立一个应用程序的makefile 这是默认值 所以如果模板没有被指定 这个将被使用

                    lib - 建立一个库的makefile

                    vcapp - 建立一个应用程序的VisualStudio项目文件

                    vclib - 建立一个库的VisualStudio项目文件

                    subdirs - 这是一个特殊的模板 它可以创建一个能够进入特定目录并且为一个项目文件生成makefile并且为它调用make的makefile

            4.指定生成的应用程序名

                    TARGET = QtDemo

            5.工程中包含的头文件

                    HEADERS += include/painter.h

            6.工程中包含的.ui设计文件

                    FORMS += forms/painter.ui

            7.工程中包含的源文件

                    SOURCES += sources/main.cpp sources

            8.工程中包含的资源文件

                    RESOURCES += qrc/painter.qrc

            9.greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

                如果QT_MAJOR_VERSION大于4  需要增加widgets模块 如果项目仅需支持Qt5 也可以直接添加“QT += widgets”一句 不过为了保持代码兼容 最好还是按照QtCreator生成的语句编写

            10.配置信息

                CONFIG用来告诉qmake关于应用程序的配置信息
                CONFIG += c++11 //使用c++11的特性（qt5.6以上版本默认使用C++11）
                使用'+=' 指添加配置选项到任何一个已经存在的配置中 这样做比使用'='那样替换已经指定的所有选项更安全
    }

    命名规则: {
        Qt的命名规则是: {
            类名：驼峰命名法 即 首字母大写的单词 后面跟着多个小写单词
            eg: {
                QPushButton QLineEdit QTextEdit QColor
            }

            函数名、变量名 第一个首字母小写 之后每个首字母大写
            eg: {
                myName myVariable
                vode connectMyFunction()
            }

            类的成员变量'设置函数'  使用: set + 成员变量名
            eg:{
                void setMyVariable(int value)
            }

            '获取'成员变量的函数 使用: 成员变量名
            eg: {
                int myVariable();

                如果是bool类型 有可能会用一些表示状态的术语 如isVisilble hasFocus
                bool isVisible();
            }
        }
    }

    Qt快捷键: {
        'Ctrl + R'  - 运行
        'Ctrl + B'  - 编译
        'F1'        - 帮助文档
        'F2' or 'Ctrl + 鼠标点击'   - 跳转到定义
        'F4'        - 同名头文件\源文件直接跳转
        'Ctrl + i'  - 自动对齐
        'Ctrl + /'  - 注释代码
        'Ctrl + 鼠标滑轮'  - 放大缩小代码
        'Ctrl + Shift + ↓ (or ↑)'  - 移动代码行

    }


}