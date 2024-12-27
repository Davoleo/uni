#include <omp.h>
#include <iostream>
#include <unistd.h>

int main()
{

    double t1, t2;

    std::cout << "Start timer" << std::endl;
    t1 = omp_get_wtime();

    // Do something long
    sleep(2);

    std::cout << "Stop timer" << std::endl;
    t2 = omp_get_wtime();

    std::cout << "time: " << t2 - t1 << std::endl;
}
