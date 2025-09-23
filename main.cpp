#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct libro{			        // struttura libro
    int id;
    string titolo;
    string autore;
    int anno_pubblicazione;
    int disponibile;		    // stato del libro 1 disponibile, 0 non disponibile

};

struct alunno{			        // struttura alunno
    int id;
    string nome;
    string cognome;
    int classe;
    char sezione;
};

struct prestito{			    // struttura prestito, combina id libro e id alunno
    int id;
    int id_libro;
    int id_alunno;
    string data_prestito;
    string data_restituzione;
    int stato;			        // stato del prestito 1 attivo, 0 non attivo
    string note;
};

// crea tre file, uno per ogni registro,
// apre i file in lettura, se non riesce li crea.
// ritorna 1 in caso di errore
// ritorna 0 se andata a buon fine.
int crea_file();


// caricamento dati dai file, ritornano indice registro
int carica_dati_libri(libro registro[], int lunghezza);
int carica_dati_alunni(alunno registro[], int lunghezza);
int carica_dati_prestiti(prestito registro[], int lunghezza);

// salvataggio dati ritornano 0 se andate a buon fine
int salva_dati_libri(libro registro[], int lunghezza);
int salva_dati_alunni(libro registro[], int lunghezza);
int salva_dati_prestiti(libro registro[], int lunghezza);

// richiama tutte le funzioni salva_dati in una volta sola.
void salva_tutto(prestito registro_pre[], libro registro_lib[],
    alunno registro_alu[], int lunghezza_pre, int lunghezza_lib, int lunghezza_alu);

// interfaccia: crea i menu delle scelte
void crea_menu(string titolo_menu, string voci_menu);


// elaborazione libri

int dati_libri(libro registro[], int lunghezza, bool &modificato);      // controller principale
int nuovo_libro(libro registro[], int lunghezza, bool &modificato);     // CRUD
void modifica_libro(libro registro[], int lunghezza, bool &modificato); // CRUD
int elimina_libro(libro registro[], int lunghezza, bool &modificato);   // CRUD
void visualizza_libri(libro registro[], int lunghezza);                 // Funzionalita'
int cerca_libro(libro registro[], int lunghezza, string titolo);        // Utilita', ritorna l'indice
void visualizza_header_libro();                                         // Utilita'
void visualizza_libro(libro registro[], int indice);                    // Utilità'


// elaborazione alunni

int dati_alunni(alunno registro[], int lunghezza, bool &modificato);        // controller principale
int nuovo_alunno(alunno registro[], int lunghezza, bool &modificato);       // CRUD
void modifica_alunno(alunno registro[], int lunghezza, bool &modificato);   // CRUD
int elimina_alunno(alunno registro[], int lunghezza, bool &modificato);     // CRUD
void visualizza_alunni(alunno registro[], int lunghezza);                   // Funzionalita'
int cerca_alunno(alunno registro[], int lunghezza,
    string nome, int pos_ini = 0);                                          // Utilita'
void visualizza_header_alunno();                                            // Utilita'
void visualizza_alunno(alunno registro[], int indice);                      // Utilità'


// elaborazione prestiti

int dati_prestiti(prestito registro_pre[], libro registro_lib[],
    alunno registro_alu[],int lunghezza_pre, int lunghezza_lib,
    int lunghezza_alu, bool &modificato);                                   // Controller principale

int nuovo_prestito(prestito registro_pre[], libro registro_lib[],
    alunno registro_alu[], int lunghezza_pre, int lunghezza_lib,
    int lunghezza_alu, bool &modificato);                                   // CRUD

void restituzione_prestito(prestito registro_pre[], libro registro_lib[],
    alunno registro_alu[], int lunghezza_pre, int lunghezza_lib,
    int lunghezza_alu, bool &modificato);                                   // CRUD

int cerca_prestito(prestito registro_pre[], int lung_pre,
    int indice, int id_alunno);                                             // Utilità'

void visualizza_dati_prestito(prestito registro_pre[],
    int indice_prestito);                                                   // Utilità'

// Funzioni di utilita' generale
void strtocha(string scr, char dest[]);	    // da stringa a vettore di char
void chatostr(char scr[], string& dest);	// da vettore di char a stringa
void premi_invio();                         // premi invio per continuare
void pulisci_schermo();                     // per win e linux

