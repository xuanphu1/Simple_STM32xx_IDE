// include/ConfigSystemDialog.h
#ifndef CONFIGSYSTEMDIALOG_H
#define CONFIGSYSTEMDIALOG_H

#include "main.h"

class ConfigSystemDialog : public wxDialog {
public:
    ConfigSystemDialog( wxWindow* parent, wxString& linkerPath, wxString& startupPath, 
                        wxString& makefilePath,wxString& libraryPath,const wxString& currentDir);
    void OnBrowseLinker(wxCommandEvent& event);
    void OnBrowseStartup(wxCommandEvent& event);
    void OnBrowseMakefile(wxCommandEvent& event);
    void OnBrowseLibrary(wxCommandEvent& event); // Sự kiện mới cho nút Browse của thư viện
    void OnOK(wxCommandEvent& event);

private:
    wxTextCtrl* linkerTextCtrl;
    wxTextCtrl* startupTextCtrl;
    wxTextCtrl* makefileTextCtrl;
    wxTextCtrl* libraryTextCtrl;

    wxString& linkerPathRef;   // Tham chiếu để cập nhật biến linkerPath
    wxString& startupPathRef;  // Tham chiếu để cập nhật biến startupPath
    wxString& makefilePathRef; // Tham chiếu để cập nhật biến makefilePath
    wxString& libraryPathRef; // Tham chiếu tới libraryPath

    wxString currentDir; // Biến lưu đường dẫn hiện tại

    enum {
        ID_BROWSE_LINKER = wxID_HIGHEST + 100,
        ID_BROWSE_STARTUP,
        ID_BROWSE_MAKEFILE,
        ID_BROWSE_LIBRARY
    };
};

#endif // CONFIGSYSTEMDIALOG_H