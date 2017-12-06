#include "Lista.h"
#include <iostream>

void CriaLista (Lista &L) {
    L = NULL;
}


void InsereRec (Lista&L, int x, bool& ok) {
    if (L==NULL){
        Lista Aux = new Node;
        Aux->info = x;
        Aux->next = NULL;
        L = Aux;
    }
    else if (x > L->info) {
        int aux = L->info;
        L->info = x;
        InsereRec(L->next, aux, ok);
    }
    else {
        InsereRec(L->next, x, ok);
    }
}

bool Vazia(Lista &L) {
    if (L==NULL) {
        return true;
    }
    else return false;
}
