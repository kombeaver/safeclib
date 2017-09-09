/*------------------------------------------------------------------
 * test_strcpy_s
 * File 'str/strcpy_s.c'
 * Lines executed:73.33% of 45
 *
 *
 *------------------------------------------------------------------
 */

#include "test_private.h"
#include "safe_str_lib.h"

#define MAX   ( 128 )
#define LEN   ( 128 )

static char   str1[LEN];
static char   str2[LEN];

int test_strcpy_s (void)
{
    errno_t rc;
    uint32_t i;
    int32_t  ind;
    int errs = 0;

/*--------------------------------------------------*/

    rc = strcpy_s(NULL, LEN, str2);
    ERR(ESNULLP)
/*--------------------------------------------------*/

   strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    rc = strcpy_s(str1, 5, NULL);
    ERR(ESNULLP)
#ifdef SAFE_LIB_STR_NULL_SLACK
    for (i=0; i<5; i++) {
        if (str1[i] != '\0') {
            debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
            errs++;
        }
    }
#else
    if (str1[0] != '\0') {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
#endif

/*--------------------------------------------------*/

    rc = strcpy_s(str1, 0, str2);
    ERR(ESZEROL)
/*--------------------------------------------------*/

    rc = strcpy_s(str1, (RSIZE_MAX_STR+1), str2);
    ERR(ESLEMAX)
/*--------------------------------------------------*/
/*--------------------------------------------------*/

    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    str2[0] = '\0';

    rc = strcpy_s(str1, LEN/2, str2);
    ERR(EOK)
#ifdef SAFE_LIB_STR_NULL_SLACK
    for (i=0; i<LEN/2; i++) {
        if (str1[i] != '\0') {
            debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
            errs++;
        }
    }
#else
    if (str1[0] != '\0') {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
#endif

/*--------------------------------------------------*/

    strcpy(str1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    rc = strcpy_s(str1, LEN, str1);
    ERR(EOK)
/*--------------------------------------------------*/

    strcpy(&str1[0], "keep it simple");

    rc = strcpy_s(&str1[0], LEN, &str1[5]);
    ERR(ESOVRLP)
#ifdef SAFE_LIB_STR_NULL_SLACK
    for (i=0; i<LEN; i++) {
        if (str1[i] != '\0') {
            debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
            errs++;
        }
    }
#else
    if (str1[0] != '\0') {
        debug_printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc );
        errs++;
    }
#endif

/*--------------------------------------------------*/

    strcpy(&str1[0], "keep it simple");
    str2[0] = '\0';

    rc = strcpy_s(str1, LEN, str2);
    ERR(EOK)
    if (*str1 != '\0') {
        debug_printf("%s %u -%s-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
        errs++;
    }
/*--------------------------------------------------*/

    str1[0] = '\0';
    strcpy(&str2[0], "keep it simple");

    rc = strcpy_s(str1, LEN, str2);
    ERR(EOK)
    /* be sure the results are the same as strcmp */
    ind = strcmp(str1, str2);
    if (ind != 0) {
        debug_printf("%s %u -%s-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
        errs++;
    }
/*--------------------------------------------------*/

    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "keep it simple");

    rc = strcpy_s(str1, LEN, str2);
    ERR(EOK)
    /* be sure the results are the same as strcmp */
    ind = strcmp(str1, str2);
    if (ind != 0) {
        debug_printf("%s %u -%s-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
        errs++;
    }
/*--------------------------------------------------*/

    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "keep it simple");

    rc = strcpy_s(str1, 1, str2);
    ERR(ESNOSPC)
    if (*str1 != '\0') {
        debug_printf("%s %u -%s-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
        errs++;
    }
/*--------------------------------------------------*/

    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "keep it simple");

    rc = strcpy_s(str1, 2, str2);
    ERR(ESNOSPC)
    if (*str1 != '\0') {
        debug_printf("%s %u -%s-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
        errs++;
    }
/*--------------------------------------------------*/

    strcpy(str1, "qqweqeqeqeq");
    strcpy(str2, "it");

    rc = strcpy_s(str1, 3, str2);
    ERR(EOK)
    /* be sure the results are the same as strcmp */
    ind = strcmp(str1, str2);
    if (ind != 0) {
        debug_printf("%s %u -%s-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
        errs++;
    }
/*--------------------------------------------------*/

    strcpy(str1, "qq12345weqeqeqeq");
    strcpy(str2, "it");

    rc = strcpy_s(str1, 10, str2);
    ERR(EOK)
    /* be sure the results are the same as strcpy */
    ind = strcmp(str1, str2);
    if (ind != 0) {
        debug_printf("%s %u -%s-  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  str1, rc );
        errs++;
    }
    for (i=0; i<10; i++) {
        debug_printf("str1[%i] = %d \n", i, str1[i]);
        /*errs++;*/
    }
/*--------------------------------------------------*/

    return (errs);
}

#ifndef __KERNEL__
/* simple hack to get this to work for both userspace and Linux kernel,
   until a better solution can be created. */
int main (void)
{
    return (test_strcpy_s());
}
#endif