int main(){
    libro registro_libri[200];              // vettore di libri
    alunno registro_alunni[200];            // vettore di alunni
    prestito registro_prestiti[2000];       // vettore di prestiti
    char scelta;
    string stringa_menu = "Libri;Alunni;Presiti;Visualizza libri;Visualizza Alunni;Salva;";

    // ogni funzione che modifica il numero di elementi dei registri
    // ritorna il numero aggiornato.
    int numero_libri = 0;
    int numero_alunni = 0;
    int numero_prestiti = 0;

    // se vengono fatte modifiche viene attivata.
    // viene passata alle funzioni per riferimento.
    bool flag_modifica = false;

    if(crea_file() != 0){
        cout << endl;
        cerr << "\tERRORE nella creazione dei file, il programma verra' chiuso\n\n";
        premi_invio();
        return 1;
    }

    // carica i dati dei libri nel registro
    if((numero_libri = carica_dati_libri(registro_libri, numero_libri)) < 0){
        cout << endl;
        cerr << "\tERRORE nella lettura dei file libri, il programma verra' chiuso\n\n";
        premi_invio();
        return 1;
    }

    // carica i dati degli alunni nel registro
    if((numero_alunni = carica_dati_alunni(registro_alunni, numero_alunni)) < 0){
        cout << endl;
        cerr << "\tERRORE nella lettura dei file, il programma verra' chiuso\n\n";
        premi_invio();
        return 1;
    }

    // carica i dati dei prestiti nel registro
    if ((numero_prestiti = carica_dati_prestiti(registro_prestiti, numero_prestiti)) < 0){
        cout << endl;
        cerr << "\tERRORE nella lettura dei file, il programma verra' chiuso\n\n";
        premi_invio();
        return 1;
    }

    do{
        crea_menu("Menu principale", stringa_menu);
        cout << endl;
        cout << "\tInserisci l'operazione da svolgere: ";
        cin >> scelta;

        // flusso di scelta
        switch(scelta){
            case '1':	// tutti i dati dei libri
                numero_libri = dati_libri(registro_libri, numero_libri, flag_modifica);
                break;
            case '2':	// tutti i dati degli alunni
                numero_alunni = dati_alunni(registro_alunni, numero_alunni, flag_modifica);
                break;
            case '3':	// tutti i dati dei prestiti
                numero_prestiti = dati_prestiti(registro_prestiti, registro_libri,
                     registro_alunni, numero_prestiti, numero_libri, numero_alunni,
                     flag_modifica);
                break;
            case '4':	// visualizza tabella dei libri
                visualizza_libri(registro_libri, numero_libri);
                cout << endl;
                premi_invio();
                break;
            case '5':	// visualizza tabella degli alunni
                visualizza_alunni(registro_alunni, numero_alunni);
                cout << endl;
                premi_invio();
                break;
            case '6':	// salva registri
                salva_tutto(registro_prestiti, registro_libri, registro_alunni,
                     numero_prestiti, numero_libri, numero_alunni);
                flag_modifica = false;
                break;
        }
    }while(scelta != '9');

    // se sono state fatte modifiche ai dati e si esce senza aver salvato
    // chiede conferma.
    if (flag_modifica) {
        char scelta;
        cout << endl;
        cout << "\tSono state fatte modifiche. Salvare prima di uscire? (s/n): ";
        cin >> scelta;

        if (scelta == 's' || scelta == 'S') {
            salva_tutto(registro_prestiti, registro_libri, registro_alunni,
                 numero_prestiti, numero_libri, numero_alunni);
            cout << endl;
            cout << "1tDati salvati correttamente.\n";
            premi_invio();
        }else{
            cout << endl;
            cout << "\tUscita senza salvataggio.\n";
            premi_invio();
        }
    }
    return 0;
}

// Funzione crea_menu()
// ha come parametro il titolo del menu che deve sviluppare e
// una stringa contenente tutte le voci del menu.
// effettua lo split e visualizza il menu.
void crea_menu(string titolo_menu, string voci_menu){

    unsigned i = 0;			// indice per scorrere voci_menu
    int conta_voci = 0;		// contatore delle voci del menu
    string voce = "";		// voce del menu

    // se manca assegno ; in ultima posizione
    if (voci_menu.empty() || voci_menu.back() != ';') {
        voci_menu += ';';
    }

    // larghezza delle celle del menu
    int larghezza_voce = 100;
    int larghezza_scelta = 3;
    const int voce_uscita = 9;

    pulisci_schermo();

    cout << endl;
    cout << "\t\t" << titolo_menu << "\n";    // visualizza il titolo
    cout << endl;
    cout << endl;
    cout << setfill('.');

    while(i < voci_menu.size()){	        // eseguo lo split della stringa
        if(voci_menu.at(i) != ';'){	        // controllo il separatore
            voce += voci_menu.at(i);	    // costruzione della voce del menu
            i++;				            // prossimo carattere
        }else{
            i++;
            conta_voci++;		// conteggio delle voci del menu

            // visualizza la voce del menu con il numero di scelta
            cout << "\t" << left << setw(larghezza_voce) << voce << setw(larghezza_scelta)
                << right << conta_voci << "\n";
            voce = "";
        }
    }
    cout << "\t" << left << setw(larghezza_voce) << "Esci" << setw(larghezza_scelta)
        << right << voce_uscita << "\n";
}

// Funzione dati_libri()
// e' il controller principale della sezione libri e
// gestisce tutti dati dei libri.
// ritorna la lunghezza del registro
int dati_libri(libro registro[], int lunghezza, bool &modificato){
    char scelta;
    // stringa per il sotto-menu
    string stringa_menu = "Nuovo libro;Modifica libro;Elimina libro";
    do{
        // sotto-menu libri
        crea_menu("Menu libri", stringa_menu);
        cout << endl;
        cout << "\tInserisci l'operazione da svolgere: ";
        cin >> scelta;

        // flusso di elaborazione
        switch(scelta){
        case '1':
            lunghezza = nuovo_libro(registro, lunghezza, modificato);
            break;
        case '2':
            modifica_libro(registro, lunghezza, modificato);
            break;
        case '3':
            lunghezza = elimina_libro(registro, lunghezza, modificato);
            break;
        }
    }while(scelta != '9');
    return lunghezza;
}

