// ?????????? ??? ?????? ? Hid. ???????? ? ??????????? ????????.
// ??? ? ??????? WINAPI ??????? LoadLibrary ?????????? hid.dll,
// ????? GetProcAddress - ????????? ?????? ??????? ?????? hid.dll.
// ????????????? ??????? ? ??????? ????????? ??? ?????? ? HID.
// ????? ?? http://speleoastronomy.org/elektro/atmega/usingusb.html
// ??????? ??????? IsConnectedDevice()
// XANDER, 2011 for WE.EASYELECTRONICS.RU

const char idstring[] = "vid_16c0&pid_05df";

#include <windows.h>
#include <setupapi.h>
#include <string>
#include <vector>
#include <map>

typedef void (WINAPI* t_HidD_GetHidGuid)( OUT LPGUID );
typedef BOOLEAN (WINAPI* t_HidD_GetManufacturerString)(IN HANDLE, OUT PVOID, IN ULONG);
typedef BOOLEAN (WINAPI* t_HidD_GetProductString)(IN HANDLE, OUT PVOID, IN ULONG);
typedef BOOLEAN (WINAPI* t_HidD_GetFeature)(IN HANDLE, OUT PVOID, IN ULONG);
typedef BOOLEAN (WINAPI* t_HidD_SetFeature)(IN HANDLE, IN PVOID, IN ULONG);

using namespace std;

template <typename T> class HIDLibrary
{
protected:
	static const int datasize = sizeof(T);
	T data;
	char pad[16];
	GUID m_hidguid;
	HINSTANCE hDLL; 
	t_HidD_GetHidGuid HidD_GetHidGuid;
	t_HidD_GetManufacturerString HidD_GetManufacturerString;
	t_HidD_GetProductString HidD_GetProductString;
	t_HidD_GetFeature HidD_GetFeature;
	t_HidD_SetFeature HidD_SetFeature;
	vector<string> m_HIDPaths;
	map<string,string> m_HIDDeviceIdents;
	string GetDevicePath(HDEVINFO hInfoSet, PSP_DEVICE_INTERFACE_DATA oInterface);
	string m_ConnectedDevice;
public:
	HIDLibrary();
	bool IsAvailableLib();
	int EnumerateHIDDevices();
	bool Connect(unsigned int device=0);
	string GetConnectedDevicePath(){return m_ConnectedDevice;};
	string GetConnectedDeviceName(){return m_HIDDeviceIdents[m_ConnectedDevice];};
	string GetDeviceCount() { return m_HIDPaths.size(); };
	string GetDeviceName(int i){
									if(i<m_HIDPaths.size()) 
										return m_HIDDeviceIdents[m_HIDPaths[i]]; 
									else 
										return string.empty;
								}
	int SendData(T* data);
	int ReceiveData(T* data);
	int IsConnectedDevice();
};

template< typename T > HIDLibrary< T >::HIDLibrary()
{
		hDLL = LoadLibrary("HID.DLL");
		if(hDLL != NULL)
		{
		   HidD_GetHidGuid = (t_HidD_GetHidGuid)GetProcAddress(hDLL, "HidD_GetHidGuid");
		   HidD_GetManufacturerString = (t_HidD_GetManufacturerString)GetProcAddress(hDLL, "HidD_GetManufacturerString");
		   HidD_GetProductString = (t_HidD_GetProductString) GetProcAddress(hDLL, "HidD_GetProductString");
		   HidD_GetFeature = (t_HidD_GetFeature) GetProcAddress(hDLL, "HidD_GetFeature");
		   HidD_SetFeature = (t_HidD_SetFeature) GetProcAddress(hDLL, "HidD_SetFeature");
		   if(HidD_GetHidGuid)
		   {
			  HidD_GetHidGuid(&m_hidguid);
		   }
		}
}

template< typename T > bool HIDLibrary< T >::IsAvailableLib()
{
	return	!(hDLL == NULL || HidD_GetHidGuid == NULL || HidD_GetManufacturerString == NULL ||
			HidD_GetProductString == NULL || HidD_GetFeature == NULL || HidD_SetFeature == NULL);
}

