#include <stdio.h>
#include <assert.h>

#if !(defined TRUE)
#define TRUE                 0
#endif

#if !(defined FALSE)
#define FALSE                (-1)
#endif

/*#define TEST_PROG            1*/
#define PLACE_HOLDER(x)      (void ) (x)

#if !(defined ASSERT)
#   define  ASSERT  assert
#endif

/* ------------------------------------------------------------- */

extern int      crc32file(
                    unsigned long                   *CRC32  ,
                    long                            *CharCnt,
                    char                            *name   );

extern int      crc32string(
                    unsigned long                   *CRC32  ,
                    long                            *CharCnt,
                    char                            *string );

/* ------------------------------------------------------------- */
