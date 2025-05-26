// include/DirectoryTreeManager.h
#ifndef DIRECTORYTREEMANAGER_H
#define DIRECTORYTREEMANAGER_H

#include "main.h"
#include "MyTreeItemData.h"

class DirectoryTreeManager {
public:
    DirectoryTreeManager(wxTreeCtrl* tree, wxStyledTextCtrl* console);
    void LoadDirectoryTree(const wxString& projectPath);
    void OnTreeSelect(wxTreeEvent& event, wxStyledTextCtrl* editor, wxString& currentfile);

private:
    wxTreeCtrl* tree;
    wxStyledTextCtrl* console;

    void LoadDirectory(wxTreeItemId parent, const wxString& path);
};

#endif // DIRECTORYTREEMANAGER_H