// Funzione dati_alunni()
// e' il controller principale della sezione alunni e
// gestisce tutti dati degli alunni.
// ritorna la lunghezza del registro
int dati_alunni(alunno registro[], int lunghezza, bool &modificato){
    char scelta;
    // stringa per il sotto-menu
    string stringa_menu = "Nuovo alunno;Modifica alunno;Elimina alunno";
    do{
        // sotto-menu alunni
        crea_menu("Menu alunni", stringa_menu);
        cout << endl;
        cout << "\tInserisci l'operazione da svolgere: ";
        cin >> scelta;
        // flusso di elaborazione
        switch(scelta){
        case '1':
            lunghezza = nuovo_alunno(registro, lunghezza, modificato);
            break;
        case '2':
            modifica_alunno(registro, lunghezza, modificato);
            break;
        case '3':
            lunghezza = elimina_alunno(registro, lunghezza, modificato);
            break;
        }
    }while(scelta != '9');
    return lunghezza;
}

// Funzione dati_prestiti()
// e' il controller principale della sezione prestiti e
// gestisce tutti dati dei prestiti.
// ritorna la lunghezza del registro
int dati_prestiti(prestito registro_pre[], libro registro_lib[],
    alunno registro_alu[], int lunghezza_pre, int lunghezza_lib,
    int lunghezza_alu, bool &modificato){

    char scelta;
    string stringa_menu = "Nuovo prestito;Restituzione libro";
    do{
        // sotto-menu prestiti
        crea_menu("Menu prestiti", stringa_menu);
        cout << endl;
        cout << "\tInserisci l'operazione da svolgere: ";
        cin >> scelta;

        switch(scelta){
        case '1':
            lunghezza_pre = nuovo_prestito(registro_pre, registro_lib,
                registro_alu, lunghezza_pre, lunghezza_lib, lunghezza_alu, modificato);
            break;
        case '2':
            restituzione_prestito(registro_pre, registro_lib, registro_alu,
                lunghezza_pre, lunghezza_lib, lunghezza_alu, modificato);
            break;
        }
    }while(scelta != '9');
    return lunghezza_pre;
}

// Funzione nuovo_libro()
// aggiunge un nuovo libro al registro dei libri.
// richiede tutti i dati tranne l'id che viene messo in automatico.
// ritorna la lunghezza del registro aggiornata.
int nuovo_libro(libro registro[], int lunghezza, bool &modificato){

    // id automatico in base alla lunghezza del registro
    if(lunghezza == 0){
        registro[lunghezza].id = 1;
    }else{
        registro[lunghezza].id = registro[lunghezza - 1].id + 1;
    }

    // input e memorizzazione dei dati del libro
    cout << endl;
    cout << "\tInserisci titolo: ";
    getline(cin >> ws, registro[lunghezza].titolo);
    cout << "\tInserisci autore: ";
    getline(cin >> ws, registro[lunghezza].autore);
    cout << "\tInserisci l'anno di pubblicazione: ";
    cin >> registro[lunghezza].anno_pubblicazione;
    registro[lunghezza].disponibile = 1;

    cout << endl;
    cout << "\tLibro inserito con successo\n";
    premi_invio();
    modificato = true;	// registro modificato
    return ++lunghezza;
}

// Funzione nuovo_alunno()
// aggiunge un nuovo alunno al registro degli alunni.
// richiede tutti i dati tranne l'id che viene messo in automatico.
// ritorna la lunghezza del registro aggiornata.
int nuovo_alunno(alunno registro[], int lunghezza, bool &modificato){

    // id automatico
    if(lunghezza == 0){
        registro[lunghezza].id = 1;
    }else{
        registro[lunghezza].id = registro[lunghezza - 1].id + 1;
    }

    // input e memorizzazione dei dati del libro
    cout << endl;
    cout << "\tInserisci il nome: ";
    getline(cin >> ws, registro[lunghezza].nome);
    cout << "\tInserisci cognome: ";
    getline(cin >> ws, registro[lunghezza].cognome);
    cout << "\tInserisci classe: ";
    cin >> registro[lunghezza].classe;
    cout << "\tInserisci sezione: ";
    cin >> registro[lunghezza].sezione;

    cout << endl;
    cout << "\tAlunno inserito con successo\n";
    premi_invio();
    modificato = true;
    return ++lunghezza;
}

