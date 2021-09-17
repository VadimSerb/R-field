#include <stdio.h>
#include <locale.h>

struct TwoNumbers {
	char first[100];
	char second[100];
	char result[100];
	int nzadp; //сокращение от - number of zeros after the decimal point
	char firstfraction[100];
	char secondfraction[100];
	char resultfraction[100];
};

void VectorPrint(char* str) {
	for (int i = 0; i < 100; i++) {
		//if(str[i]!='0')//
		printf("%c", str[i]);
	}
	printf("%c\n", ' ');
}

void RightOffsetOperation(char* a, int n) { //смещение строки вправо на n

	char result[100];
	for (int i = 0; i < 100; i++) result[i] = '0';

	int digitsize = 0;
	for (int i = 0; i < 100 && a[i] == '0'; i++, digitsize++);

	for (int i = digitsize; i + n < 100; i++) {
		result[i + n] = a[i];
	}
	for (int i = 0; i < 100; i++) a[i] = result[i];

}

void LeftOffsetOperation(char* a, int n) { //смещение строки влево на n ИЛИ умножение на 10*n
	int digitsize = 0;
	for (int i = 0; i < 100 && a[i] == '0'; i++, digitsize++);
	for (int i = digitsize; i < 100; i++) {
		a[i - n] = a[i];
	}
	for (int i = 99; i >= 100 - n; i--) a[i] = '0';
}

void ReverseNumber(char* str){

	int shift = strlen(str);
	char tempstr[100];

	for (int i = 0; i < 100; i++) {
		if (str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != ',') str[i] = '0';
		tempstr[i] = '0';
	}

	for (int i = 100 - shift, j = 0; i < 100; i++, j++) {
	tempstr[i] = str[j];
	}

	for (int i = 0; i < 100; i++) {
		str[i] = tempstr[i];
	}
}

void FillingFraction(char* str, char* f) {

	int ncadp = 0; //сокращение от - number of characters after decimal point
	for (int i = 99; i >= 0 && str[i] != ','; i--, ncadp++);

	//printf("%d\n", ncadp);

	if ((ncadp != 0) && (ncadp != 100)) {
		for (int i = 0; i < 100 && 100 - ncadp + i < 100; i++) {
			f[i] = str[100 - ncadp + i];
		}
		RightOffsetOperation(str, ncadp + 1);
	}
}

struct TwoNumbers MultiplicationTransformation(struct TwoNumbers pair) {

	for (int i = 0; i < 100; i++) pair.resultfraction[i] = '0';
	for (int i = 99; i >= 100 - pair.nzadp; i--) {
		pair.resultfraction[i] = pair.result[i];
	}
	RightOffsetOperation(pair.result, pair.nzadp);
	LeftOffsetOperation(pair.resultfraction, 100 - pair.nzadp);

	return(pair);
}

int CommaPosition(char* a) {
	int nbc = 0;
	for (int i = 99; i > 0 && a[i] != ','; i--)	nbc++;
	if (nbc != 99) {
		for (int i = 99 - nbc; i > 0; i--) a[i] = a[i - 1];
		return(nbc);
	}
	else return(0);
}

struct TwoNumbers GetFirst(struct TwoNumbers pair, char* str){
	for (int i = 0; i < 100; i++) {
		pair.first[i] = str[i];
	}
	return(pair);
}

struct TwoNumbers GetSecond(struct TwoNumbers pair, char* str) {
	for (int i = 0; i < 100; i++) {
		pair.second[i] = str[i];
		pair.result[i] = '0';
	}
	return(pair);
}

struct TwoNumbers FillingValues(struct TwoNumbers pair, char* str, char op) {
	gets(str);
	ReverseNumber(str);
	pair = GetFirst(pair, str);

	gets(str);
	ReverseNumber(str);
	pair = GetSecond(pair, str);

	if (op == '+' || op == '-') {
		for (int i = 0; i < 100; i++) {
			pair.firstfraction[i] = '0';
			pair.secondfraction[i] = '0';
			pair.resultfraction[i] = '0';
		}
		FillingFraction(pair.first, pair.firstfraction);
		FillingFraction(pair.second, pair.secondfraction);
	}
	if (op == '*') {
		pair.nzadp += CommaPosition(pair.first);
		pair.nzadp += CommaPosition(pair.second);
	}
	if (op == '/') {
		pair.nzadp += CommaPosition(pair.first);
		pair.nzadp -= CommaPosition(pair.second);
		//pair.nzadp += 25;
	}


	return(pair);
}

void AdditionOperation(char* a, char* b, char* c) {

	int term1, term2, addrank;
	addrank = 0;
	for (int i = 99; i >= 0; i--) {
		term1 = (int)a[i] - 48 + addrank;
		term2 = (int)b[i] - 48;
		addrank = 0;
		if (term1 + term2 >= 10) {
			addrank = 1;
		}
		c[i] = ((term1 + term2) % 10) + '0';
	}
	//VectorPrint(c);
}

