/* программа из вх. потока разбивает все предложения на слова (завершение ввода Ctrl+D) и подсчитывает номера строк, а затем - в каких строках встречается каждое слово.*/
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include "split.h"

using std::cin;            using std::cout;
using std::endl;           using std::getline;
using std::istream;        using std::string;
using std::vector;         using std::map;

// find all the lines that refer to each word in the input
map<string, vector<int> > //пробелы между int> > ОБЯЗАТЕЛЬНЫ!

/*
find_words() функция(см. ниже), кот. явл. 2-м аргументом ф-ции xref(). Если она не задана при вызове в кач. 2-го аргумента, то она станов. аргументгм по умолчанию и получает указатель на ф-цию split(), те она становится ф-ей split()  ТО:
xref(cin); Использует для отыскания слов во входном потоке функцию split.
xref(cin, find_urls); использует для отыскания слов функцию с именем find_urls
*/

	xref(istream& in,
	     vector<string> find_words(const string&) = split)
{
	string line;
	int line_number = 0;
	map<string, vector<int> > ret;

	// read the next line
	while (getline(in, line)) {
		++line_number;

		// break the input line into words. find_words() при вызове xref() с 1 аргументом по умлчанию становится ф-ей split() те она разбивает вх. предложение на отд. слова, сохраняя каждое из них в отдельном элементе vector<string>,  кот. затем приравнивается vector<string> words. ТО каждый элемент вектора words хранит отдельное СЛОВО из введенного ПРЕДЛОЖЕНИЯ.
		vector<string> words = find_words(line);

		// remember that each word occurs on the current line
#ifdef _MSC_VER
		for (std::vector<string>::const_iterator it = words.begin();
#else
		for (vector<string>::const_iterator it = words.begin();
#endif
		     it != words.end(); ++it)
			ret[*it].push_back(line_number);// *it возвращает слово из введенного и разбитого split() предложения, получ. из вх потока за один шаг цикла, а ret[*it] есть vector<int> из ОТОБРАЖЕНИЯ, куда и записываются знач. int line_number. Индексом для каждого номера строки явл. элемент из  vector<string> words, те СЛОВО из введенного ПРЕДЛОЖЕНИЯ. Те каждому слову из vector<string> words соотв. своя цифра, явл. номером вводимой строки, котор. сохраняется в vector<int> для каждой разбитой строки отображения map<string, vector<int> > ret; И если слово повторится в новой строке, то ей уже будет соотв. неск. цифр (как номера строк), что означает факт присутствия одного и того же слова в неск. строках.
	}
	return ret;
}

int main()
{
	// call `xref' using `split' by default
	map<string, vector<int> > ret = xref(cin);

	// write the results
#ifdef _MSC_VER
	for (std::map<string, vector<int> >::const_iterator it = ret.begin();
#else
	for (map<string, vector<int> >::const_iterator it = ret.begin();
#endif
	     it != ret.end(); ++it) {
		// write the word
		cout << it->first << " встречается в строке: ";

		// followed by one or more line numbers
#ifdef _MSC_VER
		std::vector<int>::const_iterator line_it = it->second.begin();
#else
		vector<int>::const_iterator line_it = it->second.begin();
#endif
		cout << *line_it;	// write the first line number

		++line_it; //начиная со след. значения, тк предыдущее уже выведено
		// write the rest of the line numbers, if any
		while (line_it != it->second.end()) {
			cout << ", " << *line_it;
			++line_it;
		}
		// write a new line to separate each word from the next
		cout << endl;
	}

	return 0;
}

/* ВЫВОД
alexander@alexander-Inspiron-3521:~/unix-source/chapter07/my_14_04_2017$ ./xref_14_04_17
aaa bbb ccc dddd
aaa bbb 2cc 3ddd
2cc встречается в строке: 2
3ddd встречается в строке: 2
aaa встречается в строке: 1, 2
bbb встречается в строке: 1, 2
ccc встречается в строке: 1
dddd встречается в строке: 1
*/
