#ifndef MECH_H
#define MECH_H

typedef struct {
    char model[101];
    char klasa[51];
    int moc_reaktora;
    char pilot[101];
    char stan[51];
} Mech;

typedef struct Node {
    Mech dane;
    struct Node* next;
} Node;

// przed case'ami
void wczytajZPliku(Node** start, const char* nazwaPliku);

// case 1
void dodajMecha(Node** start);

// case 2
void wyswietlWszystko(Node* start);

// case 3
void edytujMecha(Node* start);

// case 4
void usunMecha(Node** start);

// case 5
void wyszukajMecha(Node* start);

// case 6
void sortujMechy(Node* start);

// case 7
void zapiszDoPliku(Node* start, const char* nazwaPliku);

// case 8
void zwolnijPamiec(Node** start);

#endif