#ifndef __SORTING_HPP
#define __SORTING_HPP
#include <string.h>
#include "Helper.hpp"

/**
  Template implementation of SelectionSort
  Note:  the input type must define the < operator in order
   for the code to compile
  
  @param data input array
  @param n the length of the input array
 */
template <class T> T* selectionsort(T* data, int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    int minloc = i;
    for (int j = i+1; j < n; j++)
      if (data[j] < data[minloc])
        minloc = j;
    Swap(data[i], data[minloc]);
  }
  return data;
}

/**
  Template implementation of InsertionSort (iterative)

  @param data input array
  @param n the length of the input array
 */
template <class T> T* insertionsort(T* data, int n)
{
  for (int i = 1; i < n; i++)
  {
    int ins = data[i];
    int shift = i;
    while (shift > 0 && ins < data[shift-1])
    {
      data[shift] = data[shift-1];
      shift = shift - 1;
    }
    data[shift] = ins;
  }
  return data;
}

/**
  Template implementation of MergeSort (recursive)
  The third argument must be an allocated array with at least n elements

  @param data input array
  @param n the length of the input and temp arrays
  @param temp a temporary array used to merge the sub-arrays together
 */
template <class T> T* mergesort(T* data, int n, T* temp)
{
  if (n > 1)
  {
    int mid = (n+1) / 2;
    T* left = mergesort(data, mid, temp);
    T* right = mergesort(data+mid, n-mid, temp);
    int l = 0;
    int r = 0;
    int s = 0;
    while (l < mid && r < n-mid)
    {
      if (left[l] < right[r])
        temp[s++] = left[l++];
      else
        temp[s++] = right[r++];
    }
    while (l < mid)
      temp[s++] = left[l++];
    while (r < n-mid)
      temp[s++] = right[r++];
    memcpy(data, temp, s*sizeof(T));
  }

  return data;
}

/**
  Template implementation of QuickSort

  @param data input array
  @param n the length of the input array
 */
template <class T> T* quicksort(T* data, int n)
{
  if (n <= 1)
    return data;

  Swap(data[0], data[rand() % n]);

  int left = 1;
  while (left < n && data[left] < data[0])
    left++;
  for (int i = left + 1; i < n; i++)
    if (data[i] < data[0])
    {
      Swap(data[i], data[left]);
      left++;
    }
  left--;

  Swap(data[0], data[left]);
  quicksort(data, left);
  quicksort(data+left+1, n-left-1);
  return data;
}

#endif