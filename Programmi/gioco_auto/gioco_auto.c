/*
 * Autore: Francesco Zeno - R124000023
 * Data: 8 febbraio 2026
 * Gioco Auto - Evita Ostacoli
 */

#include "gioco_auto.h"

void inizializzaGioco(Gioco *gioco) {
    int i, j;
    
    for (i = 0; i < ALTEZZA; i++) {
        for (j = 0; j < LARGHEZZA; j++) {
            gioco->griglia[i][j] = '.';
        }
    }
    
    gioco->vettura.x = LARGHEZZA / 2;
    gioco->vettura.y = ALTEZZA - 1;
    gioco->numOstacoli = 0;
    gioco->passo = 0;
    gioco->gameOver = 0;
    
    for (i = 0; i < MAX_OSTACOLI; i++) {
        gioco->ostacoli[i].attivo = 0;
    }
    
    srand(time(NULL));
}

void stampaGriglia(Gioco *gioco) {
    int i, j;
    
    printf("\n=== PASSO %d - AUTO EVITA OSTACOLI ===\n\n", gioco->passo);
    
    for (i = 0; i < ALTEZZA; i++) {
        printf("   ");
        for (j = 0; j < LARGHEZZA; j++) {
            char simbolo = gioco->griglia[i][j];
            
            // Zone di sicurezza (penultima e terzultima riga)
            if (i == ALTEZZA - 2 || i == ALTEZZA - 3) {
                printf("%s", VERDE);
            } else {
                printf("%s", GIALLO);
            }
            
            if (simbolo == 'A') {
                printf("%s[A]%s", ROSSO, RESET);
            } else if (simbolo == 'O') {
                printf("%s[O]%s", BLU, RESET);
            } else {
                printf(" . %s", RESET);
            }
        }
        printf("\n");
    }
    printf("\n[Zone Verdi = Sicurezza] | [O] = Ostacoli | [A] = Auto\n");
}

void creaOstacolo(Gioco *gioco) {
    int i;
    for (i = 0; i < MAX_OSTACOLI; i++) {
        if (!gioco->ostacoli[i].attivo) {
            gioco->ostacoli[i].x = rand() % LARGHEZZA;
            gioco->ostacoli[i].y = 0;
            gioco->ostacoli[i].attivo = 1;
            gioco->numOstacoli++;
            break;
        }
    }
}

void muoviOstacoli(Gioco *gioco) {
    int i, movimento;
    
    for (i = 0; i < MAX_OSTACOLI; i++) {
        if (gioco->ostacoli[i].attivo) {
            movimento = (rand() % 2) + 1;
            gioco->ostacoli[i].y += movimento;
            
            if (gioco->ostacoli[i].y >= ALTEZZA) {
                gioco->ostacoli[i].attivo = 0;
                gioco->numOstacoli--;
            }
        }
    }
}

/* Controlla presenza ostacoli nell'intorno dell'auto e la sposta di conseguenza */
void muoviAuto(Gioco *gioco) {
    int direzione = ostacoloNellIntorno(gioco);
    
    if (direzione == -1) {
        if (gioco->vettura.x > 0) gioco->vettura.x--;
    } else if (direzione == 1) {
        if (gioco->vettura.x < LARGHEZZA - 1) gioco->vettura.x++;
    }
}

int controllaCollisione(Gioco *gioco) {
    int i;
    for (i = 0; i < MAX_OSTACOLI; i++) {
        if (gioco->ostacoli[i].attivo &&
            gioco->ostacoli[i].x == gioco->vettura.x &&
            gioco->ostacoli[i].y == gioco->vettura.y) {
            return 1;
        }
    }
    return 0;
}

/* Rileva ostacoli nell'intorno dell'auto e determina direzione di fuga */
int ostacoloNellIntorno(Gioco *gioco) {
    int i, xAuto = gioco->vettura.x, yAuto = gioco->vettura.y;
    int pericolo[3] = {0, 0, 0};
    
    for (i = 0; i < MAX_OSTACOLI; i++) {
        if (gioco->ostacoli[i].attivo) {
            int xOst = gioco->ostacoli[i].x;
            int yOst = gioco->ostacoli[i].y;
            
            if (yOst >= yAuto - 2 && yOst <= yAuto) {
                if (xOst == xAuto - 1) pericolo[0] = 1;
                if (xOst == xAuto) pericolo[1] = 1;
                if (xOst == xAuto + 1) pericolo[2] = 1;
            }
        }
    }
    
    if (pericolo[1]) {
        if (!pericolo[0] && xAuto > 0) return -1;
        if (!pericolo[2] && xAuto < LARGHEZZA - 1) return 1;
        if (!pericolo[0] && xAuto > 0) return -1;
    }
    
    return 0;
}

