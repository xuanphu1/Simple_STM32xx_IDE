#include "ProcessHandle.h"

ProcessHandle::ProcessHandle(wxWindow *parent)
    : m_parent(parent), m_process(nullptr), m_outStream(nullptr), m_inStream(nullptr), m_pid(0)
{
}

ProcessHandle::~ProcessHandle()
{
    KillProcess();
}

long ProcessHandle::RunProcess(const wxString &Command, bool redirect, long flags)
{
    KillProcess();

    m_process = new wxProcess(m_parent);
    if (redirect)
        m_process->Redirect();

    m_pid = wxExecute(Command, flags, m_process);
    if (m_pid == 0)
    {
        delete m_process;
        m_process = nullptr;
        return 0;
    }

    if (redirect)
    {
        m_outStream = m_process->GetInputStream();
        m_inStream = m_process->GetOutputStream();
    }
    else
    {
        m_outStream = nullptr;
        m_inStream = nullptr;
    }

    return m_pid;
}

void ProcessHandle::SendCommand(const wxString &cmd)
{
    if (m_inStream)
    {
        wxTextOutputStream tos(*m_inStream);
        tos << cmd << "\n";
        tos.Flush();
    }
}

void ProcessHandle::KillProcess()
{
    if (m_process)
    {
        long pid = m_pid;
        if (pid != 0)
        {
            wxProcess::Kill(pid, wxSIGKILL);
        }
    }
}

bool ProcessHandle::IsRunning() const
{
    return m_process != nullptr && m_pid != 0;
}

wxInputStream *ProcessHandle::GetOutputStream() const
{
    return m_outStream;
}

void ProcessHandle::OnProcessTerminated(wxProcessEvent &event)
{
    if (event.GetPid() == m_pid)
    {
        wxLogMessage("Process %ld terminated with exit code %ld", m_pid, event.GetExitCode());
        delete m_process;
        m_process = nullptr;
        m_outStream = nullptr;
        m_inStream = nullptr;
        m_pid = 0;
    }
}
