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
#include "dartRTD_confeditor.h"

#define DRTD_MIN_SPEC_WIDTH      500
#define DRTD_MIN_SPEC_HEIGHT     300

#define DRTD_MIN_ML_WIDTH        150

#define DRTD_MIN_PLOT_WIDTH      500
#define DRTD_MIN_PLOT_HEIGHT     200

#define DRTD_MIN_PLOTCTL_WIDTH   150

extern "C" {
    //Want to use ascii_conf_reader to read in an RTD conf file
    #include "RTD_conf_reader.h"
    #include "RTD_conf_structs.h"
}

enum
{
    ID_LoadRTDConf = 1,
    ID_OpenRTDConf = 2,
    ID_MENUVIEW    = 3
};

wxBEGIN_EVENT_TABLE(DartRTDFrame, wxFrame)
    EVT_MENU(ID_LoadRTDConf,   DartRTDFrame::OnLoadRTDConf)
    EVT_MENU(ID_OpenRTDConf,   DartRTDFrame::OnOpenRTDConf)
    EVT_MENU(wxID_EXIT,        DartRTDFrame::OnExit)
    EVT_MENU(wxID_ABOUT,       DartRTDFrame::OnAbout)

wxEND_EVENT_TABLE()

BEGIN_EVENT_TABLE ( RTDConfFrame, wxFrame )
	EVT_MENU(RTDCONFEDIT_Load, RTDConfFrame::LoadConfFile)
	EVT_MENU(RTDCONFEDIT_New, RTDConfFrame::NewConfFile)
	EVT_MENU(RTDCONFEDIT_Open, RTDConfFrame::OpenConfFile) 
	EVT_MENU(RTDCONFEDIT_Close, RTDConfFrame::CloseConfFile)
	EVT_MENU(RTDCONFEDIT_Save, RTDConfFrame::SaveConfFile)
	EVT_MENU(RTDCONFEDIT_SaveAs, RTDConfFrame::SaveConfFileAs)
	EVT_MENU(RTDCONFEDIT_Quit, RTDConfFrame::Quit)
END_EVENT_TABLE()

wxIMPLEMENT_APP(DartRTDApp);

bool DartRTDApp::OnInit()
{
    int frameWidth  = DRTD_MIN_PLOT_WIDTH +  DRTD_MIN_PLOTCTL_WIDTH;
    int frameHeight = DRTD_MIN_PLOT_HEIGHT + DRTD_MIN_SPEC_HEIGHT;

    DartRTDFrame *frame = new DartRTDFrame( "Dartmouth RTD", wxPoint(50, 50), wxSize(frameWidth, frameHeight) );
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
    menuFile->Append(ID_OpenRTDConf, "&Open RTDConf Editor...\tCtrl-O",
                     "Open RTD configuration editor");
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
    SetStatusText( wxString("Current Configuration file: ") << wxString(sCurrentRTDFile) );

    /*Config struct*/
    psuRTDConfig = new suRTDConfig();

    /*Master panel for all displays*/
    MasterPanel = new wxPanel(this, wxID_ANY);

    /*Parent panel for spectrogram and measurement list*/
    //    SpecNMeasPanel = new wxPanel(this, wxID_ANY);
    SpecNMeasPanel = new wxPanel(MasterPanel);
    mSpectroPanel = new SpectrogramPanel(SpecNMeasPanel);
    mMeasListPanel = new MeasListPanel(SpecNMeasPanel);
    
    hboxSpecNMeasSizer = new wxBoxSizer(wxHORIZONTAL);			//Set up the spectrogram and measurement list sizer
    hboxSpecNMeasSizer->Add(mSpectroPanel, 4, wxEXPAND | wxALL, 5);
    hboxSpecNMeasSizer->Add(mMeasListPanel, 1, wxEXPAND | wxALL, 5);
    SpecNMeasPanel->SetSizerAndFit(hboxSpecNMeasSizer);
    
    /*Parent panel for plots*/
    //    mPlotParentPanel = new wxPanel(this, wxID_ANY);
    mPlotParentPanel = new wxPanel(MasterPanel);
    mPlotPanel = new PlotPanel(mPlotParentPanel);
    mPlotCtlPanel   = new PlotCtlPanel(mPlotParentPanel);

    hPlotParentSizer = new wxBoxSizer(wxHORIZONTAL);
    hPlotParentSizer->Add(mPlotPanel, 4, wxEXPAND | wxALL, 5);
    hPlotParentSizer->Add(mPlotCtlPanel, 1, wxEXPAND | wxALL, 5);
    mPlotParentPanel->SetSizerAndFit(hPlotParentSizer);

    vboxall = new wxBoxSizer(wxVERTICAL);				//Set up the sizer for all panels
    vboxall->Add(SpecNMeasPanel, 2, wxEXPAND | wxALL, 5);
    vboxall->Add(mPlotParentPanel, 1, wxEXPAND | wxALL, 5);
    MasterPanel->SetSizerAndFit(vboxall);
    this->Centre();

    SetMinClientSize(MasterPanel->GetBestSize());

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
    wxFileDialog *OpenDialog = new wxFileDialog(
						this, _("Choose an RTD configuration to open"), wxEmptyString, wxEmptyString,
						_("RTD Configuration file (*.rtdconf)|*.rtdconf"),
						wxFD_OPEN, wxDefaultPosition);
    
    // Creates a "open file" dialog with .rtdconf file type
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
	    SetRTDConfFile(OpenDialog->GetPath().ToStdString());
	    LoadRTDConfFile(sCurrentRTDFile);
	}

}

