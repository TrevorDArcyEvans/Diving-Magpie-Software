//---------------------------------------------------------------------------
#ifndef utilsH
#define utilsH
//---------------------------------------------------------------------------
void            GetMachineID
(
    char*                   sMachID
);

unsigned long   CalculateCode
(
    char*                   Machine_ID ,
    char*                   Prod       
);

bool            CheckCode
(
    char*                   Machine_ID ,
    char*                   Prod       ,
    char*                   Code       
);

//---------------------------------------------------------------------------
#endif
