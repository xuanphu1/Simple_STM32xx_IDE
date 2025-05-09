// include/MyApp.h
#ifndef MYAPP_H
#define MYAPP_H

#include "main.h"
#include "../include/STM32IDE.h"

class MyApp : public wxApp {
public:
    bool OnInit() override;
};

#endif // MYAPP_H