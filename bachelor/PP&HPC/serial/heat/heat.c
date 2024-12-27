/*
heat.c

module load intel
icc -O2 heat.c -o heat

./heat -h
./heat -r 4096 -c 4096

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>  //gettimeofday
#include <getopt.h>


void options(int argc, char * argv[]) ;
void usage(char * argv[]);
void Jacobi_Iterator_CPU(float * __restrict T, float * __restrict T_new, const int NX, const int NY); 
void Init_custom(float * __restrict h_T, const int NX, const int NY); // custom 
void Init_center(float * __restrict h_T, const int NX, const int NY); // center 
void Init_left(float * __restrict h_T, const int NX, const int NY);   // left border
void Init_top(float * __restrict h_T, const int NX, const int NY);    // top border
void copy_rows(float * __restrict h_T, const int NX, const int NY);   // periodic boundary conditions
void copy_cols(float * __restrict h_T, const int NX, const int NY);   // periodic boundary conditions
void print_colormap(float * __restrict h_T);                          // 

int NX = 256;         // --- Number of discretization points along the x axis
int NY = 256;         // --- Number of discretization points along the y axis
int MAX_ITER = 1000;  // --- Number of Jacobi iterations


/********/
/* MAIN */
/********/
int main(int argc, char **argv)
{
    int iter,i,j;

    double t1, t2, t3, Tnp=0, Tp=0;
    struct timeval tempo;

    options(argc, argv);         /* optarg management */
    //  fprintf (stderr,"NX,NY,ITER,T,Tp,Tnp\n");

    float *h_T_new = (float *) calloc(NX * NY, sizeof(float));
    float *h_T_old = (float *) calloc(NX * NY, sizeof(float));
    float *h_T_temp;

    for(iter=0; iter<MAX_ITER; iter=iter+1)
    {
        gettimeofday(&tempo,0);
        t1=tempo.tv_sec+(tempo.tv_usec/1000000.0); // start timer1
    
        h_T_temp=h_T_new;
        h_T_new=h_T_old;
        h_T_old=h_T_temp;

        //Init_center(h_T_old, NX, NY);
        //Init_left(h_T_old,    NX, NY);
        //Init_top(h_T_old, NX, NY);
        Init_custom(h_T_old, NX, NY);
        copy_rows(h_T_old, NX, NY);
        copy_cols(h_T_old, NX, NY);

        gettimeofday(&tempo,0);  t2=tempo.tv_sec+(tempo.tv_usec/1000000.0); // start timer2

        Jacobi_Iterator_CPU(h_T_old, h_T_new, NX, NY);

        gettimeofday(&tempo,0);  t3=tempo.tv_sec+(tempo.tv_usec/1000000.0); // start timer3

        Tnp+=t2-t1;
        Tp+=t3-t2;

    }

   fprintf (stderr,"%d, %d, %d, %.3f, %.3f, %.3f \n", NX, NY, MAX_ITER, Tp+Tnp, Tp, Tnp);

    print_colormap(h_T_old);

    free(h_T_new);
    free(h_T_old);

    return 0;
}


/***********************************/
/* JACOBI ITERATION FUNCTION - CPU */
/***********************************/
void Jacobi_Iterator_CPU(float * __restrict T, float * __restrict T_new, const int NX, const int NY)
{
    int i,j;

    // --- Only update "interior" (not boundary) node points
    for(j=1; j<NY-1; j++)
        for(i=1; i<NX-1; i++) {
            float T_E = T[(i+1) + NX*j];
            float T_W = T[(i-1) + NX*j];
            float T_N = T[i + NX*(j+1)];
            float T_S = T[i + NX*(j-1)];
            T_new[NX*j + i] = 0.25*(T_E + T_W + T_N + T_S); //Normalize back to 0..1 interval [temp is based on the 4 adjacent cells]
        }
}


