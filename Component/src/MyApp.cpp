// src/MyApp.cpp
#include "../include/MyApp.h"

bool MyApp::OnInit() {
    STM32IDE* frame = new STM32IDE();
    frame->Show();
    return true;
}

wxIMPLEMENT_APP(MyApp);