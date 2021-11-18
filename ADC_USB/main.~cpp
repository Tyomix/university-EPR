//---------------------------------------------------------------------------
#define  uchar  unsigned char

#include <vcl.h>
#pragma hdrstop
#include "main.h"
#include "Windows.h"
#include "winbase.h"
#include <string>

#include "hidlibrary.h" // Библиотека для работы с Hid устройствами

#include "../ADC_USB_firmware/usbconfig.h"  // Здесь пишем путь к usbconfig.h


char  vendorName[]  = {USB_CFG_VENDOR_NAME, 0}; // для того что бы знать как
char  productName[] = {USB_CFG_DEVICE_NAME, 0}; // называется наше устройство

unsigned char on=0;

AnsiString result[1000000];
unsigned long int rawtime[1000000];
unsigned int it=0;
unsigned long int yy=0;
unsigned long int t=0;
unsigned long int prevtime=0;


struct dataexchange_t		// Описание структуры для передачи данных
{
unsigned char result[5][1];
};

struct dataexchange_t pdata = {0};

HIDLibrary <dataexchange_t> hid; // создаем экземпляр класса с типом нашей структуры

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

int connect()  // этой функцией будем подключаться к устройству
{
   int i, n, res=0;
   string exampleDeviceName = "";

   exampleDeviceName += vendorName;
   exampleDeviceName += " ";
   exampleDeviceName += productName;

   n = hid.EnumerateHIDDevices(); // узнаем все Hid устройства vid_16c0&pid_05df
                                  // vid и pid указаны в hidlibrary.h константой idstring

   for (i=0; i<n; i++)            // ищем среди них наше
   {
      hid.Connect(i);

      // GetConnectedDeviceName() возвращает string,
      // где через пробел указаны vendor и product Name.
      // Сравниваем, если совпало - значить устройство наше
      if ( hid.GetConnectedDeviceName() == exampleDeviceName )
      {
         res = 1;
         break;
      }
   }
   return res;
}
//---------------------------------------------------------------------------

// Кнопка "Принять данные"
void __fastcall TForm1::Button1Click(TObject *Sender)
{
      pdata.result[0][0]=0;
      if (b0->Checked){pdata.result[0][0]|=0x1;}
      if (b1->Checked){pdata.result[0][0]|=0x2;}
      if (b2->Checked){pdata.result[0][0]|=0x4;}
      if (b3->Checked){pdata.result[0][0]|=0x8;}
      if (b4->Checked){pdata.result[0][0]|=0x10;}
      if (b5->Checked){pdata.result[0][0]|=0x20;}
      if (b6->Checked){pdata.result[0][0]|=0x40;}
      if (b7->Checked){pdata.result[0][0]|=0x80;}


        hid.SendData(&pdata);
        yy=0;
        Timer1->Enabled=true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::stopClick(TObject *Sender)
{
Timer1->Enabled=false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
   if ( 1 == connect() )
   {Button1->Enabled=1;
   Timer2->Enabled=0;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
List1->Items->SaveToFile(resulttxt->Text);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Timer1Timer(TObject *Sender)
{

        hid.ReceiveData(&pdata);
        AnsiString r="";
        unsigned char y=0;
        while(pdata.result[0][y] && y==0)  //
        {
                r="";
                if(!yy){                            //обработка времени
                rawtime[0]=pdata.result[0][0];
                goto next;
                }

                if(pdata.result[0][y]<prevtime)
                {
                rawtime[yy]=(256-prevtime)+pdata.result[0][y]+rawtime[yy-1];
                goto next;
                }

                rawtime[yy]=(pdata.result[0][y]-prevtime)+rawtime[yy-1];

                next:
                prevtime=pdata.result[0][y];
                r=rawtime[yy]*256*256/12000000.0;
                r+="\t";
                for(unsigned char x=1;x<=4;x++)   //обработка результатов измерения
                {
                r+=pdata.result[x][y]*1.1/255;
                r+="\t";
                }
        result[yy]=r;
        Edit1->Text=r;
        List1->Items->Insert((0),r);
        y++;
        yy++;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
List1->Items->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CSpinEdit1Change(TObject *Sender)
{
Timer1->Interval=CSpinEdit1->Value;
}
//---------------------------------------------------------------------------