// Funzione nuovo_prestito()
// aggiunge un nuovo prestito al registro dei prestiti.
// richiede tutti i dati tranne l'id che viene messo in automatico.
// ritorna la lunghezza del registro aggiornata.
int nuovo_prestito(prestito registro_pre[], libro registro_lib[],
    alunno registro_alu[], int lunghezza_pre, int lunghezza_lib,
    int lunghezza_alu, bool &modificato){

    string cognome;		// cognome dell'alunno
    string titolo;		// titolo del libro
    int pos_libro;		// indice del libro nel registro
    int pos_alunno;		// indice dell'alunno nel registro

    cout << endl;
    cout << "\tInserisci il cognome dell'alunno: \n";
    getline(cin >> ws, cognome);
    cout << "\tInserisci il titolo del libro";
    getline(cin >> ws, titolo);

    // id del prestito in automatico
    if(lunghezza_pre == 0){
        registro_pre[lunghezza_pre].id = 1;
    }else{
        registro_pre[lunghezza_pre].id = registro_pre[lunghezza_pre-1].id + 1;
    }

    // trovo gli indici del libro e dell'alunno
    pos_libro = cerca_libro(registro_lib, lunghezza_lib, titolo);
    pos_alunno = cerca_alunno(registro_alu, lunghezza_alu, cognome);

    // memorizzo in prestito gli id di alunno e libro
    registro_pre[lunghezza_pre].id_alunno = registro_alu[pos_alunno].id;
    registro_pre[lunghezza_pre].id_libro = registro_lib[pos_libro].id;

    cout << "\tInserisci la data del prestito: ";
    cin >> registro_pre[lunghezza_pre].data_prestito;
    registro_pre[lunghezza_pre].data_restituzione = "";
    registro_pre[lunghezza_pre].stato = 1;
    registro_pre[lunghezza_pre].note = "";

    registro_lib[pos_libro].disponibile = 0;    // aggiorno disponibilita' libro
    modificato = true;
    return ++lunghezza_pre;
}

// Funzione cerca_libro()
// ha come parametri il registro dei libri, la sua lunghezza
// e il titolo del libro da cercare.
// compie una ricerca sequenziale solo sul campo del titolo.
// ritorna l'indice del libro o -1 se non trovato.
int cerca_libro(libro registro[], int lunghezza, string titolo){

    int i = 0;
    while(i < lunghezza){
        if(registro[i].titolo == titolo){
            return i;
        }else{
            i++;
        }
    }
    return -1;
}

// Funzione cerca_alunno()
// ha come parametri il registro degli alunni, la sua lunghezza
// e il cognome dell'alunno da cercare.
// compie una ricerca sequenziale solo sul campo del cognome.
// ritorna l'indice dell'alunno o -1 se non trovato.
int cerca_alunno(alunno registro[], int lunghezza, string cognome, int pos_ini){
    int i = pos_ini;
    while(i < lunghezza){
        if(registro[i].cognome == cognome){
            return i;
        }else{
            i++;
        }
    }
    return -1;
}

// Funzione modifica_libro()
// ha come parametri il registro, la sua lunghezza e il flag delle modifiche,
// richiama la funzione cerca_libro() che ritorna l'indice
// del libro cercato.
// Visualizza i dati del libro e effettua le modifiche.
void modifica_libro(libro registro[], int lunghezza, bool &modificato){

    // stringa per sotto-menu
    string stringa_menu = "Titolo;Autore;Anno;Disponibilita'";
    int pos;            // indice del libro da modificare
    char scelta;        // scelta menu fatta dall'utente
    string titolo;      // titolo del libro da modificare

    cout << endl;
    cout << "\tInserisci il titolo del libro che vuoi modificare: ";
    getline(cin >> ws, titolo);

    // ricerca per titolo
    pos = cerca_libro(registro, lunghezza, titolo);

    // controllo sul titolo
    if(pos == -1){
        cout << endl;
        cerr << "\tERRORE: Il libro non è presente\n";
        premi_invio();
    }else{
        // visualizza dati libro
        visualizza_header_libro();
        visualizza_libro(registro, pos);

        // chiedo conferma
        cout << endl;
        cout << "\tE' questo il libro da modificare (s/n): ";
        cin >> scelta;
        if(scelta == 'n'){
            cout << endl;
            cout << "\tModifiche non effettuate";
            premi_invio();
            return;
        }else{

            do{
                cout << endl;
                crea_menu("Modifica libro", stringa_menu);
                cout << endl;
                cout << "Cosa vuoi modificare: ";
                cin >> scelta;
                switch(scelta){
                case '1':
                    cout << endl;
                    cout << "\tInserisci il nuovo titolo: ";
                    getline(cin >> ws, registro[pos].titolo);
                    break;
                case '2':
                    cout << endl;
                    cout << "\tInserisci il nuovo autore: ";
                    getline(cin >> ws, registro[pos].autore);
                    break;
                case '3':
                    cout << endl;
                    cout << "\tInserisci il nuovo anno di pubblicazione: ";
                    cin >> registro[pos].anno_pubblicazione;
                    break;
                case '4':
                    cout << endl;
                    cout << "\tInserisci disponibilita' 1 per disponibile o 0 per non disponibile: ";
                    cin >> registro[pos].disponibile;
                }
            }while(scelta != '9');
        }
    }
    modificato = true;
}

