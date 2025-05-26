#include "RegisterView.h"

RegisterView::RegisterView(wxWindow* parent, RegisterGroup* Group)
    : wxFrame(parent, wxID_ANY, "Core Register View", wxDefaultPosition, wxSize(500, 400)),
      m_RegisterGroup(Group)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    grid = new wxGrid(this, wxID_ANY);
    InitGrid();
    sizer->Add(grid, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);

    RefreshView();
    Bind(wxEVT_CLOSE_WINDOW, &RegisterView::Onclose, this);
}

void RegisterView::InitGrid()
{
    SetTitle(m_RegisterGroup->GetGroupName());
    int nRegs = (int)m_RegisterGroup->GetRegisters().size();

    grid->CreateGrid(nRegs, 3);
    grid->SetColLabelValue(0, "Register Name");
    grid->SetColLabelValue(1, "Address");
    grid->SetColLabelValue(2, "Value");

    grid->EnableEditing(false);  // Không cho sửa trực tiếp
    grid->AutoSizeColumns();
}

void RegisterView::RefreshView()
{
    const auto& regs = m_RegisterGroup->GetRegisters();

    for (size_t i = 0; i < regs.size(); i++)
    {
        const Register& reg = regs[i];

        grid->SetCellValue(i, 0, wxString(reg.GetName()));
        grid->SetCellValue(i, 1, wxString::Format("0x%08X", reg.GetAddress()));
        grid->SetCellValue(i, 2, wxString::Format("0x%08X", reg.GetValue()));
    }

    grid->AutoSizeColumns();
}


void RegisterView::Onclose(wxCloseEvent& event)
{
    Destroy();
}