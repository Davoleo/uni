#include <omp.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main() {

double t1,t2; 


cout << "Start timer" << endl; 
t1=omp_get_wtime();

// Do something long 
sleep(2);

cout << "Stop timer" << endl; 
t2=omp_get_wtime();

cout << "time: " << t2-t1 << endl; 

}
