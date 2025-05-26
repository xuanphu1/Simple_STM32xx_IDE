#ifndef MEMORY_VIEW_H
#define MEMORY_VIEW_H

#include <wx/wx.h>
#include <wx/grid.h>
#include "DebugManager.h"
#include <vector>

class MemoryView : public wxFrame
{
public:
    MemoryView(wxWindow *parent,DebugManager* dbgMgr, wxWindowID id = wxID_ANY,
               const wxString &title = "Memory Viewer",
               const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxSize(800, 400));

    std::vector<uint32_t> memoryData;   
    wxString addrStr;
    void FillGridWithData32Bit(std::vector<uint32_t> &data, const wxString &startAddr = "0x08000000");

private:
    wxTextCtrl *addressInput;
    wxButton *viewButton;
    wxGrid *grid;
    DebugManager *debugManager;

    static const int WORDS_PER_ROW = 4;
    static const int NUM_ROWS = 16;

    void OnViewButtonClicked(wxCommandEvent &event);
    
};

#endif // MEMORY_VIEW_H