char ComparisonOperation(char* a, char* b) {
	int zerocount1 = 0;
	int zerocount2 = 0;
	for (int i = 0; i < 100 && a[i] == '0'; i++, zerocount1++);
	for (int i = 0; i < 100 && b[i] == '0'; i++, zerocount2++);

	if (zerocount1 < zerocount2) return('T');
	if (zerocount1 > zerocount2) return('F');
	if (zerocount1 == zerocount2) { //проверка по разрядам

		for (int i = zerocount1; i < 100; i++) {
			zerocount1 = (int)a[i] - 48;
			zerocount2 = (int)b[i] - 48;
			if (zerocount1 > zerocount2) return('T');
			if (zerocount1 < zerocount2) return('F');
		}
		return('T'); //числа равны
	}
}

void SubstractionLargerMinusSmaller(char* a, char* b, char* c) {
	int difference, addrank;
	addrank = 0;
	for (int i = 99; i >= 0; i--) {
		difference = ((int)a[i] - 48) - ((int)b[i] - 48) - addrank;
		addrank = 0;
		if (difference < 0) {
			addrank = 1;
			c[i] = difference + 10 + '0';
		}
		else c[i] = difference + '0';
	}
}

void SubstractionSmallerMinusLarger(char* a, char* b, char* c) {
	int difference, fine;
	fine = 0;
	for (int i = 99; i >= 0; i--) {
		difference = ((int)a[i] - 48) - ((int)b[i] - 48) - fine;
		fine = 0;
		if (difference < 0) {
			difference += 10;
			fine = 1;
		}
		c[i] = difference + '0';
	}
}

void SubstractionOperation(char* a, char* b, char* c) {
	//printf("%c\n", ComparisonOperation(a, b));
	if (ComparisonOperation(a, b) == 'T') {
		SubstractionLargerMinusSmaller(a, b, c);
		//VectorPrint(c);
	};

	if (ComparisonOperation(a, b) == 'F') {
		SubstractionLargerMinusSmaller(b, a, c);
		//VectorPrint(c);
	};
}

void MultiplicationOperation(char* a, char* b, char* c) {

	char result[100];
	for (int i = 0; i < 100; i++) result[i] = '0';

	int maxdigit = 0;
	int lastdigit = 0;
	
	for (int i = 0; i < 100 && b[i] == '0'; i++, maxdigit++);
	for (int i = 0; i < 100 && a[i] == '0'; i++, lastdigit++);

	int mdbd; //умножение разряда на разряд
	int addrank = 0;
	int shift = 0; //количество сдвигов влево в зависимости от разряда

	for (int i = 99; i >= maxdigit; i--) {

		for (int j = 99; j >= lastdigit-1; j--) {
			mdbd = ((int)a[j] - 48) * ((int)b[i] - 48) + addrank;
			addrank = 0;
			if (mdbd >= 10) {
				addrank = mdbd / 10;
				mdbd = mdbd % 10;
			}
			result[j] = mdbd + '0';
		}
		LeftOffsetOperation(result, shift);
		shift++;

		AdditionOperation(result, c, c);
		for (int i = 0; i < 100; i++) result[i] = '0';

	}
	//VectorPrint(c);
}

void NewtonApproximation(char* b, char* c) {
	char temp1[100];
	char temp2[100];
	char temp3[100];
	char two[100];
	for (int i = 0; i < 100; i++) {
		temp1[i] = '0';
		temp2[i] = '0';
		temp3[i] = '0';
		two[i] = '0';
	}
	two[99] = '2';

	MultiplicationOperation(two, c, temp1);

	MultiplicationOperation(c, c, temp2);
	MultiplicationOperation(b, temp2, temp3);


	while (ComparisonOperation(temp1, temp3) == 'F') LeftOffsetOperation(temp1, 1);

	SubstractionOperation(temp1, temp3, c);

	//VectorPrint(c); //вывод приближения на экран

}

void FindApproximation(char* b, char* c) {

	int zeronumber = 0;
	int fapprox;
	for (int i = 0; i < 100 && b[i] == '0'; i++) {
		zeronumber++;
	}
	fapprox = ((int)b[zeronumber] - 48) * 10;
	fapprox += ((int)b[zeronumber + 1] - 48);
	fapprox = 100 / fapprox;
	c[99] = fapprox + '0';
	//zeronumber = 100 - zeronumber; //количество нулей после запятой

	for (int i = 0; i < 5; i++) {
		NewtonApproximation(b, c);

		//ограничение на количество знаков 25, чтобы не было переполнения
		fapprox = 0;
		for (int i = 0; i < 100 && c[i] == '0'; i++) {
			fapprox++;
		}
		if (fapprox < 75) RightOffsetOperation(c, 75 - fapprox);
	}
	//VectorPrint(c);
}

void DivisionOperation(char* a, char* b, char* c) { //ограничение на делимое - 75 знаков; на делитель - 50, чтобы не было переполнения

	FindApproximation(b, c);
	for (int i = 0; i < 100; i++) b[i] = '0';
	MultiplicationOperation(a, c, b);
	for (int i = 0; i < 100; i++) c[i] = b[i];
	VectorPrint(c);
}

