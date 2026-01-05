#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mech.h"
#include "interfejs.h"

void dodajMecha(Node** start) {
    Node* nowy = (Node*)malloc(sizeof(Node));
    if (nowy == NULL) {
        printf("BLAD! brak pamieci! \n");
        return;
    }


printf("---PROCES DODAWANIA MECHA--- \n");
printf("Podaj model (max 100 znakow): ");

fgets(nowy->dane.model, 100, stdin);

nowy->dane.model[strcspn(nowy->dane.model, "\n")] = 0;

printf("Podaj klase mecha: ");
fgets(nowy->dane.klasa, 50, stdin);
nowy->dane.klasa[strcspn(nowy->dane.klasa, "\n")] = 0;

printf("Podaj moc reaktora w zakresie 0-100: ");
nowy->dane.moc_reaktora = getInt(); 

printf("Podaj nazwe pilota: ");
fgets(nowy->dane.pilot, 100, stdin);
nowy->dane.pilot[strcspn(nowy->dane.pilot, "\n")] = 0;

printf("Podaj stan mecha (sprawny/uszkodzony/w naprawie): ");
fgets(nowy->dane.stan, 50, stdin);
nowy->dane.stan[strcspn(nowy->dane.stan, "\n")] = 0;

nowy->next = *start; 
*start = nowy;       
    
printf("SUKCES: Mech zostal prawdiwlowo dodany do ewidencji. \n");

}

void wyswietlWszystko(Node* start) {
    if (start == NULL){
        printf("Baza danych jest pusta.\n");
        return;
    }

printf("\n %-20s | %-15s | %-5s | %-15s | %-15s\n");
printf("MODEL", "KLASA", "MOC", "PILOT", "STAN");
    
Node* obecny = start;
while (obecny != NULL) {
    printf("%-20s | %-15s | %-5d | %-15s | %-15s\n", 
        obecny->dane.model, 
        obecny->dane.klasa, 
        obecny->dane.moc_reaktora, 
        obecny->dane.pilot, 
        obecny->dane.stan);

    obecny = obecny->next; 
    }
}