// Funzione modifica_alunno()
// ha come parametri il registro, la sua lunghezza e il flag delle modifiche,
// richiama la funzione cerca_alunno() che ritorna l'indice
// del'alunno cercato.
// visualizza i dati dell'alunno e effettua le modifiche.
void modifica_alunno(alunno registro[], int lunghezza, bool &modificato){

    string stringa_menu = "Nome;Cognome;Classe;Sezione;";
    char scelta;
    string cognome;		    // alunno da cercare
    int id;			        // id dell'alunno trovato
    int i = 0;
    int pos = 0;		    // indice dell'alunno trovato
    int trovati = 0;	    // contatore degli alunni omonimi

    cout << endl;
    cout << "\tInserisci il cognome dell'alunno: ";
    getline(cin >> ws, cognome);
    visualizza_header_alunno();

    while(pos < lunghezza){
        // cerca_alunno() ritorna indice
        pos = cerca_alunno(registro, lunghezza, cognome, pos);
        if(pos != -1){
            visualizza_alunno(registro, pos);
            pos++;
            trovati++;
        }else{
            break;
        }
    }

    // controllo sul contatore degli alunni omonimi
    if(trovati == 0){
        cout << endl;
        cerr << "\tERRORE: non sono stati trovati alunni";
        premi_invio();
        return;
    }

    cout << endl;
    cout << "\tInserisci l'id dell'alunno: ";
    cin >> id;

    // ricerca alunno per id
    i = 0;
    while(i < lunghezza && registro[i].id != id){
        i++;
    }

    do{
        // sotto-menu modifica alunno
        cout << endl;
        crea_menu("Modifica alunno", stringa_menu);
        cout << endl;
        cout << "\tCosa vuoi modificare: ";
        cin >> scelta;

        switch(scelta){
        case '1':
            cout << endl;
            cout << "\tInserisci il nuovo nome: ";
            getline(cin >> ws, registro[i].nome);
            break;
        case '2':
            cout << endl;
            cout << "\tInserisci il nuovo cognome: ";
            getline(cin >> ws, registro[i].cognome);
            break;
        case '3':
            cout << endl;
            cout << "\tInserisci la nuova classe: ";
            cin >> registro[i].classe;
            break;
        case '4':
            cout << endl;
            cout << "\tInserisci la nuova sezione: ";
            cin >> registro[i].sezione;
        }
    }while(scelta != '9');
    modificato = true;
}


void restituzione_prestito(prestito registro_pre[], libro registro_lib[],
    alunno registro_alu[], int lunghezza_pre, int lunghezza_lib,
    int lunghezza_alu, bool &modificato){

    string cognome = "";
    int id_alunno;              // id alunno memorizzato nel prestito
    int id_prestito;            // id del prestito
    int indice_prestito = 0;    // posizione del prestito
    int indice_alunno = 0;      // posizione alunno
    int i = 0;                  // indice scansione registro prestiti
    int j = 0;                  // indice scansione registro alunni

    pulisci_schermo();
    cout << endl;
    cout << "\tInserisci il cognome dell' alunno: ";
    cin >> cognome;

    // trovo l'alunno
    indice_alunno = cerca_alunno(registro_alu, lunghezza_alu, cognome);
    id_alunno = registro_alu[indice_alunno].id;

    while(indice_prestito < lunghezza_pre){
        indice_prestito = cerca_prestito(registro_pre, lunghezza_pre, indice_prestito, id_alunno);
        visualizza_dati_prestito(registro_pre, indice_prestito);
    }

    cout << endl;
    cout << "\tInserisci l'id del prestito da chiudere: ";
    cin >> id_prestito;

    // trovo la posizione del prestito
    while(registro_pre[i].id != id_prestito){
        i++;
    }

    registro_pre[i].stato = 0;  // chiudo il prestito


    // trovo la posizione del libro associato al prestito
    while(registro_lib[j].id != registro_pre[i].id_libro){
        j++;
    }

    registro_lib[j].disponibile = 1;    // rendo disponibile il libro

    cout << endl;
    cout << "\tInserisci la data di chiusura del prestito: ";
    getline(cin >> ws, registro_pre[i].data_restituzione);
    cout << endl;
    cout << "\tInserisci le note: ";
    getline(cin >> ws, registro_pre[i].note);

    cout << endl;
    cout << "\tPrestito chiuso";
    premi_invio();
    modificato = true;
}

// ritorna la posizione del primo prestito trovato
int cerca_prestito(prestito registro_pre[], int lung_pre, int indice, int id_alunno){

    while(indice < lung_pre && registro_pre[indice].id_alunno != id_alunno){
        indice++;
    }
    return indice;
}

// visualizza i dati di un singolo prestito
void visualizza_dati_prestito(prestito registro_pre[], int indice_prestito){

    cout << "\t" << registro_pre[indice_prestito].id << "\t";
    cout << registro_pre[indice_prestito].data_prestito << "\t";
    if(registro_pre[indice_prestito].stato){
        cout << "attivo\n";
    }else{
        cout << "non attivo\n";
    }
}

