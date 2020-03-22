// DMS_DIFFWORKSIMPL : Implementation of TDMS_DiffWorksImpl (CoClass: DMS_DiffWorks, Interface: IDMS_DiffWorks)

#include <vcl.h>
#pragma hdrstop

#include "DMS_DIFFWORKSIMPL.H"
#include "ShowResults.h"
#include "GetInfo.h"
//---------------------------------------------------------------------
const String    MassFormatKilo      = "0.0000000";
const String    MassFormatGram      = "0.000";
const String    VolumeFormatMeter   = "0.0000000";
const String    VolumeFormatMilli   = "0.000";
const String    AreaFormatMeter     = "0.0000000";
const String    AreaFormatMilli     = "0.000";

const String    DensityFormatKilo   = "0.000";
const String    DensityFormatGram   = "0.0000000";
//---------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// TDMS_DiffWorksImpl
//---------------------------------------------------------------------
TDMS_DiffWorksImpl::TDMS_DiffWorksImpl()
{
}
//---------------------------------------------------------------------
TDMS_DiffWorksImpl::~TDMS_DiffWorksImpl()
{
}
//---------------------------------------------------------------------
HRESULT TDMS_DiffWorksImpl::FinalConstruct()
{
    m_Icon = NULL;
    m_frmShowResults = new TfrmShowResults(NULL);

    return S_OK;
}
//---------------------------------------------------------------------
HRESULT TDMS_DiffWorksImpl::FinalRelease  ()
{
    delete m_frmShowResults;

    return S_OK;
}
//---------------------------------------------------------------------
STDMETHODIMP TDMS_DiffWorksImpl::set_Icon(long Param1)
{
    HRESULT             hr = S_OK;

    try
        {
        m_Icon = (HICON ) Param1;
        }
    catch(Exception &e)
        {
        hr = Error(e.Message.c_str(), IID_IDMS_DiffWorks);
        }
    catch(...)
        {
        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------
STDMETHODIMP TDMS_DiffWorksImpl::GetCompareInfo(BSTR* OriginalName,
  BSTR* ChangedName, BSTR* DisplayName, double* Transparency, long* Colour)
{
    HRESULT             hr = S_OK;
    TfrmGetInfo*        frmGetInfo = new TfrmGetInfo(NULL);

    try
        {
        if (NULL != m_Icon)
            {
            frmGetInfo->Icon->Handle = m_Icon;
            }

        if (mrOk == frmGetInfo->ShowModal())
            {
            // retrieve info from fields
            CComBSTR            TempOriginal(WideString(frmGetInfo->fedOriginal->FileName));
            CComBSTR            TempChanged (WideString(frmGetInfo->fedChanged ->FileName));
            CComBSTR            TempDisplay (WideString(frmGetInfo->fedChanged ->FileName));

            TempOriginal.CopyTo(OriginalName);
            TempChanged .CopyTo(ChangedName );
            TempDisplay .CopyTo(DisplayName );
            *Transparency = frmGetInfo->sldTransparency->Value / 100.0;
            *Colour = frmGetInfo->ccbxColour->ColorValue;

            hr = S_OK;
            }
        else
            {
            // user cancelled, so set return code
            hr = S_FALSE;
            }
        }
    catch(Exception &e)
        {
        hr = Error(e.Message.c_str(), IID_IDMS_DiffWorks);
        }
    catch(...)
        {
        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------
STDMETHODIMP TDMS_DiffWorksImpl::ShowCompareResults(BSTR OriginalName,
  BSTR ChangedName, double OriginalMass, double ChangedMass,
  double OriginalVolume, double ChangedVolume, double OriginalArea,
  double ChangedArea)
{
    HRESULT             hr = S_OK;

    try
        {
        if (NULL != m_Icon)
            {
            m_frmShowResults->Icon->Handle = m_Icon;
            }
        double                  OriginalDensity = 0.0;

        if (OriginalMass * OriginalVolume < 0.01)
            {
            OriginalDensity = 0.0;
            }
        else
            {
            OriginalDensity = OriginalMass / OriginalVolume;
            }

        // transfer info to memo box
        m_frmShowResults->memResults->Clear();
        m_frmShowResults->memResults->Lines->Add("Original file     = " + String(OriginalName));
        m_frmShowResults->memResults->Lines->Add("Changed file      = " + String(ChangedName));
        m_frmShowResults->memResults->Lines->Add("");

        m_frmShowResults->memResults->Lines->Add("Density           = " + String().FormatFloat(DensityFormatKilo  , OriginalDensity) + " kilograms per cubic meter");
        m_frmShowResults->memResults->Lines->Add("                  = " + String().FormatFloat(DensityFormatGram  , OriginalDensity / 1.0e6) + " grams per cubic millimeter");
        m_frmShowResults->memResults->Lines->Add("");

        m_frmShowResults->memResults->Lines->Add("Original mass     = " + String().FormatFloat(MassFormatKilo  , OriginalMass) + " kilograms");
        m_frmShowResults->memResults->Lines->Add("                  = " + String().FormatFloat(MassFormatGram  , OriginalMass * 1.0e3) + " grams");
        m_frmShowResults->memResults->Lines->Add("Changed mass      = " + String().FormatFloat(MassFormatKilo  , ChangedMass) + " kilograms");
        m_frmShowResults->memResults->Lines->Add("                  = " + String().FormatFloat(MassFormatGram  , ChangedMass * 1.0e3) + " grams");
        m_frmShowResults->memResults->Lines->Add("");

        m_frmShowResults->memResults->Lines->Add("Original volume   = " + String().FormatFloat(VolumeFormatMeter, OriginalVolume) + " cubic meters");
        m_frmShowResults->memResults->Lines->Add("                  = " + String().FormatFloat(VolumeFormatMilli, OriginalVolume * 1.0e9) + " cubic millimeters");
        m_frmShowResults->memResults->Lines->Add("Changed volume    = " + String().FormatFloat(VolumeFormatMeter, ChangedVolume ) + " cubic meters");
        m_frmShowResults->memResults->Lines->Add("                  = " + String().FormatFloat(VolumeFormatMilli, ChangedVolume * 1.0e9) + " cubic millimeters");
        m_frmShowResults->memResults->Lines->Add("");

        m_frmShowResults->memResults->Lines->Add("Original area     = " + String().FormatFloat(AreaFormatMeter, OriginalArea) + " square meters");
        m_frmShowResults->memResults->Lines->Add("                  = " + String().FormatFloat(AreaFormatMilli, OriginalArea * 1.0e6) + " square millimeters");
        m_frmShowResults->memResults->Lines->Add("Changed area      = " + String().FormatFloat(AreaFormatMeter, ChangedArea ) + " square meters");
        m_frmShowResults->memResults->Lines->Add("                  = " + String().FormatFloat(AreaFormatMilli, ChangedArea * 1.0e6) + " square millimeters");
        m_frmShowResults->memResults->Lines->Add("");
        
        m_frmShowResults->memResults->Lines->Add("Mass difference   = " + String().FormatFloat(MassFormatKilo  , OriginalMass - ChangedMass) + " kilograms"   );
        m_frmShowResults->memResults->Lines->Add("                  = " + String().FormatFloat(MassFormatGram  , (OriginalMass - ChangedMass) * 1.0e3) + " grams"   );
        m_frmShowResults->memResults->Lines->Add("Volume difference = " + String().FormatFloat(VolumeFormatMeter, OriginalVolume - ChangedVolume) + " cubic meters");
        m_frmShowResults->memResults->Lines->Add("                  = " + String().FormatFloat(VolumeFormatMilli, (OriginalVolume - ChangedVolume) * 1.0e9) + " cubic millimeters");
        m_frmShowResults->memResults->Lines->Add("Area difference   = " + String().FormatFloat(AreaFormatMeter, OriginalArea - ChangedArea) + " square meters");
        m_frmShowResults->memResults->Lines->Add("                  = " + String().FormatFloat(AreaFormatMilli, (OriginalArea - ChangedArea) * 1.0e6) + " square millimeters");

        m_frmShowResults->Show();
        }
    catch(Exception &e)
        {
        hr = Error(e.Message.c_str(), IID_IDMS_DiffWorks);
        }
    catch(...)
        {
        hr = E_UNEXPECTED;
        }

    return hr;
}
//------------------------------------------------------------------------

