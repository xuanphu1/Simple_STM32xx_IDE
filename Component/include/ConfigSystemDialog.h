// include/ConfigSystemDialog.h
#ifndef CONFIGSYSTEMDIALOG_H
#define CONFIGSYSTEMDIALOG_H

#include "main.h"
#include "LibrarySelectionDialog.h"

class ConfigSystemDialog : public wxDialog {
public:
    ConfigSystemDialog( wxWindow* parent, wxString& linkerPath, wxString& startupPath, 
                        wxString& libraryPath,const wxString& currentDir,const wxString &ProjectPath);
    void OnBrowseLinker(wxCommandEvent& event);
    void OnBrowseStartup(wxCommandEvent& event);
    void OnBrowseLibrary(wxCommandEvent& event); // Sự kiện mới cho nút Browse của thư viện
    void OnOK(wxCommandEvent& event);
    void SyncLib(wxCommandEvent& event);

private:
    wxTextCtrl* linkerTextCtrl;
    wxTextCtrl* startupTextCtrl;
    wxTextCtrl* libraryTextCtrl;
    wxListBox* libraryListBox;   // Danh sách hiển thị các thư viện

    wxString& linkerPathRef;   // Tham chiếu để cập nhật biến linkerPath
    wxString& startupPathRef;  // Tham chiếu để cập nhật biến startupPath
    wxString& libraryPathRef; // Tham chiếu tới libraryPath

    wxString currentDir; // Biến lưu đường dẫn hiện tại
    wxString ProjectPath;

    enum {
        ID_BROWSE_LINKER = wxID_HIGHEST + 100,
        ID_BROWSE_STARTUP,
        ID_BROWSE_LIBRARY
    };
};

#endif // CONFIGSYSTEMDIALOG_H