#pragma once

#ifdef DEFINE_EXPORT
#define DLL_PORT_TYPE __declspec(dllexport)
#else
#define DLL_PORT_TYPE __declspec(dllimport)
#endif

#include <string>
#include <Windows.h>
#include <vector>

// usb�豸��Ϣ
typedef  struct sUsbDevInfo
{
    std::string strDevName;             //  �豸����
    std::string strDevGuid;             //  �豸GUID
    unsigned short nProductNum;         
    unsigned short nVersionNum;         
    unsigned short nVendorNum;          
    std::string strDevPath;             // �豸·��
}USB_DEV_INFO;

// ��������Ϣ
typedef struct sPenInfo
{
    int nPens;  // ��״̬
    int nX;     // ��x������
    int nY;     // ��y������
    int nPenP;  // ��ѹ��
}PEN_INFO;

// ����usb���ݻص�����
typedef void (*usbDataCallBack)(const char* pUsbData, const sPenInfo& penInfo);
// ����usb�豸�Ĳ��״̬
typedef void (*usbStatusCallBack)(int nDevstatus, void* context);

class CUsbDevInterface
{
public:

    // ********************************************************
    // summary: ����usb�豸Pid��ָ����usb�豸
    // fullname: _openSpecUsbDevByPid
    // access: pubilc
    // parameter: [IN] arryPid usb�豸Pid������
    // parameter: [IN] pFunc ָ���������ݵĻص� Ĭ��Ϊnull
    // return: bool �豸�Ƿ�򿪳ɹ�
    // ********************************************************
    virtual bool _openSpecUsbDevByPid(IN char* pAarryPid[], unsigned int nAarrySize, IN usbDataCallBack pFunc = NULL) = 0;

    // ********************************************************
    // summary: ����usb�豸Pid��ָ����usb�豸
    // fullname: _openSpecUsbDevByPid
    // access: pubilc
    // parameter: [IN] vecPid�豸Pid����
    // parameter: [IN] pFunc ָ���������ݵĻص� Ĭ��Ϊnull
    // return: bool �豸�Ƿ�򿪳ɹ�
    // ********************************************************
    virtual bool _openSpecUsbDevByPid(IN const std::vector<std::string>& vecPid, IN usbDataCallBack pFunc = NULL) = 0;

    // *******************************************
    // summary: �ر��豸��Դ
    // fullname: closeUsbDev
    // access: public
    // return: �Ƿ�رճɹ�
    // *******************************************
    virtual bool closeUsbDev() = 0;

    // **********************************************
    // summary: ����usb���״̬�ص�
    // fullname: setDevStatusHandler
    // access: public
    // parameter: [IN] newHandler �ص���ַ
    // parameter: [IN] pUsbDevStatusContext ������ָ��
    // return: �ϴλص���ַ
    // **********************************************
    virtual usbStatusCallBack setDevStatusHandler(usbStatusCallBack newHandler, void* pUsbDevStatusContext = NULL) = 0;
};

extern "C" DLL_PORT_TYPE CUsbDevInterface* WINAPI createObj();
extern "C" DLL_PORT_TYPE void WINAPI deleteObj(void* p);

//////////////////////////////////////////////////////////////////////////
/*���豸�ӿ�*/
//////////////////////////////////////////////////////////////////////////
extern "C" DLL_PORT_TYPE bool WINAPI _extern_openSpecUsbDevByPid(char* pAarryPid[], unsigned int nAarrySize, usbDataCallBack pFunc);

//////////////////////////////////////////////////////////////////////////
/*�ر��豸�ӿ�*/
//////////////////////////////////////////////////////////////////////////
extern "C" DLL_PORT_TYPE bool WINAPI _extern_CloseUsbDev();
 
