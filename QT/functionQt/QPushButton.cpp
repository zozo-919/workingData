July 4, 2024 :: {

    QPushButton 按钮: {
        QPushButton 继承自QAbstractButton (间接继承自QWidget) 是一个可以点击的按钮控件;
        QAbstractButton 是所有按钮控件的基类 包含很多通用按钮功能

        QPushButton按钮上可放置文本、图标(按钮左侧)
        通常用法: 是按钮内嵌到某个窗口中 作为子控件和其他控件一起使用

        QPushButton提供三种构造函数: {
            1. 按钮没有文本 图标也没有的构造函数
                QPushButton(QWidget *parent = nullptr);
                    eg: {
                        QPushButton *button1 = new QPushButton(this);           // 父窗口为this
                    }

            2. 带文本的构造函数 传入一个字符串作为按钮的文本
                QPushButton(const QString &text, QWidget *parent = nullptr);
                    eg: {
                        QPushButton *button2 = new QPushButton("按钮2", this);  // 父窗口为this
                    }

            3. 带图标的构造函数 传入一个QIcon对象作为按钮的图标
                QPushButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr);
                    eg: {
                        QPushButton *button3 = new QPushButton(QIcon("icon.png"), "按钮3", this);  // 父窗口为this
                    }

            参数说明: {
                parent - 父控件指针 通常是窗口对象
                text - 按钮文本
                icon - 按钮图标
            }

        }

        QPushButton 常用属性: {
            text() - 获取按钮的文本内容                         setText(const QString &text) - 设置按钮的文本内容 ;
            icon() - 获取按钮的图标内容                         setIcon(const QIcon &icon) - 设置按钮的图标内容 ;
            iconSize() - 获取按钮的图标大小                     setIconSize(const QSize &size) - 设置按钮的图标大小 ;
            size() - 获取按钮的大小                             reSize(int w, int h) - or - reSize(const QSize &size) - 设置按钮的大小 ;
            font() - 获取按钮的字体                             setFont(const QFont &font) - 设置按钮的字体 ;
            isFlat() - 是否显示边框                             setFlat(bool) - 设置按钮是否平面化 ;    默认(false) - 显示边框
            isEnabled() - 获取按钮是否可用                      setEnabled(bool) - 设置按钮是否可用 ;   true - 可用/false - 不可用
            autoDefault() - 获取按钮是否自动响应按下回车键      setAutoDefault(bool) - 设置按钮是否自动响应按下回车键;   默认(false)
        }
        QPushButton 常用方法:{
            move(int x, int y) - 移动按钮到父窗口指定位置
            setStyleSheet(const QString &styleSheet) - 设置按钮的样式
            setGeometry(int x, int y, int w, int h)  -  设置按钮的位置和大小
            adjustSize() - 调整按钮大小以适应文本和图标
            setDisabled(bool) - 设置按钮是否可用   true - 禁用/false - 可用
        }
        常用的 信号与槽: {
            信号函数: {
                clicked()   -   按钮被按下并释放 触发此信号
                pressed()   -   按钮被按下 触发此信号
                released()  -   按钮被释放 触发此信号
            }
            槽函数: {
                click()     -       单击指定按钮
                setIconSize() -     重置按钮的图标大小
                hide()      -       隐藏按钮
                setMenu()   -       弹出与按钮相关的菜单
            }
        }

        eg: {
            QPushButton *button1 = new QPushButton(this);   // 创建一个按钮 父窗口为this
            this->setFixedSize(500, 500);                   // 设置固定大小的父窗口
            button1->setText("按钮1");                       // 设置按钮的文本

            button1->setIcon(QIcon("icon.png"));             // 设置按钮的图标
            /* 这里传入的QIcon("icon.png") 是 显式调用 '构造函数QIcon(const QString &fileName)' 创建的QIcon对象 不是所有构造函数都可以显式调用 */

            button1->reSize(100, 60);                        // 设置按钮的大小
            button1->setIconSize(QSize(32, 32));             // 设置按钮的图标大小
            button1->setFont(QFont("微软雅黑", 12));         // 设置按钮上文本的字体
            button1->setFlat(false);                        // 设置按钮显示边框
            button1->setEnabled(true);                      // 设置按钮可用
            button1->setAutoDefault(false);                 // 设置按钮不响应回车键
            button1->setStyleSheet("QPushButton{background-color:red;color:white;border:none;}");  // 设置按钮的样式 背景色为红色 字体颜色为白色 边框为无
            button1->setGeometry(100, 100, 100, 50);        // 设置按钮的位置和大小
            button1->move(100, 100);                        // 移动按钮到父窗口指定位置
            button1->adjustSize();                          // 自动调整按钮大小以适应文本和图标
            button1->setDisabled(false);                     // 设置按钮可用

            connect(button1, SIGNAL(clicked()), this, SLOT(click()));  // 连接信号与槽 单击按钮触发槽函数click()

        }

    }

}
