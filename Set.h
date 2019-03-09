#pragma once

#include <vector>
#include <string>

using namespace std;

class Sets
{
public:
	void parse(string inputString);
	int number_of_elements(void);
	void print(void);
	void unionn(char Name1, char Name2);
	void print_union(void);

	void intersection(char Name1, char Name2);
	void print_intersection(void);
	void difference(char Name1, char Name2);
	void print_difference(void);
	void difference_sim(char Name1, char Name2);
	void print_difference_sim(void);

private:
	struct set;
	struct cortege;
	struct element;
	struct parseOutput;

	struct set
	{
		char set_name;
		vector<element> set_elements;
		set(void)
		{
			set_name = NULL;
			set_elements.clear();
		}
	};

	struct cortege
	{
		vector<element> cortege_elements;
		cortege(void)
		{
			cortege_elements.clear();
		}
	};

	struct element
	{
		char value;
		cortege	cort;
		set	st;
		element(void)
		{
			value = NULL;
			cort.cortege_elements.clear();
			st.set_elements.clear();
		}
	};

	struct parseOutput
	{
		int position;
		set st;
		cortege cort;
		parseOutput(void)
		{
			position = NULL;
			st.set_elements.clear();
			cort.cortege_elements.clear();
		}
	};


	vector<set> in_sets, help, help_intersection, help_difference, help_difference_sim;


	struct parseOutput parse(string inputString, int position, set st);
	struct parseOutput parse(string inputString, int position, cortege cort);
	int number_of_elements(set st);
	int number_of_elements(cortege cort);
	void print(set st);
	void print(cortege cort);
	void check_help_union(char stName);
	void check_help_union(set st);
	void check_help_union(cortege cort);
	int comparison(set st1, set st2);
	int comparison(char el1, char el2);
	int comparison(cortege cort1, cortege cort2);

	void intersection(int SetNumber1, int SetNuumber2);
	void print_intersection(int SetNumber);
	void difference(int setNumber1, int setNumber2);
	void print_difference(int setNumber);

	void difference_sim(int setNumber1, int setNumber2);
	void print_difference_sim(int setNumber);
	void print(char setName);
	void print(int setNumber);
	void unionn(int setNumber1);
	void print_union(int setNumber);
};
