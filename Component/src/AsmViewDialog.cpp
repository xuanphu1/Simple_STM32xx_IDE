#include "AsmViewDialog.h"

AsmViewDialog::AsmViewDialog(wxWindow* parent, wxWindowID id, const wxString& title,
                             const wxPoint& pos, const wxSize& size)
    : wxDialog(parent, id, title, pos, size)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    m_stc = new wxStyledTextCtrl(this, wxID_ANY);
    InitStyledTextCtrl();

    sizer->Add(m_stc, 1, wxEXPAND | wxALL, 5);

    SetSizer(sizer);
}

void AsmViewDialog::InitStyledTextCtrl()
{
    // Thiết lập chế độ highlight assembler (NASM style)
    m_stc->SetLexer(wxSTC_LEX_ASM);

    // Một số option cơ bản để dễ đọc
    m_stc->StyleSetForeground(wxSTC_ASM_COMMENT, wxColour(0, 128, 0)); // màu comment xanh
    m_stc->StyleSetForeground(wxSTC_ASM_REGISTER, wxColour(0, 0, 255)); // màu register xanh dương
    m_stc->StyleSetForeground(wxSTC_ASM_CPUINSTRUCTION, wxColour(128, 0, 0)); // màu lệnh asm nâu đỏ

    m_stc->StyleSetFont(wxSTC_STYLE_DEFAULT, wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    m_stc->SetMarginWidth(1, 40); // dòng số bên trái
    m_stc->SetViewWhiteSpace(false);

    m_stc->SetReadOnly(true);
}

void AsmViewDialog::SetAsmText(const wxString& asmText)
{
    m_stc->SetText(asmText);
    m_stc->GotoPos(0);
}
