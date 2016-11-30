#include "rfidoperating.h"

RfidOperating::RfidOperating()
{
    loadDLL();
}

void RfidOperating::loadDLL()
{
    //加载读卡器动态链接库
    mainLib = new QLibrary("MasterRDnew.dll");
    if(!mainLib->load())
    {
        errorMessage("动态链接库加载失败!");
        //没有动态链接库退出程序
        exit(1);
    }
    //验证动态链接库函数是否读取成功
    qDebug()<<"版本号：" << currentLibraryVersion();
}

void RfidOperating::errorMessage(QString errorString)
{
    QMessageBox::critical(NULL, "错误", errorString);
}

/**
 * @brief 获取动态库的版本号
 * @return  版本号
 */
int RfidOperating::currentLibraryVersion()
{
    lib_ver = (Lib_Ver)mainLib->resolve("lib_ver");
    if(!lib_ver)
    {
        errorMessage("动态库内容加载失败!");
        exit(1);
    }

    unsigned int version = 0;
    lib_ver(&version);
    return version;
}

/**
 * @brief 初始化端口
 * @param port 端口号
 */
void RfidOperating::intialPort(int port)
{
    rf_init_com = (Rf_Init_Com)mainLib->resolve("rf_init_com");
    if(!rf_init_com)
    {
        errorMessage("动态库内容加载失败!");
        exit(1);
    }

    if (rf_init_com(0, port, 19200))
    {
        errorMessage("端口初始化失败!");
    }
}

/**
 * @brief 关闭串口
 */
void RfidOperating::closePort()
{
    rf_ClosePort = (Rf_ClosePort)mainLib->resolve("rf_ClosePort");
    if(!rf_ClosePort)
    {
        errorMessage("动态库内容加载失败!");
        exit(1);
    }

    rf_ClosePort();
}

/**
 * @brief 控制蜂鸣器响
 * @param mSec 时间
 */
void RfidOperating::controlBeep(unsigned char mSec)
{
    rf_beep = (Rf_Beep)mainLib->resolve("rf_beep");
    if(!rf_beep)
    {
        errorMessage("动态库内容加载失败!");
        exit(1);
    }
    rf_beep(0, mSec);
}

/**
 * @brief 寻找卡
 */
void RfidOperating::findCard()
{
    rf_request = (Rf_Rrequest)mainLib->resolve("rf_request");
    if(!rf_request)
    {
        errorMessage("动态库内容加载失败!");
        exit(1);
    }

    unsigned short type;

    if(rf_request(0, 0x52, &type))
        errorMessage("寻卡失败!");
}

/**
 * @brief 防冲撞
 * @return 卡号
 */
void RfidOperating::anticoll()
{
    rf_anticoll = (Rf_Anticoll)mainLib->resolve("rf_anticoll");
    if(!rf_anticoll)
    {
        errorMessage("动态库内容加载失败!");
        exit(1);
    }

    if(rf_anticoll(0, 4, pSnr, &pLen))
        errorMessage("防碰撞失败!");
}

/**
 * @brief 激活卡
 */
void RfidOperating::selectCard()
{
    rf_select = (Rf_Select)mainLib->resolve("rf_select");
    if(!rf_select)
    {
        errorMessage("动态库内容加载失败!");
        exit(1);
    }
    unsigned char Size=0;//返回卡的容量
    if(rf_select(0, pSnr, pLen, &Size))
        errorMessage("激活卡失败!");
}

/**
 * @brief 设置工作状态
 */
void RfidOperating::setWorkType()
{
    rf_init_type = (Rf_Init_Type)mainLib->resolve("rf_init_type");
    if(!rf_init_type)
    {
        errorMessage("动态库内容加载失败!");
        exit(1);
    }
    if(rf_init_type(0, 0x41))
        errorMessage("设置工作状态失败!");
}

/**
 * @brief 验证密钥
 * @param block 卡工作块号 默认为0x01
 */
void RfidOperating::authentication(unsigned char block)
{
    Rf_M1_Authentication2 rf_M1_authentication2 = (Rf_M1_Authentication2)mainLib->resolve("rf_M1_authentication2");
    if(!rf_M1_authentication2)
    {
        errorMessage("动态库内容加载失败!");
        exit(1);
    }

    unsigned char key[6];
    memset(key, 0xff, sizeof(key));
    if(rf_M1_authentication2(0, 0x60, block, key))
        errorMessage("验证密钥失败!");
}

/**
 * @brief 读取数据
 * @return 卡里面的数据
 */
QString RfidOperating::readData()
{
    rf_M1_read = (Rf_M1_Read)mainLib->resolve("rf_M1_read");
    if(!rf_M1_read)
    {
        printf("load the function of dll fail");
        exit(1);
    }

    char *Data;
    unsigned char Len;

    if(rf_M1_read(0, 0x01, (unsigned char *)Data, &Len))
        errorMessage("读取数据失败!");

    return QString::fromLocal8Bit(Data);

}
