#ifndef CORE_REGISTER_VIEW_H
#define CORE_REGISTER_VIEW_H

#include "main.h"
#include "RegisterModel.h"  // Chứa các lớp Register, RegisterGroup, RegisterModel

class RegisterView : public wxFrame 
{
public:
    RegisterView(wxWindow* parent, RegisterGroup* Group);

    void RefreshView();  // Cập nhật lại bảng khi có thay đổi



private:
    wxGrid* grid;
    RegisterGroup* m_RegisterGroup;

    void InitGrid();
    void Onclose(wxCloseEvent& event);
};

#endif // CORE_REGISTER_VIEW_H
