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
    printf("SUKCES! Baza zostala prawidlowo wczytana, wczytano %d mechow z pliku. \n", licznik);
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
    
void edytujMecha(Node* start) {
    if (start == NULL) {
        printf("baza danych jest pusta, nie mozna nic edytowac. \n");
        return;
    }

    char szukany[100];
    printf("podaj model mecha dla ktorego dane chcesz edytowac ");
    fgets(szukany, 100, stdin);
    szukany[strcspn(szukany, "\n")] = 0;

    Node* obecny = start;
    while (obecny != NULL) {
        if (strcmp(obecny->dane.model, szukany) == 0) {
            printf("\n EDYCJA MECHA ROZPOCZETA %s \n", obecny->dane.model);
            
            // edytowanie klasy
            printf("Obecna klasa to: %s. \n podaj nowa (lub Enter by zostawic)", obecny->dane.klasa);
            char bufor[100];
            fgets(bufor, 100, stdin);
            if (strcmp(bufor, "\n") != 0) {
                bufor[strcspn(bufor, "\n")] = 0;
                strcpy(obecny->dane.klasa, bufor);
            }

            // edytowanie mocy
            printf("Obecna moc to: %d. \n podaj nowa (lub wpisz -1 aby zostawic): ", obecny->dane.moc_reaktora);
            int nowaMoc;
            char buforMocy[20];
            fgets(buforMocy, 20, stdin);
            if (sscanf(buforMocy, "%d", &nowaMoc) == 1 && nowaMoc != -1) {
                obecny->dane.moc_reaktora = nowaMoc;
            }

            // edytowanie pilota
            printf("Obecny pilot to: %s. \n podaj nowego (lub Enter aby zostawic): ", obecny->dane.pilot);
            fgets(bufor, 100, stdin);
            if (strcmp(bufor, "\n") != 0) {
                bufor[strcspn(bufor, "\n")] = 0;
                strcpy(obecny->dane.pilot, bufor);
            }
            
            // edytowanie stanu
            printf("Obecny stan: %s. \n podaj nowy (lub Enter aby zostawic): ", obecny->dane.stan);
            fgets(bufor, 100, stdin);
            if (strcmp(bufor, "\n") != 0) {
                bufor[strcspn(bufor, "\n")] = 0;
                strcpy(obecny->dane.stan, bufor);
            }

            printf("SUKCES! Nowe dane dla tego mecha zostaly zaktualizowane do bazy. \n");
            return;
        }
        obecny = obecny->next;
    }

    printf("Nie ma takiego modelu w bazie: %s\n", szukany);
}

void sortujMechy(Node* start) {
    if (start == NULL || start->next == NULL) {
        printf("BLAD! Lista za krotka, nie da sie posortowac. \n");
        return;
    }

    printf("Sortowanie mechow malejaco wedlug parametru 'MOC REAKTORA' \n");

    int zamiana;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        zamiana = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (ptr1->dane.moc_reaktora < ptr1->next->dane.moc_reaktora) {
                Mech temp = ptr1->dane;
                ptr1->dane = ptr1->next->dane;
                ptr1->next->dane = temp;
                zamiana = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (zamiana);

    printf("SUKCES! Lista zostala posortowana pomyslnie (od najwiekszej mocy).\n");
}

void zwolnijPamiec(Node** start) {
    Node* obecny = *start;
    Node* nastepny;

    while (obecny != NULL) {
        nastepny = obecny->next;
        free(obecny);
        obecny = nastepny;
    }
    *start = NULL;
    printf("Pamiec zostala zwolniona. \n");
}