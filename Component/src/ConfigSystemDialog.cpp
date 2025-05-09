// src/ConfigSystemDialog.cpp
#include "ConfigSystemDialog.h"

ConfigSystemDialog::ConfigSystemDialog(wxWindow* parent, wxString& linkerPath, wxString& startupPath, wxString& makefilePath,const wxString& currentDir)
    : wxDialog(parent, wxID_ANY, "Config System", wxDefaultPosition, wxSize(500, 300)),
      linkerPathRef(linkerPath), startupPathRef(startupPath), makefilePathRef(makefilePath), currentDir(currentDir)
{

    wxString pathTemp = currentDir + "/../Component/Tools/System";
    wxString linkerDefault = pathTemp + "/Linker.ld";
    wxString startupDefault = pathTemp + "/Startup.c";
    wxString makefileDefault = pathTemp + "/Makefile";

    linkerPath.IsEmpty() ? linkerDefault : linkerPath;
    startupPath.IsEmpty() ? startupDefault : startupPath;
    makefilePath.IsEmpty() ? makefileDefault : makefilePath;


    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Linker Script
    wxBoxSizer* linkerSizer = new wxBoxSizer(wxHORIZONTAL);
    linkerSizer->Add(new wxStaticText(this, wxID_ANY, "Linker Script:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    linkerTextCtrl = new wxTextCtrl(this, wxID_ANY, linkerPath);
    linkerSizer->Add(linkerTextCtrl, 1, wxEXPAND | wxRIGHT, 5);
    wxButton* linkerBrowseBtn = new wxButton(this, ID_BROWSE_LINKER, "Browse...");
    linkerSizer->Add(linkerBrowseBtn, 0, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(linkerSizer, 0, wxEXPAND | wxALL, 5);

    // Startup File
    wxBoxSizer* startupSizer = new wxBoxSizer(wxHORIZONTAL);
    startupSizer->Add(new wxStaticText(this, wxID_ANY, "Startup File:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    startupTextCtrl = new wxTextCtrl(this, wxID_ANY, startupPath);
    startupSizer->Add(startupTextCtrl, 1, wxEXPAND | wxRIGHT, 5);
    wxButton* startupBrowseBtn = new wxButton(this, ID_BROWSE_STARTUP, "Browse...");
    startupSizer->Add(startupBrowseBtn, 0, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(startupSizer, 0, wxEXPAND | wxALL, 5);

    // Makefile
    wxBoxSizer* makefileSizer = new wxBoxSizer(wxHORIZONTAL);
    makefileSizer->Add(new wxStaticText(this, wxID_ANY, "Makefile:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    makefileTextCtrl = new wxTextCtrl(this, wxID_ANY, makefilePath);
    makefileSizer->Add(makefileTextCtrl, 1, wxEXPAND | wxRIGHT, 5);
    wxButton* makefileBrowseBtn = new wxButton(this, ID_BROWSE_MAKEFILE, "Browse...");
    makefileSizer->Add(makefileBrowseBtn, 0, wxALIGN_CENTER_VERTICAL);
    mainSizer->Add(makefileSizer, 0, wxEXPAND | wxALL, 5);

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

void ConfigSystemDialog::OnOK(wxCommandEvent& event)
{
    // Lưu các đường dẫn vào biến tham chiếu
    linkerPathRef = linkerTextCtrl->GetValue();
    startupPathRef = startupTextCtrl->GetValue();
    makefilePathRef = makefileTextCtrl->GetValue();
    EndModal(wxID_OK);
}