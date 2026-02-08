/* File Header - Gestione Corriere Espresso */

#ifndef CORRIERE_H
#define CORRIERE_H

#define MAX_TIR 100
#define MAX_PRODOTTI 50
#define MAX_STRING 100

typedef struct {
    char codiceOggetto[MAX_STRING];
    float peso;
    char destinatario[MAX_STRING];
    char mittente[MAX_STRING];
} Prodotto;

typedef struct {
    char targa[MAX_STRING];
    char modello[MAX_STRING];
    float capacitaMassima;
    float pesoAttuale;
    int numProdotti;
    Prodotto prodotti[MAX_PRODOTTI];
} Tir;

typedef struct {
    Tir tir[MAX_TIR];
    int numTir;
} Corriere;

/* Prototipi */
void inizializzaCorriere(Corriere *corriere);
void aggiungiTir(Corriere *corriere, const char *targa, const char *modello, float capacitaMassima);
int aggiungiProdotto(Corriere *corriere, int indiceTir, const char *codice, float peso, 
                     const char *destinatario, const char *mittente);
void visualizzaProdottiPerPeso(Corriere *corriere, int indiceTir, float peso);
void visualizzaTuttiTir(Corriere *corriere);
int trovaTirPesoMassimoRicorsivo(Corriere *corriere, int indice, int maxIndice, float maxPeso);
void visualizzaTirConPesoMassimo(Corriere *corriere);
void stampaMenu();
int trovaTirPerTarga(Corriere *corriere, const char *targa);

#endif /* CORRIERE_H */
