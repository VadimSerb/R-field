Сербаев Вадим, СКБ 172. Отчет к заданию по дисциплине «Теоретико-числовые методы в криптографии».

# Программная реализация поля действительных чисел

## Цель работы

Цель работы заключается в программной реализации алгоритмов четырех арифметических операций, определенных для действительных чисел (сложение, вычитание, умножение, деление), количество разрядов которых превосходит 19 (int64 max number = 9 223 372 036 854 775 807), с последующим тестированием для проверки корректности выполнения поставленной задачи. Язык для написания программы - Cи.
Программный код является полностью оригинальным и написал с нуля.


## Структуры и функции программы

### Логика хранения числа.

Начало работы программы - пользователь вводит символ char с помощью функции пользовательского ввода scanf_s(), по значению которого определяется, какую операцию с двумя числами необходимо совершить. После чего пользователь вводит два числа (символьные строки) с помощью функции gets(). 

- Условное ограничение на ввод при выборе операций "сложение" и "вычитание"- сумма количества разрядов целой и дробной частей любого из двух чисел не должна превышать 99, чтобы избежать переполнения.

- Условное ограничение на ввод при выборе операций "умножение" и "деление"- сумма количества разрядов целой и дробной частей любого из двух чисел не должна превышать 49, чтобы избежать переполнения.

- Ограничения являются условными, потому что при желании границу, когда будет совершено переполнение, можно изменить в сторону увеличения возможного количества разрядов.


``` struct TwoNumbers ``` - структура для хранения целой и дробной частей первого числа и одновременно хранения целой и дробной частей второго числа, результата выполнения выбранной операции и, в случае выбора операции деления, используется для хранения количества разрядов после запятой.

Структура TwoNumbers включает в себя 7 полей:

- ``` char first[100] ``` - массив из 100 символов типа char, значения которых могут принимать '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' и ','. Массив используется для хранения разрядов целой части первого введенного пользователем числа. 

- ``` char first[100] ``` - аналогично первому массиву выполняет функцию хранения целой части второго введенного пользователем числа.

- ``` char result[100] ``` - массив хранит целую часть результирующего числа, образовашегося в результате выполнения выбранной операции.

- ``` char firstfraction[100] ``` - массив хранит дробную часть первого введенного числа.

- ``` char firstfraction[100] ``` - массив хранит дробную часть второго введенного числа.

- ``` char resultfraction[100] ``` - массив хранит дробную часть результирующего числа, образовашегося в результате выполнения выбранной операции.

- ``` int nzadp ``` - тип int для хранения хранения количества разрядов после запятой. Заполняется только при выборе операции "умножение" или "деление".

Алгоритм, пример заполнения и порядок хранения разрядов будет рассмотрен далее.

### Функции и логика работы программы

Лучше всего понять, зачем нужна та или иная функция, можно на примере, описывающем весь процесс от пользовательского ввода до получения и вывода ответа.

#### Операция сложения

Предположим, пользователь выбрал на исполнение операцию сложения и ввел две символьные строки: ```94762,12345``` и ```23235421,1```.

По умолчанию, заполненный массив первого числа будет выглядеть так:

```[0][1][2][3][4][5][6][7][8][9][10]...[99]``` - индекс элемента строки

```[9][4][7][6][2][,][1][2][3][4][5] ... []``` значение элемента строки (условимся для удобства, что в данной работе цифры, указанные как значения элементов массива, на самом деле являются текстовыми символами с соответствующим значением десятичного кода по таблице ASCII)

Для удобства выполнения всех операций массив желательно привести к следующему виду:

```[0][1][2] ... [89][90][91][92][93][94][95][96][97][98][99]```

```[0][0][0] ...  [9] [4] [7] [6] [2] [,] [1] [2] [3] [4] [5]```

Ещё лучше было бы отделить дробную часть в отдельный массив и производить операцию сложение / вычитание по отдельности с целой и дробной частями.

