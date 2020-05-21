#include <iostream>
#include <ctime>
#include <fstream>

void countingSort(int* array, const size_t size);
void radixSort(int* array, const size_t size);
void bucketSort(int* array, const size_t size);
void binaryInsertionSort(int* array, const size_t size);
void shellSort(int* array, const size_t size);
void shellSortHibbard(int* array, const size_t size);
void shellSortSedgewick(int* array, const size_t size);

void print(std::ostream& out, int* array, const size_t size);
void randomize(int* array, const size_t size);
void worsen(int* array, const size_t size);
void better(int* array, const size_t size);
bool isSorted(int* array, const size_t size);

const int ARRAY_SIZE = 800000;

int main()
{

  void ((*functionArray[6]))(int*, const size_t);

  functionArray[0] = countingSort;
  functionArray[1] = radixSort;
  functionArray[2] = bucketSort;
  functionArray[3] = shellSort;
  functionArray[4] = shellSortHibbard;
  functionArray[5] = shellSortSedgewick;

  clock_t time_start;
  clock_t time_end;

  std::ofstream out("base.txt");

  for (int i = 0; i < 1; i++)
  {
    for (auto fArray : functionArray)
    {
      int* averageArray = new int[ARRAY_SIZE];
      int* bestArray    = new int[ARRAY_SIZE];
      int* worstArray   = new int[ARRAY_SIZE];

      randomize(averageArray, ARRAY_SIZE);
      worsen(worstArray, ARRAY_SIZE);
      better(bestArray, ARRAY_SIZE);

      std::cout << "\n\n__________________________________________\n\n";

      std::cout << "Average data set: ";
      print(std::cout, averageArray, ARRAY_SIZE);
      std::cout << (isSorted(averageArray, ARRAY_SIZE) ?  " is sorted\n" : " is not sorted\n");

      time_start = clock();
      fArray(averageArray, ARRAY_SIZE);
      time_end = clock();

      print(std::cout, averageArray, ARRAY_SIZE);

      std::cout << "\n| Elapsed time: " << static_cast<double>(time_end - time_start) << " |\n\n";
      out << static_cast<double>(time_end - time_start) << "\n";


      std::cout << "Best data set: ";
      print(std::cout, bestArray, ARRAY_SIZE);
      std::cout << (isSorted(bestArray, ARRAY_SIZE) ? " is sorted\n" : " is not sorted\n");

      time_start = clock();
      fArray(bestArray, ARRAY_SIZE);
      time_end = clock();

      print(std::cout, bestArray, ARRAY_SIZE);

      std::cout << "\n|Elapsed time: " << static_cast<double>(time_end - time_start) << " |\n\n";
      out << static_cast<double>(time_end - time_start) << "\n";

      std::cout << "Worst data set: ";
      print(std::cout, worstArray, ARRAY_SIZE);
      std::cout << (isSorted(worstArray, ARRAY_SIZE) ? " is sorted\n" : " is not sorted\n");

      time_start = clock();
      fArray(worstArray, ARRAY_SIZE);
      time_end = clock();

      print(std::cout, worstArray, ARRAY_SIZE);

      std::cout << "\n|Elapsed time: " << static_cast<double>(time_end - time_start) << " |\n\n";
      out << static_cast<double>(time_end - time_start) << "\n";


      std::cout << "\n\n_____________END_OF_TEST_SORT_____________\n\n";

      delete[] bestArray;
      delete[] averageArray;
      delete[] worstArray;
    }
    out << "\n\n_______\n";
  }
  return 0;
}
