#ifndef RFIDOPERATING_H
#define RFIDOPERATING_H
#include <QLibrary>
#include <QMessageBox>
#include <QDebug>

class RfidOperating
{
public:
    RfidOperating();

public:
    //加载动态库
    void loadDLL();
    //错误信息
    void errorMessage(QString errorString);

    //获取动态库的版本号
    int currentLibraryVersion();
    //初始化端口
    void intialPort(int port);
    //关闭串口
    void closePort();
    //控制蜂鸣器响
    void controlBeep(unsigned char mSec);
    //寻找卡
    void findCard();
    //防冲撞
    void anticoll();
    //激活卡
    void selectCard();
    //设置工作状态
    void setWorkType();
    //验证密钥
    void authentication(unsigned char block = 0x01);
    //读取数据
    QString readData();

private:
    //从动态链接库里面加载的函数
    //获取动态库的版本号
    typedef int(*Lib_Ver)(unsigned int *pVer);
    Lib_Ver lib_ver;

    //初始化端口
    typedef int(*Rf_Init_Com)(unsigned short icdev,int port,long baud);
    Rf_Init_Com rf_init_com;

    //关闭串口
    typedef int (*Rf_ClosePort)();
    Rf_ClosePort rf_ClosePort;

    //设置读卡器非接触工作方式
    typedef int (*Rf_Init_Type) (unsigned short icdev, unsigned char type);
    Rf_Init_Type rf_init_type;

    //设置LED指示灯颜色
    typedef int (*Rf_Light) (unsigned short icdev, unsigned char color);
    Rf_Light rf_light;

    //控制蜂鸣器响
    typedef int (*Rf_Beep) (unsigned short icdev, unsigned char msec);
    Rf_Beep rf_beep;

    //寻TYPE_A卡
    typedef int (*Rf_Rrequest) (unsigned short icdev, unsigned char model,  unsigned short
                                *pTagType);
    Rf_Rrequest rf_request;
    //防冲撞
    typedef int (*Rf_Anticoll)(unsigned short icdev,unsigned char bcnt,
                               unsigned char *pSnr, unsigned char *pLen);
    Rf_Anticoll rf_anticoll;

    //激活卡
    typedef int (*Rf_Select) (unsigned short icdev, unsigned char *pSnr, unsigned char snrLen,unsigned char *pSize);
    Rf_Select rf_select;

    //验证密钥
    typedef int (*Rf_M1_Authentication2)(unsigned short icdev, unsigned char model,
                                         unsigned char block, unsigned char *pKey);
    Rf_M1_Authentication2 rf_M1_authentication2;

    //从卡片读取数据
    typedef int (*Rf_M1_Read) (unsigned short icdev, unsigned char block, unsigned char *pData,unsigned char *pLen);
    Rf_M1_Read rf_M1_read;

private :
    QLibrary *mainLib;
    unsigned char pSnr[10];//卡的序列号
    unsigned char pLen;//卡序列号长度
};

#endif // RFIDOPERATING_H
