//---------------------------------------------------------------------------
#ifndef utilsH
#define utilsH
//---------------------------------------------------------------------------
char            *GetMachineID(void);

unsigned long   CalculateCode(
                    char        *Machine_ID ,
                    char        *Prod       );

bool            CheckCode(
                    char        *Machine_ID ,
                    char        *Prod       ,
                    char        *Code       );

//---------------------------------------------------------------------------
#endif
