#include <omp.h>
#include <stdio.h>

int main()
{
    int t, i, j = 0;
#pragma omp parallel private(t, i) shared(j)
    {
        t = omp_get_thread_num();
        printf("running %d\n", t);
        for (i = 0; i < 1000000; i++)
        {
            // #pragma omp critical
            j++; /* race! */
        }
        printf("ran %d\n", t);
    }
    printf("%d\n", j);
}
