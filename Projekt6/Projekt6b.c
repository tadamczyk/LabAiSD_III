/********************************
*        TOMASZ ADAMCZYK        *
*       Nr albumu: 243217       *
*      Informatyka II ROK       *
*     Projekt6b.c - ALL.12.5    *
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BST{
	struct BST *up, *left, *right;
	char key;
	int counter;
} charBST;

charBST *tree = NULL;

charBST *STWORZ(char key);
void KOMUNIKAT_WSTAW(char x);
void WSTAW(charBST **root, charBST *element);
void KOMUNIKAT_USUN(char x);
void KOMUNIKAT_USUN_JEST();
void KOMUNIKAT_USUN_BRAK();
charBST *MINIMUM(charBST *root);
charBST *USUN(charBST* root, char x);
int SZUKAJ(charBST *root, char x, int length);
void WYNIK_SZUKAJ(char x, int result);
void DRUKUJ(charBST *root);
void WYNIK_DRUKUJ(charBST *root);

charBST *STWORZ(char key){
	charBST *element = (charBST*) malloc(sizeof(charBST));
	element->up = element->left = element->right = NULL;
	element->key = key;
	element->counter = 1;
	return element;
}

void KOMUNIKAT_WSTAW(char x){
	printf("+ \'%c\'\n", x);
}

void WSTAW(charBST **root, charBST *element){
	if (!(*root)){
		*root = element;
		KOMUNIKAT_WSTAW(element->key);
		return;
	}
	else{
		if (element->key < (*root)->key)
			WSTAW(&(*root)->left, element);
		else if (element->key > (*root)->key)
			WSTAW(&(*root)->right, element);
		else if (element->key == (*root)->key){
			(*root)->counter++;
			KOMUNIKAT_WSTAW(element->key);
		}
	}
}

void KOMUNIKAT_USUN(char x){
	printf("- \'%c\': ", x);
}

void KOMUNIKAT_USUN_JEST(){
	printf("usunieto\n");
}

void KOMUNIKAT_USUN_BRAK(){
	printf("nie ma takiego wezla\n");
}

charBST *MINIMUM(charBST *root){
	charBST* tmp = root;
	while (tmp->left != NULL)
		tmp = tmp->left;
	return tmp;
}

charBST *USUN(charBST *root, char x){
	if (root == NULL)
		return root;
	if (SZUKAJ(root, x, 0) == -1){
    KOMUNIKAT_USUN(x);
    KOMUNIKAT_USUN_BRAK();
		return root;
	}
	if (x < root->key)
		root->left = USUN(root->left, x);
	else if (x > root->key)
		root->right = USUN(root->right, x);
	else{
		if (root->left == NULL){
			charBST *tmp = root->right;
			free(root);
      KOMUNIKAT_USUN(x);
      KOMUNIKAT_USUN_JEST();
			return tmp;
		}
		else if (root->right == NULL){
			charBST *tmp = root->left;
			free(root);
      KOMUNIKAT_USUN(x);
      KOMUNIKAT_USUN_JEST();
			return tmp;
		}
		charBST *tmp = MINIMUM(root->right);
    KOMUNIKAT_USUN(x);
    KOMUNIKAT_USUN_JEST();
		root->key = tmp->key;
		root->counter = tmp->counter;
		root->right = USUN(root->right, tmp->key);
	}
	return root;
}

int SZUKAJ(charBST *root, char x, int length){
	if (root){
		if (root->key == x)
			return length;
		else{
			if (x < root->key)
				SZUKAJ(root->left, x, ++length);
			else
				SZUKAJ(root->right, x, ++length);
		}
	}
	else
		return -1;
}

void WYNIK_SZUKAJ(char x, int result){
	if (result == -1)
		printf("? \'%c\': nie ma takiego wezla\n", x);
	else
		printf("? \'%c\': jest taki wezel, jego glebokosc wynosi %d\n", x, result);
}

void DRUKUJ(charBST *root){
	if (root){
		DRUKUJ(root->left);
		printf("%c %d\n", root->key, root->counter);
		DRUKUJ(root->right);
	}
}

void WYNIK_DRUKUJ(charBST *root){
	printf("\nAktualne drzewo:\n");
	DRUKUJ(root);
	printf("\n");
}

int main(){
	WSTAW(&tree, STWORZ('k'));
	WSTAW(&tree, STWORZ('i'));
	WSTAW(&tree, STWORZ('a'));
	WSTAW(&tree, STWORZ('m'));
	WSTAW(&tree, STWORZ('l'));
	WYNIK_DRUKUJ(tree);
	WYNIK_SZUKAJ('j', SZUKAJ(tree, 'j', 0));
	WSTAW(&tree, STWORZ('j'));
	WSTAW(&tree, STWORZ('d'));
	WSTAW(&tree, STWORZ('k'));
	WSTAW(&tree, STWORZ('n'));
	USUN(tree, 'i');
	WSTAW(&tree, STWORZ('j'));
	USUN(tree, 'j');
	WYNIK_DRUKUJ(tree);
	WYNIK_SZUKAJ('j', SZUKAJ(tree, 'j', 0));
	WYNIK_SZUKAJ('s', SZUKAJ(tree, 's', 0));
	WSTAW(&tree, STWORZ('s'));
	WYNIK_DRUKUJ(tree);
	USUN(tree, 'j');
	USUN(tree, 'k');
	USUN(tree, 'z');
	WYNIK_DRUKUJ(tree);
	WYNIK_SZUKAJ('s', SZUKAJ(tree, 's', 0));
	WYNIK_SZUKAJ('z', SZUKAJ(tree, 'z', 0));
	return 0;
}
