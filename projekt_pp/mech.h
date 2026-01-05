#ifndef MECH_H
#define MECH_H

typedef struct {
    char model[101];
    char klasa[51];
    float moc_reaktora;
    char pilot[101];
    char stan[51];
} Mech;

typedef struct Node {
    Mech dane;
    struct Node* next;
} Node;

void dodajMecha(Node** start);
void wyswietlWszystko(Node* start);

#endif