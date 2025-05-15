

#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"

#include <vector>
#include <string>
#include <algorithm>

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

struct Transition {
    std::string from_state;
    bool is_final;
    char symbol;
    std::string to_state;
};

std::vector<Transition> transitions;

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
    StringGrid1->Cells[0][0] = "Стан";
    StringGrid1->Cells[1][0] = "Фінальний";
    StringGrid1->Cells[2][0] = "Символ";
    StringGrid1->Cells[3][0] = "Стан після";
    StringGrid1->RowCount = 5;
    StringGrid1->ColCount = 4;
}

// Заповнення тестового прикладу
void __fastcall TForm1::btnTest1Click(TObject *Sender)
{
    StringGrid1->Cells[0][1] = "q0";
    StringGrid1->Cells[1][1] = "0";
    StringGrid1->Cells[2][1] = "a";
    StringGrid1->Cells[3][1] = "q1";

    StringGrid1->Cells[0][2] = "q1";
    StringGrid1->Cells[1][2] = "0";
    StringGrid1->Cells[2][2] = "b";
    StringGrid1->Cells[3][2] = "q2";

    StringGrid1->Cells[0][3] = "q2";
    StringGrid1->Cells[1][3] = "1";
    StringGrid1->Cells[2][3] = "c";
    StringGrid1->Cells[3][3] = "q2";

    StringGrid1->RowCount = 4;
    Edit1->Text = "abcc";
}

// Основна перевірка ланцюжка
void __fastcall TForm1::btnCheckClick(TObject *Sender)
{
    transitions.clear();
    Memo1->Lines->Clear();
    Label1->Caption = "";

    int rowCount = StringGrid1->RowCount;

    for (int i = 1; i < rowCount; ++i) {
        String from = StringGrid1->Cells[0][i];
        String isFinal = StringGrid1->Cells[1][i];
        String symbol = StringGrid1->Cells[2][i];
        String to = StringGrid1->Cells[3][i];

        if (from == "" || symbol == "" || to == "")
            continue;

        Transition t;
        t.from_state = AnsiString(from).c_str();
        t.is_final = isFinal == "1";
        t.symbol = AnsiString(symbol)[1]; // беремо перший символ
        t.to_state = AnsiString(to).c_str();

        transitions.push_back(t);
    }

    for (auto &t : transitions) {
        String line = t.from_state.c_str();
        line += t.is_final ? " (final)" : " (non-final)";
        line += " -- ";
        line += t.symbol;
        line += " --> ";
        line += t.to_state.c_str();
        Memo1->Lines->Add(line);
    }

    std::string input = AnsiString(Edit1->Text).c_str();
    std::string current_state = "q0";

    for (char c : input) {
        auto it = std::find_if(transitions.begin(), transitions.end(),
            [&](Transition &t) {
                return t.from_state == current_state && t.symbol == c;
            });

        if (it == transitions.end()) {
            Label1->Caption = "Ланцюжок не прийнято (немає переходу)";
            return;
        }

        current_state = it->to_state;
    }

    auto final_it = std::find_if(transitions.begin(), transitions.end(),
        [&](Transition &t) {
            return t.from_state == current_state && t.is_final;
        });

    if (final_it != transitions.end()) {
        Label1->Caption = "Ланцюжок прийнято!";
    } else {
        Label1->Caption = "Ланцюжок не прийнято (не фінальний стан)";
    }
}
