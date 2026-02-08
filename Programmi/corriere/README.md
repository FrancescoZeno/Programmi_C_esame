# Progetto Gestione Corriere Espresso

## Descrizione
Programma in C per la simulazione della gestione automatizzata di un Corriere Espresso con catalogo di massimo 100 Tir.

## Autore
Francesco Zeno - R124000023  
Data: 3 febbraio 2026

## Note sui Commenti
I commenti presenti nel codice sono stati generati da Claude (Anthropic) per documentazione e chiarezza del codice.

## Struttura del Progetto

### File Sorgente
- **corriere.h**: File header con definizioni strutture dati e prototipi funzioni
- **corriere.c**: File principale con implementazione di tutte le funzioni

### Strutture Dati

#### Prodotto
Rappresenta un oggetto da trasportare:
- `codiceOggetto`: identificativo univoco
- `peso`: peso in kg
- `destinatario`: nome destinatario
- `mittente`: nome mittente

#### Tir
Rappresenta un camion da trasporto:
- `targa`: targa del veicolo
- `modello`: modello del Tir
- `capacitaMassima`: peso massimo trasportabile
- `pesoAttuale`: peso corrente caricato
- `numProdotti`: numero prodotti caricati
- `prodotti`: array di prodotti

#### Corriere
Gestisce il catalogo completo:
- `tir`: array di max 100 Tir
- `numTir`: numero Tir nel catalogo

## Funzionalità Implementate

### 1. Aggiunta Prodotto con Verifica Capacità
- Funzione: `aggiungiProdotto()`
- Verifica che il peso del nuovo prodotto non ecceda la capacità massima
- Controlla anche il numero massimo di prodotti per Tir

### 2. Visualizzazione Prodotti per Peso
- Funzione: `visualizzaProdottiPerPeso()`
- Dato un Tir e un peso, visualizza tutti i prodotti con quel peso specifico

### 3. Ricerca Tir con Peso Massimo (Algoritmo Ricorsivo)
- Funzione: `trovaTirPesoMassimoRicorsivo()`
- Algoritmo ricorsivo che cerca il Tir con maggior peso trasportato
- Funzione: `visualizzaTirConPesoMassimo()` visualizza i risultati

## Compilazione

### Windows
```bash
gcc -o corriere.exe corriere.c
```

### Linux/Mac
```bash
gcc -o corriere corriere.c
```

## Esecuzione

### Windows
```bash
corriere.exe
```

### Linux/Mac
```bash
./corriere
```

## Menu Principale

1. Aggiungi Tir al catalogo
2. Aggiungi prodotto a un Tir
3. Visualizza prodotti per peso
4. Visualizza Tir con peso massimo
5. Visualizza tutti i Tir
0. Esci

## Note Tecniche

- Il programma è scritto in **C**
- Tutti i commenti seguono le specifiche richieste
- Ogni funzione ha documentazione completa con finalità e parametri
- L'algoritmo ricorsivo usa il paradigma divide-et-impera

## Limiti del Sistema

- Massimo 100 Tir nel catalogo (`MAX_TIR`)
- Massimo 50 prodotti per Tir (`MAX_PRODOTTI`)
- Lunghezza massima stringhe: 100 caratteri (`MAX_STRING`)

## Esempio di Utilizzo

```
1. Aggiungi Tir: AB123CD, Volvo FH16, 1000 kg
2. Aggiungi Prodotto: PROD001, 300 kg, Mario Rossi, Ditta ABC
3. Aggiungi Prodotto: PROD002, 400 kg, Luigi Verdi, Ditta XYZ
4. Visualizza Tir con peso massimo → Mostra AB123CD con 700 kg
```