void aggiornaGriglia(Gioco *gioco) {
    int i, j;
    
    for (i = 0; i < ALTEZZA; i++) {
        for (j = 0; j < LARGHEZZA; j++) {
            gioco->griglia[i][j] = '.';
        }
    }
    
    gioco->griglia[gioco->vettura.y][gioco->vettura.x] = 'A';
    
    for (i = 0; i < MAX_OSTACOLI; i++) {
        if (gioco->ostacoli[i].attivo) {
            gioco->griglia[gioco->ostacoli[i].y][gioco->ostacoli[i].x] = 'O';
        }
    }
}

void pulisciSchermo() {
    system("cls");
}

void eseguiPasso(Gioco *gioco) {
    gioco->passo++;
    
    creaOstacolo(gioco);
    muoviOstacoli(gioco);
    muoviAuto(gioco);
    
    if (controllaCollisione(gioco)) {
        gioco->gameOver = 1;
        printf("\n*** COLLISIONE! L'auto ha urtato un ostacolo! ***\n");
        return;
    }
    
    if (gioco->passo >= MAX_PASSI) {
        gioco->gameOver = 1;
        return;
    }
    
    aggiornaGriglia(gioco);
    stampaGriglia(gioco);
}

void avviaGioco() {
    Gioco gioco;
    time_t ultimoTempo;
    
    printf("\n*** === GIOCO AUTO - EVITA OSTACOLI === ***\n");
    printf("L'auto si muove automaticamente ogni secondo!\n");
    printf("Evita gli ostacoli per %d passi!\n\n", MAX_PASSI);
    printf("Premi CTRL+C per uscire durante il gioco\n\n");
    
    inizializzaGioco(&gioco);
    aggiornaGriglia(&gioco);
    
    pulisciSchermo();
    stampaGriglia(&gioco);
    
    ultimoTempo = time(NULL);
    
    while (!gioco.gameOver) {
        if (time(NULL) - ultimoTempo >= 1) {
            pulisciSchermo();
            eseguiPasso(&gioco);
            ultimoTempo = time(NULL);
        }
    }
    
    if (gioco.passo >= MAX_PASSI) {
        printf("\n*** COMPLIMENTI! Hai evitato tutti gli ostacoli! ***\n");
    }
    
    printf("\nPartita conclusa al passo %d\n", gioco.passo);
    printf("Premi INVIO per tornare al menu...");
    getchar();
}

void mostraMenu() {
    int scelta;
    
    do {
        pulisciSchermo();
        printf("\n*** ========== MENU PRINCIPALE ========== ***\n");
        printf("\n[1] Avvia nuova partita\n");
        printf("[2] Regole del gioco\n");
        printf("[0] Esci\n");
        printf("\nScegli un'opzione: ");
        
        if (scanf("%d", &scelta) != 1) {
            printf("Errore: inserisci un numero valido.\n");
            while (getchar() != '\n');
            printf("Premi INVIO per continuare...");
            getchar();
            continue;
        }
        
        switch (scelta) {
            case 1:
                avviaGioco();
                break;
            case 2:
                pulisciSchermo();
                printf("\n*** === REGOLE DEL GIOCO === ***\n\n");
                printf("- L'auto [A] parte dal centro della riga inferiore\n");
                printf("- Gli ostacoli [O] compaiono casualmente sulla prima riga\n");
                printf("- L'auto si muove automaticamente ogni secondo\n");
                printf("- Le zone VERDI sono quelle di sicurezza\n");
                printf("- Vinci se sopravvivi per %d passi\n", MAX_PASSI);
                printf("- Perdi se l'auto colpisce un ostacolo\n\n");
                printf("Premi INVIO per tornare al menu...");
                getchar(); getchar();
                break;
            case 0:
                printf("\nArrivederci!\n");
                break;
            default:
                printf("Opzione non valida. Riprova.\n");
                printf("Premi INVIO per continuare...");
                getchar(); getchar();
        }
    } while (scelta != 0);
}

int main() {
    mostraMenu();
    return 0;
}