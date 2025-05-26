#include "MemoryView.h"

MemoryView::MemoryView(wxWindow* parent,DebugManager* dbgMgr, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(parent, id, title, pos, size), debugManager(dbgMgr), addrStr("0x08000000")
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Input address + button
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
    addressInput = new wxTextCtrl(this, wxID_ANY);
    addressInput->SetValue("0x08000000"); // mặc định địa chỉ
    viewButton = new wxButton(this, wxID_ANY, "View Memory");

    inputSizer->Add(new wxStaticText(this, wxID_ANY, "Start Address:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    inputSizer->Add(addressInput, 1, wxRIGHT, 5);
    inputSizer->Add(viewButton, 0);

    mainSizer->Add(inputSizer, 0, wxEXPAND | wxALL, 5);

    // Grid setup
    grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(NUM_ROWS, WORDS_PER_ROW + 1); // +1 cho cột địa chỉ

    // Đặt nhãn cột
    grid->SetColLabelValue(0, "Address");
    for (int i = 0; i < WORDS_PER_ROW; ++i)
    {
        grid->SetColLabelValue(i + 1, wxString::Format("+%X", i * 4));
    }

    // Cố định kích thước cột (pixel)
    grid->SetColSize(0, 100);  // cột Address
    for (int i = 1; i <= WORDS_PER_ROW; ++i)
        grid->SetColSize(i, 90);  // mỗi word

    grid->SetDefaultRowSize(25, true);
    grid->EnableEditing(false);

    mainSizer->Add(grid, 1, wxEXPAND | wxALL, 5);

    SetSizer(mainSizer);

    // Event khi bấm nút xem memory
    viewButton->Bind(wxEVT_BUTTON, &MemoryView::OnViewButtonClicked, this);
}

void MemoryView::OnViewButtonClicked(wxCommandEvent& event)
{
    addrStr = addressInput->GetValue();
    debugManager->SendRequestMemory(addrStr);
}

void MemoryView::FillGridWithData32Bit(std::vector<uint32_t>& data, const wxString& startAddr)
{
    unsigned long baseAddr = 0;
    try
    {
        baseAddr = std::stoul(std::string(startAddr.mb_str()), nullptr, 16);
    }
    catch (...)
    {
        wxMessageBox("Invalid address format! Please input a hex address.", "Error", wxICON_ERROR);
        return;
    }

    for (int row = 0; row < NUM_ROWS; ++row)
    {
        unsigned long rowAddr = baseAddr + row * WORDS_PER_ROW * 4;
        grid->SetCellValue(row, 0, wxString::Format("0x%08lX", rowAddr));

        for (int col = 0; col < WORDS_PER_ROW; ++col)
        {
            int idx = row * WORDS_PER_ROW + col;

            if (idx < (int)data.size())
            {
                uint32_t word = data[idx];
                grid->SetCellValue(row, col + 1, wxString::Format("0x%08X", word));
            }
            else
            {
                grid->SetCellValue(row, col + 1, "");
            }
        }
    }

    // Cố định kích thước cột (có thể đặt lại theo ý bạn)
    grid->SetColSize(0, 120);
    for (int c = 1; c <= WORDS_PER_ROW; ++c)
        grid->SetColSize(c, 100);

    grid->Refresh();
}
