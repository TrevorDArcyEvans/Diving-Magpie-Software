// DMS_PROGPIPEIMPL : Implementation of TDMS_ProgPipeImpl (CoClass: DMS_ProgPipe, Interface: IDMS_ProgPipe)

#include <vcl.h>
#pragma hdrstop

#include "DMS_PROGPIPEIMPL.H"

/////////////////////////////////////////////////////////////////////////////
// TDMS_ProgPipeImpl
TDMS_ProgPipeImpl::TDMS_ProgPipeImpl()
{
}
//--------------------------------------------------------------------------
TDMS_ProgPipeImpl::~TDMS_ProgPipeImpl()
{
}
//--------------------------------------------------------------------------
HRESULT TDMS_ProgPipeImpl::FinalConstruct()
{
    try
        {
        ObjectLock(this);

        m_frmProgDlg = new TfrmProgDlg(NULL);

        m_Icon = NULL;
        m_Text = "Initialising...";
        m_Title = "Aerodrome Overview Window";
        m_Message = "CMIDS\nCopyright © 2000\nDiving Magpie Software";
        m_TotalSteps = 10;
        m_CurrentStep = 0;

        UpdateSettings();

        return S_OK;
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
}
//--------------------------------------------------------------------------
HRESULT TDMS_ProgPipeImpl::FinalRelease  ()
{
    try
        {
        ObjectLock(this);

        delete m_frmProgDlg;
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
void TDMS_ProgPipeImpl::UpdateSettings()
{
    try
        {
        m_frmProgDlg->Caption = m_Title;
        m_frmProgDlg->lblText->Caption = m_Text;
        m_frmProgDlg->lblMessage->Caption = m_Message;

        m_frmProgDlg->imgIcon->Picture->Icon->Handle = m_Icon;

        m_frmProgDlg->pbProgBar->Max = m_TotalSteps;
        m_frmProgDlg->pbProgBar->Position = m_CurrentStep;

        double      Percent = (double ) m_CurrentStep / m_TotalSteps * 100.0;
        String      TempStr;
        m_frmProgDlg->lblPercent->Caption = TempStr.FormatFloat("0%", Percent);

        m_frmProgDlg->Update();
        }
    catch(Exception &e)
        {
        Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::get_Text(BSTR* Value)
{
    try
        {
        ObjectLock(this);
        CComBSTR        sTempStr(m_Text.c_str());

        sTempStr.CopyTo(Value);
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::get_Title(BSTR* Value)
{
    try
        {
        ObjectLock(this);
        CComBSTR        sTempStr(m_Title.c_str());

        sTempStr.CopyTo(Value);
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::get_TotalSteps(long* Value)
{
    try
        {
        ObjectLock(this);
        *Value = m_TotalSteps;
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::Hide()
{
    try
        {
        ObjectLock(this);
        m_frmProgDlg->Hide();
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::set_Text(BSTR Value)
{
    try
        {
        ObjectLock(this);
        m_Text = String(Value);
        UpdateSettings();
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::set_Title(BSTR Value)
{
    try
        {
        ObjectLock(this);
        m_Title = String(Value);
        UpdateSettings();
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::set_TotalSteps(long Value)
{
    try
        {
        ObjectLock(this);
        m_TotalSteps = Value;
        UpdateSettings();
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::Show()
{
    try
        {
        ObjectLock(this);
        m_frmProgDlg->Show();
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::Step()
{
    try
        {
        ObjectLock(this);
        // increment and then clamp value
        m_CurrentStep++;
        m_CurrentStep = (m_CurrentStep > m_TotalSteps) ? m_TotalSteps : m_CurrentStep;
        UpdateSettings();
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::get_CurrentStep(long* Value)
{
    try
        {
        ObjectLock(this);
        *Value = m_CurrentStep;
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::set_CurrentStep(long Value)
{
    try
        {
        ObjectLock(this);
        m_CurrentStep = Value;
        UpdateSettings();
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::get_Icon(long* Value)
{
    try
        {
        ObjectLock(this);

        *Value = (long ) m_Icon;
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::set_Icon(long Value)
{
    try
        {
        ObjectLock(this);
        m_Icon = (HICON ) Value;
        UpdateSettings();
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::Reset()
{
    try
        {
        ObjectLock(this);
        m_CurrentStep = 0;
        UpdateSettings();
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::get_Message(BSTR* Value)
{
    try
        {
        ObjectLock(this);             
        CComBSTR        sTempStr(m_Message.c_str());

        sTempStr.CopyTo(Value);
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------
STDMETHODIMP TDMS_ProgPipeImpl::set_Message(BSTR Value)
{
    try
        {
        ObjectLock(this);
        m_Message = String(Value);
        UpdateSettings();
        }
    catch(Exception &e)
        {
        return Error(e.Message.c_str(), IID_IDMS_ProgPipe);
        }
    return S_OK;
}
//--------------------------------------------------------------------------

