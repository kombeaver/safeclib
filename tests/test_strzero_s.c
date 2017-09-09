/*------------------------------------------------------------------
 * test_strzero_s
 * File 'extstr/strzero_s.c'
 * Lines executed:100.00% of 15
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define LEN   ( 128 )

int main()
{
    errno_t rc;
    rsize_t max_len;
    char   str1[LEN];
    uint32_t i;
    int errs = 0;

/*--------------------------------------------------*/

    rc = strzero_s(NULL, 5);
    ERR(ESNULLP)
/*--------------------------------------------------*/

    rc = strzero_s(str1, 0);
    ERR(ESZEROL)
/*--------------------------------------------------*/

    rc = strzero_s(str1, RSIZE_MAX_STR+1);
    ERR(ESLEMAX)
/*--------------------------------------------------*/

    max_len = 1;
    rc = strzero_s(str1, max_len);
    ERR(EOK)
    for (i=0; i<max_len; i++) {
       if (str1[i] != '\0') {
           debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
           errs++;
       }
    }

/*--------------------------------------------------*/

    max_len = 2;
    rc = strzero_s(str1, max_len);
    ERR(EOK)
    for (i=0; i<max_len; i++) {
       if (str1[i] != '\0') {
           debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
           errs++;
       }
    }

/*--------------------------------------------------*/

    max_len = 3;
    rc = strzero_s(str1, max_len);
    ERR(EOK)
    for (i=0; i<max_len; i++) {
       if (str1[i] != '\0') {
           debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
           errs++;
       }
    }

/*--------------------------------------------------*/

    max_len = LEN;
    rc = strzero_s(str1, max_len);
    ERR(EOK)
    for (i=0; i<max_len; i++) {
       if (str1[i] != '\0') {
           debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
           errs++;
       }
    }

/*--------------------------------------------------*/

    strcpy(str1, "Now is the time for all data to be zeroed");
    max_len = strlen("Now is the ");

    rc = strzero_s(str1, max_len);
    ERR(EOK)
    if (strcmp(&str1[max_len], "time for all data to be zeroed") ) {
        debug_printf("%s %u ERROR  --%s-- \n",
               __FUNCTION__, __LINE__,
               &str1[max_len]);
        errs++;
    }
/*--------------------------------------------------*/

    return (errs);
}
