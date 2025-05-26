#ifndef DEBUGMANAGER_H
#define DEBUGMANAGER_H
#pragma once
#include <wx/wx.h>
#include "ProcessHandle.h"
#include "RegisterGroup.h"
#include "GDBProcessWinAPI.h"

class DebugManager : public wxEvtHandler
{
public:
    DebugManager(wxWindow *parent);
    ~DebugManager();

    bool StartDebugSession(const wxString &elfpath, const wxString &toolDirPath = wxEmptyString);
    void StopDebugSession();

    void SendCommand(const wxString &cmd);
    void AddBreakpoint(wxString currentlyFile,int line);
    void RemoveBreakpoint(wxString currentlyFile,int line);
    void SendRequestPeripheralRegister(RegisterGroup registerGroup);
    void SendRequestCoreRegister();
    void SendRequestMemory(const wxString &startAddr);

    void SendStepIntoCommandASM();
    void SendStepIntoCommand();
    void SendStepOverCommand();
    void SendStepOutCommand();
    void SendContinueCommand();
    void SendStopCommand();
    void SendResetCommand();

    void FillValuePeripheralRegister(wxString output, RegisterGroup &registerGroup);
    void FillValueCoreRegister(wxString output, RegisterGroup &_registerGroupCore);
    void FillValueMemory(wxString output, std::vector<uint32_t> &memoryData);
    bool IsRunning() const { return m_isRunning; }

private:
    wxWindow *m_parent;
    ProcessHandle *m_gdbServerProcess;
    ProcessHandle *m_gdbClientProcess;
    GDBProcessWinAPI m_gdbWinProcess;

    wxTimer *m_outputTimer;

    bool m_isRunning;

    void OnGdbOutput(wxTimerEvent &event);
    void OnProcessTerminated(wxProcessEvent &event);

    
};

wxDECLARE_EVENT(EVT_DEBUG_OUTPUT, wxCommandEvent);

#endif // DEBUGMANAGER_H