/********************************/
/* TEMPERATURE INITIALIZATION : */
/* parte centrale della griglia */
/********************************/
void Init_center(float * __restrict h_T, const int NX, const int NY)
{
    int i,j;
    int startx=NX/2-NX/10;  //40% della riga
    int endx=NX/2+NX/10;    //60% della riga
    int starty=NY/2-NY/10;  //40% della colonna
    int endy=NY/2+NY/10;    //60% della colonna
//    int starty=NY/4;
//    int endy=NY-NY/4;
    for(i=startx; i<endx; i++)
        for(j=starty; j<endy; j++)
              h_T[NX*j + i] = 1.0;
}

/* Squared Torus */
void Init_custom(float *__restrict h_T, const int NX, const int NY)
{
    int i, j;
    int startx = NX / 2 - NX / 6;
    int endx = NX / 2 + NX / 6;
    int starty = NY / 2 - NY / 6;
    int endy = NY / 2 + NY / 6;
    //    int starty=NY/4;
    //    int endy=NY-NY/4;
    for (i = startx; i < endx; i++)
        for (j = starty; j < endy; j++)
            if (abs(i - (NX/2)) >= NX/12 && abs(j - (NX/2)) >= NX/12)
                    h_T[NX * j + i] = 1.0;
}


/********************************/
/* TEMPERATURE INITIALIZATION : */
/* bordo sinistro               */
/********************************/
void Init_left(float * __restrict h_T, const int NX, const int NY)
{
    int j;
    int endy=NY-1;
    for(j=0; j<endy; j++)
        h_T[NX*j + 1] = 1.0;
}


/********************************/
/* TEMPERATURE INITIALIZATION : */
/* bordo alto                   */
/********************************/
void Init_top(float * __restrict h_T, const int NX, const int NY)
{
    int i;
    int endx=NX-1;
    for(i=0; i<endx; i++)
        h_T[NX + i] = 1.0;
}


/********************************/
/* Periodic boundary conditions */
/* COPY BORDER: COLS            */
/********************************/
void copy_cols (float * __restrict h_T, const int NX, const int NY)
{
    int i;
    // copy cols
    for (i = 1; i < NY-1; ++i) {
        h_T[NX*i+0]    = h_T[NX*i+NX-2];    //Collega la prima colonna con la penultima [le rende uguali]
        h_T[NX*i+NX-1] = h_T[NX*i+1];       //Collega l'ultima colonna con la seconda [le rende uguali]
    }
}
//BA----BA



/********************************/
/* Periodic boundary conditions */
/* COPY BOREDER: ROWS           */
/********************************/
void copy_rows (float * __restrict h_T, const int NX, const int NY)
{
    //Utilizza memcpy perché le righe possono essere trattate come array direttamente [le celle sono continue]
    memcpy(&(h_T[NX*0])      ,&(h_T[NX*(NY-2)]), NX*sizeof(float));
    memcpy(&(h_T[NX*(NY-1)]) ,&(h_T[NX*1]),      NX*sizeof(float));
}




/******************************************/
/* print color map                        */
/******************************************/

void print_colormap(float * __restrict h_T)
{
   int i,j;

   for (j=1; j<NY-1; j++){
        for (i=1; i<NX-1; i++) {
            printf("%2.2f ",h_T[NX*j + i]);
        }
        printf("\n");
        }
}


/******************************************/
/* options management                     */
/******************************************/
void options(int argc, char * argv[]) {

  int i;
   while ( (i = getopt(argc, argv, "c:r:s:h")) != -1) {
        switch (i) {
        case 'c':  NX       = strtol(optarg, NULL, 10);  break;
        case 'r':  NY       = strtol(optarg, NULL, 10);  break;
        case 's':  MAX_ITER = strtol(optarg, NULL, 10);  break;
        case 'h':  usage(argv); exit(1);
        case '?':  usage(argv); exit(1);
        default:   usage(argv); exit(1);
        }
    }
}

/******************************************/
/* print help                             */
/******************************************/
void usage(char * argv[])  {

  printf ("\n%s [-c ncols] [-r nrows] [-s nsteps] [-h]",argv[0]);
  printf ("\n");

}

