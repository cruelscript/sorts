#include <ostream>
#include <ctime>
#include "List.h"

const int MAX_NUMBER_VAL = 32768;

void print(std::ostream& out, int* array, const size_t size)
{
  out << "\n";
  for(size_t i = 0; i< size; i++)
  {
    out << array[i] << " ";
  }
}

void randomize(int* array, const size_t size)
{
  srand(time(NULL));

  for (size_t i = 0; i < size; i++)
  {
    array[i] = rand() % MAX_NUMBER_VAL;
  }
}

void worsen(int* array, const size_t size)
{
  if (size < MAX_NUMBER_VAL)
    for (size_t i = 0; i < size; i++)
      array[i] = size - i;
  else
  {
    const int gap = size / MAX_NUMBER_VAL + 1;

    for (int i = 0; i < size; i += gap)
    {
      for (int j = i; j < i + gap; j++)
      {
        array[j] = (size - j) / gap;
      }
    }
  }
}

void better(int* array, const size_t size)
{
  if (size < MAX_NUMBER_VAL)
    for (size_t i = 0; i < size; i++)
      array[i] = i;
  else
  {
    const int gap = size / MAX_NUMBER_VAL + 1;

    for (size_t i = 0; i < size; i += gap)
    {
      for (size_t j = i; j < i + gap; j++)
      {
        array[j] = j / gap;
      }
    }
  }
}

bool isSorted(int* array, const size_t size)
{

  for(size_t i = 0; i < size-1; i++)
  {
    if (array[i] > array[i+1])
      return false;
  }
  return true;
}

void countingSort(int* array, const size_t size)
{
  std::cout << "\n" << __FUNCTION__ << " has been called\n";

  int* count = new int[MAX_NUMBER_VAL];

  for(size_t i = 0; i < MAX_NUMBER_VAL; i++)
  {
    count[i] = 0;
  }

  for(size_t i = 0; i < size; i++)
  {
    count[array[i]]++;
  }
  for(size_t j = 1; j < MAX_NUMBER_VAL; j++)
  {
    count[j] += count[j - 1];
  }

  int* result = new int[size];

  for(size_t i = size; i > 0; i--)
  {
    count[array[i-1]]--;
    result[count[array[i-1]]] = array[i-1];
  }
  for(size_t i = 0; i < size; i++)
  {
    array[i] = result[i];
  }
  delete[] result;
  delete[] count;
}

int binarySearch(int* array, int item, int low, int high)
{
  if (high <= low)
    return (item > array[low]) ? (low + 1) : low;

  int mid = (low + high) / 2;

  if (item == array[mid])
    return mid + 1;

  if (item > array[mid])
    return binarySearch(array, item, mid + 1, high);

  return binarySearch(array, item, low, mid - 1);
}

void binaryInsertionSort(int* array, const size_t size)
{
  int j, loc, selected;

  for (size_t i = 1; i < size; i++)
  {
    j = i - 1;
    selected = array[i];

    loc = binarySearch(array, selected, 0, j);

    while (j >= loc)
    {
      array[j + 1] = array[j];
      j--;
    }
    array[j + 1] = selected;
  }
}

void bucketSort(int* array, const size_t size)
{
  std::cout << "\n" << __FUNCTION__ << " has been called\n";

  if (size <= 100)
  {
    binaryInsertionSort(array, size);
    return;
  }

  const int nBuckets = (MAX_NUMBER_VAL <= 15000) ? (MAX_NUMBER_VAL / 10) : 1500;

  List* buckets = new List[nBuckets];

  int index = 0;
  for (size_t i = 0; i < size; i++)
  {
    index = (nBuckets * array[i]) / MAX_NUMBER_VAL;
    buckets[index] += array[i];
  }

  index = 0;
  for(size_t i = 0; i < nBuckets; i++)
  {
    while(buckets[i].head())
    {
      array[index++] = buckets[i].head()->data_;
      buckets[i].setHead(buckets[i].head()->next_);
    }
  }
  delete[] buckets;
}

const int MAX_DIGIT = 10;

void countSort(int* array, int exp, const size_t size)
{
  int* result = new int[size];
  int count[MAX_DIGIT] = { 0 };

  for (size_t i = 0; i < size; i++)
  {
    count[(array[i] / exp) % MAX_DIGIT]++;
  }
  for (size_t i = 1; i < MAX_DIGIT; i++)
  {
    count[i] += count[i - 1];
  }
  for (size_t i = size; i > 0; i--)
  {
    result[count[(array[i - 1] / exp) % MAX_DIGIT] - 1] = array[i - 1];
    count[(array[i - 1] / exp) % MAX_DIGIT]--;
  }
  for (size_t i = 0; i < size; i++)
  {
    array[i] = result[i];
  }
  delete[] result;
}

void radixSort(int* array, const size_t size)
{
  std::cout << "\n" << __FUNCTION__ << " has been called\n";

  for(size_t exp = 1; (MAX_NUMBER_VAL-1)/exp > 0; exp*=10 )
  {
    countSort(array, exp, size);
  }
}

void shellSort(int* array, const size_t size)
{
  std::cout << "\n" << __FUNCTION__ << " has been called\n";

  for (int gap = size / 2; gap > 0; gap /= 2)
  {
    for(int i = gap; i < size; i++)
    {
      int temp = array[i];
      int j;
      for(j = i; j >= gap && array[j - gap] > temp; j -= gap)
      {
        array[j] = array[j - gap];
      }
      array[j] = temp;
    }
  }
}

void shellSortHibbard(int* array, const size_t size)
{
  std::cout << "\n" << __FUNCTION__ << " has been called\n";

  int gap = 1;
  while ((gap << 1 | 1) < size)
    gap = (gap << 1) | 1;

  for (; gap > 0; gap >>= 1)
  {
    for(int i = gap; i < size; i++)
    {
      int temp = array[i];
      int j;
      for(j = i; j >= gap && array[j - gap] > temp; j -= gap)
      {
        array[j] = array[j - gap];
      }
      array[j] = temp;
    }
  }
}

void shellSortSedgewick(int* array, const size_t size)
{
  std::cout << "\n" << __FUNCTION__ << " has been called\n";

  int gaps[100];
  gaps[0] = 1;
  int i = 1;

  for (; gaps[i - 1] * 3 < size; i++)
  {
    gaps[i] = (i % 2 == 0)
      ? (9 * (1 << i) - 9 * (1 << (i / 2)) + 1)
      : (8 * (1 << i) - 6 * (1 << ((i + 1) / 2)) + 1);
  }
  i--;
  for (; i >= 0; i--)
  {
    int gap = gaps[i];
    for (int i = gap; i < size; i++)
    {
      int temp = array[i];
      int j;
      for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
      {
        array[j] = array[j - gap];
      }
      array[j] = temp;
    }
  }
}
