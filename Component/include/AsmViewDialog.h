#ifndef ASM_VIEW_DIALOG_H
#define ASM_VIEW_DIALOG_H

#include <wx/wx.h>
#include <wx/stc/stc.h>

class AsmViewDialog : public wxDialog
{
public:
    AsmViewDialog(wxWindow* parent, wxWindowID id = wxID_ANY,
                  const wxString& title = "Assembly Viewer",
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxSize(600, 400));

    // Cập nhật nội dung asm vào control
    void SetAsmText(const wxString& asmText);

private:
    wxStyledTextCtrl* m_stc;

    void InitStyledTextCtrl();
};

#endif // ASM_VIEW_DIALOG_H
