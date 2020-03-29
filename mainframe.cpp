#include "mainframe.h"

// 00:00 1 января 1970

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
EVT_TIMER(TIMER_ID, CMainFrame::OnTimerProcess)
END_EVENT_TABLE()

CMainFrame::CMainFrame(wxFrame* frame)
    : wxFrame(frame, wxID_ANY, wxT("UnixtimeConverter"))
    , m_timer(this, TIMER_ID)
{
    wxPanel* panel = new wxPanel(this, NewControlId());

    m_secDataTime = new wxTextCtrl(panel, NewControlId(), wxT(""));
    m_dataTime = new wxTextCtrl(panel, NewControlId(), wxT("0000-00-00 00:00:00"), wxDefaultPosition, wxSize(130, 10));

    // Date time to second
    wxButton* m_btnConvertDateTimeToSecond = new wxButton(panel, NewControlId(), wxT("ConvertDTtoS"));
    m_txtSecOut = new wxTextCtrl(panel, NewControlId(), wxT("m_txtSecOut"));
    m_gridIn = new wxGrid(panel, NewControlId());
    m_gridIn->CreateGrid(1, 6);
    m_gridIn->SetRowLabelSize(0);
    m_gridIn->SetColLabelValue(0, wxT("Seconds"));
    m_gridIn->SetColLabelValue(1, wxT("Minutes"));
    m_gridIn->SetColLabelValue(2, wxT("Hours"));
    m_gridIn->SetColLabelValue(3, wxT("Days"));
    m_gridIn->SetColLabelValue(4, wxT("Months"));
    m_gridIn->SetColLabelValue(5, wxT("Years"));
    m_gridIn->AutoSizeColumns();

    // Second to date time
    wxButton* m_btnConvertSecondToDateTime = new wxButton(panel, NewControlId(), wxT("ConvertStoDT"));
    m_txtSecIn = new wxTextCtrl(panel, NewControlId(), wxT("m_txtSecIn"));
    m_gridOut = new wxGrid(panel, NewControlId());
    m_gridOut->CreateGrid(1, 6);
    m_gridOut->SetRowLabelSize(0);
    m_gridOut->SetColLabelValue(0, wxT("Seconds"));
    m_gridOut->SetColLabelValue(1, wxT("Minutes"));
    m_gridOut->SetColLabelValue(2, wxT("Hours"));
    m_gridOut->SetColLabelValue(3, wxT("Days"));
    m_gridOut->SetColLabelValue(4, wxT("Months"));
    m_gridOut->SetColLabelValue(5, wxT("Years"));
    m_gridOut->AutoSizeColumns();

    wxBoxSizer* main_box = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* h_box = nullptr;
    wxBoxSizer* v_box = nullptr;

    h_box = new wxStaticBoxSizer(wxHORIZONTAL, panel, wxT("Current time"));
    h_box->Add(m_secDataTime, 1, wxEXPAND);
    h_box->Add(m_dataTime, 1, wxEXPAND);
    main_box->Add(h_box);

    v_box = new wxStaticBoxSizer(wxVERTICAL, panel, wxT("Data and time to seconds"));
    v_box->Add(m_gridIn);

    h_box = new wxBoxSizer(wxHORIZONTAL);
    h_box->Add(m_btnConvertDateTimeToSecond);
    h_box->Add(m_txtSecOut);
    v_box->Add(h_box);

    main_box->Add(v_box);

    v_box = new wxStaticBoxSizer(wxVERTICAL, panel, wxT("Seconds to data and time"));

    h_box = new wxBoxSizer(wxHORIZONTAL);
    h_box->Add(m_txtSecIn);
    h_box->Add(m_btnConvertSecondToDateTime);

    v_box->Add(h_box);
    v_box->Add(m_gridOut);

    main_box->Add(v_box);

    panel->SetSizer(main_box);
    wxBoxSizer* panel_box = new wxBoxSizer(wxHORIZONTAL);
    panel_box->Add(panel);
    this->SetSizerAndFit(panel_box);

    Bind(wxEVT_BUTTON, &CMainFrame::OnConvertDateTimeToSecond, this, m_btnConvertDateTimeToSecond->GetId());
    Bind(wxEVT_BUTTON, &CMainFrame::OnConvertSecondToDateTime, this, m_btnConvertSecondToDateTime->GetId());

    m_timer.Start(1000);
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::OnConvertSecondToDateTime(wxCommandEvent& event)
{
    std::string temp = m_txtSecIn->GetValue().ToStdString();
    double t_d = ConvertStringToDouble(temp);
    tDateTime dateTime = convertSecToDateTime(long(t_d));

    m_gridOut->SetCellValue(0, 0, wxString::Format(wxT("%i"), dateTime.second));
    m_gridOut->SetCellValue(0, 1, wxString::Format(wxT("%i"), dateTime.minute));
    m_gridOut->SetCellValue(0, 2, wxString::Format(wxT("%i"), dateTime.hour));
    m_gridOut->SetCellValue(0, 3, wxString::Format(wxT("%i"), dateTime.day));
    m_gridOut->SetCellValue(0, 4, wxString::Format(wxT("%i"), dateTime.month));
    m_gridOut->SetCellValue(0, 5, wxString::Format(wxT("%i"), dateTime.year));
}

void CMainFrame::OnConvertDateTimeToSecond(wxCommandEvent& event)
{
    uint8_t countCol = m_gridIn->GetNumberCols();
    wxString t_str[countCol];
    int t_int[countCol];
    for(int i = 0; i < countCol; i++) {
        t_str[i] = m_gridIn->GetCellValue(0, i);
        if(t_str[i].empty() == true)
            t_str[i] = wxT("1");
    }

    for(int i = 0; i < countCol; i++)
        t_int[i] = wxAtoi(t_str[i]);

    tDateTime dateTime{ (uint8_t)t_int[0], (uint8_t)t_int[1], (uint8_t)t_int[2], (uint8_t)t_int[3], (uint8_t)t_int[4],
        (uint16_t)t_int[5] };

    long res = convertDateTimeToSec(dateTime);
    t_str[0] = wxString::Format(wxT("%i"), res);

    m_txtSecOut->SetValue(t_str[0]);
}

void CMainFrame::SetDefaultValue(tDateTime dateTime, wxString t_string)
{
    m_txtSecOut->SetValue(t_string);
    m_txtSecIn->SetValue(t_string);

    m_gridOut->SetCellValue(0, 0, wxString::Format(wxT("%i"), dateTime.second));
    m_gridOut->SetCellValue(0, 1, wxString::Format(wxT("%i"), dateTime.minute));
    m_gridOut->SetCellValue(0, 2, wxString::Format(wxT("%i"), dateTime.hour));
    m_gridOut->SetCellValue(0, 3, wxString::Format(wxT("%i"), dateTime.day));
    m_gridOut->SetCellValue(0, 4, wxString::Format(wxT("%i"), dateTime.month));
    m_gridOut->SetCellValue(0, 5, wxString::Format(wxT("%i"), dateTime.year));

    m_gridIn->SetCellValue(0, 0, wxString::Format(wxT("%i"), dateTime.second));
    m_gridIn->SetCellValue(0, 1, wxString::Format(wxT("%i"), dateTime.minute));
    m_gridIn->SetCellValue(0, 2, wxString::Format(wxT("%i"), dateTime.hour));
    m_gridIn->SetCellValue(0, 3, wxString::Format(wxT("%i"), dateTime.day));
    m_gridIn->SetCellValue(0, 4, wxString::Format(wxT("%i"), dateTime.month));
    m_gridIn->SetCellValue(0, 5, wxString::Format(wxT("%i"), dateTime.year));
}

void CMainFrame::SetDateAndTime()
{
    wxDateTime dt = wxDateTime::Now();

    tDateTime dateTime{ (uint8_t)dt.GetSecond(), (uint8_t)dt.GetMinute(), (uint8_t)dt.GetHour(), (uint8_t)dt.GetDay(),
        (uint8_t)dt.GetMonth(), (uint16_t)dt.GetYear() };

    long res = convertDateTimeToSec(dateTime);
    wxString t_string = wxString::Format(wxT("%i"), res);

    m_secDataTime->SetValue(t_string);
    m_dataTime->SetValue(dt.Format(wxT("%Y-%m-%d %H:%M:%S")));
}

void CMainFrame::OnTimerProcess(wxTimerEvent& event)
{
    SetDateAndTime();
}