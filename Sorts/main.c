#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


// Функция генерации случайных числе в не убывающем порядке
void *inordered(int n, long long int *a) {
    srand(time(NULL)); // Инициализируем генератор случайных чисел текущим временем
    long long int lim = LLONG_MAX / n * 2; // Задаём передел шага для генерации шага
    long long int step = ((((long long)rand() << 32) | rand()) & (~0 >> 1)) % lim; // Генерируем первый шаг
    a[0] = LLONG_MIN + step; // Записываем первое число
    for (int i = 1; i < n; i++) {
        step = ((((long long)rand() << 32) | rand()) & (~0 >> 1)) % lim; // Генерируем очередной шаг
        a[i] = a[i - 1] + step; // Записываем очередное число
    }
}

// Функция генерации случайных чисел в не возрастающем порядке
void *postordered(int n, long long int *a) {
    // Действия аналогичные предыдущей функции но записывать значения начинаем с конца массива
    srand(time(NULL));
    long long int lim = LLONG_MAX / n * 2;
    long long int step = ((((long long)rand() << 32) | rand()) & (~0 >> 1)) % lim;
    a[n - 1] = LLONG_MIN + step;
    for (int i = n - 2; i >= 0; i--) {
        step = ((((long long)rand() << 32) | rand()) & (~0 >> 1)) % lim;
        a[i] = a[i - 1] + step;
    }
}

// Функция генерации массива случайных чисел
void *randomed(int n, long long int *a) {
    srand(time(NULL));  // Инициализируем генератор случайных чисел текущим временем
    for (int i = 0; i < n; i++)
        a[i] = ((long long int)rand() << 32) | rand(); // Генерируем случайное число
}

int swp = 0; // Переменная количества обменов
int cmp = 0; // Переменная количества сравнений

// Функция обмена
void swap(long long int* a, long long int* b) {
    swp++; // Увеличиваем счётчик обменов
    long long int temp = *a; // Обмен
    *a = *b;
    *b = temp;
}

// Функция сравнения
long long int compare(long long int a, long long int b) {
    cmp++; // Увеличиваем счётчик сравнений
    return ((a < 0) ? -a : a) - ((b < 0) ? -b : b); // Сравнение по модулю
}

// Функция разделения массива на две половины относительно выбранного значения
int partition(int n, long long int *a) {
    long long int pivot = a[n/2]; // Выбираем значения относительно, которого будем делить массив
    int i = 0, j = n - 1; // Устанавливаем счётчики в начальные положения
    do{
        while (compare(a[i], pivot) < 0)
            i++; // Двигаем левый счётчик вправо
        while (compare(a[j], pivot) > 0)
            j--; // Двигаем правый счётчик влево
        if (i <= j) { // Проверяем правильность расположения счётчиков
            swap(&a[i], &a[j]); // Ставим неподходящие значения на правильные места
            i++, j--; // Обновляем счётчики
        }
    } while (i <= j);
    return i; // Возращаем счетчик для разделения массива
}

// Функция быстрой сортировки
void qsortCustom(int n, long long int *a) {
    if (n > 2) { // Проверяем необходимость запуска рекурсии
        int rif = partition(n, a); // Устанавливаем счетчик для разделения массива
        qsortCustom(rif , a); // Запускаем рекурсию для частей массива
        qsortCustom(n - rif, a + rif);
    } else if (n == 2 && a[0] > a[1]) { // Базовый случай
        swap(&a[0], &a[1]);
    }
}

//функция просеивания дерева с корнем i
void heapify(int n, long long int *a, int i) {
    int largest = i; // Инициализируем наибольший элемент корнем
    int left = 2 * i + 1; // Инициализируем сыновей
    int right = 2 * i + 2;

    // Проверяем является ли корень наибольшим значением
    if (left < n && compare(a[largest], a[left]) < 0)
        largest = left;
    if (right < n && compare(a[largest], a[right]) < 0)
        largest = right;
    // Если корень не наибольший
    if (largest != i) {
        swap(&a[i], &a[largest]); // Инициализируем наибольшего сына корнем
        heapify(n, a, largest); // Запускаем рекурсию для большего сына
    }
}

