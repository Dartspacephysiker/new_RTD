//dartRTD.h

#ifndef __DART_RTD_H_INCLUDED__   
#define __DART_RTD_H_INCLUDED__   


#include <fstream>

extern "C" {
    //Want to use ascii_conf_reader to read in an RTD conf file
    #include "RTD_conf_structs.h"
}

const int ID_PLUS = 101;
const int ID_MINUS = 102;

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

    wxStaticText *m_text;
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
    
    void SetRTDConfFile(const std::string sRTDConfFilename);
    void LoadRTDConfFile(const std::string sRTDConfFilename);
    std::string          sCurrentRTDFile;

    struct suRTDConfig * psuRTDConfig;

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
    void OnOpenRTDConf(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

class DARTRTD_Measurement { 

  private:
    std::string        sName;
    std::string        sAbbrev;
    std::string        sUser;

    std::string        sRTDDataFile;
    std::ifstream      fsRTDDataFile;

    std::string        sRTDDataOut;
    std::ofstream      fsRTDDataOut;

    unsigned short     uDataType;

    long int           lSPS;

    long int           nFFTSamples;
    long int           nFFTsToAvg;
    double           * pFFTInBuff   = NULL;
    double           * pFFTOutBuff  = NULL;

    //For displaying this measurement
    SpectrogramPanel * SpecPanel    = NULL;
    PlotPanel        * PltPanel     = NULL;
// int* a = NULL;   // Pointer to int, initialize to nothing.
// int n;           // Size needed for array
// cin >> n;        // Read in the size
// a = new int[n];  // Allocate n ints and save ptr in a.
// for (int i=0; i<n; i++) {
//     a[i] = 0;    // Initialize all elements to zero.
// }
// . . .  // Use a as a normal array
// delete [] a;  // When done, free memory pointed to by a.
// a = NULL;     // Clear a to prevent using invalid memory reference.

};

#endif //end #define __DART_RTD_H_INCLUDED__   
