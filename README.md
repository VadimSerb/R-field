Сербаев Вадим, СКБ 172. Отчет к заданию по дисциплине «Теоретико-числовые методы в криптографии».

# Программная реализация поля действительных чисел

## Цель работы

Цель работы заключается в программной реализации алгоритмов четырех арифметических операций, определенных для действительных чисел (сложение, вычитание, умножение, деление), количество разрядов которых превосходит 19 (int64 max number = 9 223 372 036 854 775 807), с последующим тестированием для проверки корректности выполнения поставленной задачи. Язык для написания программы - Cи.
Программный код является полностью оригинальным и написал с нуля.


## Структуры и функции программы

### Логика хранения числа.

Начало работы программы - пользователь вводит символ char с помощью функции пользовательского ввода scanf_s(), по значению которого определяется, какую операцию с двумя числами необходимо совершить. После чего пользователь вводит два числа (символьные строки) с помощью функции gets(). 

- Условное ограничение на ввод при выборе операций "сложение" и "вычитание"- сумма количества разрядов целой и дробной частей любого из двух чисел не должна превышать 99, чтобы избежать переполнения.

- Условное ограничение на ввод при выборе операций "умножение" и "деление"- сумма количества разрядов целой и дробной частей делителя не должна превышать 50, чтобы избежать переполнения. Сумма количества разрядов целой и дробной частей делимого не должна превышать 75.

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

- Условное ограничение - выбрав операцию сложения, считаем, что оба введенных числа являются либо оба положительными, либо оба отрицательными. Для сложения отрицательного числа с положительным, либо положительного с отрицательным используется операция "вычитание".
   
- Ограничение является условным, потому что при желании можно добавить необходимую проверку на знак, чтобы можно было складывать положительное число с отрицательным, либо отрицательное с положительным при выборе операции "сложение" (вызывая функции операции "вычитание").
   
#### Операция вычитания

Если в начале была выбрана операция "вычитание", то заместо ```AdditionOperation``` будет вызвана функция ```void SubstractionOperation(char* a, char* b, char* c)```.
- Полагаем, что оба числа либо являются отрицательными, либо положительными, потому что иначе будет просто вызвана функция сложения и выведен ответ со знаком '-' или '+'. Для удобства рассмотрим случай с двумя положительными числами (с двумя отрицательными числами всё аналогично, только в начале берется знак '-' и учитывается при выводе ответа).

```SubstractionOperation``` получает на вход три массива: first - целая часть первого числа, second - целая часть второго числа, и result, куда будет записал результат математического вычитания одного числа из другого. Далее ```SubstractionOperation``` вызывает функцию ```char ComparisonOperation(char* a, char* b)```, которая реализует беззнаковое сравнение first и second, возвращая символ 'T', если first >= second и 'F' в противном случае. ```SubstractionOperation```, равно как и ```ComparisonOperation```, не учитывает знак числа. Далее вызывается функция ```void SubstractionLargerMinusSmaller(char* a, char* b, char* c)```, где a - наибольшее из first и second чисел, а b - меньшее; c - массив result, куда будет записан ответ. 

```SubstractionLargerMinusSmaller``` - реализация алгоритма вычитания в столбик целочисленных чисел, где уменьшаемое больше вычитаемого.

Теперь необходимо разобраться с дробной частью и знаком. Возможны 4 сценария: 
- Указание - далее целая часть первого числа - это ```first```, целая часть второго числа - это ```second```;  дробная часть первого числа - это ```firstfraction```, второго - ```secondfraction```.
- I.    ```first``` >= ```second``` и ```firstfraction``` >= ```secondfraction```
- II.   ```first``` < ```second``` и ```firstfraction``` < ```secondfraction```
- III.  ```first``` >= ```second``` и ```firstfraction``` < ```secondfraction```
- IV.   ```first``` < ```second``` и ```firstfraction``` >= ```secondfraction```

В первом и четвертом случаях всё очевидно - вызываем функцию ```SubstractionOperation``` для ```firstfraction``` и ```secondfraction``` и выводим ответ на экран (в 4 случае добавим в начале вывода символ '-').


### Теоретическая вставка: Метод Ньютона для аппроксимации корня функции, алгоритм быстрого нахождения обратного числа

Алгоритм нахождения численного решения уравнения ![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/cf85883d74b75fe35ca8d3f2b44802df078e4fa1)
сводится к итерационной процедуре вычисления: ![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/ad1c904e2d2798c0cbac6365db61c4c6e853d582)
и последовательность приближений стремится к корню уравнения ![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/cf85883d74b75fe35ca8d3f2b44802df078e4fa1)

