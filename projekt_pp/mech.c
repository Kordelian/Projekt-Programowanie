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

printf("\n %-20s | %-15s | %-5s | %-15s | %-15s\n", "MODEL", "KLASA", "MOC", "PILOT", "STAN");
    
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

void zapiszDoPliku(Node* start, const char* nazwaPliku) {
    FILE* plik = fopen(nazwaPliku, "w");
    if (plik == NULL) {
        printf("BLAD! Nie udalo sie otworzyc pliku do zapisu!\n");
        return;
    }

    Node* obecny = start;
    while (obecny != NULL) {
        fprintf(plik, "%s;%s;%d;%s;%s\n",
                obecny->dane.model,
                obecny->dane.klasa,
                obecny->dane.moc_reaktora,
                obecny->dane.pilot,
                obecny->dane.stan);

        obecny = obecny->next;
    }

    fclose(plik);
    printf("SUKCES! Baza danych zostala zapisan do pliku: %s\n", nazwaPliku);
}

void wczytajZPliku(Node** start, const char* nazwaPliku) {
    FILE* plik = fopen(nazwaPliku, "r");
    if (plik == NULL) {
        printf("Plik %s nie istnieje! Zostanie utworzony przy zapisie.\n", nazwaPliku);
        return;
    }

    char bufor[512]; 
    int licznik = 0;

    while (fgets(bufor, sizeof(bufor), plik)) {
        Node* nowy = (Node*)malloc(sizeof(Node));
        if (nowy == NULL) break;
    
    sscanf(bufor, "%[^;];%[^;];%d;%[^;];%[^\n]",
               nowy->dane.model,
               nowy->dane.klasa,
               &nowy->dane.moc_reaktora,
               nowy->dane.pilot,
               nowy->dane.stan);

        nowy->next = *start;
        *start = nowy;
        licznik++;
    }

    fclose(plik);
    printf("SUKCES! Baza zostala prawidlowo wczytana. \n");
}

void usunMecha(Node** start) {
    if (*start == NULL) {
        printf("Lista jest pusta, nie ma pozycji do usuniecia. \n");
        return;
    }

    char szukany[100];
    printf("Podaj nazwe modelu ktory chceszu usunac: ");
    
    fgets(szukany, 100, stdin);
    szukany[strcspn(szukany, "\n")] = 0;

    Node* obecny = *start;
    Node* poprzedni = NULL;

    while (obecny != NULL) {
        if (strcmp(obecny->dane.model, szukany) == 0) {
            if (poprzedni == NULL) {
                *start = obecny->next;
            } 
            else {
                poprzedni->next = obecny->next; 
            }

        free(obecny); 

        printf("SUKCES! Mech '%s' zostal pomyslnie usuniety z bazy danych. \n", szukany);
        return;
        }
        poprzedni = obecny;
        obecny = obecny->next;
    }
    printf("Nie znaleziono mecha o nazwie: %s \n", szukany);
}

void wyszukajMecha(Node* start) {
    if (start == NULL) {
        printf("Baza jest pusta. \n");
        return;
    }
    
    char szukany[100];
    printf("Podaj model do wyszukania: ");
    fgets(szukany, 100, stdin);
    szukany[strcspn(szukany, "\n")] = 0;

    printf("\n TWOJE WYNIKI WYSZUKIWANIA TO: \n");
    printf("%-20s | %-15s | %-5s | %-15s | %-15s \n", "MODEL", "KLASA", "MOC", "PILOT", "STAN");

    Node* obecny = start;
    int znaleziono = 0;

    while (obecny != NULL) {
        if (strstr(obecny->dane.model, szukany) != NULL) {
            printf("%-20s | %-15s | %-5d | %-15s | %-15s\n", 
                obecny->dane.model, 
                obecny->dane.klasa, 
                obecny->dane.moc_reaktora, 
                obecny->dane.pilot, 
                obecny->dane.stan);
            znaleziono = 1;
        }
        obecny = obecny->next;
    }

    if (znaleziono == 0) {
        printf("Brak wynikow dla frazy: '%s'\n", szukany);
    }

}