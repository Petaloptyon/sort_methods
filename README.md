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

## Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/petaloptyon/sorting-algorithms-comparison.git
   cd sorting-algorithms-comparison
