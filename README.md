![License](https://img.shields.io/badge/License-MIT-green)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-yellow)
![Learning](https://img.shields.io/badge/Learning-C++-orange)

# Management school library v1.0

Programma per la gestione della biblioteca scolastica con tre entità di dati:
- Alunni - anagrafica studenti
- Libri - catalogo dei libri
- Prestiti - tracciamento prestiti e restituzioni

## Tecnologie uttilizzate
- Linguaggio: C++
- Strutture dati: srtuct per ogni entità di dati.
- Memorizzazione: array statici di struct per la gestine dei registri.
- Persistenza: file di testo per il salvataggio dei dati.

## Sistema di salvataggio
I dati dei registri vengono salvati in tre file separati:
- registro_libri.txt - Catalogo libri
- registro_alunni.txt - Anagrafica studenti
- registro_prestiti.txt - Storico dei prestiti

Il programma legge e scrive i dati record per record in maniera strutturata.

Il salvataggio viene effettuato:
- Manualmente - con la selezione della voce "Salva" del menù.
- Automaticamente all'uscita del programma se sono state fatte modifiche ai registri.

## Funzionalità:
Il programma è provvisto di un menu testuale che gestisce tutti i dati:

Menù Principale

1. Libri - Gestione catalogo bibliotecario
2. Alunni - Gestione delle anagrafiche degli studenti
3. Prestiti - Gestione prestiti/restituzioni
4. visualizza Libri - Consultazione catalogo
5. Visualizza Alunni - Consultazione anagrafica
6. Salva - Salvataggio dati
7. Esci - Uscita dal programma

Sottomenù Libri/Alunni

- Nuovo - Inserimento record
- Modifica - Aggiornamento dati
- Elimina - Rimozione record
- Esci - Ritorno al menu principale

Sottomenù Prestiti

- Nuovo prestito - Inserimento dati
- Restituzione libro - Chiusura del prestito
- Esci - Ritorno al menu principale

## Come usare il programma
1. Scarica la repository.
2. Compila il file `main.cpp` usando un compilatore C++.
3. Esegui il programma (`./biblioteca` su Linux/Mac o `biblioteca.exe` su Windows).
4. Scegli le operazioni da svolgere tramite il menù.

## Struttura file
```
biblioteca/
├── main.cpp              # Codice sorgente principale
├── registro_libri.txt    # Database libri (auto-generato)
├── registro_alunni.txt   # Database alunni (auto-generato)
└── registro_prestiti.txt # Database prestiti (auto-generato)
```

## Autore
Gabriele Henriet - [GitHub](https://github.com/Gabri-dev-C)

## Licenza
Questo progetto è rilasciato sotto licenza [MIT](https://opensource.org/licenses/MIT).

## Note:
All'avvio il programma crea automaticamente i file di database se non presenti e carica i dati nei registri.
