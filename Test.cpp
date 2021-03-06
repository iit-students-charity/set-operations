#include "stdafx.h"
#include "Set.h"
#include <conio.h>
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int main(void)
{
	Sets st;
	int n;

	ifstream in("input.txt");
	string s;
	in >> n;
	getline(in, s);
	for (int i = 0; i < n; i++) {
		string str = "";
		getline(in, str);
		st.parse(str);
	}

	in.close();

	st.print();
	cout << endl;

	int mark = 0;
	while (mark == 0) {

		char name1, q, name2;
		cout << "1 - Union of two sets\n";
		cout << "2 - Intersection of two sets\n";
		cout << "3 - Difference of two sets\n";
		cout << "4 - Symmetric difference of two sets\n";
		cout << "0 - exit\n";
		int key;
		cout << "Your choice: ";
		cin >> key;

		switch (key)
		{
		case 1:
			cout << "\nEnter the names of the two sets\n";
			cin >> name1 >> name2;
			st.unionn(name1, name2);
			st.print_union();
			break;

		case 2:
			cout << "\nEnter the names of the two sets\n";
			cin >> name1 >> name2;
			st.intersection(name1, name2);
			st.print_intersection();
			break;

		case 3:
			cout << "\nEnter the names of the two sets\n";
			cin >> name1 >> name2;
			st.difference(name1, name2);
			st.print_difference();
			break;

		case 4:
			cout << "\nEnter the names of the two sets\n";
			cin >> name1 >> name2;
			st.difference_sim(name1, name2);
			st.print_difference_sim();
			break;

		case 0:
			return 0;

		default:
			cout << "\nError! Repeat your choice\n";
			break;
		}
		cout << endl;

	}


	_getch();
	return 0;
}

//печать пустых множеств и кортежей
//исключения + исключения вместо cout << error