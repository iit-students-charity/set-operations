#include "stdafx.h"
#include "Set.h"
#include <iostream>


void Sets::parse(string inputString)				// формат: A = { a, b, c, { a, d }, f, <a, b, g>. A, B}
{
	int position = 0;
	int SESize = 0;
	bool nameError = true;
	char name = NULL;
	parseOutput out;

	//	if (inputString.length() == 0)
	//ошибка длины (если передана пустая строка)

	// + проверка на правильность расстановки скобок (перва¤ и последн¤¤ всегда фигурные)

	for (int i = 0; i < inputString.length(); i++)
	{
		if (isupper(inputString[i]))
		{
			name = inputString[i];
			// + проверка на уникальность имени:     A = {1, 2, 3}     A = {4, 5}   -   ошибка
			nameError = false;
		}
		if (inputString[i] == '{')
		{
			position = i + 1;
			break;
		}
	}
	//	if (nameError)
	// ошибка имени (если им¤ не найдено перед множеством)

	in_sets.resize(in_sets.size() + 1);
	in_sets[in_sets.size() - 1].set_name = name;

	for (int i = position; i < inputString.length(); i = position)
	{
		if (islower(inputString[i]))
		{
			SESize = in_sets[in_sets.size() - 1].set_elements.size();				//SESize -- размер вектора set_elements для последнего элемента in_sets
			in_sets[in_sets.size() - 1].set_elements.resize(SESize + 1);
			in_sets[in_sets.size() - 1].set_elements[SESize].value = inputString[i];
			position++;
			continue;
		}
		if (isupper(inputString[i]))
		{
			SESize = in_sets[in_sets.size() - 1].set_elements.size();
			in_sets[in_sets.size() - 1].set_elements.resize(SESize + 1);
			in_sets[in_sets.size() - 1].set_elements[SESize].st.set_name = inputString[i];
			position++;
			continue;
		}
		if (inputString[i] == '{')
		{
			SESize = in_sets[in_sets.size() - 1].set_elements.size();
			in_sets[in_sets.size() - 1].set_elements.resize(SESize + 1);
			out = parse(inputString, position + 1, in_sets[in_sets.size() - 1].set_elements[SESize].st);
			position = out.position;
			in_sets[in_sets.size() - 1].set_elements[SESize].st = out.st;
			continue;
		}
		if (inputString[i] == '<')
		{
			SESize = in_sets[in_sets.size() - 1].set_elements.size();
			in_sets[in_sets.size() - 1].set_elements.resize(SESize + 1);
			out = parse(inputString, position + 1, in_sets[in_sets.size() - 1].set_elements[SESize].cort);
			position = out.position;
			in_sets[in_sets.size() - 1].set_elements[SESize].cort = out.cort;
			continue;
		}
		if (inputString[i] == '}')
			return;

		position++;
	}

	// + проверка на повторение элементов:     A = {1, 2, 2}   -   ошибка
	// + проверка вложенных множеств на наличие имени:     A = {1, 2}     B = {1, {1, 2}}   =>   B = {1, A}
	return;
}

Sets::parseOutput Sets::parse(string inputString, int position, set st)
{
	int SESize = 0;
	parseOutput out;

	for (int i = position; i < inputString.length(); i = position)
	{
		if (islower(inputString[i]))
		{
			SESize = st.set_elements.size();				
			st.set_elements.resize(SESize + 1);
			st.set_elements[SESize].value = inputString[i];
			position++;
			continue;
		}
		if (isupper(inputString[i]))
		{
			SESize = st.set_elements.size();
			st.set_elements.resize(SESize + 1);
			st.set_elements[SESize].st.set_name = inputString[i];
			position++;
			continue;
		}
		if (inputString[i] == '{')
		{
			SESize = st.set_elements.size();
			st.set_elements.resize(SESize + 1);
			out = parse(inputString, position + 1, st.set_elements[SESize].st);
			position = out.position;
			st.set_elements[SESize].st = out.st;
			continue;
		}
		if (inputString[i] == '<')
		{
			SESize = st.set_elements.size();
			st.set_elements.resize(SESize + 1);
			out = parse(inputString, position + 1, st.set_elements[SESize].cort);
			position = out.position;
			st.set_elements[SESize].cort = out.cort;
			continue;
		}
		if (inputString[i] == '}')
		{
			out.st = st;
			out.position = position + 1;
			return out;
		}

		position++;
	}
	out.st = st;
	out.position = position + 1;
	return out;
}

