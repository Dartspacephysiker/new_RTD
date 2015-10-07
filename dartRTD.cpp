/*
          dartRTD      - Finally, an RTD that doesn't use FLU!
     =================   

     Author:             Spencer M. Hatch, Dartmouth College
     ======= 

     Revision history:
     =================
     2015/10/07          Beginnings



 */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <fstream>
#include <iostream>

#include <fftw3.h>

#include "dartRTD.h"

extern "C" {
    //Want to use ascii_conf_reader to read in an RTD conf file
    #include "RTD_conf_reader.h"
    #include "RTD_conf_structs.h"
}

enum
{
    ID_LoadRTDConf = 1,

    ID_MENUVIEW    = 3
};


wxBEGIN_EVENT_TABLE(DartRTDFrame, wxFrame)
    EVT_MENU(ID_LoadRTDConf,   DartRTDFrame::OnLoadRTDConf)
    EVT_MENU(wxID_EXIT,        DartRTDFrame::OnExit)
    EVT_MENU(wxID_ABOUT,       DartRTDFrame::OnAbout)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(DartRTDApp);
bool DartRTDApp::OnInit()
{
    
    DartRTDFrame *frame = new DartRTDFrame( "Dartmouth RTD", wxPoint(50, 50), wxSize(450, 340) );
    frame->Show( true );
    return true;
}
DartRTDFrame::DartRTDFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_LoadRTDConf, "&Load RTD Config...\tCtrl-L",
                     "Load an RTD configuration file");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuView = new wxMenu;
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuView, "&View" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to Dartmouth RTD!" );
}
void DartRTDFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void DartRTDFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "Dartmouth Real-Time Display, vBIZZAZZ",
                  "About Dartmouth RTD", wxOK | wxICON_INFORMATION );
}
void DartRTDFrame::OnLoadRTDConf(wxCommandEvent& event)
{
    wxLogMessage("Bout to load dat");
}