// Функция пирамидальной сортировки
void heapSort(int n, long long int *a) {
    // Строим кучу
    for (int i = 0; i < n; i++)
        heapify(n, a, i);


    for (int i = n - 1; i > 0; i--) {
        swap(&a[0], &a[i]); // Наибольший элемент отправляем в конец
        heapify(i, a, 0); // Запускаем рекурсию для меньшей кучи
    }
}

// Функция копирования массива
long long int *arrCopy(int n, long long int *a) {
    long long int *b = malloc(n * sizeof(long long int)); // Выделяем в памяти место под копию
    for (int i = 0; i < n; i++)
        b[i] = a[i]; // Копируем
    return b; // Возращаем указатель на копию
}

// Отладочные функции
/*
void arrPrint(int n, long long int *a) {
    for (int i = 0; i < n; i++) {
        printf("%20lld ", a[i]);
        if ((i + 1) % 5 == 0) printf("\n");
    }
}

int isNotDecreasing(int n, long long int *a) {
    for (int i = 1; i < n; i++)
        if (a[i] < a[i - 1])
            return 0;
    return 1;
}

int isNotIncreasing(int n, long long int *a) {
    for (int i = 1; i < n; i++)
        if (a[i] > a[i - 1])
            return 0;
    return 1;
}
*/

int main(void) {
    int n = 100; // Задаём размер генерируемых массивов

    long long int *arr1 = malloc(n * sizeof(long long int)); // Выделяем память под массив
    inordered(n, arr1); // Генерируем массив
    long long int *arr2 = arrCopy(n, arr1); // Копируем массив
    qsortCustom(n, arr1); // Соритируем массив первым способом
    printf("Not decreasing array.\nqSort.\nCompares: %d\nSwaps: %d\n", cmp, swp); // Вывод
    printf("=====================\n");
    swp = 0, cmp = 0; // Обнуляем счётчики
    heapSort(n, arr2); // Сортируем вторым способом
    printf("Not decreasing array.\nheapSort.\nCompares: %d\nSwaps: %d\n", cmp, swp); // Вывод
    printf("=====================\n");
    free(arr1); // Возвращаем память
    free(arr2);

    // Далее аналогично
    arr1 = malloc(n * sizeof(long long int));
    postordered(n, arr1);
    arr2 = arrCopy(n, arr1);
    swp = 0, cmp = 0;
    qsortCustom(n, arr1);
    printf("Not increasing array.\nqSort.\nCompares: %d\nSwaps: %d\n", cmp, swp);
    printf("=====================\n");
    swp = 0, cmp = 0;
    heapSort(n, arr2);
    printf("Not increasing array.\nheapSort.\nCompares: %d\nSwaps: %d\n", cmp, swp);
    printf("=====================\n");
    free(arr1);
    free(arr2);

    arr1 = malloc(n * sizeof(long long int));
    randomed(n, arr1);
    arr2 = arrCopy(n, arr1);
    swp = 0, cmp = 0;
    qsortCustom(n, arr1);
    printf("Random array.\nqSort.\nCompares: %d\nSwaps: %d\n", cmp, swp);
    printf("=====================\n");
    swp = 0, cmp = 0;
    heapSort(n, arr2);
    printf("Random array.\nheapSort.\nCompares: %d\nSwaps: %d\n", cmp, swp);
    printf("=====================\n");
    free(arr1);
    free(arr2);

    arr1 = malloc(n * sizeof(long long int));
    randomed(n, arr1);
    arr2 = arrCopy(n, arr1);
    swp = 0, cmp = 0;
    qsortCustom(n, arr1);
    printf("Random array.\nqSort.\nCompares: %d\nSwaps: %d\n", cmp, swp);
    printf("=====================\n");
    swp = 0, cmp = 0;
    heapSort(n, arr2);
    printf("Random array.\nheapSort.\nCompares: %d\nSwaps: %d\n", cmp, swp);
    free(arr1);
    free(arr2);

    return 0;
}
