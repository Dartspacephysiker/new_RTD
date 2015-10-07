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
    /*File menu*/
    menuFile = new wxMenu;
    menuFile->Append(ID_LoadRTDConf, "&Load RTD Config...\tCtrl-L",
                     "Load an RTD configuration file");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    /*View menu*/
    menuView = new wxMenu;
    
    /*Help menu*/
    menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    /*Menu bar*/
    menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuView, "&View" );
    menuBar->Append( menuHelp, "&Help" );

    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to Dartmouth RTD!" );

    m_parent = new wxPanel(this, wxID_ANY);

    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    
    m_lp = new SpectrogramPanel(m_parent);
    m_rp = new SpectrListPanel(m_parent);
    
    hbox->Add(m_lp, 1, wxEXPAND | wxALL, 5);
    hbox->Add(m_rp, 1, wxEXPAND | wxALL, 5);
    
    m_parent->SetSizer(hbox);
    
    this->Centre();
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


SpectrogramPanel::SpectrogramPanel(wxPanel * parent)
       : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_SUNKEN)
{
  count = 0;
  m_parent = parent;
  m_plus = new wxButton(this, ID_PLUS, wxT("+"), 
      wxPoint(10, 10));
  m_minus = new wxButton(this, ID_MINUS, wxT("-"), 
      wxPoint(10, 60));
  Connect(ID_PLUS, wxEVT_COMMAND_BUTTON_CLICKED, 
      wxCommandEventHandler(SpectrogramPanel::OnPlus));
  Connect(ID_MINUS, wxEVT_COMMAND_BUTTON_CLICKED, 
      wxCommandEventHandler(SpectrogramPanel::OnMinus));
}

void SpectrogramPanel::OnPlus(wxCommandEvent & WXUNUSED(event))
{
  count++;

  DartRTDFrame *comm = (DartRTDFrame *) m_parent->GetParent();
  comm->m_rp->m_text->SetLabel(wxString::Format(wxT("%d"), count));
}

void SpectrogramPanel::OnMinus(wxCommandEvent & WXUNUSED(event))
{
  count--;

  DartRTDFrame *comm = (DartRTDFrame *) m_parent->GetParent();
  comm->m_rp->m_text->SetLabel(wxString::Format(wxT("%d"), count));
}


SpectrListPanel::SpectrListPanel(wxPanel * parent)
       : wxPanel(parent, wxID_ANY, wxDefaultPosition, 
         wxSize(270, 150), wxBORDER_SUNKEN)
{
    m_text = new wxStaticText(this, -1, wxT("0"), wxPoint(40, 60));
}
