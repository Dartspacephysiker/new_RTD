//dartRTD.h

#ifndef __DART_RTD_H_INCLUDED__   
#define __DART_RTD_H_INCLUDED__   


#include <fstream>

const int ID_PLUS = 101;
const int ID_MINUS = 102;

class DARTRTD_Measurement { 

  private:
    std::string        sName;
    std::string        sAbbrev;
    std::string        sUser;

    std::string        sRTDDataFile;
    std::ifstream      fsRTDDataFile;

    std::string        sRTDDataOut;
    std::ofstream      fsRTDDataOut;

    std::string        sDataType;
    unsigned short     uDataType;

    long int           lSPS;
};

class DartRTDApp: public wxApp
{
public:
    virtual bool OnInit();
};

/*The panel that holds the spectrograms*/
class SpectrogramPanel : public wxPanel
{
public:
    SpectrogramPanel(wxPanel *panSpecNMeas);

    void OnPlus(wxCommandEvent & event);
    void OnMinus(wxCommandEvent & event);

    wxButton *m_plus;
    wxButton *m_minus;
    wxPanel *SpecNMeasPanel;
    int count;

};

/*The panel that holds the list of available measurements*/
class MeasListPanel : public wxPanel
{
public:
    MeasListPanel(wxPanel *panSpecNMeas);

    void OnSetText(wxCommandEvent & event);

    wxStaticText *m_text;

};

/*The panel with spectrum plots*/
class PlotPanel : public wxPanel
{
public:
    PlotPanel(wxPanel *panPlotParent);

    void OnSetText(wxCommandEvent & event);

    wxStaticText *m_text;

};

/*The panel with plot controls*/
class PlotCtlPanel : public wxPanel
{
public:
    PlotCtlPanel(wxPanel *panPlotParent);

    void OnSetText(wxCommandEvent & event);

    wxStaticText *m_text;

};

class DartRTDFrame: public wxFrame
{
    wxMenu             * menuFile;
    wxMenu             * menuView;
    wxMenu             * menuHelp;
		       
    wxMenuBar          * menuBar;

public:
    DartRTDFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    wxPanel            * MasterPanel;

    wxPanel            * SpecNMeasPanel;
    SpectrogramPanel   * mSpectroPanel;
    MeasListPanel      * mMeasListPanel;
    wxBoxSizer         * hboxSpecNMeasSizer;

    wxPanel            * mPlotParentPanel;
    PlotPanel          * mPlotPanel;
    PlotCtlPanel       * mPlotCtlPanel;
    wxBoxSizer         * hPlotParentSizer;

    wxBoxSizer         * vboxall;

private:
    void OnHello(wxCommandEvent& event);
    void OnLoadRTDConf(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

#endif //end #define __DART_RTD_H_INCLUDED__   
