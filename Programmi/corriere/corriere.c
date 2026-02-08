/* Programma Gestione Corriere Espresso
 * Autore: Francesco Zeno - R124000023
 * Data: 3 febbraio 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corriere.h"

void inizializzaCorriere(Corriere *corriere)
{
    corriere->numTir = 0;
}

void aggiungiTir(Corriere *corriere, const char *targa, const char *modello, float capacitaMassima)
{
    if (corriere->numTir >= MAX_TIR)
    {
        printf("Errore: Catalogo Tir pieno (massimo %d Tir).\n", MAX_TIR);
        return;
    }

    Tir *nuovoTir = &corriere->tir[corriere->numTir];
    strcpy(nuovoTir->targa, targa);
    strcpy(nuovoTir->modello, modello);
    nuovoTir->capacitaMassima = capacitaMassima;
    nuovoTir->pesoAttuale = 0.0;
    nuovoTir->numProdotti = 0;

    corriere->numTir++;
    printf("Tir aggiunto con successo: %s (%s) - Capacita': %.2f kg\n",
           targa, modello, capacitaMassima);
}

/* Aggiunge un prodotto al Tir specificato verificando la capacità */
int aggiungiProdotto(Corriere *corriere, int indiceTir, const char *codice, float peso,
                     const char *destinatario, const char *mittente)
{
    if (indiceTir < 0 || indiceTir >= corriere->numTir)
    {
        printf("Errore: Indice Tir non valido.\n");
        return 0;
    }

    Tir *tir = &corriere->tir[indiceTir];

    if (tir->pesoAttuale + peso > tir->capacitaMassima)
    {
        printf("Errore: Capacita' massima superata! ");
        printf("(Attuale: %.2f kg, Disponibile: %.2f kg, Richiesto: %.2f kg)\n",
               tir->pesoAttuale, tir->capacitaMassima - tir->pesoAttuale, peso);
        return 0;
    }

    if (tir->numProdotti >= MAX_PRODOTTI)
    {
        printf("Errore: Numero massimo di prodotti raggiunto per questo Tir.\n");
        return 0;
    }

    Prodotto *nuovoProdotto = &tir->prodotti[tir->numProdotti];
    strcpy(nuovoProdotto->codiceOggetto, codice);
    nuovoProdotto->peso = peso;
    strcpy(nuovoProdotto->destinatario, destinatario);
    strcpy(nuovoProdotto->mittente, mittente);

    tir->pesoAttuale += peso;
    tir->numProdotti++;

    printf("Prodotto aggiunto con successo al Tir %s\n", tir->targa);
    printf("Peso attuale del Tir: %.2f/%.2f kg\n", tir->pesoAttuale, tir->capacitaMassima);

    return 1;
}

void visualizzaProdottiPerPeso(Corriere *corriere, int indiceTir, float peso)
{
    if (indiceTir < 0 || indiceTir >= corriere->numTir)
    {
        printf("Errore: Indice Tir non valido.\n");
        return;
    }

    Tir *tir = &corriere->tir[indiceTir];
    int trovati = 0;

    printf("\n========================================\n");
    printf("PRODOTTI DI PESO %.2f kg SUL TIR %s\n", peso, tir->targa);
    printf("========================================\n");

    for (int i = 0; i < tir->numProdotti; i++)
    {
        if (tir->prodotti[i].peso == peso)
        {
            printf("\nCodice: %s\n", tir->prodotti[i].codiceOggetto);
            printf("Peso: %.2f kg\n", tir->prodotti[i].peso);
            printf("Mittente: %s\n", tir->prodotti[i].mittente);
            printf("Destinatario: %s\n", tir->prodotti[i].destinatario);
            printf("----------------------------------------\n");
            trovati++;
        }
    }

    if (trovati == 0)
    {
        printf("Nessun prodotto trovato con peso %.2f kg.\n", peso);
    }
    else
    {
        printf("Totale prodotti trovati: %d\n", trovati);
    }
}

/* Funzione ricorsiva per trovare il Tir con peso massimo
 * Caso base: indice >= numTir
 * Caso ricorsivo: confronta e continua la ricerca
 */
int trovaTirPesoMassimoRicorsivo(Corriere *corriere, int indice, int maxIndice, float maxPeso)
{
    if (indice >= corriere->numTir)
    {
        return maxIndice;
    }

    int nuovoMaxIndice = maxIndice;
    float nuovoMaxPeso = maxPeso;

    if (corriere->tir[indice].pesoAttuale > maxPeso)
    {
        nuovoMaxIndice = indice;
        nuovoMaxPeso = corriere->tir[indice].pesoAttuale;
    }

    return trovaTirPesoMassimoRicorsivo(corriere, indice + 1, nuovoMaxIndice, nuovoMaxPeso);
}

void visualizzaTirConPesoMassimo(Corriere *corriere)
{
    if (corriere->numTir == 0)
    {
        printf("Nessun Tir presente nel catalogo.\n");
        return;
    }

    int maxIndice = trovaTirPesoMassimoRicorsivo(corriere, 0, 0, -1.0);
    Tir *tirMax = &corriere->tir[maxIndice];

    printf("\n========================================\n");
    printf("TIR CON PESO MASSIMO TRASPORTATO\n");
    printf("========================================\n");
    printf("Targa: %s\n", tirMax->targa);
    printf("Modello: %s\n", tirMax->modello);
    printf("Peso trasportato: %.2f kg\n", tirMax->pesoAttuale);
    printf("Capacita' massima: %.2f kg\n", tirMax->capacitaMassima);
    printf("Percentuale carico: %.2f%%\n",
           (tirMax->pesoAttuale / tirMax->capacitaMassima) * 100);

    printf("\n--- PRODOTTI TRASPORTATI ---\n");
    if (tirMax->numProdotti == 0)
    {
        printf("Nessun prodotto presente.\n");
    }
    else
    {
        for (int i = 0; i < tirMax->numProdotti; i++)
        {
            printf("\nProdotto %d:\n", i + 1);
            printf("  Codice: %s\n", tirMax->prodotti[i].codiceOggetto);
            printf("  Peso: %.2f kg\n", tirMax->prodotti[i].peso);
            printf("  Mittente: %s\n", tirMax->prodotti[i].mittente);
            printf("  Destinatario: %s\n", tirMax->prodotti[i].destinatario);
        }
    }
    printf("========================================\n");
}

