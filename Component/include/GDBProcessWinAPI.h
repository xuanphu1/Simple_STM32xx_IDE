#include <windows.h>
#include <winnt.h>
#include <string>

class GDBProcessWinAPI
{
public:
    bool Start(const std::wstring &gdbCmd)
    {
        STARTUPINFOW si = {sizeof(si)};
        ZeroMemory(&pi, sizeof(pi));
        DWORD flags = CREATE_NO_WINDOW | CREATE_NEW_PROCESS_GROUP;
        wchar_t *cmdLine = _wcsdup(gdbCmd.c_str());
        BOOL ok = CreateProcessW(nullptr, cmdLine, nullptr, nullptr, FALSE, flags, nullptr, nullptr, &si, &pi);
        free(cmdLine);
        return (ok == TRUE);
    }

    void Interrupt()
    {
        if (pi.dwProcessId)
            GenerateConsoleCtrlEvent(CTRL_C_EVENT, pi.dwProcessId);
    }

    void Stop()
    {
        if (pi.hProcess)
        {
            TerminateProcess(pi.hProcess, 0);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            ZeroMemory(&pi, sizeof(pi));
        }
    }

    void WriteToStdin(const wxString &line)
    {
        DWORD written;
        if (m_hChildStdinWrite != NULL)
        {
            std::string cmd = std::string(line.mb_str());
            WriteFile(m_hChildStdinWrite, cmd.c_str(), cmd.length(), &written, NULL);
        }
    } // Gửi lệnh vào GDB đã chạy

    DWORD GetPid() const { return pi.dwProcessId; }

private:
    PROCESS_INFORMATION pi = {};
    HANDLE m_hChildStdinWrite = NULL;   // <--- BỔ SUNG DÒNG NÀY
};
