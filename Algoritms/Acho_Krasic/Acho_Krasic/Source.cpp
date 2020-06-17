#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include <stdio.h>
#include <time.h>

using namespace std;	

const int k = 26;
struct bohr_vrtx
{
	int next_vrtx[k], pat_num;
	bool flag;
	int suff_link;
	int auto_move[k], par;
	char symb;
	int suff_flink;
};

//БОР
vector<bohr_vrtx> bohr;

//Создание новой вершины бора
bohr_vrtx make_bohr_vrtx(int p, char c)
{
	bohr_vrtx v;
	memset(v.next_vrtx, 255, sizeof(v.next_vrtx));
	memset(v.auto_move, 255, sizeof(v.auto_move));
	v.par = p;
	v.symb = c;
	v.flag = false;
	v.suff_link = -1;
	v.suff_flink = -1;
	return v;
}

//Инициализация бора
void bohr_ini()
{
	bohr.push_back(make_bohr_vrtx(0, '$'));
}

//Массив свех добавленных строк
vector<string> pattern;

//Добавлнение строки в бор
void add_string_to_bohr(const string &s)
{
	int num = 0;
	for (int i = 0; i < s.length(); i++)
	{
		char ch = s[i] - 'a';

		if (bohr[num].next_vrtx[ch] == -1)
		{
			bohr.push_back(make_bohr_vrtx(num, ch));
			bohr[num].next_vrtx[ch] = bohr.size() - 1;
		}

		num = bohr[num].next_vrtx[ch];
	}

	bohr[num].flag = true;	
	pattern.push_back(s);
	bohr[num].pat_num = pattern.size() - 1;
}

//Проверка наличия строки в боре
bool is_string_in_bohr(const string& s)
{
	int num = 0;

	for (int i = 0; i < s.length(); i++)
	{
		char ch = s[i] - 'a';

		if (bohr[num].next_vrtx[ch] == -1)
		{
			return -1;
		}

		num = bohr[num].next_vrtx[ch];
	}
	return true;
}


//Создание автомата
int get_auto_move(int v, int ch);


int get_suff_link(int v)
{
	if (bohr[v].suff_link == -1)
	{
		if (v == 0 || bohr[v].par == 0)
		{
			bohr[v].suff_link = 0;
		}
		else
		{
			bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].par), bohr[v].symb);
		}
	}

	return bohr[v].suff_link;
}


int get_auto_move(int v, int ch)
{
	if (bohr[v].auto_move[ch] == -1)
		if (bohr[v].next_vrtx[ch] != -1)
		{
			bohr[v].auto_move[ch] = bohr[v].next_vrtx[ch];
		}
		else
			if (v == 0)
			{
				bohr[v].auto_move[ch] = 0;
			}
			else
			{
				bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
			}

	return bohr[v].auto_move[ch];
}


//Поиск хорошей суфиксной ссылки
int get_suff_flink(int v) 
{
	if (bohr[v].suff_flink == -1) 
	{
		int u = get_suff_link(v);

		if (u == 0)
		{
			bohr[v].suff_flink = 0;
		}
		else
		{
			bohr[v].suff_flink = (bohr[u].flag) ? u : get_suff_flink(u);
		}
	}

	return bohr[v].suff_flink;
}


//Поиск вхождений
void check(int v, int i) 
{
	for (int u = v; u != 0; u = get_suff_flink(u)) 
	{
		if (bohr[u].flag)
		{
			cout << i - pattern[bohr[u].pat_num].length() + 1 << " " << pattern[bohr[u].pat_num] << endl;
		}
	}
}


void find_all_pos(const string& s) 
{
	int u = 0;

	for (int i = 0; i < s.length(); i++) 
	{
		u = get_auto_move(u, s[i] - 'a');
		check(u, i + 1);
	}
}


void main()
{
	bohr_ini();
	add_string_to_bohr("abc");
	add_string_to_bohr("bcdc");
	add_string_to_bohr("cccb");
	add_string_to_bohr("bcdd");
	add_string_to_bohr("bbbc");

	unsigned start = clock();
	find_all_pos("abcdcbcddbbbcccbbbcccbb");
	unsigned stop = clock();
	cout << "\n\n\n" << (double)(stop - start) / CLOCKS_PER_SEC << 'c' << "\n\n\n";

	system("pause");
}