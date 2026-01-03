#include <stdio.h>
#include <stdlib.h>
#include "interfejs.h"

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} 
}

int getInt() {
    int value;

    while (scanf("%d", &value) != 1) {
        printf("Blednia podana liczba, wpisz ponownie!");
        clearBuffer();
    }
    clearBuffer();
    return value;
}

void pressEnterToContinue(){
    printf("Nacisnij klawisz Enter, aby kontunowac.");
    getchar();
}