// Funzione visualizza_libro()
// ha come parametri il registro e l'indice del libro
// da visualizzare.
void visualizza_libro(libro registro[], int indice){

    int larg_id = 3;
    int larg_titolo = 25;
    int larg_autore = 20;
    int larg_anno = 11;
    int larg_disponibile = 15;

    cout << "\t";
    cout << left;
    cout << setfill(' ');
    cout << setw(larg_id) << registro[indice].id;
    cout << setw(larg_titolo) << registro[indice].titolo;
    cout << setw(larg_autore) << registro[indice].autore;
    cout << setw(larg_anno) << registro[indice].anno_pubblicazione;
    if(registro[indice].disponibile)
        cout << setw(larg_disponibile) << "si";
    else
        cout << setw(larg_disponibile) << "no";
    cout << endl;

}

// visualizza l'intestazione della tabella libri
void visualizza_header_libro(){

    int larg_id = 3;
    int larg_titolo = 25;
    int larg_autore = 20;
    int larg_anno = 11;
    int larg_disponibile = 15;

    cout << endl;
    cout << "\t";
    cout << left;
    cout << setfill(' ');
    cout << setw(larg_id) << "ID";
    cout << setw(larg_titolo) << "Titolo";
    cout << setw(larg_autore) << "Autore";
    cout << setw(larg_anno) << "Anno";
    cout << setw(larg_disponibile) << "Disponibilita'";
    cout << endl;

}

// Funzione visualizza_alunno()
// ha come parametri il registro e l'indice dell'alunno
// da visualizzare.
void visualizza_alunno(alunno registro[], int indice){

    int larg_id = 7;
    int larg_nome = 15;
    int larg_cognome = 15;
    int larg_classe = 10;
    int larg_sezione = 10;

    cout << "\t";
    cout << left;
    cout << setfill(' ');
    cout << endl;
    cout << setw(larg_id) << registro[indice].id;
    cout << setw(larg_nome) << registro[indice].nome;
    cout << setw(larg_cognome) << registro[indice].cognome;
    cout << setw(larg_classe) << registro[indice].classe;
    cout << setw(larg_sezione) << registro[indice].sezione;
    cout << endl;

}

// visualizza l'intestazione della tabella alunni
void visualizza_header_alunno(){

    int larg_id = 7;
    int larg_nome = 15;
    int larg_cognome = 15;
    int larg_classe = 10;
    int larg_sezione = 10;

    cout << endl;
    cout << "\t";
    cout << left;
    cout << setfill(' ');
    cout << endl;
    cout << setw(larg_id) << "ID";
    cout << setw(larg_nome) << "Nome";
    cout << setw(larg_cognome) << "Cognome";
    cout << setw(larg_classe) << "Classe";
    cout << setw(larg_sezione) << "Sezione";
    cout << endl;

}

// Funzione elimina_libro()
// ricerca per titolo, e chiede conferma sulla cancellazione.
// esegue shift circolare a sinistra e aggiorna la lunghezza del vettore.
int elimina_libro(libro registro[], int lunghezza, bool &modificato){
    int indice;
    string titolo;
    char scelta;


    cout << endl;
    cout << "\tInserisci il titolo del libro da eliminare: ";
    getline(cin >> ws, titolo);

    // ritorna la posizione nel vettore
    indice = cerca_libro(registro, lunghezza, titolo);

    if (indice == -1){
        cout << endl;
        cerr << "\tERRORE: il libro non e' presente";
        premi_invio();
    }else{
        visualizza_libro(registro, indice);
        cout << endl;
        cout << "\tConferma cancellazione (s/n): ";
        cin >> scelta;

        if(scelta == 's'){
            // shift a sinistra
            while(indice < lunghezza - 1){
                registro[indice] = registro[indice+1];
                indice++;
            }
            cout << endl;
            cout << "\tLibro cancellato";

            modificato = true;
        }else{
            return lunghezza;
        }
    }
    return --lunghezza;
}

// Funzione elimina_alunno()
// ricerca per cognome, e chiede conferma sulla cancellazione.
// esegue shift circolare a sinistra e aggiorna la lunghezza del vettore.
int elimina_alunno(alunno registro[], int lunghezza, bool &modificato){
    int id;
    string cognome;
    char scelta;
    int i = 0;

    cout << endl;
    cout << "\tInserisci il cognome dell'alunno da eliminare: ";
    getline(cin >> ws, cognome);

    cerca_alunno(registro, lunghezza, cognome);
    cout << endl;
    cout << "\tInserisci l'id da eliminare";
    cin >> id;

    //trovo la posizione dell'alunno
    while(registro[i].id != id){
        i++;
    }

    cout << endl;
    cout << "\tConferma cancellazione (s/n): ";
    cin >> scelta;

    if(scelta == 's'){
        // shift a sinistra
        while(i < lunghezza - 1){
            registro[i] = registro[i+1];
            i++;
        }

        cout << endl;
        cout << "\tAlunno cancellato";
        premi_invio();
        modificato = true;
    }
    return --lunghezza;
}

