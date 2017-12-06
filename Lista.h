#pragma once
#ifndef Lista_H
#define Lista_H

typedef struct Node {
    int info;
    Node *next;
} Node;

typedef Node* Lista;

void CriaLista (Lista &L);

void InsereRec(Lista &L, int x, bool &ok);

bool Vazia (Lista&L);
#endif // Lista_H
