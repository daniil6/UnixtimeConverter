#ifndef CMAINFRAME_H
#define CMAINFRAME_H

#include "wx/wx.h"

class CMainFrame : public wxFrame
{
private:
    enum { TIMER_ID = wxID_HIGHEST + 1 };

    wxTimer m_timer;
    wxTextCtrl* m_secDataTime;
    wxTextCtrl* m_dataTime;

    void OnTimerProcess(wxTimerEvent& event);

    DECLARE_EVENT_TABLE()

public:
    CMainFrame(wxFrame* frame);
    ~CMainFrame();
};

#endif // CMAINFRAME_H
