#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int NUMB_SWAPS = 0;
int NUMB_COMPARES = 0;

static int* generate_array(int n) { // функция для создания массива, заполненного случайнми числами
    int* arr = calloc(n, sizeof(int)); // выделяем память под массив
    for (int i = 0; i < n; i++) { // проходимся по нему
        arr[i] = rand(); // и заполняем его случайными числами
    }
    return arr;
}

static int* copy_arr(int *src, int n) { // функция для создания копии массива
    int* arr = calloc(n, sizeof(int)); // выделяем память под массив-копию
    for (int i = 0; i < n; i++) { // проходимся по нему
        arr[i] = src[i]; // и копируем в него значения
    }
    return arr; // возвращаем указатель на копию массива
}

static void swap(int * arr, int i_1, int i_2) { // функция для подсчета количества перемещений элементов
    int temp = 0; // создаем временную переменную

    temp = arr[i_1]; // и с помощью нее меняем местами элементы в массиве
    arr[i_1] = arr[i_2];
    arr[i_2] = temp;
    NUMB_SWAPS++; // увеличиваем счетчик перемещений
}

static int is_less(int a, int b) { // функция для подсчета сравнений жлементов массива между собой
    NUMB_COMPARES++; // увеличиваем счетчик
    if (a < b) { // сравниваем переменные и возвращаем результат
        return 1;
    }
    return 0;
}

static void prime_sort(int *arr, int n) { // функция сортировки методом простого выбора
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) { // проходим по каждому элементу массива, кроме последнего (так как он к концу сортировки уже будет на своем месте)
        min_idx = i; // считаем текущий элемент минимальным
        for (j = i + 1; j < n; j++) { // ищем индекс минимального элемента в оставшейся части массива
            if (is_less(arr[j], arr[min_idx])) { // если нашли элемент меньше текущего минимального
                min_idx = j; // обновляем индекс минимального элемента
            }
        }
        if (arr[i] != arr[min_idx]) {
            swap(arr, i, min_idx); // если нашли новый минимум, меняем его местами с текущим элементом
        }
    }
}

static void quick_sort(int *arr, int l, int r) { // функция быстрой сортировки массива arr с индексами от l до r
    if (l >= r) return; // базовый случай рекурсии: если подмассив имеет 0 или 1 элемент, он уже отсортирован
    int var = arr[(l + r) / 2]; // выбираем опорный элемент: берем средний элемент подмассива
    int i = l, j = r; // Инициализируем указатели для сортировки: i - с начала, j - с конца подмассива

    // разделяем массив на две части:
    // левая часть – элементы, меньше или равные опорному,
    // правая – элементы, большие или равные опорному.
    // цикл выполняется, пока i не "пересечёт" j
    while (i <= j) {
        while (is_less(arr[i], var)) { // ищем слева элемент, который не меньше var (то есть, a[i] >= var)
            i++;
        }
        while (is_less(var, arr[j])) { // ищем справа элемент, который не больше var (то есть, a[j] > var)
            j--;
        }
        if (i <= j) { // если указатели не пересеклись, меняем найденные элементы местами
            if (arr[i] != arr[j]) {
                swap(arr, i, j); // меняем a[i] и a[j]
            }
            i++;
            j--;
        }
    }

    // получаем, что все элементы от l до j <= var, а от i до r >= var.
    // и теперь рекурсивно сортируем левую и правую части.
    quick_sort(arr, l, j);
    quick_sort(arr, i, r);
}

static int is_in_order(int *sorted, int n) { //функция для проверки, внужном ли порядке расположены элементы
    for (int i = 1; i < n; i++) { // проходимся по отсортированному массиву
        if (sorted[i] < sorted[i - 1]) {
            return 0; // Не отсортирован
        }
    }
    return 1; // Отсортирован
}

static int is_all_included(int *init, int *sorted, int n) { // проверка но то, совпадает ли набор элементов в изначально и отсортированном массиве
    int *temp = calloc(n, sizeof(int));  // Выделяем память для временного массива

    // Для каждого элемента из исходного массива ищем его в отсортированном
    for (int i = 0; i < n; i++) {
        int found = 0;  // Флаг, указывающий, найден ли элемент
        for (int j = 0; j < n; j++) {
            if (init[i] == sorted[j] && temp[j] == 0) {
                temp[j] = 1;  // Помечаем, что элемент найден
                found = 1;    // Элемент найден
                break;        // Прерываем внутренний цикл, так как элемент уже найден
            }
        }
        if (!found) {
            // Если элемент не найден, массивы не совпадают
            free(temp);
            return 0;
        }
    }

    // Если хотя бы один элемент не найден в отсортированном массиве, возвращаем 0
    for (int i = 0; i < n; i++) {
        if (temp[i] == 0) {
            free(temp);  // Освобождаем память
            return 0;
        }
    }

    free(temp);  // Освобождаем память
    return 1;
}

static int is_correct_sort(int *init, int *sorted, int n) { // общая проверка отсортированности
    return is_in_order(sorted, n) && is_all_included(init, sorted, n);
}

