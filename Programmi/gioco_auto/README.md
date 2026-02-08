# Gioco Auto - Evita Ostacoli

## Descrizione
Simulazione di un gioco colorato dove un'auto deve evitare automaticamente ostacoli che si muovono verso di essa su una griglia 6x6. L'auto si sposta automaticamente ogni secondo quando rileva ostacoli nella sua zona di pericolo. La griglia è colorata con sfondo giallo e zone di sicurezza verdi.

## Autore
Francesco Zeno - R124000023

## Data
8 febbraio 2026

## Note sui Commenti
I commenti nel codice sono stati generati da Claude (Anthropic), mantenuti essenziali per funzioni complesse e algoritmi di rilevamento ostacoli.

## Strutture Dati

### `Ostacolo`
- `int x, y`: posizione sulla griglia
- `int attivo`: flag per indicare se l'ostacolo è presente

### `Auto`
- `int x, y`: posizione dell'auto sulla griglia

### `Gioco`
- `char griglia[6][6]`: rappresentazione visuale del campo di gioco
- `Auto vettura`: struttura che rappresenta l'auto del giocatore
- `Ostacolo ostacoli[10]`: array di ostacoli presenti nel gioco
- `int numOstacoli`: contatore ostacoli attivi
- `int passo`: numero del turno corrente
- `int gameOver`: flag per termine partita

## Funzionalità Implementate

### Gestione del Gioco
- **inizializzaGioco()**: configura stato iniziale della partita
- **eseguiPasso()**: gestisce la logica di un singolo turno di gioco
- **avviaGioco()**: loop principale di una partita
- **mostraMenu()**: interfaccia utente con menu interattivo

### Meccaniche di Gioco
- **creaOstacolo()**: genera casualmente un nuovo ostacolo sulla prima riga
- **muoviOstacoli()**: sposta tutti gli ostacoli di 1-2 posizioni verso il basso
- **muoviAuto()**: implementa il movimento automatico dell'auto per evitare ostacoli
- **ostacoloNellIntorno()**: algoritmo di rilevamento ostacoli nella zona di pericolo
- **controllaCollisione()**: verifica scontri tra auto e ostacoli

### Visualizzazione
- **stampaGriglia()**: mostra lo stato corrente del gioco con colori ANSI
- **aggiornaGriglia()**: aggiorna la rappresentazione visiva
- **pulisciSchermo()**: pulisce il terminale per animazione fluida

### Sistema Temporizzazione
- **Movimento automatico**: l'auto si muove ogni secondo senza input utente
- **Animazione continua**: la griglia si aggiorna automaticamente
- **Controllo temporale**: usa time.h per gestire intervalli di 1 secondo

## Regole del Gioco

1. L'auto [A] (rossa) inizia al centro della riga inferiore
2. Ad ogni turno viene creato un ostacolo [O] (blu) in posizione casuale sulla prima riga
3. Gli ostacoli si muovono verso il basso di 1-2 posizioni casuali per turno
4. L'auto si muove automaticamente ogni secondo quando rileva ostacoli nella zona di pericolo
5. **Zone di sicurezza**: le ultime due righe prima dell'auto sono colorate di verde
6. **Colori della griglia**:
   - Sfondo giallo per le zone normali
   - Sfondo verde per le zone di sicurezza (penultima e terzultima riga)
   - Auto in rosso [A]
   - Ostacoli in blu [O]
7. La partita termina in caso di:
   - Collisione tra auto e ostacolo (sconfitta)
   - Completamento di 100 passi senza collisioni (vittoria)
8. **Controlli**: nessun input richiesto durante il gioco, movimento completamente automatico

## Compilazione ed Esecuzione

### Compilazione
```bash
gcc -o gioco_auto gioco_auto.c
```

### Esecuzione
```bash
./gioco_auto
```

### Requisiti di Sistema
- Compilatore GCC
- Sistema operativo Windows/Linux/macOS
- Terminale che supporta colori ANSI (Windows Terminal, PowerShell 7+, terminali Linux/Mac)
- Librerie standard C (stdio.h, stdlib.h, time.h)

## Limiti del Sistema

1. **Dimensione griglia fissa**: 6x6 celle non modificabile a runtime
2. **Numero massimo ostacoli**: limitato a 10 ostacoli contemporanei
3. **Algoritmo di evasione**: l'auto potrebbe rimanere bloccata in situazioni di ostacoli multipli
4. **Velocità di gioco fissa**: 1 secondo per passo, non modificabile
5. **Casualità**: il generatore di numeri casuali usa time() come seed
6. **Interfaccia**: solo testuale con colori ANSI, nessuna grafica avanzata
7. **Compatibilità colori**: alcuni terminali potrebbero non supportare i colori ANSI
8. **Controllo utente**: impossibile mettere in pausa o interrompere il gioco una volta iniziato (eccetto CTRL+C)
9. **Salvataggio**: non supporta salvataggio/caricamento partite

## Possibili Miglioramenti

- Implementazione di livelli di difficoltà con velocità variabile
- Controlli per pausa/resume durante il gioco
- Algoritmo di evasione più sofisticato con pathfinding
- Sistema di punteggio basato su ostacoli evitati e tempo di sopravvivenza
- Interfaccia grafica con librerie come SDL o ncurses
- Supporto per terminali senza colori ANSI (modalità compatibilità)
- Salvataggio statistiche giocatore e high scores
- Dimensioni griglia configurabili
- Effetti sonori per collisioni e vittorie