#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int NUMB_SWAPS = 0;
int NUMB_COMPARES = 0;

static int* generate_array(int n) { // function to create an array filled with random numbers
    int* arr = calloc(n, sizeof(int)); // allocate memory for the array
    for (int i = 0; i < n; i++) { // iterate through the array
        arr[i] = rand(); // fill it with random numbers
    }
    return arr;
}

static int* copy_arr(int *src, int n) { // function to create a copy of an array
    int* arr = calloc(n, sizeof(int)); // allocate memory for the copy array
    for (int i = 0; i < n; i++) { // iterate through the array
        arr[i] = src[i]; // copy values into it
    }
    return arr; // return a pointer to the copied array
}

static void swap(int * arr, int i_1, int i_2) { // function to count the number of element swaps
    int temp = 0; // create a temporary variable

    temp = arr[i_1]; // use it to swap elements in the array
    arr[i_1] = arr[i_2];
    arr[i_2] = temp;
    NUMB_SWAPS++; // increment the swap counter
}

static int is_less(int a, int b) { // function to count the number of comparisons between array elements
    NUMB_COMPARES++; // increment the counter
    if (a < b) { // compare variables and return the result
        return 1;
    }
    return 0;
}

static void prime_sort(int *arr, int n) { // function for selection sort
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) { // iterate through each element of the array, except the last one (as it will already be in place by the end of sorting)
        min_idx = i; // consider the current element as the minimum
        for (j = i + 1; j < n; j++) { // find the index of the minimum element in the remaining part of the array
            if (is_less(arr[j], arr[min_idx])) { // if a smaller element than the current minimum is found
                min_idx = j; // update the index of the minimum element
            }
        }
        if (arr[i] != arr[min_idx]) {
            swap(arr, i, min_idx); // if a new minimum is found, swap it with the current element
        }
    }
}

static void quick_sort(int *arr, int l, int r) { // function for quicksort of array arr with indices from l to r
    if (l >= r) return; // base case of recursion: if the subarray has 0 or 1 element, it is already sorted
    int var = arr[(l + r) / 2]; // choose the pivot element: take the middle element of the subarray
    int i = l, j = r; // Initialize pointers for sorting: i - from the start, j - from the end of the subarray

    // divide the array into two parts:
    // left part – elements less than or equal to the pivot,
    // right part – elements greater than or equal to the pivot.
    // the loop runs until i "crosses" j
    while (i <= j) {
        while (is_less(arr[i], var)) { // find an element on the left that is not less than var (i.e., a[i] >= var)
            i++;
        }
        while (is_less(var, arr[j])) { // find an element on the right that is not greater than var (i.e., a[j] > var)
            j--;
        }
        if (i <= j) { // if the pointers have not crossed, swap the found elements
            if (arr[i] != arr[j]) {
                swap(arr, i, j); // swap a[i] and a[j]
            }
            i++;
            j--;
        }
    }

    // we get that all elements from l to j <= var, and from i to r >= var.
    // now recursively sort the left and right parts.
    quick_sort(arr, l, j);
    quick_sort(arr, i, r);
}

static int is_in_order(int *sorted, int n) { // function to check if the elements are in the correct order
    for (int i = 1; i < n; i++) { // iterate through the sorted array
        if (sorted[i] < sorted[i - 1]) {
            return 0; // Not sorted
        }
    }
    return 1; // Sorted
}

static int is_all_included(int *init, int *sorted, int n) { // check if the set of elements in the initial and sorted arrays matches
    int *temp = calloc(n, sizeof(int));  // Allocate memory for a temporary array

    // For each element from the initial array, search for it in the sorted array
    for (int i = 0; i < n; i++) {
        int found = 0;  // Flag indicating whether the element is found
        for (int j = 0; j < n; j++) {
            if (init[i] == sorted[j] && temp[j] == 0) {
                temp[j] = 1;  // Mark that the element is found
                found = 1;    // Element is found
                break;        // Break the inner loop as the element is already found
            }
        }
        if (!found) {
            // If the element is not found, the arrays do not match
            free(temp);
            return 0;
        }
    }

    // If at least one element is not found in the sorted array, return 0
    for (int i = 0; i < n; i++) {
        if (temp[i] == 0) {
            free(temp);  // Free memory
            return 0;
        }
    }

    free(temp);  // Free memory
    return 1;
}

static int is_correct_sort(int *init, int *sorted, int n) { // overall check for sortedness
    return is_in_order(sorted, n) && is_all_included(init, sorted, n);
}

static void print_array(int *a, int n) { // function to print an array (if needed)
    for (int i = 0; i < n; i++) { // iterate through the array
        printf("%d ", a[i]); // print the elements of the array
    }
    printf("\n");
}

