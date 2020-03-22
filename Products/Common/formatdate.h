// Copied from olevar.cpp
const static COleDateTime MinDate (1900,1,1,1,1,1);
const static COleDateTime MaxDate (9999,1,1,1,1,1);

static CComBSTR FormatDate (const CComVariant& Var)
{
    COleDateTime Date = Var.date;

    if (Date.GetStatus () == COleDateTime::valid 
     && Date <= MaxDate 
     && Date >= MinDate)
        return Date.Format ((UINT)IDS_DATETIMEFORMAT);
    else
        return _T ("Invalid Time");
    //if
}