void GiveMeAnswer(struct TwoNumbers pair, char sign) {

	char zero[100] = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	int zeronumber = 0;

	if (sign == '-') printf("%c", sign);
	for (int i = 0; i < 100 && pair.result[i] == '0'; i++) zeronumber++;
	if (zeronumber-100 != 0) for (int i = zeronumber; i < 100; i++) printf("%c", pair.result[i]);
	else printf("%d", 0);

	if (ComparisonOperation(zero, pair.resultfraction) != 'T') {
		printf("%c", ',');
		zeronumber = 0;
		for (int i = 99; i >= 0 && pair.resultfraction[i] == '0'; i--) zeronumber++;
		for (int i = 0; i < 100 - zeronumber; i++) printf("%c", pair.resultfraction[i]);
	}
}


//
int main()
{
	struct TwoNumbers pair = { {""}, {""}, {""}, 0, {""}, {""}, {""} };

	char str[100];

	char option;
	//Выберите операцию, затем введите два числа одно за другим
	setlocale(LC_ALL, "Russian");

	printf("%s\n\n", "       МЕНЮ");
	printf("%s\n\n", "Выберите операцию:");
	printf("%s\n", "1. Введите '+' для сложения двух чисел");
	printf("%s\n", "2. Введите '-' для получения разности двух чисел");
	printf("%s\n", "3. Введите '*' для перемножения двух чисел");
	printf("%s\n\n", "4. Введите '/' для деления двух чисел");
	//printf("%s\n\n", "5. Введите 'T' для запуска тестов");

	scanf_s("%c\n", &option);
	
	switch (option) {
	case '+':

		pair = FillingValues(pair, str, option);

		AdditionOperation(pair.first, pair.second, pair.result);
		AdditionOperation(pair.firstfraction, pair.secondfraction, pair.resultfraction);
		if ((int)pair.resultfraction[0] - 48 < (int)pair.firstfraction[0] - 48) {
			char one[100] = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
			AdditionOperation(pair.result, one, pair.result);
		}
		GiveMeAnswer(pair, '+');

		break;

	case '-':
		
		pair = FillingValues(pair, str, option);

		char sign = '+';

		
		SubstractionOperation(pair.first, pair.second, pair.result);
		
		//работа с дробной частью
		if ((ComparisonOperation(pair.first, pair.second) == 'T') && (ComparisonOperation(pair.firstfraction, pair.secondfraction) == 'T')) 
			SubstractionOperation(pair.firstfraction, pair.secondfraction, pair.resultfraction);
		if ((ComparisonOperation(pair.first, pair.second) == 'F') && (ComparisonOperation(pair.firstfraction, pair.secondfraction) == 'F')) {
			SubstractionOperation(pair.firstfraction, pair.secondfraction, pair.resultfraction);
			sign = '-';
		}
		if ((ComparisonOperation(pair.first, pair.second) == 'F') && (ComparisonOperation(pair.firstfraction, pair.secondfraction) == 'T')) {
			SubstractionSmallerMinusLarger(pair.secondfraction, pair.firstfraction, pair.resultfraction);
			if (ComparisonOperation(pair.secondfraction, pair.firstfraction) == 'F') {
				char one[100] = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
				SubstractionLargerMinusSmaller(pair.result, one, pair.result);
			}
			sign = '-';
		}
		if ((ComparisonOperation(pair.first, pair.second) == 'T') && (ComparisonOperation(pair.firstfraction, pair.secondfraction) == 'F')) {
			char one[100] = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
			if (ComparisonOperation(pair.result, one) == 'T') {
				SubstractionLargerMinusSmaller(pair.result, one, pair.result);
				SubstractionSmallerMinusLarger(pair.firstfraction, pair.secondfraction, pair.resultfraction);
			}
			else {
				sign = '-';
				SubstractionOperation(pair.firstfraction, pair.secondfraction, pair.resultfraction);
			}

		}

		GiveMeAnswer(pair, sign);
		
		break;

	case '*':
		
		pair = FillingValues(pair, str, option);
		MultiplicationOperation(pair.first, pair.second, pair.result);
		pair = MultiplicationTransformation(pair);

		GiveMeAnswer(pair, '+');

		break;

	case '/':
		
		pair = FillingValues(pair, str, option);

		int zeronumber = 0;
		for (int i = 0; i < 100 && pair.second[i] == '0'; i++) {
			zeronumber++;
		}
		zeronumber = 99 - zeronumber; //количество нулей после запятой
		pair.nzadp += zeronumber;

		FindApproximation(pair.second, pair.result);
		for (int i = 0; i < 100; i++) pair.second[i] = '0';

		zeronumber = 0;
		for (int i = 0; i < 100 && pair.result[i] == '0'; i++) zeronumber++;
		pair.nzadp += 100 - zeronumber;

		MultiplicationOperation(pair.first, pair.result, pair.second);
		for (int i = 0; i < 100; i++) pair.result[i] = pair.second[i];

		pair = MultiplicationTransformation(pair);

		GiveMeAnswer(pair, '+');

		break;
/*
	case 'T':

		Testing();

		break;
*/
	default:
		printf("%s", "Ошибка ввода");
		break;
	}


	return 0;
}