// visualizza una tabella con tutti i libri
void visualizza_libri(libro registro[], int lunghezza){
    int i = 0;

    if(lunghezza == 0){
        cout << endl;
        cout << "\tIl registro e' vuoto";
    }else{
        visualizza_header_libro();
        cout << endl;
        while(i < lunghezza){
            visualizza_libro(registro, i);
            i++;
        }
    }
}

// visualizza una tabella con tutti gli alunni
void visualizza_alunni(alunno registro[], int lunghezza){
    int i = 0;
    if(lunghezza == 0){
        cout << endl;
        cout << "\tIl registro e' vuoto\n";
    }else{
        visualizza_header_alunno();
        cout << endl;
        while(i < lunghezza){
            visualizza_alunno(registro, i);
            i++;
        }

    }
}

// se non esistono crea i file per memorizzare i registri
// ritorna 0 se andata a buon fine
// ritorna 1 se fallisce
int crea_file(){

    FILE* punta_libri;
    FILE* punta_alunni;
    FILE* punta_prestiti;

    if(fopen_s(&punta_libri, "registro_libri.txt", "r") != 0){
        if(fopen_s(&punta_libri, "registro_libri.txt", "w") != 0){
            return 1;
        }
    }
    fclose(punta_libri);

    if(fopen_s(&punta_alunni, "registro_alunni.txt", "r") != 0){
        if(fopen_s(&punta_alunni, "registro_alunni.txt", "w") != 0){
            return 1;
        }
    }
    fclose(punta_alunni);

    if(fopen_s(&punta_prestiti, "registro_prestiti.txt", "r") != 0){
        if(fopen_s(&punta_prestiti, "registro_prestiti.txt", "w") != 0){
            return 1;
        }
    }
    fclose(punta_prestiti);

    return 0;
}

// legge i record dal file e li memorizza nel registro.
// ritorna la posizione dell'ultimo elemento memorizzato nel registro.
// ritorna -1 se non riesce ad aprire il file in lettura.
int carica_dati_libri(libro registro[], int lunghezza){

    char titolo_temp[30];   // stringa di appoggio per titolo
    char autore_temp[20];   // stringa di appoggio per autore
    int i = 0;		        // indice del registro
    FILE* punta_libri;

    if(fopen_s(&punta_libri, "registro_libri.txt", "r") != 0){
        return -1;
    }

    // fino a che fscanf() ritorna 5, il numero di valori
    // letti correttamente, legge il file.
    while(fscanf(punta_libri, "%d %s %s %d %d",
        &registro[i].id,
        titolo_temp,
        autore_temp,
        &registro[i].anno_pubblicazione,
        &registro[i].disponibile) == 5){

        // conversione stringhe da char a tring
        chatostr(titolo_temp, registro[i].titolo);
        chatostr(autore_temp, registro[i].autore);
        i++;
    }
    fclose(punta_libri);
    return i;
}

// legge i record dal file e li memorizza nel registro.
// ritorna la posizione dell'ultimo elemento memorizzato nel registro.
// ritorna -1 se non riesce ad aprire il file in lettura.
int carica_dati_alunni(alunno registro[], int lunghezza){

    char nome_temp[20];         // stringa di appoggio per nome
    char cognome_temp[20];      // stringa di appoggio per cognome
    int i = 0;		            // indice del registro
    FILE* punta_alunni;

    if(fopen_s(&punta_alunni, "registro_alunni.txt", "r") != 0){
        return -1;
    }

    // fino a che fscanf() ritorna 5, il numero di valori
    // letti correttamente, legge il file.
    while(fscanf(punta_alunni, "%d %s %s %d %c",
        &registro[i].id,
        nome_temp,
        cognome_temp,
        &registro[i].classe,
        &registro[i].sezione) == 5){

        // conversione stringhe da char a tring
        chatostr(nome_temp, registro[i].nome);
        chatostr(cognome_temp, registro[i].cognome);
        i++;
    }
    fclose(punta_alunni);
    return i;
}

// legge i record dal file e li memorizza nel registro.
// ritorna la posizione dell'ultimo elemento memorizzato nel registro.
// ritorna -1 se non riesce ad aprire il file in lettura.
int carica_dati_prestiti(prestito registro[], int lunghezza){

    char data_prestito_temp[11];        // stringa appoggio per la data prestito
    char data_restituzione_temp[11];    // stringa appoggio per data restituzione
    char note_temp[100];                // stringa appoggio per le note
    int i = 0;			                // indice del registro
    FILE* punta_prestiti;

    if(fopen_s(&punta_prestiti, "registro_prestiti.txt", "r") != 0){
        return -1;
    }

    // fino a che fscanf() ritorna 7, il numero di valori
    // letti correttamente, legge il file.
    while(fscanf(punta_prestiti, "%d %d %d %s %s %d %s",
        &registro[i].id,
        &registro[i].id_libro,
        &registro[i].id_alunno,
        data_prestito_temp,
        data_restituzione_temp,
        &registro[i].stato,
        note_temp) == 7){

        // conversione stringhe da char a tring
        chatostr(data_prestito_temp, registro[i].data_prestito);
        chatostr(data_restituzione_temp, registro[i].data_restituzione);
        chatostr(note_temp, registro[i].note);
        i++;
    }
    fclose(punta_prestiti);
    return i;
}

