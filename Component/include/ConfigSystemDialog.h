// include/ConfigSystemDialog.h
#ifndef CONFIGSYSTEMDIALOG_H
#define CONFIGSYSTEMDIALOG_H

#include "main.h"

class ConfigSystemDialog : public wxDialog {
public:
    ConfigSystemDialog(wxWindow* parent, wxString& linkerPath, wxString& startupPath, wxString& makefilePath,const wxString& currentDir);
    void OnBrowseLinker(wxCommandEvent& event);
    void OnBrowseStartup(wxCommandEvent& event);
    void OnBrowseMakefile(wxCommandEvent& event);
    void OnOK(wxCommandEvent& event);

private:
    wxTextCtrl* linkerTextCtrl;
    wxTextCtrl* startupTextCtrl;
    wxTextCtrl* makefileTextCtrl;

    wxString& linkerPathRef;   // Tham chiếu để cập nhật biến linkerPath
    wxString& startupPathRef;  // Tham chiếu để cập nhật biến startupPath
    wxString& makefilePathRef; // Tham chiếu để cập nhật biến makefilePath

    wxString currentDir; // Biến lưu đường dẫn hiện tại

    enum {
        ID_BROWSE_LINKER = wxID_HIGHEST + 100,
        ID_BROWSE_STARTUP,
        ID_BROWSE_MAKEFILE
    };
};

#endif // CONFIGSYSTEMDIALOG_H