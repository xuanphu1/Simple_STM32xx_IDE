#include "LibrarySelectionDialog.h"

LibrarySelectionDialog::LibrarySelectionDialog(wxWindow *parent, const wxArrayString &initialPaths, const wxString &currentDir)
    : wxDialog(parent, wxID_ANY, "Select Library Directories", wxDefaultPosition, wxSize(400, 300)),
      libraryPaths(initialPaths), currentDir(currentDir)
{
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    // Thêm wxListBox để hiển thị danh sách thư viện
    libraryListBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(350, 200));
    libraryListBox->Set(libraryPaths); // Khởi tạo với danh sách hiện tại
    mainSizer->Add(libraryListBox, 1, wxEXPAND | wxALL, 10);

    // Thêm các nút
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *addButton = new wxButton(this, ID_ADD, "Add");
    wxButton *deleteButton = new wxButton(this, ID_DELETE, "Delete");
    wxButton *okButton = new wxButton(this, ID_OK, "OK");

    buttonSizer->Add(addButton, 0, wxALL, 5);
    buttonSizer->Add(deleteButton, 0, wxALL, 5);
    buttonSizer->Add(okButton, 0, wxALL, 5);

    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    SetSizerAndFit(mainSizer);

    // Bind events
    Bind(wxEVT_BUTTON, &LibrarySelectionDialog::OnAdd, this, ID_ADD);
    Bind(wxEVT_BUTTON, &LibrarySelectionDialog::OnDelete, this, ID_DELETE);
    Bind(wxEVT_BUTTON, &LibrarySelectionDialog::OnOK, this, ID_OK);
}

void LibrarySelectionDialog::OnAdd(wxCommandEvent &event)
{
    // Lưu thư mục làm việc hiện tại
    wxString originalCwd = wxGetCwd();
    wxString lastSelectedDir = currentDir;
    bool continueAdding = true;
    while (continueAdding)
    {
        wxDirDialog dirDlg(this, "Select Library Directory", lastSelectedDir, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
        if (dirDlg.ShowModal() == wxID_OK)
        {
            wxString selectedPath = dirDlg.GetPath();
            // Loại bỏ ký tự xuống dòng và khoảng trắng thừa
            selectedPath.Trim(true).Trim(false).Replace("\n", "");

            if (libraryPaths.Index(selectedPath) == wxNOT_FOUND) // Nếu không tìm thấy, thêm vào danh sách
            {
                libraryPaths.Add(selectedPath);
                libraryListBox->Append(selectedPath);
            }

            wxFileName path(selectedPath);
            path.SetPath(path.GetPath()); // Đảm bảo đây là thư mục
            lastSelectedDir = path.GetPath(); // Gán thư mục cha vào lastSelectedDir

            // Hỏi người dùng có muốn thêm thư mục khác không
            if (libraryPaths.GetCount() > 0)
            {
                int answer = wxMessageBox("Do you want to add another library directory?",
                                          "Add More", wxYES_NO | wxCENTRE, this);
                continueAdding = (answer == wxYES);
            }
            else
            {
                continueAdding = false; // Dừng nếu không có thư mục nào được thêm
            }
        }
        else
        {
            continueAdding = false; // Dừng nếu người dùng hủy dialog
        }
    }
    // Khôi phục thư mục làm việc ban đầu
    wxSetWorkingDirectory(originalCwd);
}

void LibrarySelectionDialog::OnDelete(wxCommandEvent &event)
{
    int selected = libraryListBox->GetSelection();
    if (selected != wxNOT_FOUND)
    {
        libraryPaths.RemoveAt(selected);
        libraryListBox->Delete(selected);
    }
}

void LibrarySelectionDialog::OnOK(wxCommandEvent &event)
{
    EndModal(wxID_OK);
}