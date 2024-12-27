
/* gcc factorize1.c -o factorize1 -lcrypto -lm */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>
#include <math.h>

void status() {}
int block_factorize(unsigned long int);

BIGNUM *P, *Q, *M, *F, *ZERO, *ONE, *TWO, *BLOCK_SIZE, *BLOCK_SIZE_BIT;
BN_CTX *ctx;
int block_addr, found = 0;
unsigned long int block_size_bit, block_size, block_num_bit, block_num;

int main(int argc, char *argv[])
{

  double t1, t2; // timer
  unsigned long int nbits;
  if (argc >= 2 && argv[1])
    nbits = atol(argv[1]);
  else
    nbits = 24;
  if (argc >= 3 && argv[2])
    block_size_bit = atol(argv[2]);
  else
    block_size_bit = 20;

  P = BN_new(); // prime number
  Q = BN_new(); // prime number
  M = BN_new(); // modulw = p x q
  F = BN_new(); // found number

  ZERO = BN_new();           //  0
  ONE = BN_new();            //  1
  TWO = BN_new();            //  2
  BLOCK_SIZE_BIT = BN_new(); // quanti bit per blocco
  BLOCK_SIZE = BN_new();     // dimensione blocco
  ctx = BN_CTX_new();

  block_num_bit = nbits - block_size_bit; //Default: 4
  block_num = pow(2, block_num_bit);      //Default: 2^4

  BN_set_word(ZERO, 0);
  BN_set_word(ONE, 1);
  BN_set_word(TWO, 2);
  BN_set_word(BLOCK_SIZE_BIT, block_size_bit); // bits per block
  BN_exp(BLOCK_SIZE, TWO, BLOCK_SIZE_BIT, ctx); //Default: 2^20

  printf(" # BLOCK_SIZE_BIT: ");
  BN_print_fp(stdout, BLOCK_SIZE_BIT);
  printf("  ");
  printf(" BLOCK_SIZE:");
  BN_print_fp(stdout, BLOCK_SIZE);
  printf("\n");

  BN_generate_prime(P, nbits, 1, NULL, NULL, status, NULL);
  BN_generate_prime(Q, nbits, 1, NULL, NULL, status, NULL);
  BN_mul(M, P, Q, ctx);

  printf("\n #P : ");
  BN_print_fp(stdout, P);
  printf("\n #Q : ");
  BN_print_fp(stdout, Q);
  printf("\n #M : ");
  BN_print_fp(stdout, M);
  printf("\n");

  for (block_addr = block_num - 1; block_addr > -1; block_addr--)
    block_factorize(block_addr);

  printf("FOUND: ");
  BN_print_fp(stdout, F);
  printf("\n");
  return (0);
}

int block_factorize(unsigned long int block_addr)
{

  BIGNUM *R, *X, *Y, *BLOCK_IDX, *BLOCK_ADDR;
  BN_CTX *ctx2;
  R = BN_new();          // resto della divisione
  X = BN_new();          // primo numero del blocco
  Y = BN_new();          // ultimo numero del  blocco
  BLOCK_IDX = BN_new();  // indicw chw scorre il blocco
  BLOCK_ADDR = BN_new(); // indizizzo blocco
  ctx2 = BN_CTX_new();

  BN_set_word(R, 0);
  BN_set_word(X, 1);
  BN_set_word(Y, 1);
  BN_set_word(BLOCK_ADDR, block_addr);
  
  BN_mul(X, BLOCK_ADDR, BLOCK_SIZE, ctx2); // x = i  block_size
  BN_add(X, X, ONE);                       // x = x+1
  BN_add(Y, X, BLOCK_SIZE);                // y = x + block_size
  BN_sub(Y, Y, TWO);                       // y = y - 2
  BLOCK_IDX = BN_dup(X);

  while (!found && BN_cmp(BLOCK_IDX, Y))
  {
    BN_add(BLOCK_IDX, BLOCK_IDX, TWO);
    BN_mod(R, M, BLOCK_IDX, ctx2);
    if (BN_is_zero(R))
    {
      F = BN_dup(BLOCK_IDX);
      found = 1;
    }
  }

  printf("# BLOCK_ADDR:");
  BN_print_fp(stdout, BLOCK_ADDR);
  printf(" BLOCK:");
  BN_print_fp(stdout, X);
  printf("-");
  BN_print_fp(stdout, Y);
  if (found)
    printf(" found \n");
  else
    printf(" not found \n");

  return (0);
}
