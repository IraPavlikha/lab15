// Unit1.h

#ifndef Unit1H
#define Unit1H

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>

class TForm1 : public TForm
{
__published:
    TStringGrid *StringGrid1;
    TButton *btnTest1;
    TButton *btnCheck;
    TEdit *Edit1;
    TLabel *Label1;
    TMemo *Memo1;

    void __fastcall btnTest1Click(TObject *Sender);
    void __fastcall btnCheckClick(TObject *Sender);

public:
    __fastcall TForm1(TComponent* Owner);
};

extern PACKAGE TForm1 *Form1;

#endif