Обоснование: чтобы численно решить уравнение ![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/cf85883d74b75fe35ca8d3f2b44802df078e4fa1) методом простой итерации, его необходимо привести к эквивалентному уравнению: ![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/77e3afd25cdf5479ad11868e5da0fcc2ea4ddeb3) , где ![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/33ee699558d09cf9d653f6351f9fda0b2f4aaa3e) - это сжимающее отображение.

Для наилучшей сходимости метода в точке очередного приближения ![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/e5be23ee5d433f8b576e63bcb47518128ee0b6bb) должно выполняться условие ![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/9b52c7204059afbe59b1793ff6a69db9dfbd9e1b), и решение данного уравнения ищут в виде ![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/f6842a06e315c7a2d2ab1c88ad26c8b5ac52cee2). 

Тогда ![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/3194091b5b420574b450346ebca40f1f15f78a0f) 

В предположении, что точка приближения «достаточно близка» к корню ![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/4f5c5435030c952a58a756e691ea64f60c1bd240) и что заданная функция непрерывна ![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/98bc7283c5bd3e7713dacf04a3984f93646972de), окончательная формула для ![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/43941ef40b4eb751a8daea118d0012ea998f5610):  

![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/e9acab9df7351ad979a7178cd0bfc209b7a33996).

С учётом этого функция ![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/4c4046f1f2de7df04bde418ba2bc4d3898ac2385) определяется как:

![Альтернативный текст](https://wikimedia.org/api/rest_v1/media/math/render/svg/11a9b58e68d224bb8e23930cae986fec1ad1fbd7) 


Для получения формулы получения приближения обратного числа необходимо рассмотреть аппроксимацию корня функции f(1/b), где b - исходное число.

Рассмотрим функцию f(x) = 1/x - b; оценим функцию f(1/b): f(1/b) = 1/(1/b) - b = b - b = 0, таким образом, нулем функции можно считать 1/b.
Далее, остается подставить функцию f(x) = 1/x - b в формулу Ньютона, и в результате получится следующая формула для нахождения итерационного приближения обратного значения:

x_(n+1) = 2x_n - b(x_n)^2

## Тестовые векторы

### Тестирование операции 'деление':

#### TEST #1

a = 942283467167248271848742827487.17856454323212354

b = 7898993216564754.12

Python answer: ```119291590881634.430975617339866417250109596928198147308854757157286693950```

RField answer: ```119291590881634.434159360696870933883239176472042051640117650544000722398```

```TEST PASS```

#### TEST #2

a = 4769987932721654.57889899362743886732

b = 1838587394758867993.9907

Python answer: ```0.00259437650139401846467798203578640439550531804329156134924179```

RField answer: ```0.00259437650139401819896819340830514307435375511108406107446876```

```TEST PASS```

#### TEST #3

a = 0.6879988838458

b = 3758799573728395.1

Python answer: ```1.83036863325853329572862610759E-16```

RField answer: ```0.00000000000000018303686332585332705749154653909942806```

```TEST PASS```

#### TEST #4

a = 6764372478786751274765676879975878352808786883475568789898798234525366.7476

b = 900.88

Python answer: ```7508627651614811814317243212500873751126828629053771828591854966279.36426319256065509783639770007```

RField answer: ```7508627651614811378613885105024479577243533367131369650715028908275.1352168994795171341636758174132```

в обоих ответах совпадают только первые 17 разрядов: ```7508627651614811```.

Попробуем получить исходное делимое, умножив каждый результат на b:

Python answer: ```6764372478786752203249750112838797433540743816817786597958253499383808.00000000000000000000000000```

RField answer: ```6764372478786750855012852793247051585020435927803327995870616594939904.00000000000000000000000000```

У обоих ответов совпадают с исходным числом только 15 первые разрядов - ```67643724787867```. Таким образом, точно восстановить число ни одной программе не удалось, а результаты восстановления достаточно схожи между собой - 16-ый разряд равен 5. Тест можно считать пройденным.

```TEST PASS```

#### TEST #5

a = 1

b = 5503905482881223746655678290175382378287657634739

Python answer: ``` 1.816891665582369083130274E-49 ```

RField answer: ``` 0.0000000000000000000000000000000000000000000000001816891665568241662694584 ```

```TEST PASS```

#### TEST #6

a = 71377634643665121627864598458969867216726513787398

b = 394876764898278264856865837365251314786078778436

Python answer: ``` 180.759267165421262319986357293629063208114705395998722333675305011927549199 ```

RField answer: ``` 180.759267165421262319947925779242863003624201933573675387024507920052476394 ```

```TEST PASS```







