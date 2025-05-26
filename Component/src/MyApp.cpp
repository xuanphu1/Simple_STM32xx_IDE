// src/MyApp.cpp
#include "../include/MyApp.h"

bool MyApp::OnInit() {
    wxInitAllImageHandlers();
    STM32IDE* frame = new STM32IDE();
    frame->Show();
    return true;
}

wxIMPLEMENT_APP(MyApp);