// memorizza tutto il registro sul file sovrascrivendo quello vecchio.
// ritorna 0 se la scrittura è andata a buon fine.
// ritorna 1 se non riesce ad aprire il file.
int salva_dati_libri(libro registro[], int lunghezza){

    char titolo_temp[30];           // stringa appoggio per titolo
    char autore_temp[20];           // stringa appoggio per autore
    int i = 0;                      // indice del registro
    FILE* punta_libri;

    if(fopen_s(&punta_libri, "registro_libri.txt", "w") != 0){
        return 1;
    }

    // scansione sequenziale del registro
    while(i < lunghezza){

        //conversione da string a char
        strtocha(registro[i].titolo, titolo_temp);
        strtocha(registro[i].autore, autore_temp);

        // scrittura sul file
        fprintf(punta_libri, "%d %s %s %d %d\n",
        registro[i].id,
        titolo_temp,
        autore_temp,
        registro[i].anno_pubblicazione,
        registro[i].disponibile);

        i++;
    }

    fclose(punta_libri);
    return 0;
}

// memorizza tutto il registro sul file sovrascrivendo quello vecchio.
// ritorna 0 se la scrittura è andata a buon fine.
// ritorna 1 se non riesce ad aprire il file.
int salva_dati_alunni(alunno registro[], int lunghezza){

    char nome_temp[30];             // stringa appoggio per nome
    char cognome_temp[20];          // stringa appoggio per cognome
    int i = 0;                      // indice del registro
    FILE* punta_alunni;

    if(fopen_s(&punta_alunni, "registro_alunni.txt", "w") != 0){
        return 1;
    }

    // scansione sequenziale del registro
    while(i < lunghezza){

        //conversione da string a char
        strtocha(registro[i].nome, nome_temp);
        strtocha(registro[i].cognome, cognome_temp);

        // scrittura sul file
        fprintf(punta_alunni, "%d %s %s %d %c\n",
        registro[i].id,
        nome_temp,
        cognome_temp,
        registro[i].classe,
        registro[i].sezione);

        i++;
    }

    fclose(punta_alunni);
    return 0;
}

// memorizza tutto il registro sul file sovrascrivendo quello vecchio.
// ritorna 0 se la scrittura è andata a buon fine.
// ritorna 1 se non riesce ad aprire il file.
int salva_dati_prestiti(prestito registro[], int lunghezza){

    char data_prestito_temp[11];            // stringa appoggio per data prestito
    char data_restituzione_temp[11];        // stringa appoggio per data restituzione
    char note_temp[100];                    // stringa appoggio per note
    int i = 0;                              // indice del registro
    FILE* punta_prestiti;

    if(fopen_s(&punta_prestiti, "registro_prestiti.txt", "w") != 0){
        return 1;
    }

    while(i < lunghezza){

        //conversione da string a char
        strtocha(registro[i].data_prestito, data_prestito_temp);
        strtocha(registro[i].data_restituzione, data_restituzione_temp);
        strtocha(registro[i].note, note_temp);

        // scrittura sul file
        fprintf(punta_prestiti, "%d %d %d %s %s %d %s\n",
        registro[i].id,
        registro[i].id_libro,
        registro[i].id_alunno,
        data_prestito_temp,
        data_restituzione_temp,
        registro[i].stato,
        note_temp);

        i++;
    }

    fclose(punta_prestiti);
    return 0;
}

// richiama tutte le funzioni per il salvataggio dei registri.
void salva_tutto(prestito registro_pre[], libro registro_lib[], alunno registro_alu[],
     int lunghezza_pre, int lunghezza_lib, int lunghezza_alu){

    salva_dati_libri(registro_lib, lunghezza_lib);
    salva_dati_alunni(registro_alu, lunghezza_alu);
    salva_dati_prestiti(registro_pre, lunghezza_pre);
}

// funzione di utilita' per la conversione da string a char
void strtocha(string scr, char dest[]){

    unsigned i = 0;         // indice della stringa

    // scrittura del vettore carattere per carattere
    while(i < scr.size()){
        // converto spazi con underscore per rendere i record
        // nei file più facili da gestire
        dest[i] = (scr[i] == ' ') ? '_' : scr[i];
        i++;
    }
    dest[i] = '\0';
}

// funzione di utilita' per la conversione da char a string
void chatostr(char scr[], string& dest){
    dest = "";
    int i = 0;

    // scrittura della stringa carattere per carattere
    while(scr[i] != '\0'){
        // converto gli underscore in spazi bianchi
        dest += (scr[i] == '_')? ' ' : scr[i];
        i++;
    }
}

// utilita' per leggere l'output
void premi_invio(){
    cout << endl << endl;
    cout << "Premi invio per continuare";
    cin.ignore();
    cin.get();
}

// utilita' per formattare l'interfaccia
void pulisci_schermo(){
    if(system("CLS") != 0){
        system("clear");
    }
}
