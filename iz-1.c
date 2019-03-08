/*
Задача A-3. Задача о максимальном подотрезке.
Time limit:14 s
Memory limit:64 M
Составить программу определения такого максимального подотрезка среди элементов заданного целочисленного массива, элементы которого увеличиваются по порядку на 1. 
Подотрезок массива - это часть ("кусок") массива, который включает в себя все элементы исходного массива от некоторого начального индекса до некоторого другого конечного индекса без изменения порядка следования элементов. Элементы подотрезка функция должна вернуть через указатель-параметр, а ее длину — через возвращаемый результат. 

Формат входных данных: 
N - длина входного массива 
A1 ... An - целочисленный массив 

Формат выходных данных: 
N - длинна найденного подотрезка 
A1 ... An - подотрезок 

Гарантируется, что все значения помещаются в 32-битный целый тип (int). Если заданный подотрезок не найден, или если найден только вырожденный подотрезок (длиной 1), необходимо вывести только длину - 0. Если подходящих подотрезков несколько, то необходимо вывести информацию (длину, подотрезок) про первый из них. 

Программа должна уметь обрабатывать ошибки во входных данных (отрицательное количество элементов и др.). В случае возникновения ошибки нужно вывести в поток стандартного вывода сообщение "[error]" (без кавычек) и завершить выполнение программы. 

ВАЖНО! Программа в любом случае должна возвращать 0. Не пишите return -1, exit(1) и т.п. Даже если обнаружилась какая-то ошибка, все равно необходимо вернуть 0! (и напечатать [error] в stdout).


*/

#include <stdio.h>
#include <stdlib.h>

int find_max(int n, int *a) {
  int *k = a, *now_k = a;
  int kol = 1, now_kol = 1;
  for (int i = 1; i <= n; i++) {
    if (i< n && a[i] - a[i-1] == 1) {
      now_kol++;
    }
    else {
      if (now_kol > kol) {
  	    kol = now_kol;
	      k = &(*now_k);
      }
      now_kol = 1;
      now_k = &a[i];
    }
  }
  for (int i=0; i<kol; i++) {
    a[i] = k[i];
  } 
  return kol;
} 

int scan_data(int n, int *a) {
    for (int i=0; i < n; i++) {
      if (scanf("%d", &a[i]) == 0) {
        return 1;
      }
    }
    return 0;
}

void print_data(int kol, int *k) {
  if (kol == 1) { //Проверка на вырожденность отрезка
    printf("%d", 0);
  }
  else {
    printf("%d\n", kol);
    for (int i=0; i < kol; i++, k++) {
      printf("%d ", *k);
    }
  }
  return;
}

int main(void) {
  int n, err, *a=(int *)NULL;

  if ( scanf("%d", &(n)) != 0  //Если число n успешно считалось
  && n > 0 //И оно больше 0
  && (a = (int*)calloc(n+1, sizeof(*a))) ) { //И если на указатель a выделилась память
    err = scan_data(n, a);//Считывание данных
  }
  else {
    err = 1;
  }

  if (err == 0) { //Если нет ошибок 
    n = find_max(n, a); //Поиск максимального подотрезка
    print_data(n, a);//Печать данных
  }
  else {
    printf("[error]"); //Напечатать ошибка
  }

  free(a);
  return 0;
}

