/*Задача B-2. Калькулятор для строковых множеств
Time limit:	14 s
Memory limit:	64 M
Разработайте программу-калькулятор, умеющую вычислять арифметические выражения над множествами строк.
Входные данные (выражение с описанием множеств и производимых над ними операций) подаются на стандартный поток ввода 
программы, результат вычислений должен подаваться на стандартный поток вывода. 

Поддерживаемые операции: 'U' - объединение, '^' - пересечение, '\' - разность множеств, '()' - задание приоритета вычислений.
Множества задаются в виде [el1,el2,...], где элементами являются строки в формате "abc def" (могут содержать пробелы).
Множества могут быть пустыми. Между операциями, множествами и элементами множеств пробелы запрещены.

При вычислениях должны учитываться приоритеты операций (в том числе, заданные вручную при помощи круглых скобочек).

Элементы результирующего множества должны выводиться в лексикографическом порядке.
В случае, если введенное выражение содержит ошибку, необходимо вывести в поток стандартного вывода сообщение "[error]" 
и завершить выполнение программы. 

ВАЖНО! Программа в любом случае должна возвращать 0. Не пишите return -1, exit(1) и т.п. Даже если обнаружилась 
какая-то ошибка, все равно необходимо вернуть 0! (и напечатать [error] в stdout).

Examples
Input	                                                            Output
(["1","2","3"]U["1","2","4 2","8"]U[])^["1","8","3","1 3"]          ["1","3","8"]
*/

#include <stdio.h>
#include <stdlib.h>

#define N_SIZE 1000 // Размер одного элемента калькулятора (строкового множества или операции)
#define SIZE_STR 1000 // Размер считываемой строки
#define N_SETS 1000 // Количество элементов калькулятора (множеств и операций)
#define N_ELEMENT 100 // Количество символов на один элемент множества

char* calc_array(char **expr);

char* transform_one(char** arr) { // Трансформация двумерного массива в одноимерный
    char *arrNew = (char *)calloc(N_SIZE, sizeof(char));
    int k = 0;
    arrNew[k++] = '['; // Символ начала множества
    int i = 0, j = 0;
    while (arr[i][0] != '\0') {
        j = 0;
        if (i != 0) // Если элемент не один
            arrNew[k++] = ','; // То добавляем запятую
        arrNew[k++] = '"'; // Символ начала элемента множества
        while (arr[i][j] != '\0') { // Добавляем все содержимое элемента
            arrNew[k++] = arr[i][j++];
        }
        arrNew[k++] = '"'; // Символ конца элемента множества
        i++;
    }
    arrNew[k] = ']'; // Символ конца множества
    for (k = 0; k < N_ELEMENT; k++) // Очищаем память
        free(arr[k]);
    free(arr);
    return arrNew;
}

char** transform_two(char* arr) { // Трансформация одномерного массива в двумерный
    char **arrNew = (char **)calloc(N_ELEMENT, sizeof(char *));
    for (int k = 0; k < N_ELEMENT; k++) {
        arrNew[k] = (char *)calloc(N_ELEMENT, sizeof(char));
    }
    int i = 0, j = 0, k = 0;
    if (arr[k] == '[')
        k++;
    while (arr[k] != ']') {
        if (arr[k] == '"')
            k++;
        j = 0;
        while (arr[k] != '"') { // Считываем один элемент множества
            arrNew[i][j++] = arr[k++];
        }
        arrNew[i][j++] = '\0';
        i++; // Переходим на следующую строку в новом массиве
        k++;
        if (arr[k] == ',')
            k++;
    }
    arrNew[i][0] = '\0';
    free(arr); // Очищаем память
    return arrNew;
}

int find_in_arr(char *elem, char **arr) { // Поиск элемента в массиве
    int j = 0;
    while (arr[j][0] != '\0') {
        int flag = 1, i = 0;
        while (arr[j][i] != '\0' && elem[i] != '\0') {
            char c1 = arr[j][i], c2 = *(elem + i);
            if (c1 != c2) {
                flag = 0;
                break;
            }
            i++;
        }
        if (arr[j][i] != '\0' || elem[i] != '\0')
            flag = 0;
        j++;
        if (flag == 1)
            return 1;
    }
    return 0;
}

char* inter_arr(char **arr1, char **arr2) { // Пересечение множеств
    int n = 0;
    char** arrNew = (char **)calloc(N_SIZE, sizeof(char*)); // Выделение памяти на массив
    for (int i = 0; i < N_SIZE; i++) {
        arrNew[i] = (char *)calloc(N_SIZE, sizeof(char));
    }

    for (; **arr1 != '\0'; arr1++) { // Проходим по первому массиву
        if (find_in_arr(*arr1, arr2) == 1) { // Если элемент есть и во втором массиве то
            arrNew[n++] = *arr1; // Записываем элемент в новый массив
        }
    }
    /*for (int i = 0; i < N_SIZE; i++) { // Освобождаем память
        free(arr1[i]);
    }
    free(arr1);
    for (int i = 0; i < N_SIZE; i++) {
        free(arr2[i]);
    }
    free(arr2); // Удаляем данные первого и второго массива */
    //arr1 = arrNew; // Изменяем ссылку у первого массива
    return transform_one(arrNew); // Возвращаем трансформированный в одномерный массив
}

