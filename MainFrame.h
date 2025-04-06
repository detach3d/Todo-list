//
// Created by Rasul Mammadov on 06.04.25.
//

#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <wx/wx.h>


class MainFrame : public wxFrame{
public:
    MainFrame(const wxString& title);
    private:
    void CreateControls();
    void BindEventHandlers();

    void OnAddButtonClicked(wxCommandEvent& event);
    void OnInputEnter(wxCommandEvent& event);
    void OnListKeyDown(wxKeyEvent& event);
    void OnClearButtonClicked(wxCommandEvent& event);
    void OnDeleteButtonClicked(wxCommandEvent& event);
    void OnSaveButtonClicked(wxCommandEvent& event);
    void OnLoadButtonClicked(wxCommandEvent& event);

    void DeleteButtonClicked();
    void AddTaskFromInput();
    void MoveSelectedTask(int offset);
    void SwapTasks(int i, int j);

    wxPanel* panel;
    wxStaticText* headlineText;
    wxTextCtrl* inputField;
    wxButton* addButton;
    wxCheckListBox* checkBox;
    wxButton* clearButton;
    wxButton* deleteButton;
    wxButton* saveButton;
    wxTextCtrl* saveFile;
    wxTextCtrl* loadFile;
    wxButton* loadButton;
};



#endif //MAINFRAME_H
