/********************************
*        TOMASZ ADAMCZYK        *
*       Nr albumu: 243217       *
*      Informatyka II ROK       *
*     Projekt5b.c - ALL.10.3    *
*        Wariant: W + OL        *
********************************/

#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#define CONST_C 4

using namespace std;

struct hashTable{
    int liczba;
    string nazwisko;
};

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

int H(unsigned long long int k, int i, int m){
    return (h(k, m)+i) % m;
}

void readFromFile(hashTable TH[], int m){
	fstream file;
	int tmp;
	file.open("in.in");
	if (file.good()){
		for (int a=0; a<m; a++){
            file >> tmp >> TH[a].nazwisko;
            TH[a].liczba = h(strToInt(TH[a].nazwisko), m);
		}
	}
	file.close();
}

void hashInsert(hashTable TH[], int T[], int m, double p){
	for (int a=0; a<(p*m); a++){
		unsigned long long int x = strToInt(TH[a].nazwisko);
		int w = h(x, m);
		T[w] = x;
	}
}

double hashInsertWithCounting(hashTable TH[], int T[], int m, double p){
    double wyn = 0.0;
    for (int a=p*m; a<((p*m)+(5*m)/100); a++){
    int i = 0;
        do{
            int j = H(TH[a].liczba, i, m);
            if (T[j]==0 || T[j]==-1){
                T[j] = TH[a].liczba;
                break;
            }
            i++;
        } while (i<m);
        if (i==m) wyn += m;
        else wyn += i;
    }
    return wyn;
}

void testForM(int m, double p){
    hashTable TH[m];
    int T[m];
    double wyn = 0.0;
    putZeroToTab(T, m);
    readFromFile(TH, m);
    hashInsert(TH, T, m, p);
    wyn = hashInsertWithCounting(TH, T, m, p)/(p*m) + 1.0;
    cout.precision(5);
    cout << "Test dla m = " << m << ";\t\tZapelnienie = " << p*100 << "%:" << endl;
    cout << "Srednia liczba prob wstawienia elementow = " << wyn << endl << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    testForM(6000, 0.5);
    testForM(6000, 0.7);
    testForM(6000, 0.9);
    testForM(9000, 0.5);
    testForM(9000, 0.7);
    testForM(9000, 0.9);
    testForM(12000, 0.5);
    testForM(12000, 0.7);
    testForM(12000, 0.9);
    testForM(15000, 0.5);
    testForM(15000, 0.7);
    testForM(15000, 0.9);
    testForM(20000, 0.5);
    testForM(20000, 0.7);
    testForM(20000, 0.9);
    testForM(17519, 0.5);
    testForM(17519, 0.7);
    testForM(17519, 0.9);
    return 0;
}
