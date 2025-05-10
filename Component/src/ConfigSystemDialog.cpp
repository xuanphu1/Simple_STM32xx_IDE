// src/ConfigSystemDialog.cpp
#include "ConfigSystemDialog.h"

ConfigSystemDialog::ConfigSystemDialog( wxWindow* parent, wxString& linkerPath, 
                                        wxString& startupPath, wxString& makefilePath,
                                        wxString& libraryPath,const wxString& currentDir)

    : wxDialog(parent, wxID_ANY, "Config System", wxDefaultPosition, wxSize(600, 400), wxDEFAULT_DIALOG_STYLE),
      linkerPathRef(linkerPath), startupPathRef(startupPath), makefilePathRef(makefilePath), libraryPathRef(libraryPath), currentDir(currentDir)
{

    wxString pathTemp = currentDir + "/../Component/Tools/System";
    wxString linkerDefault = pathTemp + "/Linker.ld";
    wxString startupDefault = pathTemp + "/Startup.c";
    wxString makefileDefault = pathTemp + "/Makefile";


    linkerPath = linkerPath.IsEmpty() ? linkerDefault : linkerPath;
    startupPath = startupPath.IsEmpty() ? startupDefault : startupPath;
    makefilePath = makefilePath.IsEmpty() ? makefileDefault : makefilePath;


    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Linker Script
    // Linker Script
    wxBoxSizer* linkerSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* linkerLabel = new wxStaticText(this, wxID_ANY, "Linker Script:");
    linkerLabel->SetMinSize(wxSize(100, -1)); // Đặt chiều rộng cố định cho nhãn
    linkerSizer->Add(linkerLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    linkerTextCtrl = new wxTextCtrl(this, wxID_ANY, linkerPath, wxDefaultPosition, wxSize(500, -1));
    linkerSizer->Add(linkerTextCtrl, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    wxButton* linkerBrowseBtn = new wxButton(this, ID_BROWSE_LINKER, "Browse...");
    linkerSizer->Add(linkerBrowseBtn, 0, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(linkerSizer, 0, wxEXPAND | wxALL, 10);

    // Startup File
    wxBoxSizer* startupSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* startupLabel = new wxStaticText(this, wxID_ANY, "Startup File:");
    startupLabel->SetMinSize(wxSize(100, -1)); // Đặt chiều rộng cố định cho nhãn
    startupSizer->Add(startupLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    startupTextCtrl = new wxTextCtrl(this, wxID_ANY, startupPath, wxDefaultPosition, wxSize(500, -1));
    startupSizer->Add(startupTextCtrl, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    wxButton* startupBrowseBtn = new wxButton(this, ID_BROWSE_STARTUP, "Browse...");
    startupSizer->Add(startupBrowseBtn, 0, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(startupSizer, 0, wxEXPAND | wxALL, 10);

    // Makefile
    wxBoxSizer* makefileSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* makefileLabel = new wxStaticText(this, wxID_ANY, "Makefile:");
    makefileLabel->SetMinSize(wxSize(100, -1)); // Đặt chiều rộng cố định cho nhãn
    makefileSizer->Add(makefileLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    makefileTextCtrl = new wxTextCtrl(this, wxID_ANY, makefilePath, wxDefaultPosition, wxSize(500, -1));
    makefileSizer->Add(makefileTextCtrl, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    wxButton* makefileBrowseBtn = new wxButton(this, ID_BROWSE_MAKEFILE, "Browse...");
    makefileSizer->Add(makefileBrowseBtn, 0, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(makefileSizer, 0, wxEXPAND | wxALL, 10);

    // Library Path (Ô mới)
    wxBoxSizer* librarySizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* libraryLabel = new wxStaticText(this, wxID_ANY, "Library Path:");
    libraryLabel->SetMinSize(wxSize(100, -1));
    librarySizer->Add(libraryLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    libraryTextCtrl = new wxTextCtrl(this, wxID_ANY, libraryPath, wxDefaultPosition, wxSize(500, -1));
    librarySizer->Add(libraryTextCtrl, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    wxButton* libraryBrowseBtn = new wxButton(this, ID_BROWSE_LIBRARY, "Browse...");
    librarySizer->Add(libraryBrowseBtn, 0, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(librarySizer, 0, wxEXPAND | wxALL, 10);

    // Buttons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* okBtn = new wxButton(this, wxID_OK, "OK");
    wxButton* cancelBtn = new wxButton(this, wxID_CANCEL, "Cancel");
    buttonSizer->Add(okBtn, 0, wxRIGHT, 5);
    buttonSizer->Add(cancelBtn, 0);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizerAndFit(mainSizer);

    // Bind events
    Bind(wxEVT_BUTTON, &ConfigSystemDialog::OnBrowseLinker, this, ID_BROWSE_LINKER);
    Bind(wxEVT_BUTTON, &ConfigSystemDialog::OnBrowseStartup, this, ID_BROWSE_STARTUP);
    Bind(wxEVT_BUTTON, &ConfigSystemDialog::OnBrowseMakefile, this, ID_BROWSE_MAKEFILE);
    Bind(wxEVT_BUTTON, &ConfigSystemDialog::OnBrowseLibrary,this,ID_BROWSE_LIBRARY);
    Bind(wxEVT_BUTTON, &ConfigSystemDialog::OnOK, this, wxID_OK);
    
}

void ConfigSystemDialog::OnBrowseLinker(wxCommandEvent& event)
{
    wxFileDialog openDlg(this, "Select Linker Script", "", "", "Linker Scripts (*.ld)|*.ld|All Files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openDlg.ShowModal() == wxID_OK)
    {
        linkerTextCtrl->SetValue(openDlg.GetPath());
    }
}

void ConfigSystemDialog::OnBrowseStartup(wxCommandEvent& event)
{
    wxFileDialog openDlg(this, "Select Startup File", "", "", "Assembly Files (*.s)|*.s|All Files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openDlg.ShowModal() == wxID_OK)
    {
        startupTextCtrl->SetValue(openDlg.GetPath());
    }
}

void ConfigSystemDialog::OnBrowseMakefile(wxCommandEvent& event)
{
    wxFileDialog openDlg(this, "Select Makefile", "", "", "Makefiles (Makefile;*.mk)|Makefile;*.mk|All Files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openDlg.ShowModal() == wxID_OK)
    {
        makefileTextCtrl->SetValue(openDlg.GetPath());
    }
}

void ConfigSystemDialog::OnBrowseLibrary(wxCommandEvent& event)
{
    wxDirDialog dirDlg(this, "Select Library Directory", currentDir, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dirDlg.ShowModal() == wxID_OK)
    {
        libraryTextCtrl->SetValue(dirDlg.GetPath());
    }
}

void ConfigSystemDialog::OnOK(wxCommandEvent& event)
{
    // Lưu các đường dẫn vào biến tham chiếu
    linkerPathRef = linkerTextCtrl->GetValue();
    startupPathRef = startupTextCtrl->GetValue();
    makefilePathRef = makefileTextCtrl->GetValue();
    libraryPathRef = libraryTextCtrl->GetValue(); // Lưu giá trị đường dẫn thư viện
    EndModal(wxID_OK);
}