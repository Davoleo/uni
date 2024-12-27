
/* gcc factorize2.c -o factorize2   -lcrypto -lm */

/*
openssl genrsa -out rsa_key.pem 68
openssl rsa -in rsa_key.pem -modulus -noout

time ./factorize2 -m B81915BC0A2222F4B  -a 4    # modulus 68 bit - prime 34 bit (4 addr + 30 block)
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>
#include <math.h>
#include <getopt.h>

void status() {}
void options(int argc, char *argv[]);
void usage(char *argv[]);
int block_factorize(unsigned long int);

BIGNUM *P, *Q, *M, *F, *ZERO, *ONE, *TWO, *BLOCK_DIM_SIZE, *BLOCK_DIM_BIT;
BN_CTX *ctx;
int block_idx = 0, found = 0, skip = 0; thr = 0;
unsigned long int modulus_bit, prime_bit, block_addr_bit, block_addr_size, block_dim_bit, block_dim_size;
char m[256] = "";

int main(int argc, char *argv[])
{

  double t1, t2; // timer

  P = BN_new(); // prime number
  Q = BN_new(); // prime number
  M = BN_new(); // modulw = p x q
  F = BN_new(); // found number

  ZERO = BN_new();           //  0
  ONE = BN_new();            //  1
  TWO = BN_new();            //  2
  BLOCK_DIM_BIT = BN_new();  // quanti bit per blocco
  BLOCK_DIM_SIZE = BN_new(); // dimensione blocco
  ctx = BN_CTX_new();

  BN_set_word(ZERO, 0);
  BN_set_word(ONE, 1);
  BN_set_word(TWO, 2);

  modulus_bit = 64; // init modulus bits
  block_addr_bit = 4;

  options(argc, argv);

  block_addr_size = pow(2, block_addr_bit);

  //Number of omp threads
  if (thr != 0)
    omp_set_num_threads(thr);
  else
    omp_set_num_threads(2);

  if (strcmp(m, ""))
  {
    BN_hex2bn(&M, m);
    modulus_bit = strlen(m) * 4;
    prime_bit = modulus_bit / 2;
    block_dim_bit = prime_bit - block_addr_bit;
    block_dim_size = pow(2, block_dim_bit);
  }
  else
  {
    prime_bit = modulus_bit / 2;
    block_dim_bit = prime_bit - block_addr_bit;
    block_dim_size = pow(2, block_dim_bit);
    BN_generate_prime(P, prime_bit, 1, NULL, NULL, status, NULL);
    BN_generate_prime(Q, prime_bit, 1, NULL, NULL, status, NULL);
    BN_mul(M, P, Q, ctx);
    strcpy(m, BN_bn2hex(M));
  }
  BN_set_word(BLOCK_DIM_BIT, block_dim_bit); // bits per block
  BN_print_fp(stdout, BLOCK_DIM_BIT);
  BN_exp(BLOCK_DIM_SIZE, TWO, BLOCK_DIM_BIT, ctx);

  printf("\n# Modulus: ");
  BN_print_fp(stdout, M);
  printf(" %d bits - prime: address %d bit, block %d bit \n\n", modulus_bit, block_addr_bit, block_dim_bit);

  //TODO 
  #pragma omp parallel private(block_idx) shared(found) num_threads(thr)
  {
    //TODO
    #pragma omp parallel
    for (block_idx = block_addr_size - 1; block_idx > -1; block_idx--) {
      t1 += omp_get_wtime();
      block_factorize(block_idx);
      t2 += omp_get_wtime();
    }
  }

  printf("FOUND: ");
  BN_print_fp(stdout, F);
  printf("\n");

  //TODO
  #pragma omp parallel 
  {
    //TODO
    #pragma omp single
    printf("Totale: %.3f --- Numero thread: %d\n", t2-t1, thr);
    //TODO
    #pragma omp critical
    {
      printf("# Thread: %d / %d\n", omp_get_thread_num(), thr);
    }
  }

  return (0);
}

int block_factorize(unsigned long int block_addr)
{

  BIGNUM *R, *X, *Y, *BLOCK_IDX, *BLOCK_ADDR;
  BN_CTX *ctx2;
  ctx2 = BN_CTX_new();
  R = BN_new();          // resto della divisione
  X = BN_new();          // indice del  blocco
  Y = BN_new();          // ultimo numero del  blocco
  BLOCK_IDX = BN_new();  // ultimo numero del  blocco
  BLOCK_ADDR = BN_new(); // Block Address

  BN_set_word(R, 0);
  BN_set_word(X, 1);
  BN_set_word(Y, 1);
  BN_set_word(BLOCK_ADDR, block_addr);
  BN_mul(X, BLOCK_ADDR, BLOCK_DIM_SIZE, ctx2); // x = i  block_size
  BN_add(X, X, ONE);                           // x = x+1
  BN_add(Y, X, BLOCK_DIM_SIZE);                // y = x + block_size
  BN_sub(Y, Y, TWO);                           // y = y - 2
  BLOCK_IDX = BN_dup(X);

  //TODO CHECK
  #pragma omp parallel 
  {
    while (!skip && BN_cmp(BLOCK_IDX, Y))
    {
      BN_add(BLOCK_IDX, BLOCK_IDX, TWO);
      BN_mod(R, M, BLOCK_IDX, ctx2);
      if (BN_is_zero(R))
      {
        F = BN_dup(BLOCK_IDX);
        found = 1;
        skip = 1;
      }
    }
  }

  printf(" Blk:");
  BN_print_fp(stdout, BLOCK_ADDR);
  printf(" ");
  BN_print_fp(stdout, X);
  printf("-");
  BN_print_fp(stdout, Y);
  if (found)
  {
    printf(" FOUND \n");
    found = 0;
  }
  else if (skip)
    printf(" skip \n");
  else
    printf(" not found \n");

  return (0);
}

/************************************************/

void options(int argc, char *argv[])
{
  int i;
  while ((i = getopt(argc, argv, "a:b:m:h")) != -1)
  {
    switch (i)
    {
    case 'a':
      block_addr_bit = strtol(optarg, NULL, 10);
      break;
    case 'b':
      modulus_bit = strtol(optarg, NULL, 10);
      break;
    case 'm':
      strcpy(m, optarg);
      break;
    case 'h':
      usage(argv);
      exit(1);
    case '?':
      usage(argv);
      exit(1);
    default:
      usage(argv);
      exit(1);
    }
  }
}

/***************************************/

void usage(char *argv[])
{
  printf("\n%s [-b modulus_bit] [-m modulus] [-a block_addr_bit] [-h]", argv[0]);
  printf("\n");
}
