#include<iostream>
#include<string>
using namespace std;
void rulesnr(int &rulesnumber)
{
	cout << "Witaj w generatorze jezykow bezkontekstowych.\nUwaga! Program nie symuluje zachowania wykladnika potegi, ktory w kazdym przypadku jest rowny n o nieokreslonej wartosci.\nAby kontynuowac, wpisz liczbe regul produkcji, ktorych chcesz uzyc (max. 10):  ";
	cin >> rulesnumber;
	while (rulesnumber < 1 || rulesnumber>10)
	{
		cout << "Podaj liczbe wieksza od 0 i mniejsza od 10!\n";
		cin >> rulesnumber;
	}
	cout << "Podana liczba regul: " << rulesnumber << "\n";
}
void rules(int& rulesnumber, string(&left)[10], string(&right)[10])
{
	cout << endl;
	const int rn = rulesnumber;
	
	int control = 1;
	while (control == 1)
	{
		int control1 = 0;
		while (control1 == 0)
		{
			for (int i = 0; i < rulesnumber; i++)
			{
				cout << "Podaj lewa strone reguly nr. " << i + 1 << ": ";
				cin >> left[i];
				cout << "Podaj prawa strone reguly nr. " << i + 1 << "(ta po znaku '->'): ";
				cin >> right[i];
			}
			if (left[0] != "S")
			{
				cout << "Wyrazenie poczatkowe musi miec postac 'S'. " << endl<<endl;
			}
			else
			{
				control1 = 1;
			}
		}
		cout << endl << "Wprowadzone przez Ciebie reguly: " << endl;
		for (int i = 0; i < rulesnumber; i++)
		{
			cout << left[i] << "->" << right[i] << endl;
		}
		cout << "Jesli chcesz zmienic reguly, wprowadz 1. Jesli reguly sa poprawne, wprowadz 2. ";
		cin >> control;
		cout << endl;
	}
	for (int i = 0; i < rulesnumber; i++)
	{
		right[i] += '|';
	}
}
void builder(string &left_s, string(&options)[10], string(&result)[100])
{
	char cleft = left_s[0];
	int opt = 10 - count(options, options + 10, " ");
	string tabpom[100];
	int pointer = 0;
	int ressize = 100 - count(result, result + 100, " ");
	for (int i = 0; i < ressize; i++)//result chars
	{
		if (result[i] == left_s)
		{
			int reccount = 0;
			for (int j = 0; j < opt; j++)//all options
			{
				int recc = 0;
				for (int k = 0; k < options[j].size(); k++)//option chars
				{
					if (cleft == options[j][k])
					{
						recc = k;
						reccount++;
					}
				}
				if (recc != 0)
				{
					int size = options[j].size()-1;
					int a = 1;
					while (a <= size)
					{
						if (options[j][a] != cleft && a <= size && options[j][a]!=' ')
						{
							a++;
							options[j].insert(a, "^n");//dynamic letter change, table of 'n's and its values--
							size+=2;
							a++;
						}
						a++;
					}
				}
			}
			if(reccount > 0 && opt ==2)
			{
				string answer = "";
				string answer2;
				for (int j = 0; j < opt; j++)//all options
				{
					for (int k = 0; k < options[j].size(); k++)//option chars
					{
						if (cleft == options[j][k])//S found
						{
							options[j][k] = ' ';
							answer += "(";
							for (int l = 0; l < opt; l++)
							{
								if (l != j)
								{
									answer += options[l];
								}
							}
							k++;
							options[j].insert(k, answer);
							options[j] += ")";
							answer2 = options[j];
						}
					}
				}
				result[i] = answer2;
			}
			else if (reccount > 0 && opt>2)
			{
				string answer="";
				string answer2;
				for (int j = 0; j < opt; j++)//all options
				{
					for (int k = 0; k < options[j].size(); k++)//option chars
					{
						if (cleft == options[j][k])//S found
						{
							options[j][k] = ' ';
							answer = "(";
							for (int l = 0; l < opt; l++)
							{
								if (l != j)
								{
									answer += options[l];
									if (l != opt - 1)
									{
										answer += " + ";
									}
								}
							}
							answer += " ) ";
							k++;
							options[j].insert(k, answer);
							answer2 = options[j];
						}
					}
				}
				result[i] = answer2;
			}
			else if (opt > 1)
			{
				string answer = " ( ";
				for (int j = 0; j < opt; j++)
				{
					answer += options[j];
					if (j != opt - 1)
					{
						answer += " + ";
					}
				}
				answer += " ) ";
				result[i] = answer;
			}
			else
			{
				result[i] = options[0];
			}
		}
	}
	for (int i = 0; i < ressize; i++)
	{
		if (result[i] != " ")
		{
			for (int j = 0; j < result[i].size(); j++)
			{
				tabpom[pointer] = result[i][j];
				pointer++;
			}
		}
	}
	for (int i = 0; i < 100; i++)
	{
		result[i] = tabpom[i];
	}
}
int main()
{
	int runner = 1;
	while (runner == 1)
	{
		int rulesnumber = 0;
		rulesnr(rulesnumber);
		string left[10];
		string right[10];
		rules(rulesnumber, left, right);
		string result[100];
		for (int i = 0; i < 100; i++)
		{
			result[i] = " ";
		}
		result[0] = "S";
		//Executer
		for (int i = 0; i < rulesnumber; i++)
		{
			string left_s = left[i];
			string options[10];
			for (int j = 0; j < 10; j++)
			{
				options[j] = " ";
			}
			int counter = 0;
			int linemarker = -1;
			for (int j = 0; j < right[i].size(); j++)
			{
				if (right[i][j] == '|')
				{
					for (int k = linemarker + 1; k < j; k++)
					{
						options[counter] += right[i][k];
					}
					counter++;
					linemarker = j;
				}
			}
			builder(left_s, options, result);
		}
		//Result
		int ressize = 100 - count(result, result + 100, "");
		for (int i = 0; i < ressize; i++)
		{
			for (int j = 0; j < result[i].size(); j++)
			{
				if (result[i][j] >= 'A' && result[i][j] <= 'Z')
				{
					string left_s = left[i];
					string options[10];
					int counter = 0;
					int linemarker = -1;
					for (int j = 0; j < right[i].size(); j++)
					{
						if (right[i][j] == '|')
						{
							for (int k = linemarker + 1; k < j; k++)
							{
								options[counter] += right[i][k];
							}
							counter++;
							linemarker = j;
						}
					}
					for (int j = 0; j < 10; j++)
					{
						options[j] = " ";
					}
					builder(left_s, options, result);
				}
			}
		}
		cout << "Wygenerowany jezyk: " << endl;
		for (int i = 0; i < ressize; i++)
		{
			cout << result[i];
		}
		cout << endl << "Aby ropoczac ponownie, wprowadz 1. Aby zakonczyc, wprowadz 2. ";
		cin >> runner;
	}
	cout<<endl << "Dziekuje za skorzystanie z programu. \nWykonal Marcin Bator.\n";
	return 0;
}