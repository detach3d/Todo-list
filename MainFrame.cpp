//
// Created by Rasul Mammadov on 06.04.25.
//

#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <string>
#include "Task.h"

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title) {
    CreateControls();
    BindEventHandlers();
}

void MainFrame::CreateControls() {
    wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
    wxFont mainFont(wxFontInfo(wxSize(0, 15)));

    panel = new wxPanel(this);
    panel->SetFont(mainFont);

    headlineText = new wxStaticText(panel, wxID_ANY, "To-Do List", wxPoint(0, 22), wxSize(800, -1),
                                    wxALIGN_CENTER_HORIZONTAL);
    headlineText->SetFont(headlineFont);

    inputField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 87), wxSize(495, 20), wxTE_PROCESS_ENTER);
    // inputField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 87), wxSize(495, 20), wxTE_PROCESS_ENTER);
    addButton = new wxButton(panel, wxID_ANY, "Add", wxPoint(600, 80), wxSize(100, 35));
    checkBox = new wxCheckListBox(panel, wxID_ANY, wxPoint(100, 120), wxSize(600, 400));
    clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(100, 525), wxSize(100, 35));
    deleteButton = new wxButton(panel, wxID_ANY, "Delete", wxPoint(220, 525), wxSize(100, 35));
    saveButton =  new wxButton(panel, wxID_ANY, "Save", wxPoint(340, 560), wxSize(100, 35));
    loadButton =  new wxButton(panel, wxID_ANY, "Load", wxPoint(340, 600), wxSize(100, 35));
    saveFile = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 567), wxSize(220, 20));
    loadFile = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 607), wxSize(220, 20));
}

void MainFrame::BindEventHandlers() {
    addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddButtonClicked, this);
    inputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputEnter, this);
    checkBox->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this);
    clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClicked, this);
    deleteButton->Bind(wxEVT_BUTTON, &MainFrame::OnDeleteButtonClicked, this);
    saveButton->Bind(wxEVT_BUTTON, &MainFrame::OnSaveButtonClicked, this);
    loadButton->Bind(wxEVT_BUTTON, &MainFrame::OnLoadButtonClicked, this);
}

void MainFrame::OnAddButtonClicked(wxCommandEvent &event) {
    AddTaskFromInput();
}

void MainFrame::OnInputEnter(wxCommandEvent &event) {
    AddTaskFromInput();
}

void MainFrame::AddTaskFromInput() {
    wxString description = inputField->GetValue();

    if (!description.IsEmpty()) {
        checkBox->Insert(description, checkBox->GetCount());
        inputField->Clear();
    }
    inputField->SetFocus();
}

void MainFrame::OnListKeyDown(wxKeyEvent &event) {
    switch (event.GetKeyCode()) {
        case WXK_DELETE:
            DeleteButtonClicked();
            break;
        case WXK_UP:
            MoveSelectedTask(-1);
            break;
        case WXK_DOWN:
            MoveSelectedTask(1);
            break;
    }
}

void MainFrame::DeleteButtonClicked() {
    int index = checkBox->GetSelection();
    if (index == wxNOT_FOUND) {
        return;
    }
    checkBox->Delete(index);
}

void MainFrame::MoveSelectedTask(int index) {
    int selectedTask = checkBox->GetSelection();

    if (selectedTask == wxNOT_FOUND) {
        return;
    }

    int newTaskIndex = selectedTask + index;

    if (newTaskIndex >= 0 && newTaskIndex < checkBox->GetCount()) {
        SwapTasks(selectedTask, newTaskIndex);
        checkBox->SetSelection(newTaskIndex, true);
    }
}

void MainFrame::SwapTasks(int i, int j) {
    Task TaskI{ checkBox->GetString(i).ToStdString(), checkBox->IsChecked(i) };
    Task TaskJ{ checkBox->GetString(j).ToStdString(), checkBox->IsChecked(j) };

    checkBox->SetString(i, TaskJ.description);
    checkBox->SetString(j, TaskI.description);

    checkBox->Check(i, TaskJ.done);
    checkBox->Check(j, TaskI.done);
}

void MainFrame::OnClearButtonClicked(wxCommandEvent &event) {
    if (checkBox -> IsEmpty()) {
        return;
    }
    wxMessageDialog dialog(this, "Are you sure?", "Clear",wxYES_NO | wxCANCEL);

    int result = dialog.ShowModal();

    if (result == wxID_YES) {
        checkBox->Clear();
    }
}

void MainFrame::OnDeleteButtonClicked(wxCommandEvent &event) {
    int index = checkBox->GetSelection();
    if (index == wxNOT_FOUND) {
        return;
    }
    checkBox->Delete(index);
}

void MainFrame::OnSaveButtonClicked(wxCommandEvent &event) {
    std::vector<Task> tasks;
    std::string s = saveFile->GetValue().ToStdString();
    for (int i = 0; i < checkBox->GetCount(); i++) {
        tasks.push_back(Task(checkBox->GetString(i).ToStdString(), checkBox->IsChecked(i)));
    }
    saveTasks(tasks, s);
    event.Skip();
}

void MainFrame::OnLoadButtonClicked(wxCommandEvent &event) {
    checkBox->Clear();
    std::string s = loadFile->GetValue().ToStdString();
    std::vector<Task> tasks{loadTasks(s)};

    for (const Task &task : tasks) {
        int index = checkBox->GetCount();
        checkBox->Insert(task.description, index);
        checkBox->Check(index, task.done);
    }
}