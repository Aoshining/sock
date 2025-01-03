#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <immintrin.h>

#define MAXN 100000000

float a[MAXN];
float b[MAXN];
float c[MAXN];
float d[MAXN];

int main()
{
    for (int i = 0; i < MAXN; ++i)
    {
        a[i] = 1.0 / (rand() + 1);
        b[i] = 1.0 / (rand() + 1);
    }
    for (int n = 0; n < 20; ++n)
    {
        for (int i = 0; i < MAXN; ++i)
        {
            d[i] += a[i] * b[i];
        }
    }
    clock_t start, end;
    start = clock();
    for (int n = 0; n < 20; ++n)
    {
        /* 可以修改的代码区域 */
        // -----------------------------------
    __m512 asimd,bsimd,csimd;
    for(int i=0;i<MAXN;i+=16)
    {
        asimd=_mm512_load_ps(&a[i]);
        bsimd=_mm512_load_ps(&b[i]);
        csimd=_mm512_fmadd_ps(asimd,bsimd,_mm512_load_ps(&c[i]));
        _mm512_store_ps(&c[i],csimd);
    }
    	// -----------------------------------
    }
    end = clock();
    printf("time=%f\n", (double)(end - start) / CLOCKS_PER_SEC);
    for (int i = 0; i < MAXN; ++i)
    {
        if (fabs(c[i] - d[i]) / d[i] > 0.0001)
        {
            printf("Check Failed at %d\n", i);
            return 0;
        }
    }
    printf("Check Passed");
}
