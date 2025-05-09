// src/DirectoryTreeManager.cpp
#include "DirectoryTreeManager.h"

DirectoryTreeManager::DirectoryTreeManager(wxTreeCtrl* tree, wxTextCtrl* console)
    : tree(tree), console(console) {}

void DirectoryTreeManager::LoadDirectoryTree(const wxString& projectPath) {
    tree->DeleteAllItems();
    if (projectPath.empty()) return;
    wxFileName projectDir(projectPath);
    wxTreeItemId root = tree->AddRoot(projectDir.GetFullName());
    LoadDirectory(root, projectPath);
    tree->Expand(root);
}

void DirectoryTreeManager::LoadDirectory(wxTreeItemId parent, const wxString& path) {
    wxDir dir;
    if (!dir.Open(path)) {
        console->AppendText("Cannot access directory: " + path + "\n");
        return;
    }
    wxString filename;
    bool cont = dir.GetFirst(&filename);
    while (cont) {
        wxFileName filepath(path, filename);
        wxString fullPath = filepath.GetFullPath();
        wxTreeItemId child = tree->AppendItem(parent, filename);
        tree->SetItemData(child, new MyTreeItemData(fullPath));
        if (wxDir::Exists(fullPath)) {
            LoadDirectory(child, fullPath);
        }
        cont = dir.GetNext(&filename);
    }
}

void DirectoryTreeManager::OnTreeSelect(wxTreeEvent& event, wxTextCtrl* editor) {
    wxTreeItemId item = event.GetItem();
    if (!item.IsOk()) {
        console->AppendText("Invalid tree item selected.\n");
        return;
    }
    MyTreeItemData* data = dynamic_cast<MyTreeItemData*>(tree->GetItemData(item));
    if (!data) {
        console->AppendText("No data associated with the selected item.\n");
        return;
    }
    wxString filepath = data->GetPath();
    console->AppendText("Selected file: " + filepath + "\n");
    if (wxFile::Exists(filepath)) {
        wxFile file(filepath, wxFile::read);
        if (file.IsOpened()) {
            wxString content;
            file.ReadAll(&content);
            editor->SetValue(content);
            file.Close();
            console->AppendText("File loaded successfully: " + filepath + "\n");
        } else {
            console->AppendText("Cannot open file: " + filepath + "\n");
        }
    } else {
        console->AppendText("Selected item is a directory, not a file: " + filepath + "\n");
    }
}