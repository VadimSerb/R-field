Сербаев Вадим, СКБ 172. Отчет к заданию по дисциплине «Теоретико-числовые методы в криптографии».

# Программная реализация поля действительных чисел

## Цель работы

Цель работы заключается в программной реализации алгоритмов четырех арифметических операций, определенных для действительных чисел (сложение, вычитание, умножение, деление), с последующим тестированием для проверки корректности выполнения поставленной задачи. Язык для написания программы - Cи.
Программный код является полностью оригинальным и написал с нуля.


## Структуры и функции программы

### Логика хранения числа.

Начало работы программы - пользователь вводит символ char с помощью функции пользовательского ввода scanf_s(), по значению которого определяется, какую операцию с двумя числами необходимо совершить. После чего пользователь вводит два числа (символьные строки) с помощью функции gets(). 

- Условное ограничение на ввод при выборе операций "сложение" и "вычитание"- сумма количества разрядов целой и дробной частей не должна превышать 99, чтобы избежать переполнения.

- Условное ограничение на ввод при выборе операций "умножение" и "деление"- сумма количества разрядов целой и дробной частей не должна превышать 49, чтобы избежать переполнения.

- Ограничения являются условными, потому что при желании границу, когда будет совершено переполнение, можно изменить в сторону увеличения возможного количества разрядов.

- ``` struct TwoNumbers ``` - структура для хранения целой и дробной частей первого числа и одновременно хранения целой и дробной частей второго числа, результата выполнения выбранной операции и, в случае выбора операции деления, используется для хранения количества разрядов после запятой.

Структура TwoNumbers включает в себя 7 полей:

``` char first[100] ``` - массив из 100 символов типа char, значения которых могут принимать '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' и ','. Массив используется для хранения разрядов целой части первого введенного пользователем числа. Пример заполнения и порядок хранения разрядов будет рассмотрен далее.

``` char first[100] ``` - аналогично первому массиву выполняет функцию хранения целой части второго введенного пользователем числа.

``` char result[100] ``` - массив хранит целую часть результирующего числа, образовашегося в результате выполнения выбранной операции.

``` char firstfraction[100] ``` - массив хранит дробную часть первого введенного числа.

``` char firstfraction[100] ``` - массив хранит дробную часть второго введенного числа.


Алгоритм заполнения будет рассмотрен далее.

### Функции программы

- ``` void VectorPrint(char* str) ``` - тестовая функция для вывода числа на экран - число представлено в виде массива типа char, где каждый элемент является цифрой разряда.
- ``` void LeftOffsetOperation(char* a, int n) ```

## Логика работы программы: операция сложения