void visualizzaTuttiTir(Corriere *corriere)
{
    printf("\n========================================\n");
    printf("CATALOGO TIR - Totale: %d\n", corriere->numTir);
    printf("========================================\n");

    if (corriere->numTir == 0)
    {
        printf("Nessun Tir presente.\n");
        return;
    }

    for (int i = 0; i < corriere->numTir; i++)
    {
        Tir *tir = &corriere->tir[i];
        printf("\n[%d] Targa: %s\n", i, tir->targa);
        printf("    Modello: %s\n", tir->modello);
        printf("    Capacita': %.2f kg\n", tir->capacitaMassima);
        printf("    Peso attuale: %.2f kg\n", tir->pesoAttuale);
        printf("    Prodotti: %d\n", tir->numProdotti);
        printf("    Spazio disponibile: %.2f kg\n",
               tir->capacitaMassima - tir->pesoAttuale);
    }
    printf("========================================\n");
}

int trovaTirPerTarga(Corriere *corriere, const char *targa)
{
    for (int i = 0; i < corriere->numTir; i++)
    {
        if (strcmp(corriere->tir[i].targa, targa) == 0)
        {
            return i;
        }
    }
    return -1;
}

void stampaMenu()
{
    printf("\n");
    printf("========================================\n");
    printf("    GESTIONE CORRIERE ESPRESSO\n");
    printf("========================================\n");
    printf("1. Aggiungi Tir al catalogo\n");
    printf("2. Aggiungi prodotto a un Tir\n");
    printf("3. Visualizza prodotti per peso\n");
    printf("4. Visualizza Tir con peso massimo\n");
    printf("5. Visualizza tutti i Tir\n");
    printf("0. Esci\n");
    printf("========================================\n");
    printf("Scelta: ");
}

int main()
{
    Corriere corriere;
    inizializzaCorriere(&corriere);

    int scelta;
    char targa[MAX_STRING], modello[MAX_STRING];
    float capacita, peso;
    char codice[MAX_STRING], destinatario[MAX_STRING], mittente[MAX_STRING];
    int indiceTir;

    printf("========================================\n");
    printf("SISTEMA GESTIONE CORRIERE ESPRESSO\n");
    printf("========================================\n");
    printf("Programma per la gestione automatizzata\n");
    printf("di un corriere con max %d Tir\n", MAX_TIR);
    printf("========================================\n");

    do
    {
        stampaMenu();
        scanf("%d", &scelta);
        getchar();

        switch (scelta)
        {
        case 1:
            printf("\n--- AGGIUNGI TIR ---\n");
            printf("Targa: ");
            fgets(targa, MAX_STRING, stdin);
            targa[strcspn(targa, "\n")] = 0;

            printf("Modello: ");
            fgets(modello, MAX_STRING, stdin);
            modello[strcspn(modello, "\n")] = 0;

            printf("Capacita' massima (kg): ");
            scanf("%f", &capacita);
            getchar();

            aggiungiTir(&corriere, targa, modello, capacita);
            break;

        case 2:
            if (corriere.numTir == 0)
            {
                printf("Nessun Tir presente. Aggiungere prima un Tir.\n");
                break;
            }

            visualizzaTuttiTir(&corriere);
            printf("\n--- AGGIUNGI PRODOTTO ---\n");
            printf("Indice Tir (0-%d): ", corriere.numTir - 1);
            scanf("%d", &indiceTir);
            getchar();

            printf("Codice prodotto: ");
            fgets(codice, MAX_STRING, stdin);
            codice[strcspn(codice, "\n")] = 0;

            printf("Peso (kg): ");
            scanf("%f", &peso);
            getchar();

            printf("Destinatario: ");
            fgets(destinatario, MAX_STRING, stdin);
            destinatario[strcspn(destinatario, "\n")] = 0;

            printf("Mittente: ");
            fgets(mittente, MAX_STRING, stdin);
            mittente[strcspn(mittente, "\n")] = 0;

            aggiungiProdotto(&corriere, indiceTir, codice, peso, destinatario, mittente);
            break;

        case 3:
            if (corriere.numTir == 0)
            {
                printf("Nessun Tir presente.\n");
                break;
            }

            visualizzaTuttiTir(&corriere);
            printf("\n--- VISUALIZZA PRODOTTI PER PESO ---\n");
            printf("Indice Tir (0-%d): ", corriere.numTir - 1);
            scanf("%d", &indiceTir);

            printf("Peso da cercare (kg): ");
            scanf("%f", &peso);
            getchar();

            visualizzaProdottiPerPeso(&corriere, indiceTir, peso);
            break;

        case 4:
            printf("\n--- RICERCA TIR CON PESO MASSIMO ---\n");
            visualizzaTirConPesoMassimo(&corriere);
            break;

        case 5:
            visualizzaTuttiTir(&corriere);
            break;

        case 0:
            printf("\nUscita dal programma...\n");
            break;

        default:
            printf("Scelta non valida.\n");
        }

        if (scelta != 0)
        {
            printf("\nPremere INVIO per continuare...");
            getchar();
        }

    } while (scelta != 0);

    return 0;
}
