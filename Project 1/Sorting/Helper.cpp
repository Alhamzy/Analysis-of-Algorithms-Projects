#include "Helper.hpp"
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <stdint.h>
using namespace std;

/*
  xor shift random number generator
  Period of 2^64
  Source:  https://en.wikipedia.org/wiki/Xorshift
 */
uint64_t rng_state = 1;
void Srand(void) { rng_state = clock(); }
uint64_t Rand()
{
	uint64_t x = rng_state;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return rng_state = x;
}

/**
  Fills an allocated int array with sorted values

  @param data the array to fill
  @param n the size of the array
 */
void sortedArray(int* data, int n)
{
  for (int i = 0; i < n; i++)
    data[i] = i+1;
}

/**
  Fills an allocated int array with n zeros

  @param data the array to fill
  @param n the size of the array
 */
void constArray(int* data, int n)
{
  memset(data, 0, n*sizeof(int));
}

/**
  Fills an allocated int array with a random permutation of the integers 1 to n

  @param n the size of the array
  @return the array
 */
void randomArray(int* data, int n)
{
  sortedArray(data, n);
  for (int i = n; i > 1; i--)
    Swap(data[rand() % i], data[i-1]);
}
