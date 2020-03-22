//----------------------------------------------------------------------------
#ifndef UnfragFileH
#define UnfragFileH
//----------------------------------------------------------------------------

//-----------------------------------------------
void	RemovePreview(
                    int         nTimeOut    ,
                    char        *pcFileName );

void	RemoveGeometry(
                    int         nTimeOut    ,
                    char        *pcFileName );

int 	UnfragFile(
                    int         nTimeOut    ,
                    char        *pcFileName );
//-----------------------------------------------
#endif    
