
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "simplerandom.h"

static int test_multi(void)
{
    SimpleRandomCong_t      cong;
    SimpleRandomSHR3_t      shr3;
    SimpleRandomMWC1_t      mwc1;
    SimpleRandomMWC2_t      mwc2;
    SimpleRandomKISS_t      kiss;
    SimpleRandomMWC64_t     mwc64;
    SimpleRandomKISS2_t     kiss2;
    SimpleRandomLFSR113_t   lfsr113;
    SimpleRandomLFSR88_t    lfsr88;
    uint32_t                i;
    uint32_t                k;


    printf("1,000,000 sample tests\n");
    /* Cong */
    simplerandom_cong_seed(&cong, UINT32_C(2051391225));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_cong_next(&cong);
    }
    printf("    Cong        %"PRIu32"\n", k - UINT32_C(2416584377));

    /* SHR3 */
    simplerandom_shr3_seed(&shr3, UINT32_C(3360276411));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_shr3_next(&shr3);
    }
    printf("    SHR3        %"PRIu32"\n", k - UINT32_C(1153302609));

    /* MWC1 */
    simplerandom_mwc1_seed(&mwc1, UINT32_C(2374144069), UINT32_C(1046675282));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_mwc1_next(&mwc1);
    }
    printf("    MWC1        %"PRIu32"\n", k - UINT32_C(904977562));

    /* MWC2 */
    simplerandom_mwc2_seed(&mwc2, UINT32_C(12345), UINT32_C(65437));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_mwc2_next(&mwc2);
    }
    printf("    MWC2        %"PRIu32"\n", k - UINT32_C(55050263));

    /* KISS */
    simplerandom_kiss_seed(&kiss, UINT32_C(2247183469), UINT32_C(99545079), UINT32_C(3269400377), UINT32_C(3950144837));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_kiss_next(&kiss);
    }
    printf("    KISS        %"PRIu32"\n", k - UINT32_C(2100752872));

#ifdef UINT64_C

    /* MWC64 */
    simplerandom_mwc64_seed(&mwc64, UINT32_C(7654321), UINT32_C(521288629));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_mwc64_next(&mwc64);
    }
    printf("    MWC64       %"PRIu32"\n", k - UINT32_C(3377343606));

    /* KISS2 */
    simplerandom_kiss2_seed(&kiss2, UINT32_C(7654321), UINT32_C(521288629), UINT32_C(123456789), UINT32_C(362436000));
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_kiss2_next(&kiss2);
    }
    printf("    KISS2       %"PRIu32"\n", k - UINT32_C(1010846401));

#endif /* defined(UINT64_C) */

    /* LFSR113 */
    simplerandom_lfsr113_seed(&lfsr113, 0, 0, 0, 0);
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_lfsr113_next(&lfsr113);
    }
    printf("    LFSR113     %"PRIu32"\n", k - UINT32_C(300959510));

    /* LFSR88 */
    simplerandom_lfsr88_seed(&lfsr88, 0, 0, 0);
    for (i = 0; i < 1000000; i++)
    {
        k = simplerandom_lfsr88_next(&lfsr88);
    }
    printf("    LFSR88      %"PRIu32"\n", k - UINT32_C(3774296834));

    printf("\n");
    return 0;
}

static int test_byte_cong(void)
{
    SimpleRandomCong_t      sr;
    uint32_t                i;
    uint32_t                j;

    printf("byte API tests\n");
    printf("    word output:\n");
    simplerandom_cong_seed(&sr, 1);
    for (i = 0; i < 3; i++)
    {
        printf("        %08X\n", simplerandom_cong_next(&sr));
    }

    printf("    uint16 output:\n");
    simplerandom_cong_seed(&sr, 1);
    for (i = 0; i < 3; i++)
    {
        printf("        ");
        for (j = 0; j < 2; j++)
        {
            printf("%04X ", simplerandom_cong_next_uint16(&sr));
        }
        printf("\n");
    }

    printf("    uint8 output:\n");
    simplerandom_cong_seed(&sr, 1);
    for (i = 0; i < 3; i++)
    {
        printf("        ");
        for (j = 0; j < 4; j++)
        {
            printf("%02X ", simplerandom_cong_next_uint8(&sr));
        }
        printf("\n");
    }

    printf("\n");
    return 0;
}

int main(void)
{
    int ret_val;

    ret_val = test_multi();
    if (ret_val != 0)
        return ret_val;

    ret_val = test_byte_cong();
    if (ret_val != 0)
        return ret_val;

    return 0;
}
