// include/MyTreeItemData.h
#ifndef MYTREEITEMDATA_H
#define MYTREEITEMDATA_H

#include "main.h"

class MyTreeItemData : public wxTreeItemData {
public:
    MyTreeItemData(const wxString& path);
    const wxString& GetPath() const { return m_path; }

private:
    wxString m_path;
};

#endif // MYTREEITEMDATA_H