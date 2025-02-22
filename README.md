# sort_methods
This repository contains a C program that implements and compares two sorting algorithms: Selection Sort (prime_sort) and Quick Sort (quick_sort)



# Sorting Algorithms Comparison

This project implements and compares two popular sorting algorithms: **Selection Sort** and **Quick Sort**. The program generates random arrays, sorts them using both algorithms, and provides detailed performance metrics, including the number of comparisons and swaps. It also includes functions to validate the correctness of the sorting results and handles edge cases.

---

## Features

- **Random Array Generation**: Generates arrays of specified length filled with random integers.
- **Array Copying**: Creates a copy of an array for independent sorting.
- **Selection Sort (`prime_sort`)**: Sorts an array using the Selection Sort algorithm.
- **Quick Sort (`quick_sort`)**: Sorts an array using the Quick Sort algorithm.
- **Performance Metrics**: Tracks the number of comparisons and swaps performed during sorting.
- **Validation Functions**:
  - `is_in_order`: Checks if an array is sorted in non-decreasing order.
  - `is_all_included`: Verifies that the sorted array contains the same elements as the original array.
  - `is_correct_sort`: Combines the above checks to validate the sorting result.
- **Edge Case Handling**: Tests the algorithms on already sorted arrays and arrays sorted in reverse order.
- **Array Reversal**: Reverses the order of elements in an array.

---

## How It Works

1. **Array Generation**:
   - The program generates random arrays of a specified size using the `generate_array` function.
   - It also creates copies of the array for independent sorting using `copy_arr`.

2. **Sorting**:
   - The `prime_sort` function implements Selection Sort.
   - The `quick_sort` function implements Quick Sort.

3. **Performance Tracking**:
   - The number of comparisons (`NUMB_COMPARES`) and swaps (`NUMB_SWAPS`) are tracked during sorting.

4. **Validation**:
   - The `is_correct_sort` function ensures that the sorted array is both in order and contains the same elements as the original array.

5. **Edge Cases**:
   - The program tests the sorting algorithms on already sorted arrays and arrays sorted in reverse order using the `edge_case` function.

6. **Output**:
   - The program prints the results of sorting, including whether the array is correctly sorted, the number of comparisons, and the number of swaps.

---

## Functions Overview

 - generate_array(int n): Generates an array of size n filled with random integers.

 - copy_arr(int *src, int n): Creates a copy of the array src.

 - swap(int *arr, int i_1, int i_2): Swaps elements at indices i_1 and i_2 in the array arr.

 - is_less(int a, int b): Compares two integers and returns 1 if a < b, otherwise 0.

 - prime_sort(int *arr, int n): Sorts the array arr using Selection Sort.

 - quick_sort(int *arr, int l, int r): Sorts the array arr using Quick Sort.

 - is_in_order(int *sorted, int n): Checks if the array sorted is in non-decreasing order.

 - is_all_included(int *init, int *sorted, int n): Checks if the sorted array contains the same elements as the original array.

 - is_correct_sort(int *init, int *sorted, int n): Combines is_in_order and is_all_included to validate sorting.

 - print_array(int *a, int n): Prints the elements of the array a.

 - sort_generated_array(int n, int idx): Generates an array, sorts it using both algorithms, and prints the results.

 - unwrap_array(int *arr, int n): Reverses the order of elements in the array arr.

 - edge_case(int n): Tests the sorting algorithms on edge cases (already sorted and reverse-sorted arrays).

---
---
## Example of output

Enter the size of the array: 10

SORT ########################## 0
Quick sort:
is sorted: 1
    compares: 45
    swaps: 7

Prime sort:
is sorted: 1
    compares: 45
    swaps: 5
#################################

#######   EDGE CASE   #######
is arrays sorted: quick sort: 1; prime sort: 1
Quick sort for sorted array:
is sorted: 1
    compares: 45
    swaps: 0
Quick sort for sorted unwraped array:
is sorted: 1
    compares: 45
    swaps: 5

Prime sort for sorted array:
is sorted: 1
    compares: 45
    swaps: 0
Prime sort for sorted unwraped array:
is sorted: 1
    compares: 45
    swaps: 5
---
---
## Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/petaloptyon/sorting-algorithms-comparison.git
   cd sorting-algorithms-comparison
