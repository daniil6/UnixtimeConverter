#include "RBKLib.h"
#include "mainframe.h"

// 00:00 1 января 1970

CMainFrame::CMainFrame(wxFrame* frame)
    : wxFrame(frame, wxID_ANY, wxT("UnixtimeConverter"))
{
    wxBoxSizer* main_sizer = new wxBoxSizer(wxHORIZONTAL);
    wxTextCtrl* m_dataTime = new wxTextCtrl(this, NewControlId(), wxT(""));
    main_sizer->Add(m_dataTime);
    this->SetSizerAndFit(main_sizer);

    long res = CalculateTime(36, 12, 45, 4, 5, 2020);

    wxString temp = wxString::Format(wxT("%i"), res);
    m_dataTime->SetValue(temp);
}

CMainFrame::~CMainFrame()
{
}
