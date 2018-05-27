//файл реализации ф-ции split() - подсчитывает во вх. потоке кол-во слов в предложении, игнорируя лидирующие проб. символы.

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include "split.h"

using std::find_if;
using std::string;
using std::vector;

#ifndef _MSC_VER
using std::isspace;
#endif

// `true' если аргумент пробельный символ, ложь в обратном случае
bool space(char c)
{
	return isspace(c);
}

// `false' если арг. пробельный символ, `true' в противном случае
bool not_space(char c)
{
	return !isspace(c);
}

vector<string> split(const string& str)
{
	typedef string::const_iterator iter;
	vector<string> ret;

	iter i = str.begin();
	while (i != str.end()) {

		// игнорим лидирующие пробелы
		i = find_if(i, str.end(), not_space); //устанавливаем итератор на 1-й НЕ пробельный символ строки, те на 1-й символ СЛОВА в строке

		// ищем конец след. слова
		iter j = find_if(i, str.end(), space); //устанавливаем итератор на последний символ СЛОВА

		// копируем символы из `[i,' `j)' копируем слово, ограниченное этими итераторами
		if (i != str.end()) //те если ВСЯ строка НЕ пустая, то...
			ret.push_back(string(i, j));
		i = j; //подвигаем 1-й итератор i на позицию j и продолжаем поиск дальше начала СЛЕД. слова
	}
	return ret;
}

