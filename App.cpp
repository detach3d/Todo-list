//
// Created by Rasul Mammadov on 06.04.25.
//

#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainFrame* mainFrame = new MainFrame{"To-Do list"};
    mainFrame->SetClientSize(800, 800);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}


