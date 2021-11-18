#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>   /* нужно для usbdrv.h */
#include "usbdrv.h"


struct dataexchange_t       // Описание структуры для передачи данных
{

   unsigned char result[5][1];
};  

unsigned char x=1;
unsigned char y=0;
unsigned char interrupted=0;

struct dataexchange_t pdata = {0};


PROGMEM char usbHidReportDescriptor[22] = { // USB report descriptor         // Дескриптор описывает структуру пакета данных для обмена
    0x06, 0x00, 0xff,                       // USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                             // USAGE (Vendor Usage 1)
    0xa1, 0x01,                             // COLLECTION (Application)
    0x15, 0x00,                             //    LOGICAL_MINIMUM (0)        // min. значение для данных
    0x26, 0xff, 0x00,                       //    LOGICAL_MAXIMUM (255)      // max. значение для данных, 255 тут не случайно, а чтобы уложиться в 1 байт
    0x75, 0x08,                             //    REPORT_SIZE (8)            // информация передается порциями, это размер одного "репорта" 8 бит
    0x95, sizeof(struct dataexchange_t),    //    REPORT_COUNT               // количество порций (у нашем примере = 3, описанная выше структура передастся за три репорта)
    0x09, 0x00,                             //    USAGE (Undefined)
    0xb2, 0x02, 0x01,                       //    FEATURE (Data,Var,Abs,Buf)
    0xc0                                    // END_COLLECTION
};
/* Здесь мы описали только один report, из-за чего не нужно использовать report-ID (он должен быть первым байтом).
 * С его помощью передадим 3 байта данных (размер одного REPORT_SIZE = 8 бит = 1 байт, их количество REPORT_COUNT = 3).
 */


/* Эти переменные хранят статус текущей передачи */
static uchar    currentAddress;
static uchar    bytesRemaining;


/* usbFunctionRead() вызывается когда хост запрашивает порцию данных от устройства
 * Для дополнительной информации см. документацию в usbdrv.h
 */
uchar   usbFunctionRead(uchar *data, uchar len)
{
    if(len > bytesRemaining)
        len = bytesRemaining;

    uchar *buffer = (uchar*)&pdata;
	interrupted=1;

   // if(!currentAddress)        // Ни один кусок данных еще не прочитан.
  //  {                          // Заполним структуру для передачи
            
//			pdata.result[0][0] = ADCH;
   //         pdata.result[0][0] = 24;
 //           pdata.result[0][0] = ADCH;
 //   }

    uchar j;
    for(j=0; j<len; j++)
        data[j] = buffer[j+currentAddress];

    currentAddress += len;
    bytesRemaining -= len;
	return len;
}


/* usbFunctionWrite() вызывается когда хост отправляет порцию данных к устройству
 * Для дополнительной информации см. документацию в usbdrv.h
 */
uchar   usbFunctionWrite(uchar *data, uchar len)
{
    if(bytesRemaining == 0)
	PORTB=pdata.result[0][0];
	interrupted=1;
	TCNT1=0;

        return 1;               /* конец передачи */

    if(len > bytesRemaining)
        len = bytesRemaining;

    uchar *buffer = (uchar*)&pdata;
    
    uchar j;
    for(j=0; j<len; j++)
        buffer[j+currentAddress] = data[j];

    currentAddress += len;
    bytesRemaining -= len;

//    if(bytesRemaining == 0)     // Все данные получены
  //  {                           // Выставим значения на PORTB
//        if ( pdata.b1 )
//            PORTB |= _BV(1);
  //      else
    //        PORTB &= ~_BV(1);
//
//
  //      if ( pdata.b2 )
    //        PORTB |= _BV(2);
      //  else
        //    PORTB &= ~_BV(2);
//
//
  //      if ( pdata.b3 )
    //        PORTB |= _BV(3);
      //  else
        //    PORTB &= ~_BV(3);
    //}
	
    return bytesRemaining == 0; /* 0 означает, что есть еще данные */
}

/* ------------------------------------------------------------------------- */

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
usbRequest_t    *rq = (void *)data;

    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS){    /* HID устройство */
        if(rq->bRequest == USBRQ_HID_GET_REPORT){  /* wValue: ReportType (highbyte), ReportID (lowbyte) */
            // у нас только одна разновидность репорта, можем игнорировать report-ID
            bytesRemaining = sizeof(struct dataexchange_t);
            currentAddress = 0;
            return USB_NO_MSG;  // используем usbFunctionRead() для отправки данных хосту
        }else if(rq->bRequest == USBRQ_HID_SET_REPORT){
            // у нас только одна разновидность репорта, можем игнорировать report-ID
            bytesRemaining = sizeof(struct dataexchange_t);
            currentAddress = 0;
            return USB_NO_MSG;  // используем usbFunctionWrite() для получения данных от хоста
        }
    }else{
        /* остальные запросы мы просто игнорируем */
    }
    return 0;
}
/* ------------------------------------------------------------------------- */

int main(void)
{
    DDRB = 0b00111111;      // PB1,PB2,PB3 - выход

	ADCSRA =  (1 << ADPS2) | (0 << ADPS1) | (0 << ADPS0); // Set ADC prescalar Division factor 16. Частота измерений 56 кГц при системной 12 МГц
	ADMUX = 0b11100000; // Set ADC reference to внутреннее опорное 1.1V voltage with external capacitor at AREF pin
  	
	// no left ajustment needed in 10 bit mode!
	//ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading
   	// No MUX values needed to be changed to use ADC0
	

   	ADCSRA |= (1 << ADATE);  // Auto trigger enable, ADCSRB (ADTS2:0) нули - Free running mode
   	ADCSRA |= (1 << ADEN);  // Enable ADC
   	ADCSRA |= (1 << ADSC);  // Start A2D Conversions


			// read data (10 bit mode), ADCL - first
			//t=ADCL;
			//r=ADCH;
			//r=(r<<8)+t;;  // now we have the result in 16 bit var 'r'
			
	
   
    usbInit();
    usbDeviceDisconnect();  // принудительно отключаемся от хоста, так делать можно только при выключенных прерываниях!
    
    uchar i = 0;
    while(--i){             // пауза > 250 ms
        _delay_ms(1);
    }
	TCCR1B=0b00000100; //clkI/O/256 (from prescaler)
    
    usbDeviceConnect();     // подключаемся

    sei();                  // разрешаем прерывания

for(;;)
{
	
	if(interrupted)
	{
	interrupted=0;
	pdata.result[0][0] = 0;

	ADMUX = 0b11100000;
	
			for(x=1;x<=4;x++)
			{
			_delay_us(100);
			pdata.result[x][0]=ADCH;
			ADMUX++;
			}

		pdata.result[0][0]=TCNT1/256; //1тик=0.005461333333 с
		if(!(pdata.result[0][0])){pdata.result[0][0]=255;}
	    usbPoll();          
		_delay_ms(49);
    }


_delay_ms(10); 	
usbPoll();// эту функцию надо регулярно вызывать с главного цикла, максимальная задержка между вызовами - 50 ms
}               
return 0;
}
/* ------------------------------------------------------------------------- */ 