Функция ```FillingValues(struct TwoNumbers pair, char* str, char op)``` заполняет соответсвующие поля структуры TwoNumbers именно таким образом. И если я выведу с помощью тестовой функции ```void VectorPrint(char* str)``` массивы ```first``` и ```firstfraction```, то получу следующее:

- char first[100]:

```[0][1][2] ... [89][90][91][92][93][94][95][96][97][98][99]```

```[0][0][0] ... [0] [0] [0] [0] [0] [0] [9] [4] [7] [6] [2] ```

- char firstfraction[100]:

```[0][1][2][4][5][6][7] ...[99]```

```[1][2][3][4][5][0][0] ... [0] ```

В таком представлении очень просто реализовать сложение отдельно целых частей и отдельно дробных частей двух чисел, предусмотрев возможное переполнение первого разряда дробной части прибавкой единицы к результату сложения целых частей. Остается только вывести по отдельности целую и дробную части одну за другой, разделив их выводом символа ','.

Функция ```FillingValues``` работает следующим образом:
- I. Получает из пользовательского ввода массив символов ```str``` и вызывает функцию ```void ReverseNumber(char* str)```, которая "зануляет" все символы массива, не являющиеся '1', '2', '3', '4', '5', '6', '7', '8', '9', ',', параллельно считая их количество ```n```. После чего ```ReverseNumber``` выполняет сдвиг всех символов вправо на ```n```, "зануляя" первые ```100-n``` элементов (в последствие я создал две функции, выполняющие такой сдвиг на подавоемое ```n``` элементов влево / вправо). Таким образом, мы получили массив first

   ```[0][1][2] ... [89][90][91][92][93][94][95][96][97][98][99]```

   ```[0][0][0] ...  [9] [4] [7] [6] [2] [,] [1] [2] [3] [4] [5]```

- II. Теперь необходимо отделить целую часть от дробной. ```FillingValues``` вызывает ```void FillingFraction(char* first, char* firstfraction)```, которая и вычленяет из массива ```first``` дробную часть, записывая её элементы в ```firstfraction```. Работает схожим образом с ```ReverseNumber```, только сдвиг осуществляется не вручную, а автоматизированно функцией ```void RightOffsetOperation(char* a, int n)```, выполняющей сдвиг элементов вправо на ```n``` элементов с соответствующим занулением.

- III. В случае, когда выбрана операция умножения или деления, ```FillingValues``` не будет вызывать ```FillingFraction``` и дробная часть отделяться от целой не будет. Наоборот, будет вызвана функция ```int CommaPosition(char* a)``` для "склеивания" целой и дробной частей путем удаления запятой и сдвига на 1 символ вправо всех символов, стоящих перед ней. То есть массив, полученный после вызова ```ReverseNumber``` , после вызова ```CommaPosition``` будет иметь вид:

   ```[0][1][2] ... [89][90][91][92][93][94][95][96][97][98][99]```

   ```[0][0][0] ...  [0] [9] [4] [7] [6] [2] [1] [2] [3] [4] [5]```

   Зачем так сделано? Ответ - потому что в отличие от операций сложения и вычитания (школьный алгоритм), дробная часть при умножении (реализованном алгоритмом в столбик) двух      чисел влияет только на позицию запятой в ответе. Поэтому намного легче вычислить и хранить число, отвечающее за положение запятой в результирующем массиве, чем пытаться          разделить целую и дробную части на массивы и оперировать ими. Функция ```CommaPosition``` помимо "склеивания" целой части с дробной, подсчитывает количество символов до      запятой, начиная с индекса со значением 99. В случае, если запятая отсутствует (то есть было подано целое число без дробной части), функция возвращает 0. После выполнения        функции, ```FillingValues``` приплюсовывает возвращаемое ```CommaPosition``` значение к ```nzadp``` (сокращение от number of zeros after the decimal point).
   
После ```FillingValues``` вызывается функция ```void AdditionOperation(char* a, char* b, char* c)``` отдельно для целой и для дробной части. Функция представляет из себя реализацию сложения в столбик, осуществляя поразрядное сложение и добавление единицы к следующему разряду в случае переполнения текущего.
   
   
















