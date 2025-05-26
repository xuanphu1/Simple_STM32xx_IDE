#ifndef PROCESSHANDLE_H
#define PROCESSHANDLE_H

#include <wx/wx.h>
#include <wx/process.h>
#include <wx/txtstrm.h>  // Thêm dòng này để dùng wxTextOutputStream

class ProcessHandle : public wxEvtHandler
{

public:
    ProcessHandle(wxWindow *parent);
    ~ProcessHandle();

    long RunProcess(const wxString &Command, bool redirect = true,long flags = wxEXEC_ASYNC);
    void SendCommand(const wxString &cmd);
    void KillProcess();
    bool IsRunning() const;
    long GetPID() const { return m_pid; }
    wxInputStream *GetOutputStream() const;

private:
    void OnProcessTerminated(wxProcessEvent &event);


    wxProcess *m_process = nullptr;
    wxInputStream *m_outStream = nullptr;
    wxOutputStream *m_inStream = nullptr;
    wxWindow *m_parent = nullptr;
    long m_pid = 0;

};

#endif // PROCESSHANDLE_H