#include <stdio.h>
#include <stdlib.h>
#include "mech.h"
#include "interfejs.h"

void Menu(){
    printf("SYSTEM ZARZADZANIA FLOTA MECHOW BOJOWYCH \n");
    printf("1. Dodaj nowego mecha \n");
    printf("2. Wyswietl wszystkie mechy \n");
    printf("3. Edytuj mecha \n");
    printf("4. Zdemontuj mecha \n");
    printf("5. Wyszkuja mecha \n");
    printf("6. Sortuj liste mechow \n");
    printf("7. Zapisz i opusc system \n");
    printf("Twoj wybor: ");
}

int main(int argc, char* argv[]) {
    if (argc < 2){
        printf("BLAD! Podaj nazwe pliku dla bazy danych \n");
        return 1;
    }

    char* filename = argv[1]; 
    printf("Witaj uzytkowniku! Uzywany plik: %s \n", filename);

    Node* lista = NULL;

    int running = 1;

    while (running == 1) {
        Menu();
        int choice = getInt();

        switch (choice){
            case 1:
                printf("Dodawanie mecha. \n");
                dodajMecha(&lista);
                pressEnterToContinue();
                break;

            case 2:
                printf("Wyswietlanie mecha. \n");
                wyswietlWszystko(lista);
                pressEnterToContinue();
                break;

            case 3:
                printf("Edytowanie mecha. \n");
                pressEnterToContinue();
                break;

            case 4:
                printf("Demontowanie mecha. \n");
                pressEnterToContinue();
                break;

            case 5:
                printf("Wyszukiwanie mecha. \n");
                pressEnterToContinue();
                break;

            case 6:
                printf("Sortowanie listy mechow. \n");
                pressEnterToContinue();
                break;

            case 7:
                printf("Zapisywanie i opuszczanie systemu. \n");
                pressEnterToContinue();
                break;

        // UZUPELNIC CASE'Y dodac funkcje do nich.
        }
    }

    return 0;

}