void DartRTDFrame::OnOpenRTDConf(wxCommandEvent& event)
{

    // Create an instance of window for RTD configuration editor
    RTDConfFrame *RTDConfWin = new RTDConfFrame(_("RTD Configuration Editor"), wxPoint(1, 1), wxSize(300, 200), this);
    RTDConfWin->Show(TRUE); // show the window
    RTDConfWin->Iconize(false); //Raise it from the dead (i.e., task bar)
    RTDConfWin->SetFocus();//Raise it to the top!
}

void DartRTDFrame::SetRTDConfFile(const std::string sRTDConfFilename)
{
    sCurrentRTDFile = sRTDConfFilename;
    SetStatusText( wxString("Current Configuration file: ") << wxString(sCurrentRTDFile) );

}

void DartRTDFrame::LoadRTDConfFile(const std::string sRTDConfFilename)
{
    wxLogMessage(wxString("Bout to load ") << wxString(sCurrentRTDFile));

    iInitRTDConfigFromASCII(sCurrentRTDFile.c_str(), psuRTDConfig, 1);
    //Update status bar
    SetStatusText( wxString("Current Configuration file: ") << wxString(sCurrentRTDFile) );
}

/*Panels*/

/*The panel that holds the spectrograms*/
SpectrogramPanel::SpectrogramPanel(wxPanel * panSpecNMeas)
       : wxPanel(panSpecNMeas, -1, wxPoint(-1, -1), wxSize(DRTD_MIN_SPEC_WIDTH, DRTD_MIN_SPEC_HEIGHT), wxBORDER_SUNKEN)
{
  count = 0;
  SpecNMeasPanel = panSpecNMeas;
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


  DartRTDFrame *comm = (DartRTDFrame *) SpecNMeasPanel->GetParent()->GetParent();
  comm->mMeasListPanel->m_text->SetLabel(wxString::Format(wxT("%d"), count));
}

void SpectrogramPanel::OnMinus(wxCommandEvent & WXUNUSED(event))
{
  count--;

  DartRTDFrame *comm = (DartRTDFrame *) SpecNMeasPanel->GetParent()->GetParent();
  comm->mMeasListPanel->m_text->SetLabel(wxString::Format(wxT("%d"), count));

  m_text = new wxStaticText(this, -1, wxT("Spectrograms live here"), wxPoint(100, 100));

}

/*The panel that holds the list of available measurements*/
MeasListPanel::MeasListPanel(wxPanel * panSpecNMeas)
       : wxPanel(panSpecNMeas, wxID_ANY, wxDefaultPosition, 
         wxSize(DRTD_MIN_ML_WIDTH, DRTD_MIN_SPEC_HEIGHT), wxBORDER_SUNKEN)
{
    m_text = new wxStaticText(this, -1, wxT("0"), wxPoint(40, 60));
    m_text = new wxStaticText(this, -1, wxT("Spectrogram control panel"), wxPoint(10, 100));
}

PlotPanel::PlotPanel(wxPanel * panPlotParent)
       : wxPanel(panPlotParent, wxID_ANY, wxDefaultPosition, 
         wxSize(DRTD_MIN_PLOT_WIDTH, DRTD_MIN_PLOT_HEIGHT), wxBORDER_SUNKEN)
{
    m_text = new wxStaticText(this, -1, wxT("Plot panel"), wxPoint(40, 60));
}

PlotCtlPanel::PlotCtlPanel(wxPanel * panPlotParent)
       : wxPanel(panPlotParent, wxID_ANY, wxDefaultPosition, 
         wxSize(DRTD_MIN_PLOTCTL_WIDTH, DRTD_MIN_PLOT_HEIGHT), wxBORDER_SUNKEN)
{
    m_text = new wxStaticText(this, -1, wxT("Plot control panel"), wxPoint(40, 60));
}
