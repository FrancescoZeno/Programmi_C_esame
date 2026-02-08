/* File Header - Gioco Auto */

#ifndef GIOCO_AUTO_H
#define GIOCO_AUTO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LARGHEZZA 6
#define ALTEZZA 6
#define MAX_OSTACOLI 10
#define MAX_PASSI 100

// Colori ANSI
#define GIALLO "\033[43m"
#define VERDE "\033[42m"
#define RESET "\033[0m"
#define ROSSO "\033[41m"
#define BLU "\033[44m"

typedef struct {
    int x, y;
    int attivo;
} Ostacolo;

typedef struct {
    int x, y;
} Auto;

typedef struct {
    char griglia[ALTEZZA][LARGHEZZA];
    Auto vettura;
    Ostacolo ostacoli[MAX_OSTACOLI];
    int numOstacoli;
    int passo;
    int gameOver;
} Gioco;

void inizializzaGioco(Gioco *gioco);
void stampaGriglia(Gioco *gioco);
void creaOstacolo(Gioco *gioco);
void muoviOstacoli(Gioco *gioco);
void muoviAuto(Gioco *gioco);
int controllaCollisione(Gioco *gioco);
int ostacoloNellIntorno(Gioco *gioco);
void aggiornaGriglia(Gioco *gioco);
void pulisciSchermo();
void eseguiPasso(Gioco *gioco);
void avviaGioco();
void mostraMenu();

#endif