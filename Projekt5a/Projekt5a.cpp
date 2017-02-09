/********************************
*        TOMASZ ADAMCZYK        *
*       Nr albumu: 243217       *
*      Informatyka II ROK       *
*     Projekt5a.c - ALL.10.2    *
********************************/

#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#define CONST_C 4

using namespace std;

void readFromFile(string words[], int m){
	fstream file;
	file.open("in.in");
	if (file.good()){
		for (int a=0; a<(2*m); a++){
			getline(file, words[a]);
		}
	}
	file.close();
}

void putZeroToTab(int T[], int m){
	for (int a=0; a<m; a++){
		T[a] = 0;
  }
}

unsigned long long int strToInt(string word){
	unsigned long long int sum = (int) word[0];
	for (int i=1; i<(int) word.length(); i++){
		sum = sum*CONST_C + (int) word[i];
  }
	return sum;
}

int h(unsigned long long int k, int m){
	return k % m;
}

void hashInsert(string words[], int T[], int m){
	for (int a=0; a<(2*m); a++){
		unsigned long long int x = strToInt(words[a]);
		int w = h(x, m);
		T[w]++;
	}
}

void setAndViewResults(int nr, int T[], int m, char z){
	int count_0 = 0, countNot_0 = 0;
	int max = 0;
	double avg = 0.0;
	for (int a=0; a<m; a++){
		if (T[a]==0) count_0++;
		if (T[a]>max) max = T[a];
		if (T[a]>0){
			avg += T[a];
			countNot_0++;
		}
	}
	cout.precision(5);
	cout << z << " Test nr " << nr << ":\t\t\t\t"<< "m = " << m << endl;
	cout << "Ilosc zerowych pozycji w T[]:    \t" << count_0 << endl;
	cout << "Wartosc maksymalna w T[]:        \t" << max << endl;
	cout << "Srednia wartosc pozycji >0 w T[]:\t" << avg/countNot_0 << endl;
	cout << endl;
}

void testForM(int nr, int m, char z){
	string words[2*m];
	int T[m];
	readFromFile(words, m);
	putZeroToTab(T, m);
	hashInsert(words, T, m);
	setAndViewResults(nr, T, m, z);
}

int main(){
	ios_base::sync_with_stdio(0);
	srand(time(0));
	testForM(1, 1200, '-');
  testForM(2, 1223, '+');
  testForM(3, 1500, '-');
  testForM(4, 1453, '+');
  testForM(5, 1800, '-');
  testForM(6, 1823, '+');
	return 0;
}
