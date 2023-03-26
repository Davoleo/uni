
/* gcc module_factorize.c -o module_factorize -lcrypto */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>

void status() {}

int main(int argc, char *argv[])
{
    BIGNUM *p, *q, *m, *rem, *x, *incr;
    BN_CTX *ctx;

    long int num_bits = 0;
    if(argc >= 2 && argv[1]) 
        num_bits = atol(argv[1]);
    else
        num_bits = 1024;

    p = BN_new();     // numero primo
    q = BN_new();     // numero primo
    m = BN_new();     // modulo = p x q
    x = BN_new();     // 
    rem = BN_new();   // resto divisione
    incr = BN_new();  // incremento 
    ctx = BN_CTX_new(); //

    BN_generate_prime(p,num_bits,1,NULL,NULL,status,NULL);
    BN_generate_prime(q,num_bits,1,NULL,NULL,status,NULL);
    printf("\n p : ");
    BN_print_fp(stdout, p);
    printf("\n q : ");
    BN_print_fp(stdout, q);

    BN_mul(m, p, q, ctx); 
    printf("\n m : ");
    BN_print_fp(stdout, m);
    printf("\n");

    BN_one(x);
    BN_one(rem);
    BN_dec2bn(&incr, "2");   // increment = 2

    while (!BN_is_zero(rem))
    {
        BN_add(x, x, incr);
        if (BN_is_prime(x, 5, NULL, NULL, NULL))
            BN_mod(rem,m,x, ctx);
    }

    printf("\n FOUND : ");
    BN_print_fp(stdout,x);
    printf("\n ");

    BN_free(p);
    BN_free(q);
    BN_free(m);
    BN_free(rem);
    BN_free(incr);
}