static void print_array(int *a, int n) { // функция печати массива (по необходимости)
    for (int i = 0; i < n; i++) { // проходимся по массиву
        printf("%d ", a[i]); // и печатаем элементы массива
    }
    printf("\n");
}

static void sort_generated_array(int n, int idx) { // функция для упрощения обработки большого колическтва массивов
    int *a = generate_array(n); // создаем массив нужной длины
    int *a_quick = copy_arr(a, n), *a_prime = copy_arr(a, n); // создаем его копии

    NUMB_SWAPS = 0, NUMB_COMPARES = 0; // для начала зануляем счетчики
    quick_sort(a_quick, 0, n - 1); // сортируем массив первым способом
    printf("SORT ########################## %d\n", idx);
    printf("Quick sort: \nis sorted: %d\n\t compares: %d\n\t swaps: %d\n", is_correct_sort(a, a_quick, n), NUMB_COMPARES, NUMB_SWAPS);
    NUMB_SWAPS = 0, NUMB_COMPARES = 0; // снова зануляем счетчики
    prime_sort(a_prime, n); // сортируем массив вторым способом
    printf("Prime sort: \nis sorted: %d\n\t compares: %d\n\t swaps: %d\n", is_correct_sort(a, a_prime, n), NUMB_COMPARES, NUMB_SWAPS);
    printf("#################################\n\n\n");

    //print_array(a_prime, n);
    //print_array(a_quick, n);
    // освобождаем всю выделенную под массивы память
    free(a);
    free(a_quick);
    free(a_prime);
}

static int* unwrap_array(int *arr, int n) { // функция для разворачивания массива (при необходимости)
    int* temp = calloc(n, sizeof(int)); // создаем временный массив
    for (int i = 0; i < n; i++) { // проходимся по массиву и и переворачиваем его, записывая в другой массив
        temp[i] = arr[n - 1 - i];
    }
    free(arr); // освобождаем память из-под исходного массива
    return temp;

}

static void edge_case(int n) { // функция для обработки вырожденных случаев
    printf("#######   EDGE CASE   #######\n");
    int *arr = generate_array(n); // создаем массив
    int *arr_quick = copy_arr(arr, n), *arr_prime = copy_arr(arr, n); // делаем его копии
    quick_sort(arr_quick, 0, n - 1); // сортируем каждую из них
    prime_sort(arr_prime, n);

    //print_array(arr, n);
    //print_array(arr_quick, n);
    //print_array(arr_prime, n);

    // проверяем, отсортированны ли массивы
    printf("is arrays sorted: quick sort: %d; prime sort: %d\n", is_correct_sort(arr, arr_quick, n), is_correct_sort(arr, arr_prime, n));

    NUMB_SWAPS = 0, NUMB_COMPARES = 0; // зануляем счетчики
    quick_sort(arr_quick, 0, n - 1); //сортируем массив
    printf("Quick sort for sorted array: \nis sorted: %d\n", is_correct_sort(arr, arr_quick, n));
    printf("\t compares: %d\n\t swaps: %d\n",  NUMB_COMPARES, NUMB_SWAPS);
    arr_quick = unwrap_array(arr_quick, n); // переворачиваем его
    NUMB_SWAPS = 0, NUMB_COMPARES = 0; // опять зануляем счетчики
    quick_sort(arr_quick, 0, n - 1); // и снова сортируем его
    printf("Quick sort for sorted unwraped array: \nis sorted: %d\n", is_correct_sort(arr, arr_quick, n));
    printf("\t compares: %d\n\t swaps: %d\n",  NUMB_COMPARES, NUMB_SWAPS);


    NUMB_SWAPS = 0, NUMB_COMPARES = 0; // зануляем счетчики
    prime_sort(arr_prime, n); //сортируем массив
    printf("Prime sort for sorted array: \nis sorted: %d\n", is_correct_sort(arr, arr_prime, n));
    printf("\t compares: %d\n\t swaps: %d\n",  NUMB_COMPARES, NUMB_SWAPS);
    arr_prime = unwrap_array(arr_prime, n); // переворачиваем его
    NUMB_SWAPS = 0, NUMB_COMPARES = 0; // опять зануляем счетчики
    prime_sort(arr_prime, n); // и снова сортируем его
    printf("Prime sort for sorted unwraped array: \nis sorted: %d\n", is_correct_sort(arr, arr_prime, n));
    printf("\t compares: %d\n\t swaps: %d\n",  NUMB_COMPARES, NUMB_SWAPS);

    // освобождаем всю выделенную память
    free(arr);
    free(arr_prime);
    free(arr_quick);

}

int main(void) {
    srand(time(NULL));
    int n = 0;
    scanf("%d", &n); // считываем количество элементов массива

    int numb_attempts = 2; // количество раз проведения эксперимента с сортировками
    for (int i = 0; i < numb_attempts; i++) {
        sort_generated_array(n, i); //функция для реализации задачи
    }

    edge_case(n); // сортируем отсортированный массив и отсортированный, но записанный в обратном порядке
    return 0;
}
