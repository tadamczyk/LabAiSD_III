/********************************
*        TOMASZ ADAMCZYK        *
*       Nr albumu: 243217       *
*      Informatyka II ROK       *
*     Projekt4.c - ALL.8.1      *
********************************/

#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;

struct Lista {
	string word;
	Lista *prev, *next;
};
Lista *head1 = NULL, *head2 = NULL, *head3 = NULL, *headCopy1 = NULL, *headCopy2 = NULL;

int ROZMIAR(Lista *);
void WSTAW(Lista **, string);
void USUN(Lista **, string);
void DRUKUJ(Lista *);
Lista SZUKAJ(Lista *);
void KASUJ(Lista *);
Lista *SCAL(Lista *, Lista *, Lista*);
Lista *BEZPOWTORZEN(Lista *);

int ROZMIAR(Lista *list){
	Lista *wsk = list;
	int l = 0;
	while (wsk!=NULL){
		l++;
		wsk = wsk->next;
	}
	return l;
}

void WSTAW(Lista **list, string slowo){
	Lista *wsk = new Lista;
	wsk->word = slowo;
	wsk->next = *list;
	*list = wsk;
}

void USUN(Lista **list, string slowo){
	Lista *wsk = *list;
	Lista *prev = NULL;
	while (wsk!=NULL && wsk->word!=slowo){
		prev = wsk;
		wsk = wsk->next;
	}
	if (wsk==NULL) cout << "Nie ma takiego slowa!" << endl;
	else{
		if (prev==NULL){
			(*list) = (*list)->next;
			delete(wsk);
		}
		else{
			prev->next = wsk->next;
			delete(wsk);
		}
		cout << "Podane slowo zostalo usuniete!" << endl;
	}
}

void DRUKUJ(Lista *list){
	Lista *wsk = list;
	if (list==NULL) cout << "Lista jest pusta!" << endl;
	else cout << "Lista zawiera "<< ROZMIAR(list) << " elementow:" << endl;
	while (wsk!=NULL){
		cout << wsk->word << endl;
		wsk = wsk->next;
	}
}

Lista SZUKAJ(Lista *list, string slowo){
	Lista *wsk = list;
	int i, l = 0;
	for (i=1; i<=ROZMIAR(list); i++){
		if (wsk->word==slowo){
			cout << i << ". " << wsk->word << endl;
			l++;
		};
		wsk = wsk->next;
	}
	if (l==0) cout << "Nie ma takiego slowa!" << endl;
	if (l!=0) return *list;
}

void KASUJ(Lista *list){
	Lista *wsk;
	while ((wsk=list)!=NULL){
		list = list->next;
		delete(wsk);
	}
	cout << "Lista zostala wyczyszczona!" << endl;
}

Lista *SCAL(Lista *jeden, Lista *dwa, Lista *trzy){
	Lista *wsk = jeden;
	while (wsk){
		WSTAW(&trzy, wsk->word);
		wsk = wsk->next;
	}
	wsk = dwa;
	while (wsk){
		WSTAW(&trzy, wsk->word);
		wsk = wsk->next;
	}
	cout << "Listy zostaly scalone!" << endl;
	DRUKUJ(trzy);
	//BEZPOWTORZEN(trzy);
	return trzy;
}

Lista *BEZPOWTORZEN(Lista *list){
	Lista *wsk = list, *p, *r;
	int l = 0;
	while (wsk){
		p = wsk;
		while (p->next)
			if (p->next->word == wsk->word){
				r = p->next;
				p->next = r->next;
				delete(r);
				l++;
			}
			else p = p->next;
		wsk = wsk->next;
	}
	if (l>0) cout << l << " duplikaty zostaly usuniete!" << endl;
	else cout << "Brak duplikatow!" << endl;
	DRUKUJ(list);
	return list;
}

int main(){
	ios_base::sync_with_stdio(0);
	string slowo;
	char wyb;
	int wybL, l = 0;
	do{
		printf("-----------------------------------------\n");
		printf("| A-dodaj,  D-usun,    W-szukaj         |\n");
		printf("| S-pokaz,  Q-kasuj,   X-usun duplikaty |\n");
		printf("| Z-scal,   E-zakoncz                   |\n");
		printf("-----------------------------------------\n");
		cout << ++l << ". Twoj wybor: " << endl;
		cin >> wyb;
		wyb = toupper(wyb);
		if (wyb!='E' && wyb!='Z'){
			cout << "Wybierz liste: 1 or 2" << endl;
			cin >> wybL;
		}
		switch (wyb){
		case 'A':
			cout << "Podaj slowo:" << endl;
			cin >> slowo;
			if (wybL == 1) WSTAW(&head1, slowo);
			else WSTAW(&head2, slowo);
			break;
		case 'D':
			cout << "Podaj slowo:" << endl;
			cin >> slowo;
			if (wybL == 1) USUN(&head1, slowo);
			else USUN(&head2, slowo);
			break;
		case 'W':
			cout << "Podaj slowo:" << endl;
			cin >> slowo;
			if (wybL == 1) SZUKAJ(head1, slowo);
			else SZUKAJ(head2, slowo);
			break;
		case 'S':
			if (wybL == 1) DRUKUJ(head1);
			else DRUKUJ(head2);
			break;
		case 'Q':
			if (wybL == 1) {KASUJ(head1); head1 = NULL;}
			else {KASUJ(head2); head2 = NULL;}
			break;
		case 'Z':
			head3 = SCAL(head1, head2, head3);
			head1 = NULL;
			head2 = NULL;
			break;
		case 'X':
			if (wybL == 1) {headCopy1 = head1; BEZPOWTORZEN(headCopy1);}
			else {headCopy2 = head2; BEZPOWTORZEN(headCopy2);}
			break;
		case 'E':
			return 0;
			break;
		default:
			break;
		}
	}
	while (wyb!='E');
	return 0;
}