template<typename T> string HIDLibrary<T>::GetDevicePath(HDEVINFO hInfoSet, PSP_DEVICE_INTERFACE_DATA oInterface)
{
	    char vpath [1000];
		vpath[0]=0;
		DWORD nRequiredSize = 0;
		// Get the device interface details
		if (!SetupDiGetDeviceInterfaceDetail(hInfoSet, oInterface, 0, 0, &nRequiredSize, 0))
		{
			PSP_DEVICE_INTERFACE_DETAIL_DATA oDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(nRequiredSize);
			oDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);	
			if (SetupDiGetDeviceInterfaceDetail(hInfoSet, oInterface, oDetail, nRequiredSize, &nRequiredSize, 0))
			{
				string s(oDetail->DevicePath);
				free(oDetail);
				return s;
			}
		}
		return "";
}

template<typename T> int HIDLibrary<T>::EnumerateHIDDevices()
{
		wchar_t buffer[1000];
		char s1[1000];
		m_HIDPaths.clear();
		int nIndex = 0;
		HDEVINFO hInfoSet = SetupDiGetClassDevs(&m_hidguid,0,0,DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
		SP_DEVICE_INTERFACE_DATA spd;
		spd.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
        while (SetupDiEnumDeviceInterfaces(hInfoSet, 0, &m_hidguid, nIndex, &spd))
		{
            string path = GetDevicePath(hInfoSet, &spd);	
			if(path.find(idstring)!= string::npos)
			{
				HANDLE h = CreateFile(path.c_str(),GENERIC_READ,0,0,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);
				if(h != INVALID_HANDLE_VALUE)
				{
					HidD_GetManufacturerString(h,buffer,500);
					wcstombs(s1,buffer, 1000);
					if(strlen(s1)>2)
					{
						strcat(s1," ");
						HidD_GetProductString(h,buffer,500);
 						wcstombs(s1+strlen(s1),buffer, 1000);
					}
					CloseHandle(h);
				}
				else
  					strcpy(s1,"Unknown device");
				string name(s1);
				m_HIDDeviceIdents[path]=s1;
				m_HIDPaths.push_back(path);
			}
			nIndex++;
		}
		SetupDiDestroyDeviceInfoList(hInfoSet);
		return nIndex;
}

template<typename T> bool HIDLibrary<T>::Connect(unsigned int device)
{
	if(m_HIDPaths.size() < device+1)
	{
		EnumerateHIDDevices();
		if(m_HIDPaths.size() < device+1) return false;
	}
	m_ConnectedDevice = m_HIDPaths[device];
	return true;
}

template<typename T> int HIDLibrary<T>::SendData(T* data)
{
   char vpath[datasize+16];
   vpath[0]=0;
   int len=datasize+1;
   HANDLE h = CreateFile(m_ConnectedDevice.c_str(),GENERIC_READ,0,0,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);
   if(h != INVALID_HANDLE_VALUE)
   {
		memcpy(vpath+1,data,datasize);
		int err = HidD_SetFeature(h, vpath , len);
		CloseHandle(h);
		return err;
   }
   else
		return 0;
}

template<typename T> int HIDLibrary<T>::ReceiveData(T* data)
{
    char vpath[datasize+16];
	memset(vpath,0,sizeof(vpath));
	int len=datasize+1;
	HANDLE h = CreateFile(m_ConnectedDevice.c_str(),GENERIC_READ,0,0,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);
   if(h != INVALID_HANDLE_VALUE)
   {
		int err = HidD_GetFeature(h, vpath , len);
		memcpy(data,vpath+1,datasize);
		CloseHandle(h);
		return err;
   }
   else
		return 0;
}

template<typename T> int HIDLibrary<T>::IsConnectedDevice()
{
   HANDLE h = CreateFile(m_ConnectedDevice.c_str(),GENERIC_READ,0,0,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);
   if(h != INVALID_HANDLE_VALUE)
   {
		CloseHandle(h);
		return 1;
   }
   else
		return 0;
}
