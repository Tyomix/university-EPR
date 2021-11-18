//---------------------------------------------------------------------------

#ifndef mainH
#define mainH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <jpeg.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TCheckBox *b0;
        TCheckBox *b1;
        TCheckBox *b2;
   TButton *Button1;
   TButton *Button2;
        TEdit *Edit1;
        TButton *stop;
        TTimer *Timer1;
        TLabel *Label1;
        TTimer *Timer2;
        TListBox *List1;
        TButton *Button3;
        TEdit *resulttxt;
        TCheckBox *b3;
        TCheckBox *b4;
        TCheckBox *b5;
        TCheckBox *b6;
        TCheckBox *b7;
        TButton *Button4;
        TCSpinEdit *CSpinEdit1;
   void __fastcall Button1Click(TObject *Sender);
        void __fastcall stopClick(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall CSpinEdit1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