static void sort_generated_array(int n, int idx) { // function to simplify processing a large number of arrays
    int *a = generate_array(n); // create an array of the required length
    int *a_quick = copy_arr(a, n), *a_prime = copy_arr(a, n); // create its copies

    NUMB_SWAPS = 0, NUMB_COMPARES = 0; // first, reset the counters
    quick_sort(a_quick, 0, n - 1); // sort the array using the first method
    printf("SORT ########################## %d\n", idx);
    printf("Quick sort: \nis sorted: %d\n\t compares: %d\n\t swaps: %d\n", is_correct_sort(a, a_quick, n), NUMB_COMPARES, NUMB_SWAPS);
    NUMB_SWAPS = 0, NUMB_COMPARES = 0; // reset the counters again
    prime_sort(a_prime, n); // sort the array using the second method
    printf("Prime sort: \nis sorted: %d\n\t compares: %d\n\t swaps: %d\n", is_correct_sort(a, a_prime, n), NUMB_COMPARES, NUMB_SWAPS);
    printf("#################################\n\n\n");

    //print_array(a_prime, n);
    //print_array(a_quick, n);
    // free all allocated memory for the arrays
    free(a);
    free(a_quick);
    free(a_prime);
}

static int* unwrap_array(int *arr, int n) { // function to reverse an array (if needed)
    int* temp = calloc(n, sizeof(int)); // create a temporary array
    for (int i = 0; i < n; i++) { // iterate through the array and reverse it, writing to another array
        temp[i] = arr[n - 1 - i];
    }
    free(arr); // free memory from the original array
    return temp;

}

static void edge_case(int n) { // function to handle edge cases
    printf("#########   EDGE CASE   #########\n");
    int *arr = generate_array(n); // create an array
    int *arr_quick = copy_arr(arr, n), *arr_prime = copy_arr(arr, n); // make its copies
    quick_sort(arr_quick, 0, n - 1); // sort each of them
    prime_sort(arr_prime, n);

    //print_array(arr, n);
    //print_array(arr_quick, n);
    //print_array(arr_prime, n);

    // check if the arrays are sorted
    printf("is arrays sorted: quick sort: %d; prime sort: %d\n", is_correct_sort(arr, arr_quick, n), is_correct_sort(arr, arr_prime, n));

    NUMB_SWAPS = 0, NUMB_COMPARES = 0; // reset the counters
    quick_sort(arr_quick, 0, n - 1); // sort the array
    printf("Quick sort for sorted array: \nis sorted: %d\n", is_correct_sort(arr, arr_quick, n));
    printf("\t compares: %d\n\t swaps: %d\n",  NUMB_COMPARES, NUMB_SWAPS);
    arr_quick = unwrap_array(arr_quick, n); // reverse it
    NUMB_SWAPS = 0, NUMB_COMPARES = 0; // reset the counters again
    quick_sort(arr_quick, 0, n - 1); // sort it again
    printf("Quick sort for sorted unwraped array: \nis sorted: %d\n", is_correct_sort(arr, arr_quick, n));
    printf("\t compares: %d\n\t swaps: %d\n",  NUMB_COMPARES, NUMB_SWAPS);


    NUMB_SWAPS = 0, NUMB_COMPARES = 0; // reset the counters
    prime_sort(arr_prime, n); // sort the array
    printf("Prime sort for sorted array: \nis sorted: %d\n", is_correct_sort(arr, arr_prime, n));
    printf("\t compares: %d\n\t swaps: %d\n",  NUMB_COMPARES, NUMB_SWAPS);
    arr_prime = unwrap_array(arr_prime, n); // reverse it
    NUMB_SWAPS = 0, NUMB_COMPARES = 0; // reset the counters again
    prime_sort(arr_prime, n); // sort it again
    printf("Prime sort for sorted unwraped array: \nis sorted: %d\n", is_correct_sort(arr, arr_prime, n));
    printf("\t compares: %d\n\t swaps: %d\n",  NUMB_COMPARES, NUMB_SWAPS);

    // free all allocated memory
    free(arr);
    free(arr_prime);
    free(arr_quick);

}

int main(void) {
    srand(time(NULL));
    int n = 0;
    scanf("%d", &n); // read the number of elements in the array

    int numb_attempts = 2; // number of times to conduct the sorting experiment
    for (int i = 0; i < numb_attempts; i++) {
        sort_generated_array(n, i + 1); // function to implement the task
    }

    edge_case(n); // sort the sorted array and the sorted array written in reverse order
    return 0;
}
