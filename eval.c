#include <stdio.h>
#include <math.h>    /* for pow(x, y) */
#include "type.h"
#include <stdlib.h>
#define n_dim 30
#define bits_per_dim 8
#define bit_weight 256

double decode(IPTR pj, int index, int size);
double binToDec(int *chrom, int l);

double eval(POPULATION *p, IPTR pj) 
     /* Called from gen.c and init.c */
{

  double val;
  //double square = 0.0;

  val = decode(pj, 0, p->lchrom); 
  //square = val * val;

  return val;
}

double decode(IPTR pj, int index, int size)
{

  return ((double) binToDec(&(pj->chrom[0]), size));
}

double rand_gen() {
   // return a uniformly distributed random value
   return ( (double)(rand()) + 1. )/( (double)(RAND_MAX) + 1. );
}
double normalRandom() {
   // return a normally distributed random value
   double v1=rand_gen();
   double v2=rand_gen();
   return cos(2*3.14*v2)*sqrt(-2.*log(v1));
}
double binToDec(int *chrom, int l)
{
  double x[n_dim];
  int i;
  int j = 0;
  int k = 0;
  double prod;
  double sum = 0;

  prod = 0.0;

  for(i = 0; i < l; i++)
  {
    j = i % bits_per_dim;
    if (j == 0)
    {
      k=floor(i/(bits_per_dim));
      sum += k*(pow(prod,4)-bit_weight/2) + normalRandom();
      prod = 0;
    }
    prod += (chrom[i] == 0 ? 0.0 : pow((double)2.0, (double) j))/bit_weight;
  }
//  printf("sum-sqs: %2.2f ", sum);
  sum = 1408 - sum;
  return sum;
}

void decToBin(int ad, int *barray, int size)
{
  int i, t;

  t = ad;
  for(i = 0; i < size; i++){
    barray[i] = t%2;
    t = t/2;

  }
}
