#ifndef LIBRARYSELECTIONDIALOG_H
#define LIBRARYSELECTIONDIALOG_H

#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/filename.h>

class LibrarySelectionDialog : public wxDialog {
public:
    LibrarySelectionDialog(wxWindow* parent, const wxArrayString& initialPaths, const wxString& currentDir);
    wxArrayString GetSelectedPaths() const { return libraryPaths; }

private:
    wxListBox* libraryListBox;
    wxArrayString libraryPaths;
    wxString currentDir;

    void OnAdd(wxCommandEvent& event);
    void OnDelete(wxCommandEvent& event);
    void OnOK(wxCommandEvent& event);

    enum {
        ID_ADD = wxID_HIGHEST + 100,
        ID_DELETE,
        ID_OK
    };
};

#endif // LIBRARYSELECTIONDIALOG_H