Sets::parseOutput Sets::parse(string inputString, int position, cortege cort)
{
	int SESize = 0;
	parseOutput out;

	for (int i = position; i < inputString.length(); i = position)
	{
		if (islower(inputString[i]))
		{
			SESize = cort.cortege_elements.size();
			cort.cortege_elements.resize(SESize + 1);
			cort.cortege_elements[SESize].value = inputString[i];
			position++;
			continue;
		}
		if (isupper(inputString[i]))
		{
			SESize = cort.cortege_elements.size();
			cort.cortege_elements.resize(SESize + 1);
			cort.cortege_elements[SESize].st.set_name = inputString[i];
			position++;
			continue;
		}
		if (inputString[i] == '{')
		{
			SESize = cort.cortege_elements.size();
			cort.cortege_elements.resize(SESize + 1);
			out = parse(inputString, position + 1, cort.cortege_elements[SESize].st);
			position = out.position;
			cort.cortege_elements[SESize].st = out.st;
			continue;
		}
		if (inputString[i] == '<')
		{
			SESize = cort.cortege_elements.size();
			cort.cortege_elements.resize(SESize + 1);
			out = parse(inputString, position + 1, cort.cortege_elements[SESize].cort);
			position = out.position;
			cort.cortege_elements[SESize].cort = out.cort;
			continue;
		}
		if (inputString[i] == '>')
		{
			out.cort = cort;
			out.position = position + 1;
			return out;
		}

		position++;
	}

	out.cort = cort;
	out.position = position + 1;
	return out;
}

void Sets::print(void)
{
	int number = number_of_elements();
	for (int i = 0; i < number; i++)
	{
		print(i);
		cout << endl;
	}

	return;
}

