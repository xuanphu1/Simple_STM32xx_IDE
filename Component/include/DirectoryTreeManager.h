// include/DirectoryTreeManager.h
#ifndef DIRECTORYTREEMANAGER_H
#define DIRECTORYTREEMANAGER_H

#include "main.h"
#include "MyTreeItemData.h"

class DirectoryTreeManager {
public:
    DirectoryTreeManager(wxTreeCtrl* tree, wxTextCtrl* console);
    void LoadDirectoryTree(const wxString& projectPath);
    void OnTreeSelect(wxTreeEvent& event, wxTextCtrl* editor);

private:
    wxTreeCtrl* tree;
    wxTextCtrl* console;

    void LoadDirectory(wxTreeItemId parent, const wxString& path);
};

#endif // DIRECTORYTREEMANAGER_H