char* union_arr(char **arr1, char **arr2) { // Объединение множеств
    int n = 0;
    char** arrNew = (char **)calloc(N_SIZE, sizeof(char*)); // Выделение памяти на массив
    for (int i = 0; i < N_SIZE; i++) {
        arrNew[i] = (char *)calloc(N_SIZE, sizeof(char));
    }
    for (; **arr1 != '\0'; arr1++) { // Переносим данные первого массива в новый массив
        arrNew[n++] = *arr1;
    }
    arr1 -= n;
    int n1 = n, n2 = 0;
    for (; **arr2 != '\0'; arr2++) { // Проходим по второму массиву
        if (find_in_arr(*arr2, arr1) == 0) { // Если элемента нет в первом массиве то
            arrNew[n++] = *arr2; // Добавить его в новый массив
        }
        n2++;
    }
    arr1 -= n1;
    arr2 -= n2;
    /*for (int i = 0; i < N_SIZE; i++) { // Освобождаем память
        free(arr1[i]);
    }
    free(arr1);
    for (int i = 0; i < N_SIZE; i++) {
        free(arr2[i]);
    }
    free(arr2); // Удаляем данные первого и второго массива*/
    //arr1 = arrNew; // Изменяем ссылку у первого массива
    return transform_one(arrNew); // Возвращаем трансформированный в одномерный массив
}

char* diff_arr(char **arr1, char **arr2) { // Разность множеств
    int n = 0;
    char** arrNew;
    arrNew = (char **)calloc(N_SIZE, sizeof(char*)); // Выделение памяти на массив
    for (int i = 0; i < N_SIZE; i++) {
        arrNew[i] = (char *)calloc(N_SIZE, sizeof(char));
    }
    int k = 0;
    for (; **arr1 != '\0'; arr1++, k++) {// Проходим по первому массиву
        if (find_in_arr(*arr1, arr2) == 0) { // Если элемента нет во втором массиве то
            arrNew[n++] = *arr1;// Записываем элемент в новый массив
        }
    }
    /*arr1 -= k;
    for (int i = 0; i < N_SIZE; arr1++, i++) { // Освобождаем память
        free(*arr1);
    }
    free(arr1);
    for (int i = 0; i < N_SIZE; arr2++, i++) {
        free(*arr2);
    }
    free(arr2); // Удаляем данные первого и второго массива */
    //arr1 = arrNew; // Изменяем ссылку у первого массива
    return transform_one(arrNew); // Возвращаем трансформированный в одномерный массив
}

char *array(char **expr)
{
    char *arr1;

    if (**expr == '(') // Если операция скобка
    {
        expr++; // Идем к множеству (инкрементируем по строке)
        arr1 = calc_array(expr); // Считаем значение в скобках
        expr++;
        if (**expr == ')') {// Если скобки закончились
            expr++; // То инкрементирем выражение по строке
        }
        return arr1; // Возвращаем значение, посчитанное в скобках
    }
    return *expr;
}

char *factors(char **expr)
{
    char *arr1;
    char *arr2;
    char op;

    arr1 = array(expr);
    expr++;
    while (**(expr) != '\0')
    {
        op = **(expr);
        if (op != '^')
            return arr1;
        expr++;
        arr2 = array(expr);
        if (op == '^')
            arr1 = inter_arr(transform_two(arr1), transform_two(arr2));
        expr++;
    }
    return arr1;
}

char* calc_array(char **expr) { // Сам калькулятор
    char *arr1;
    char *arr2;
    char op;

    arr1 = factors(expr); // Первые операции - пересечение множеств
    ++expr;
    while (**(expr) != '\0')
    {
        op = **(expr);
        if (op != '\\' && op != 'U')
            return arr1;
        expr++;
        arr2 = factors(expr);
        if (op == 'U') {
            arr1 = union_arr(transform_two(arr1), transform_two(arr2));
        }
        else {
            arr1 = diff_arr(transform_two(arr1), transform_two(arr2));
        }
        expr++;
    }
    return arr1;
}

char **read_data(char *str, int n_sets) {
    n_sets = 0;
    int i = 0, j = 0;
    char **sets = (char **)malloc(N_SETS * sizeof(char *)); // Выделение памяти

    for (; j < N_SETS; j++) {
        sets[j] = (char *)malloc(N_SIZE * sizeof(char));
    }
    j = 0; // Счетчик массива множеств

    while (str[i] != '\0') { // Проходим по всей строке
        if (str[i] != '[') { // Если символ не начало множества
            sets[j++][0] = str[i++]; // То записываем его одного в массив - это операция
        }
        int k = 0;
        while (str[i] != ']') { // Пока в строке множество
            sets[j][k++] = str[i++]; // Записываем в один элемент массива - элементы множества
        }
        sets[j++][k] = ']'; // Переходим к следующей строке массива
        i++;
    }
    sets[j][0] = '\0';
    return sets;
}

void clear_mem(char *str, char **sets, char *result) { // Очистка памяти
    free(str);
    free(result);
    /*for (int i = 0; i < N_SETS; i++) {
        free(sets[i]);
    } */
    //free(sets);
}

int main(void)
{
    char *str = (char *)calloc(SIZE_STR, sizeof(char)); // Выделение памяти на вводимую строку
    gets(str); // Считать данные (getline)

    int n_sets = 0; // Количество элементов калькулятора - множество = 1 элемент, операция = 1 элемент
    char **sets = read_data(str, n_sets); // Преобразовать данные

    char *result;
    result = calc_array(sets); // Подсчет результата

    printf("%s", result); // Печать результата

    clear_mem(str, sets, result); // Очистка памяти всего
    return 0;
}