void Sets::print(int setNumber)
{
	cout << in_sets[setNumber].set_name << " = {";
	for (int i = 0; i < in_sets[setNumber].set_elements.size(); i++)
	{
		if (in_sets[setNumber].set_elements[i].value != NULL)
		{
			cout << in_sets[setNumber].set_elements[i].value;
			if (i != in_sets[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (in_sets[setNumber].set_elements[i].st.set_name != NULL)
		{
			cout << in_sets[setNumber].set_elements[i].st.set_name;
			if (i != in_sets[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (in_sets[setNumber].set_elements[i].st.set_elements.size() != 0)
		{
			print(in_sets[setNumber].set_elements[i].st);
			if (i != in_sets[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (in_sets[setNumber].set_elements[i].cort.cortege_elements.size() != 0)
		{
			print(in_sets[setNumber].set_elements[i].cort);
			if (i != in_sets[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
	}
	cout << "}";

	return;
}

void Sets::print(char setName)
{
	//
}

void Sets::print(set st)
{
	int number = number_of_elements(st);
	cout << "{";
	for (int i = 0; i < number; i++)
	{
		if (st.set_elements[i].value != NULL)
		{
			cout << st.set_elements[i].value;
			if (i != number - 1)
				cout << ", ";
			continue;
		}
		if (st.set_elements[i].st.set_elements.size() != 0)
		{
			print(st.set_elements[i].st);
			continue;
		}
		if (st.set_elements[i].cort.cortege_elements.size() != 0)
		{
			print(st.set_elements[i].cort);
			continue;
		}
	}
	cout << "}";
}

void Sets::print(cortege cort)
{
	int number = number_of_elements(cort);
	cout << "<";
	for (int i = 0; i < number; i++)
	{
		if (cort.cortege_elements[i].value != NULL)
		{
			cout << cort.cortege_elements[i].value;
			if (i != number - 1)
				cout << ", ";
			continue;
		}
		if (cort.cortege_elements[i].st.set_elements.size() != 0)
		{
			print(cort.cortege_elements[i].st);
			continue;
		}
		if (cort.cortege_elements[i].cort.cortege_elements.size() != 0)
		{
			print(cort.cortege_elements[i].cort);
			continue;
		}
	}
	cout << ">";
}



int Sets::number_of_elements(void)
{
	return in_sets.size();
}

int Sets::number_of_elements(set st)
{
	return st.set_elements.size();
}

int Sets::number_of_elements(cortege cort)
{
	return cort.cortege_elements.size();
}



int Sets::comparison(char el1, char el2) {
	if (el1 == el2) return 1;
	return 0;
}

int Sets::comparison(cortege cort1, cortege cort2) {
	int mark = 0;
	if ((cort1.cortege_elements.size() != cort2.cortege_elements.size()) || (cort1.cortege_elements.size() == 0)) return 0;

	for (int i = 0; i < cort1.cortege_elements.size(); i++) {

		if ((cort1.cortege_elements[i].value != NULL) && ((cort2.cortege_elements[i].value != NULL)))
		{
			if (comparison(cort1.cortege_elements[i].value, cort2.cortege_elements[i].value) == 1) mark = 1;
			else return 0;
		}

		if ((cort1.cortege_elements[i].cort.cortege_elements.size() != 0) && (cort2.cortege_elements[i].cort.cortege_elements.size() != 0))
		{
			if (comparison(cort1.cortege_elements[i].cort, cort2.cortege_elements[i].cort) == 1) mark = 1;
			else return 0;
		}
		if ((cort1.cortege_elements[i].st.set_elements.size() != 0) && (cort2.cortege_elements[i].st.set_elements.size() != 0))
		{
			if (comparison(cort1.cortege_elements[i].st, cort2.cortege_elements[i].st) == 1) mark = 1;
			else return 0;
		}

	}
	return mark;
}

int Sets::comparison(set st1, set st2) {
	int mark = 0;
	if (st1.set_elements.size() != st2.set_elements.size()) return 0;
	for (int i = 0; i < st1.set_elements.size(); i++) {
		mark = 0;
		for (int j = 0; j < st2.set_elements.size(); j++) {

			if ((st1.set_elements[i].value != NULL) && ((st2.set_elements[j].value != NULL)))
			{
				if (comparison(st1.set_elements[i].value, st2.set_elements[j].value) == 1) mark = 1;
			}

			if ((st1.set_elements[i].cort.cortege_elements.size() != 0) && (st2.set_elements[j].cort.cortege_elements.size() != 0))
			{
				if (comparison(st1.set_elements[i].cort, st2.set_elements[j].cort) == 1) mark = 1;
			}
			if ((st1.set_elements[i].st.set_elements.size() != 0) && (st2.set_elements[j].st.set_elements.size() != 0))
			{
				if (comparison(st1.set_elements[i].st, st2.set_elements[j].st) == 1) mark = 1;
			}
		}
		if (mark == 0) return 0;
	}
	return mark;
}


void Sets::check_help_union(char stName) {
	int mark = 0;
	for (int i = 0; i < help.size(); i++) {
		for (int j = 0; j < help[i].set_elements.size(); j++) {
			if (comparison(help[i].set_elements[j].value, stName) == 1) mark = 1;
		}
	}
	if (mark == 0) {
		help[help.size() - 1].set_elements.resize(help[help.size() - 1].set_elements.size() + 1);
		help[help.size() - 1].set_elements[help[help.size() - 1].set_elements.size() - 1].value = stName;
	}
}

void Sets::check_help_union(set st) {
	int mark = 0;
	for (int i = 0; i < help.size(); i++) {
		for (int j = 0; j < help[i].set_elements.size(); j++) {
			if (comparison(help[i].set_elements[j].st, st) == 1) mark = 1;
		}
	}
	if (mark == 0) {
		help[help.size() - 1].set_elements.resize(help[help.size() - 1].set_elements.size() + 1);
		help[help.size() - 1].set_elements[help[help.size() - 1].set_elements.size() - 1].st = st;
	}
}

void Sets::check_help_union(cortege cort) {
	int mark = 0;
	for (int i = 0; i < help.size(); i++) {
		for (int j = 0; j < help[i].set_elements.size(); j++) {
			if (comparison(help[i].set_elements[j].cort, cort) == 1) mark = 1;
		}
	}
	if (mark == 0) {
		help[help.size() - 1].set_elements.resize(help[help.size() - 1].set_elements.size() + 1);
		help[help.size() - 1].set_elements[help[help.size() - 1].set_elements.size() - 1].cort = cort;
	}
}

void Sets::unionn(char Name1, char Name2)
{
	help.clear();
	int x, y;
	x = -1; y = -1;
	help.resize(help.size() + 1);
	int number = number_of_elements();
	for (int i = 0; i < number; i++)
	{
		if (in_sets[i].set_name == Name1) x = i;
		if (in_sets[i].set_name == Name2) y = i;
	}
	if ((x == -1) || (y == -1)) cout << "Error union" << endl;
	else {
		unionn(x);
		unionn(y);
	}

	return;
}

void Sets::unionn(int setNumber)
{

	for (int i = 0; i < in_sets[setNumber].set_elements.size(); i++)
	{
		if (in_sets[setNumber].set_elements[i].value != NULL)
		{
			check_help_union(in_sets[setNumber].set_elements[i].value);
		}

		if (in_sets[setNumber].set_elements[i].cort.cortege_elements.size() != 0)
		{
			check_help_union(in_sets[setNumber].set_elements[i].cort);
		}
		if (in_sets[setNumber].set_elements[i].st.set_elements.size() != 0) {
			check_help_union(in_sets[setNumber].set_elements[i].st);
		}
	}

	return;
}

void Sets::print_union(void)
{
	int number = help.size();
	for (int i = 0; i < number; i++)
	{
		print_union(i);
		cout << endl;
	}

	return;
}

void Sets::print_union(int setNumber)
{
	cout << "Union = {";
	for (int i = 0; i < help[setNumber].set_elements.size(); i++)
	{
		if (help[setNumber].set_elements[i].value != NULL)
		{
			cout << help[setNumber].set_elements[i].value;
			if (i != help[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (help[setNumber].set_elements[i].st.set_name != NULL)
		{
			cout << help[setNumber].set_elements[i].st.set_name;
			if (i != help[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (help[setNumber].set_elements[i].st.set_elements.size() != 0)
		{
			print(help[setNumber].set_elements[i].st);
			if (i != help[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (help[setNumber].set_elements[i].cort.cortege_elements.size() != 0)
		{
			print(help[setNumber].set_elements[i].cort);
			if (i != help[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
	}
	cout << "}";

	return;
}



void Sets::intersection(char Name1, char Name2)
{
	help_intersection.clear();
	int x, y;
	x = -1; y = -1;
	help_intersection.resize(help_intersection.size() + 1);
	int number = number_of_elements();
	for (int i = 0; i < number; i++)
	{
		if (in_sets[i].set_name == Name1) x = i;
		if (in_sets[i].set_name == Name2) y = i;
	}
	if ((x == -1) || (y == -1)) cout << "Error intersection" << endl;
	else intersection(x, y);

	return;
}

void Sets::intersection(int setNumber1, int setNumber2)
{

	for (int i = 0; i < in_sets[setNumber1].set_elements.size(); i++)
	{
		for (int j = 0; j < in_sets[setNumber2].set_elements.size(); j++)
		{
			if ((in_sets[setNumber1].set_elements[i].value != NULL) && (in_sets[setNumber2].set_elements[j].value != NULL))
			{
				if (comparison(in_sets[setNumber1].set_elements[i].value, in_sets[setNumber2].set_elements[j].value) == 1) {
					help_intersection[help_intersection.size() - 1].set_elements.resize(help_intersection[help_intersection.size() - 1].set_elements.size() + 1);
					help_intersection[help_intersection.size() - 1].set_elements[help_intersection[help_intersection.size() - 1].set_elements.size() - 1].value = in_sets[setNumber2].set_elements[j].value;
				}

			}

			if ((in_sets[setNumber1].set_elements[i].cort.cortege_elements.size() != 0) && (in_sets[setNumber2].set_elements[j].cort.cortege_elements.size() != 0))
			{
				if (comparison(in_sets[setNumber1].set_elements[i].cort, in_sets[setNumber2].set_elements[j].cort) == 1) {
					help_intersection[help_intersection.size() - 1].set_elements.resize(help_intersection[help_intersection.size() - 1].set_elements.size() + 1);
					help_intersection[help_intersection.size() - 1].set_elements[help_intersection[help_intersection.size() - 1].set_elements.size() - 1].cort = in_sets[setNumber2].set_elements[j].cort;
				}
			}
			if ((in_sets[setNumber1].set_elements[i].st.set_elements.size() != 0) && (in_sets[setNumber2].set_elements[j].st.set_elements.size() != 0))
			{
				if (comparison(in_sets[setNumber1].set_elements[i].st, in_sets[setNumber2].set_elements[j].st) == 1) {
					help_intersection[help_intersection.size() - 1].set_elements.resize(help_intersection[help_intersection.size() - 1].set_elements.size() + 1);
					help_intersection[help_intersection.size() - 1].set_elements[help_intersection[help_intersection.size() - 1].set_elements.size() - 1].st = in_sets[setNumber2].set_elements[j].st;
				}
			}
		}
	}

	return;
}

void Sets::print_intersection(void)
{
	int number = help_intersection.size();
	for (int i = 0; i < number; i++)
	{
		print_intersection(i);
		cout << endl;
	}

	return;
}

void Sets::print_intersection(int setNumber)
{
	cout << "Intersection = {";
	for (int i = 0; i < help_intersection[setNumber].set_elements.size(); i++)
	{
		if (help_intersection[setNumber].set_elements[i].value != NULL)
		{
			cout << help_intersection[setNumber].set_elements[i].value;
			if (i != help_intersection[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (help_intersection[setNumber].set_elements[i].st.set_name != NULL)
		{
			cout << help_intersection[setNumber].set_elements[i].st.set_name;
			if (i != help_intersection[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (help_intersection[setNumber].set_elements[i].st.set_elements.size() != 0)
		{
			print(help_intersection[setNumber].set_elements[i].st);
			if (i != help_intersection[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (help_intersection[setNumber].set_elements[i].cort.cortege_elements.size() != 0)
		{
			print(help_intersection[setNumber].set_elements[i].cort);
			if (i != help_intersection[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
	}
	cout << "}";

	return;
}


void Sets::difference(char Name1, char Name2)
{
	help_difference.clear();
	int x, y;
	x = -1; y = -1;
	help_difference.resize(help_difference.size() + 1);
	int number = number_of_elements();
	for (int i = 0; i < number; i++)
	{
		if (in_sets[i].set_name == Name1) x = i;
		if (in_sets[i].set_name == Name2) y = i;
	}
	if ((x == -1) || (y == -1)) cout << "Error difference" << endl;
	else difference(x, y);

	return;
}
void Sets::difference(int setNumber1, int setNumber2)
{

	for (int i = 0; i < in_sets[setNumber1].set_elements.size(); i++)
	{
		int metka_v = 0;
		int metka_c = 0;
		int metka_m = 0;

		for (int j = 0; j < in_sets[setNumber2].set_elements.size(); j++)
		{
			if ((in_sets[setNumber1].set_elements[i].value != NULL) && (in_sets[setNumber2].set_elements[j].value != NULL))
			{

				if (comparison(in_sets[setNumber1].set_elements[i].value, in_sets[setNumber2].set_elements[j].value) == 1) {
					metka_v = 1;
				}

			}

			if ((in_sets[setNumber1].set_elements[i].cort.cortege_elements.size() != 0) && (in_sets[setNumber2].set_elements[j].cort.cortege_elements.size() != 0))
			{

				if (comparison(in_sets[setNumber1].set_elements[i].cort, in_sets[setNumber2].set_elements[j].cort) == 1) {
					metka_c = 1;
				}
			}
			if ((in_sets[setNumber1].set_elements[i].st.set_elements.size() != 0) && (in_sets[setNumber2].set_elements[j].st.set_elements.size() != 0))
			{
				if (comparison(in_sets[setNumber1].set_elements[i].st, in_sets[setNumber2].set_elements[j].st) == 1) {
					metka_m = 1;
				}
			}
		}
		if ((metka_v == 0) && (in_sets[setNumber1].set_elements[i].value != NULL)) {
			help_difference[help_difference.size() - 1].set_elements.resize(help_difference[help_difference.size() - 1].set_elements.size() + 1);
			help_difference[help_difference.size() - 1].set_elements[help_difference[help_difference.size() - 1].set_elements.size() - 1].value = in_sets[setNumber1].set_elements[i].value;
		}

		if ((metka_c == 0) && (in_sets[setNumber1].set_elements[i].cort.cortege_elements.size() != 0)) {
			help_difference[help_difference.size() - 1].set_elements.resize(help_difference[help_difference.size() - 1].set_elements.size() + 1);
			help_difference[help_difference.size() - 1].set_elements[help_difference[help_difference.size() - 1].set_elements.size() - 1].cort = in_sets[setNumber1].set_elements[i].cort;
		}

		if ((metka_m == 0) && (in_sets[setNumber1].set_elements[i].st.set_elements.size() != 0)) {
			help_difference[help_difference.size() - 1].set_elements.resize(help_difference[help_difference.size() - 1].set_elements.size() + 1);
			help_difference[help_difference.size() - 1].set_elements[help_difference[help_difference.size() - 1].set_elements.size() - 1].st = in_sets[setNumber1].set_elements[i].st;
		}
	}

	return;
}

void Sets::print_difference(void)
{
	int number = help_difference.size();
	for (int i = 0; i < number; i++)
	{
		print_difference(i);
		cout << endl;
	}

	return;
}
void Sets::print_difference(int setNumber)
{
	cout << " Difference= {";
	for (int i = 0; i < help_difference[setNumber].set_elements.size(); i++)
	{
		if (help_difference[setNumber].set_elements[i].value != NULL)
		{
			cout << help_difference[setNumber].set_elements[i].value;
			if (i != help_difference[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (help_difference[setNumber].set_elements[i].st.set_name != NULL)
		{
			cout << help_difference[setNumber].set_elements[i].st.set_name;
			if (i != help_difference[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (help_difference[setNumber].set_elements[i].st.set_elements.size() != 0)
		{
			print(help_difference[setNumber].set_elements[i].st);
			if (i != help_difference[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (help_difference[setNumber].set_elements[i].cort.cortege_elements.size() != 0)
		{
			print(help_difference[setNumber].set_elements[i].cort);
			if (i != help_difference[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
	}
	cout << "}";

	return;
}


void Sets::difference_sim(char Name1, char Name2)
{
	help_difference_sim.clear();
	int x, y;
	x = -1; y = -1;
	help_difference_sim.resize(help_difference_sim.size() + 1);
	int number = number_of_elements();
	for (int i = 0; i < number; i++)
	{
		if (in_sets[i].set_name == Name1) x = i;
		if (in_sets[i].set_name == Name2) y = i;
	}
	if ((x == -1) || (y == -1)) cout << "Error difference" << endl;
	else
	{
		difference_sim(x, y);
		difference_sim(y, x);
	}

	return;
}
void Sets::difference_sim(int setNumber1, int setNumber2)
{

	for (int i = 0; i < in_sets[setNumber1].set_elements.size(); i++)
	{
		int metka_v = 0;
		int metka_c = 0;
		int metka_m = 0;

		for (int j = 0; j < in_sets[setNumber2].set_elements.size(); j++)
		{
			if ((in_sets[setNumber1].set_elements[i].value != NULL) && (in_sets[setNumber2].set_elements[j].value != NULL))
			{

				if (comparison(in_sets[setNumber1].set_elements[i].value, in_sets[setNumber2].set_elements[j].value) == 1) {
					metka_v = 1;
				}

			}

			if ((in_sets[setNumber1].set_elements[i].cort.cortege_elements.size() != 0) && (in_sets[setNumber2].set_elements[j].cort.cortege_elements.size() != 0))
			{

				if (comparison(in_sets[setNumber1].set_elements[i].cort, in_sets[setNumber2].set_elements[j].cort) == 1) {
					metka_c = 1;
				}
			}
			if ((in_sets[setNumber1].set_elements[i].st.set_elements.size() != 0) && (in_sets[setNumber2].set_elements[j].st.set_elements.size() != 0))
			{
				if (comparison(in_sets[setNumber1].set_elements[i].st, in_sets[setNumber2].set_elements[j].st) == 1) {
					metka_m = 1;
				}
			}
		}
		if ((metka_v == 0) && (in_sets[setNumber1].set_elements[i].value != NULL)) {
			help_difference_sim[help_difference_sim.size() - 1].set_elements.resize(help_difference_sim[help_difference_sim.size() - 1].set_elements.size() + 1);
			help_difference_sim[help_difference_sim.size() - 1].set_elements[help_difference_sim[help_difference_sim.size() - 1].set_elements.size() - 1].value = in_sets[setNumber1].set_elements[i].value;
		}

		if ((metka_c == 0) && (in_sets[setNumber1].set_elements[i].cort.cortege_elements.size() != 0)) {
			help_difference_sim[help_difference_sim.size() - 1].set_elements.resize(help_difference_sim[help_difference_sim.size() - 1].set_elements.size() + 1);
			help_difference_sim[help_difference_sim.size() - 1].set_elements[help_difference_sim[help_difference_sim.size() - 1].set_elements.size() - 1].cort = in_sets[setNumber1].set_elements[i].cort;
		}

		if ((metka_m == 0) && (in_sets[setNumber1].set_elements[i].st.set_elements.size() != 0)) {
			help_difference_sim[help_difference_sim.size() - 1].set_elements.resize(help_difference_sim[help_difference_sim.size() - 1].set_elements.size() + 1);
			help_difference_sim[help_difference_sim.size() - 1].set_elements[help_difference_sim[help_difference_sim.size() - 1].set_elements.size() - 1].st = in_sets[setNumber1].set_elements[i].st;
		}
	}

	return;
}

void Sets::print_difference_sim(void)
{
	int number = help_difference_sim.size();
	for (int i = 0; i < number; i++)
	{
		print_difference_sim(i);
		cout << endl;
	}

	return;
}
void Sets::print_difference_sim(int setNumber)
{
	cout << " Symmetric difference= {";
	for (int i = 0; i < help_difference_sim[setNumber].set_elements.size(); i++)
	{
		if (help_difference_sim[setNumber].set_elements[i].value != NULL)
		{
			cout << help_difference_sim[setNumber].set_elements[i].value;
			if (i != help_difference_sim[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (help_difference_sim[setNumber].set_elements[i].st.set_name != NULL)
		{
			cout << help_difference_sim[setNumber].set_elements[i].st.set_name;
			if (i != help_difference_sim[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (help_difference_sim[setNumber].set_elements[i].st.set_elements.size() != 0)
		{
			print(help_difference_sim[setNumber].set_elements[i].st);
			if (i != help_difference_sim[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
		if (help_difference_sim[setNumber].set_elements[i].cort.cortege_elements.size() != 0)
		{
			print(help_difference_sim[setNumber].set_elements[i].cort);
			if (i != help_difference_sim[setNumber].set_elements.size() - 1)
				cout << ", ";
			continue;
		}
	}
	cout << "}";

	return;
}