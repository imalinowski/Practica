//#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <random>
#include <string>
#include <fstream>
using namespace std;

string bin(int n,int l) {
	string a = "";
	while (n > 0) {
		a += to_string(n % 2);
		n /= 2;
	}
	while (a.length() < l)
		a += "0";
	reverse(a.begin(), a.end());
	return a;
}

int countStar(string line) {
	int c=0;
	for (auto i : line)
		if (i == '*')
			c++;
	return c;
}

struct letter {
	char l;//�����
	int q;//���-��
	int p;//����
};

class table {
	vector<letter>t = { {'�',10,1},{'�',3,3},{'�',5,2},{'�',3,3},{'�',5,2},{'�',9,1},{'�',2,5},{'�',2,5},{'�',8,1},{'�',4,2},{'�',6,2},{'�',4,2},{'�',5,2},{'�',8,1},{'�',10,1},{'�',6,2}
		,{'�',6,2},{'�',6,2},{'�',5,2},{'�',3,3},{'�',1,10},{'�',2,5},{'�',1,10},{'�',2,5},{'�',1,10}, {'�',1,10},{'�',1,10},{'�',2,5},{'�',2,5},{'�',1,10},{'�',1,10},{'�',3,3},{'*',3,0} };
public:
	table() {}
	table(vector<letter> t) {
		this->t = t;
	}
	letter* operator [](char a) {
		for (int i = 0; i < t.size(); i++)
			if (t[i].l == a)
				return &t[i];
		return nullptr;
	}
	letter* operator [](int a) {
		return &t[a];
	}
	void add(letter a) {
		t.push_back(a);
	}
};

//!!!!!!!!!!!!!!!!!!!!!!!!!����� ��������� ������ ��� - ������� ����� �������.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int main() {
	setlocale(LC_ALL, "Russian");
	char n = ' ';
	cout << "Input task num:";
	cin >> n;
	//������ ������� - ����� ������ ������ ��� �����(���������� [M;N])!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (n == '1') {
		int M, N;
		cout << "���������� [M;N]";
		cin >> M >> N;
		int maxDel=0;
		int num=0;
		for (int i = M; i <= N; i++) {
			int c=0;
			for (int j = 1; j <= i; j++)
				if (i % j == 0)	c++;
			if (c > maxDel) {
				maxDel = c;
				num = i;
			}
		}
		cout << "MaxDel: " << num << " with " << maxDel;
	}
	//������ �������: ����� ������� �����, ��������� ������� - ������ ��������� ��� ���.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (n == '2') {
		srand(time(0));
		int n = rand() % 100;
		int guess = n-1;
		while (guess != n) {
			cout << "Try to guess: ";
			cin >> guess;
			if (guess > n)
				cout << "n is less";
			else if (guess < n)
				cout << "n is greater";
			else {
				cout << "You guessed right!";
				break;
			}
			cout << endl;
		}
	}
	//������ ����� - ���-�� ������. ������ ������ - �� ����� ����� ������.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (n == '3') {
		int N;
		cout << "����������� ������: ";
		cin >> N;
		int* mas = new int[N];
		cout << "����� ������: ";
		for (int i = 0; i < N; i++) {
			cin >> mas[i];
		}
		int left = 0;
		int right = 0;
		for (int i = 0; i < pow(2, N); i++) {
			string way = bin(i,N);
			for (int j = 0; j < way.length(); j++)
				if (way[j] == '1')
					left += mas[j];
				else
					right += mas[j];
			if (left == right) {
				cout << "YES";
				break;
			}
			left = 0;
			right = 0;
		}
		if (left == 0 && right == 0)
			cout << "NO";
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (n == '4') {
		srand(time(0));
		fstream dic("dictionary.txt");
		if (!dic) {
			cout << "Error Openning dictionary!";
			return 0;
		}
		table shop;
		string firstSeven = "";
		int starFirst=0;
		string extra = "";
		int starEx = 0;
		bool ex=false;
		string hiword,word,word2;
		int score = 0;
		int hiscore=0;

		letter* templ;

		while(firstSeven.size()<7){
			templ = shop[rand() % 33];
			if (templ->q == 0)
				continue;
			templ->q--;
			firstSeven += templ->l;
		}
		starFirst = countStar(firstSeven);

		char game = 'y';
		while (game=='y') {
			dic.seekg(0);
			ex = false;

			cout << "������ 7 �����: ";
			for (auto i : firstSeven)
				cout << i << " ";
			//����� ��� �����
			int c = 0;
			while (c<134) {
				c++;
				templ = shop[rand() % 33];
				if (templ->q == 0)
					continue;
				templ->q--;
				extra += templ->l;
				break;
			}
			if (c == 134) {
				cout << "����� ���������!" << endl;
				break;
			}
			starEx = countStar(extra);
			cout << endl;
			cout << "��� �����: ";
			for (auto i : extra)
				cout << i << " ";
			cout << endl;

			while (!dic.eof()) {
				getline(dic, word);
				word2 = word;
				ex = false;
				score = 0;

				if (word.size() == 1)
					continue;
				for (auto i : extra)
					if (word.find(i) != -1) {
						word.erase(word.find(i), 1);
						ex = true;
						score += shop[i]->p;
					}
				for (auto i : firstSeven)
					if (word.find(i) != -1) {
						word.erase(word.find(i), 1);
						score += shop[i]->p;
					}

				if (word.size()>0 && word.size() < (starFirst + starEx) && (starEx > 0 || ex)) {
					if (score > hiscore) {
						hiword = word2;
						hiscore = score;
					}
				}
				else if (word == "" && score > hiscore && ex ) {
					hiword =  word2;
					hiscore = score;
				}
			}
			if (hiscore != 0)
				cout << "Found: >" << hiword << "< with score " << hiscore;
			else
				cout << "Didn't find word in dictionary!";
			cout << endl;
			cout << "����� ��� �����? y/n:";
			cin >> game;
		}
	}
	cout << endl;
	main();
}
