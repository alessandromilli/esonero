#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> //bho
#include "gamelib.h"
#include <string.h>

unsigned char exitCode;
int playerNumber;
bool valid;
struct Giocatore* giocatori[4];
struct Zona_mappa* pFirst;
struct Zona_mappa* pLast;
//int* turni;
//Difficoltà
float level;

//TODO fai che se c'è roba nel buffer lo svuota senno no

//Funziona
static void str_spacer(char *str, int req_len){
    /*
     * This function takes a string and adds a space to the beginning and then one at the end of the string
     * until it reaches the reqired length then add terminatore
     * */

    //check the length of the required string without importing string.h
    int strlen;
    int tmp;
    bool loom = true;
    for (strlen = 0; str[strlen] != '\0'; strlen++);
    printf("%d", strlen);
    //if the string is already of the required length (or even more, although it couldn't be), no spaces have to be added
    if(strlen < req_len){
        //if the string is already of the required length (or even more, although it couldn't be), no spaces have to be added
        while(strlen < req_len){
            // add a space to the right
            if(loom == true){
                str[strlen] = ' ';
                str[strlen+1] = '\0';
                strlen++;
                loom=false;
            }
            if(loom == false){
                // add a space to the left
                loom=true;
                tmp = strlen;
                while(tmp>=0){
                    str[tmp+1] = str[tmp];
                    tmp--;
                }
                str[0] = ' ';
                strlen++;

            }
        }
    }
    str[req_len] = '\0';
}

//Funziona
static void turn_manager(int *turns){

    int i, z;
    int RanPlr;

    //initialize array
    for(i=0; i<playerNumber;i++){
        turns[i]=-1;
    }

    i=0;
    while(i < playerNumber){
        RanPlr = (rand() % playerNumber);
        valid = true;
        z = 0;
        while(z<i){
            if(turns[z] == RanPlr){
                //il giocatore è già assegnato ad un turno
                valid = false;
            }
            z++;
        }
        if(valid == true){
            //questo giocatore non e ancora stato assegnato a nessun turno, quindi giochera l'i-esimo turno
            turns[i] = RanPlr;
            i++;
        }
    }
}

//Funziona
static int genera_zona(){
    //enum Tipo_zona {caravan = 29, cucina = 20, soggiorno = 21, camera = 22, bagno = 23, garage = 24, seminterrato = 25};
    //Caravan non può essere, tutte le altre hanno le stesse possibilità

    int ret = (rand() % 6) + 20;

    return ret;
}

//Funziona
static int genera_ogg_zona(){
    //enum Tipo_oggetto_zona {adrenalina = 10, cento_dollari = 11, coltello = 12, nessun_oggetto = 13};rand() % 5
    /*
     * 2/5 (40%) di probabilità che non ci sia nessun_oggetto
     * 1/5 (20%) di probabilità che venga estratta adrenalina
     * 1/5 (20%) di probabilità che vengano estratti cento_dollari
     * 1/5 (20%) di probabilità che venga estratto coltello
     * */
    switch (rand() % 5) {
        case 0:{
            //adrenalina
            return 10;
        }
        case 1:{
            return 11;
        }
        case 2:{
            return 12;
        }
        case 3:
        case 4:{
            return 13;
        }
        default:{
            return 13;
        }
    }
}

//Funziona
static int genera_prova(){
    //enum Tipo_prova {prova_EMF = 30, prova_spirit_box = 31, prova_videocamera = 32, nessuna_prova = 33};
    /*
     * 2/5 (40%) di probabilità che non ci sia nessuna_prova
     * 1/5 (20%) di probabilità che venga estratta prova_EMF
     * 1/5 (20%) di probabilità che venga estratta prova_spirit_box
     * 1/5 (20%) di probabilità che venga estratta prova_videocamera
     * */
    switch (rand() % 5) {
        case 0:{
            //adrenalina
            return 30;
        }
        case 1:{
            return 31;
        }
        case 2:{
            return 32;
        }
        case 3:
        case 4:{
            return 33;
        }
    }
}

static int genera_ogg_iniziale(){
    //enum Tipo_oggetto_iniziale {EMF = 0,spirit_box = 1, videocamera = 2, calmanti = 3, sale = 4};
    switch (rand() % 5) {
        case 0:{
            //EMF
            return 0;
        }
        case 1:{
            //spirit_box
            return 1;
        }
        case 2:{
            //videocamera
            return 2;
        }
        case 3:{
            //calmanti
            return 3;
        }
        case 4:{
            //sale
            return 4;
        }
    }
}

//Dovrebbe Funzionare, da provare
static void stampa_giocatore(int numeroGiocatore){
    /*
     * Il numeroGiocatore sarà l'indice dell'array giocatori in cui si trova il giocatore di cui vogliamo stampare i dati
     * */
    int z;

    char name[65];
    //name 64 characters + \0
    char ms[4];
    //Mental sanity 3 digits + \0
    char bckpk[4][18];
    //4 elements contained in the backpack (item with longest name has 17 letters + \0)

    for(z = 0 ; z < 65 || (giocatori[numeroGiocatore]->nome_giocatore[z]) != '\0' ; z++){
        name[z] = giocatori[numeroGiocatore]->nome_giocatore[z];
    }
    //copia il nome del giocatore nella stringa name

    sprintf(ms, "%d", (int)giocatori[numeroGiocatore]->sanita_mentale);
    // si fa il casting della sanità mentale del giocatore prima a intero e dopodiché a stringa

    for(z = 0 ; z < 4 ; z++){
        switch (giocatori[numeroGiocatore]->zaino[z]) {
            case EMF:{
                strcpy(bckpk[z], "EMF");
                //EMF
            }
            case spirit_box:{
                strcpy(bckpk[z], "Spirit Box");
                //spirit box
            }
            case videocamera:{
                strcpy(bckpk[z], "VideoCamera");
                //videocamera
            }
            case calmanti:{
                strcpy(bckpk[z], "Calmanti");
                //calmanti
            }
            case sale:{
                strcpy(bckpk[z], "Sale");
                //sale
            }
            case adrenalina:{
                strcpy(bckpk[z], "Adrenalina");
                //adrenalina
            }
            case cento_dollari:{
                strcpy(bckpk[z], "100 Dollari");
                //cento dollari
            }
            case coltello:{
                strcpy(bckpk[z], "Coltello");
                //coltello
            }
            case nessun_oggetto:{
                strcpy(bckpk[z], "Vuoto");
                //nessun Oggetto
            }
            case prova_EMF:{
                strcpy(bckpk[z], "Prova EMF");
                //Prova emf
            }
            case prova_spirit_box:{
                strcpy(bckpk[z], "Prova Spirit Box");
                //prova_spirit_box
            }
            case prova_videocamera:{
                strcpy(bckpk[z], "Prova Videocamera");
                //prova videocamera
            }
                //Non ci metto il 32 (nessuna_prova) poiche non potra mai accadere che si trovi nello zaino del giocatore
                str_spacer(&bckpk[z], 17);
        }
    }
    str_spacer(&name, 64);
    str_spacer(&ms, 3);
    //TODO assegnagli il valore del giocatore in questione
    printf(" __________________________________________________________________________________                                                                            |\n"
           "|     ___                                   NOME:                                  |\n"
           "|    /.,.\\     %s    |\n"//64
           "|  __\\ - /__                           SANITA' MENTALE:                            |\n"
           "| |         |                                %s                                   |\n"//3
           "| | |     | |                              ZAINO:                                  |\n"
           "| | |     | |                      ---------------------                           |\n"
           "| |_|     |_|                      | %s |                           |\n"//17
           "|   |  |  |                        | %s |                           |\n"//17
           "|   |  |  |                        | %s |                           |\n"//17
           "|   |  |  |                        | %s |                           |\n"//17
           "|   |__|__|                        |___________________|                           |\n"
           "|__________________________________________________________________________________|", name, ms, bckpk[0], bckpk[1], bckpk[2], bckpk[3]);
}

//Dovrebbe Funzionare, da provare
static void stampa_zona(struct Zona_mappa *z){
    char zona[13];
    char ogg[12];
    char prova[18];

    switch (z->zona) {
        case cucina:{
            strcpy(zona, "CUCINA");
        }
        case soggiorno:{
            strcpy(zona, "SOGGIORNO");
        }
        case camera:{
            strcpy(zona, "CAMERA");
        }
        case bagno:{
            strcpy(zona, "BAGNO");
        }
        case garage:{
            strcpy(zona, "GARAGE");
        }
        case seminterrato:{
            strcpy(zona, "SEMINTERRATO");
        }
    }
    switch (z->oggetto_zona) {
        case adrenalina:{
            strcpy(ogg, "Adrenalina");
        }
        case cento_dollari:{
            strcpy(ogg, "100 Dollari");
        }
        case coltello:{
            strcpy(ogg, "Coltello");
        }
        case nessun_oggetto:{
            strcpy(ogg, "Niente");
        }
    }
    switch (z->prova) {
        case prova_EMF:{
            strcpy(prova, "Prova EMF");
        }
        case prova_spirit_box:{
            strcpy(prova, "Prova Spirit Box");
        }
        case prova_videocamera:{
            strcpy(prova, "Prova Videocamera");
        }
        case nessuna_prova:{
            strcpy(prova, "Adrenalina");
        }
    }

    str_spacer(&zona, 12);
    str_spacer(&ogg, 11);
    str_spacer(&prova, 17);

    printf(" ____________________________________\n"
           "|            -%s-          |\n"
           "|                                    |\n"
           "|               OGGETTO:             |\n"
           "|             %s            |\n"
           "|                PROVA:              |\n"
           "|          %s         |\n"
           "|____________________________________|", zona, ogg, prova);
}

int imposta_gioco(){
    time_t t;
    srand((unsigned)time(&t));
    //Inserimento numero di Giocatori

    int z, x;
    do {
        printf("\n\nInsert the number of players (1-4):");
        exitCode = scanf("%d", &playerNumber);

        if (exitCode==1 && playerNumber >= 1 && playerNumber <= 4) {
            //The selection made by the user is actually a valid one
            valid = true;
        } else {
            //the selection made by the user is either an invalid type or not an option
            valid = false;
            printf("\n\nAN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN\n\n");
            scanf("%*[^\n]%*c");
            //This "flushes" the stdin buffer up until the \n
            /* the %*[^\n] part scans the buffer until it finds a \n
             * the * part discards whatever was just scanned
             * The %*c scans and discards the \n left by the first part
             * */
        }
    } while (!valid);



    //Si crea la prima zona della mappa
    pFirst = malloc(sizeof(struct Zona_mappa));
    pLast = &pFirst;
    pFirst->prossima_zona = &pLast;
    pFirst->zona = genera_zona();
    pFirst->oggetto_zona = genera_ogg_zona();
    pFirst->prova = nessuna_prova;

    //Cleans Up buffer for the fgets after the scanf(Which leaves an /n)
    while ((getchar()) != '\n');

    for(z=0; z<4;z++){
        if(z<playerNumber){
            //inizializza il giocatore z
            giocatori[z] = malloc(sizeof(struct Giocatore));
            //Inserimento Del Nome
            do {
                printf("\nPlayer %d, Insert Your Name:", z+1);

                fgets(giocatori[z]->nome_giocatore, 64, stdin);
                //fgets reads up to and including a /n, which I have to remove
                for (x = 0; x < 64 && giocatori[z]->nome_giocatore[x] != 0; x++) {
                    if (giocatori[z]->nome_giocatore[x] == 10) {
                        //Terminate string at first \n
                        giocatori[z]->nome_giocatore[x] = 0;
                        break;
                    }
                }
                if (giocatori[z]->nome_giocatore[0] == 0 || giocatori[z]->nome_giocatore[0] == 10) {
                    //String is either empty or just made of an \n
                    valid = false;
                    printf("\nAN UNEXPECTED ERROR OCCURED, INSERT AGAIN\n");
                    scanf("%*[^\n]%*c");
                    printf("\n");

                } else {
                    valid = true;
                    printf("\nYour name is is: \"%s\", press ENTER to Continue:", giocatori[z]->nome_giocatore);
                    scanf("%*[^\n]%*c");
                    while ((getchar()) != '\n');
                    //This "flushes" the stdin buffer up until the \n
                    /* the %*[^\n] part scans the buffer until it finds a \n
                     * the * part discards whatever was just scanned
                     * The %*c scans and discards the \n left by the first part
                     * The printf prevents the user from having to press enter twice
                     * */
                }

            } while (!valid);



            //Tutti i giocatori partono da 100
            giocatori[z]->sanita_mentale = 100;
            //Tutti i giocatori partono dalla prima zona
            giocatori[z]->posizione = &pFirst;
            //Lo Zaino viene riempito di nessun_oggetto
            for(x=0; x<4; x++){
                giocatori[z]->zaino[x] = 13;

            }

        } else {
            // il giocatore z non gioca, quindi è null
            giocatori[z] = NULL;
        }
    }

    //Livello di Difficoltà
    int* usrChoice = malloc(sizeof(int));
    do {
        printf("\n\n Select Difficulty"
               "\n  1)Dilettante"
               "\n  2)Intermedio"
               "\n  3)Incubo"
               " La tua Scelta:");
        exitCode = scanf("%d", usrChoice);

        if (exitCode==1 && *usrChoice >= 1 && 3 >= *usrChoice) {
            //The selection made by the user is actually a valid one
            valid = true;
            scanf("%*[^\n]%*c");
            //This "flushes" the stdin buffer up until the \n
            /* the %*[^\n] part scans the buffer until it finds a \n
             * the * part discards whatever was just scanned
             * The %*c scans and discards the \n left by the first part
             * */
            if(*usrChoice == 1){
                level = 1.1;
            } else if(*usrChoice == 2){
                level = 1.2;
            } else if(*usrChoice == 3){
                level = 1.5;
            } else {
                valid = false;
                printf("\n\nAN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN\n\n");
                scanf("%*[^\n]%*c");
            }
        } else {
            //the selection made by the user is either an invalid type or not an option
            valid = false;
            printf("\n\nAN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN\n\n");
            scanf("%*[^\n]%*c");
            //This "flushes" the stdin buffer up until the \n
            /* the %*[^\n] part scans the buffer until it finds a \n
             * the * part discards whatever was just scanned
             * The %*c scans and discards the \n left by the first part
             * */
        }

    } while (!valid);


    //Genera gli oggetti iniziali
    unsigned char* oggetti_iniziali = malloc(playerNumber * sizeof (unsigned char));
    valid = false;
    do {
        for (z = 0; z < playerNumber; z++) {
            oggetti_iniziali[z] = genera_ogg_iniziale();
            if(oggetti_iniziali[z] >= 0 && oggetti_iniziali[z] <=2){
                valid = true;
            }
        }
    } while (!valid);

    //fai scegliere ai giocatori i vari cosi
    int turni[playerNumber];
    //TODO risolvi istanziamento turni
    turn_manager(&turni);

    printf("\nScelta degli oggetti iniziali:");
    for(z=0; z<playerNumber; z++){
        printf("\nGiocatore %d, %s:", turni[z], giocatori[turni[z]]->nome_giocatore);
        for (x = 0; x < playerNumber; x++) {
            printf("\n|%d|", x+1);
            switch (oggetti_iniziali[x]) {
                case 0:{
                    printf("    EMF    ");
                    break;
                }
                case 1:{
                    printf(" Spirit Box");
                    break;
                }
                case 2:{
                    printf("VideoCamera");
                    break;
                }
                case 3:{
                    printf("  Calmanti ");
                    break;
                }
                case 4:{
                    printf("    Sale   ");
                    break;
                }
                case -1:{
                    printf("Oggetto gia preso");
                    break;
                }
            }
            printf("|");
        }
        //TODO non va questo input
        do {
            printf("\n La tua Scelta:");
            exitCode = scanf("%d", &usrChoice);
            if (exitCode==1 && usrChoice >= 1 && usrChoice <= playerNumber) {
                //TODO non entra qui
                //The selection made by the user is actually a valid one
                valid = true;
            } else {
                //the selection made by the user is either an invalid type or not an option
                valid = false;
                printf("\n\nprovaAN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN\n\n");
                scanf("%*[^\n]%*c");
                //This "flushes" the stdin buffer up until the \n
                /* the %*[^\n] part scans the buffer until it finds a \n
                 * the * part discards whatever was just scanned
                 * The %*c scans and discards the \n left by the first part
                 * */
            }
            switch (oggetti_iniziali[*usrChoice-1]) {
                case 0:{
                    printf("\n\nGiocatore %d ha scelto EMF!\n\n", z);
                    giocatori[z]->zaino[0] = 0;
                }
                case 1:{
                    printf("\n\nGiocatore %d ha scelto Spirit Box!\n\n", z);
                    giocatori[z]->zaino[0] = 1;
                }
                case 2:{
                    printf("\n\nGiocatore %d ha scelto Videocamera\n\n", z);
                    giocatori[z]->zaino[0] = 2;
                }
                case 3:{
                    printf("\n\nGiocatore %d ha scelto Calmanti\n\n", z);
                    giocatori[z]->zaino[0] = 3;
                }
                case 4:{
                    printf("\n\nGiocatore %d ha scelto Sale\n\n", z);
                }
                case -1:{
                    valid = false;
                    printf("\n\nNon puoi avere un oggetto che è già stato preso!\n\n");

                }
                default:{
                    valid = false;
                    printf("\n\nAN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN\n\n");
                    scanf("%*[^\n]%*c");
                }

            }
        } while (!valid);
    }
    free(usrChoice);
    free(oggetti_iniziali);
    stampa_giocatore(0);
    stampa_zona(&pFirst);
    /*
     *  il nome viene inserito da tastiera.
Dopodiché si deve generare la mappa di gioco, che è costituita da una lista di struct Zona_mappa. Per
questo c’è quindi bisogno di due puntatori globali per memorizzare il primo e l’ultimo elemento della
2
lista (struct Zona_mappa* pFirst e struct Zona_mappa* pLast). La mappa è implementata da una lista
circolare: il campo prossima_zona dell’ultima zona contiene l’indirizzo della prima zona. In questo
modo il giocatore che si trova sull’ultima zona e avanza si troverà di nuovo sulla prima zona. Da notare
che il caravan non fa parte di questa lista, ma è una zona a parte.
Per la creazione della mappa, si lascia la possibilità all’utente (supponiamo sia un “game master” in
questo caso) di richiedere tramite un menu le seguenti quattro funzioni:
1) Inserimento di una zona al termine della lista (funzione inserisci_zona()). Essa crea la nuova
zona in memoria dinamica (malloc()), la inserisce nella lista modificando il valore del puntatore
prossima_zona dell’ultima terra della lista con il risultato della malloc(). Il tipo della zona (enum
Tipo_zona) così come l’oggetto trovato all’interno della zona vengono generati casualmente: tutte le zone sono equiprobabili (eccetto caravan che non può essere mai aggiunta alla lista), nessun_oggetto ha probabilità 40% mentre gli altri oggetti in enum Tipo_oggetto_zona hanno pari
probabilità. Infine, il campo enum Tipo_prova prova verrà inserito con una certa probabilità tutte le
volte che un giocatore arriverà in una data zona (vedere funzione avanza() sotto). Ripercorrendo le
stesse zone sarà quindi possibile trovare prove differenti.
2) Cancella l’ultima zona inserita nel percorso (cancella_zona()). Ricordarsi di liberare la memoria
occupata dalla zona cancellata. Ricordarsi di trattare il caso particolare in cui nella lista non è
presente nessuna zona.
3) Stampa i campi di tutte le zone create fino a quel momento (stampa_mappa()).
4) Fine della creazione della mappa: chiudi_mappa(). Ci si ricorda che la creazione della mappa è
terminata (per esempio settando una variabile globale e statica da 0 a 1). Questa variabile viene
controllata quando si chiama gioca(), per controllare che il gioco sia stato in effetti completamente
impostato. Infine si esce anche dalla funzione imposta_gioco().
     * */
    return 0;
}

int gioca(){
    //controlla se il gioco sia stato impostato correttamente

    /*
Tutti i giocatori iniziano il gioco
sulla prima zona della lista creata (che non è caravan).
Il gioco è strutturato in turni. Il giocatore che muove in un dato turno è scelto a caso, anche se prima di poter
rigiocare un turno tutti i rimanenti giocatori devono aver giocato il loro; ad esempio, i giocatori possono giocare
nell’ordine 2-4-1-3, e poi si riparte, sempre con un nuovo ordine casuale (2-4-4-1-3 invece non è possibile).
Durante il turno di un giocatore, le funzioni che possono essere chiamate per giocare sono:
• torna_caravan(): il caravan è la base d’appoggio per i giocatori: può essere visto come una zona speciale e ne esiste sempre una ed una sola: non può essere quindi generata un’altra zona caravan durante
la creazione della mappa. Con questa funzione il giocatore ritorna automaticamente al caravan: le prove
eventualmente raccolte dal giocatore verranno lasciata nel caravan, marcandole come trovate. **inizio
modifica** Al posto della prova, nello zaino comparirà uno dei rimanenti oggetti tra EMF, spirit_box,
videocamera che non è ancora stato distribuito ai giocatori (altrimenti risulterebbe impossibile raccogliere tutte e tre le prove e concludere il gioco) **fine modifica** . Alla fine il giocatore verrà posizionato
sulla prima zona della lista e il turno passerà al prossimo giocatore. La presenza del fantasma nella stessa
zona impedisce di ritornare al caravan, e quindi questa funzione non potrà essere chiamata.
• stampa_giocatore(): stampa i valori di tutti i campi del giocatore.
3
• stampa_zona(): stampa i valori di tutti i campi della zona dove si trova il giocatore.
• avanza(): il giocatore avanza sulla zona successiva della mappa. Quando un giocatore avanza e arriva
in una certa zona, il campo enum Tipo_prova prova di questa zona viene aggiornato in modo casuale:
nessuna_prova 40%, mentre prova_EMF, prova_spirit_box, prova_videocamera tutte con 20% ciascuna.
Ogni giocatore può avanzare una volta sola per turno.
• raccogli_prova(): se in una stanza si trova una certa prova, per esempio prova_spirit_box, è possibile
raccoglierla solo se il giocatore è in possesso dell’oggetto corrispondente, in questo caso spirit_box: nello
zaino, spirit_box viene sostituito automaticamente da prova_spirit_box. Ogni volta che un giocatore
raccoglie una prova, c’è una probabilità dipendente dal livello di difficoltà impostato che il fantasma
appaia (scegliere queste probabilità). Se il fantasma appare, tutti i giocatori in quella zona diminuiscono
la loro sanità mentale di un numero dipendente dalla difficoltà del gioco selezionata (scegliere queste
quantità). La probabilità di apparizione del fantasma incrementa con la prova raccolta: alla prima prova
raccolta la probabilità sarà minore che alla seconda, e la seconda minore rispetto alla terza (scegliere
questi incrementi).
• raccogli_oggetto(): in una stanza con un oggetto è possibile raccogliere l’oggetto, sempre se c’è posto
nello zaino.
• usa_oggetto(): oltre agli oggetti per raccogliere le prove, è possibile utilizzare uno degli altri oggetti
presenti nello zaino. Questi altri oggetti quando usati hanno degli effetti speciali (vedere di seguito).
Quando si usa un oggetto, esso scompare dallo zaino.
• passa(): il giocatore cede il turno al prossimo giocatore.
Se tutte e tre le prove prova_EMF, prova_spirit_box, prova_videocamera vengono marcate come trovate
(lasciate quindi nel caravan), allora i giocatori (sopravvissuti) hanno vinto la partita. Se invece la sanità mentale
di un giocatore scende a 0 o sotto, questo giocatore non parteciperà più al gioco. Se tutti i giocatori scendono
sotto 0, la partita è persa.
Di seguito l’effetto degli oggetti:
sale: se si usa il sale , se il fantasma apparirà non provocherà nessun decremento di sanità mentale.
calmanti: aumenta di 40 punti la sanità mentale.
100 dollari: se si usano i dollari, al posto dei dollari nello zaino compare un oggetto a caso tra calmante e sale.
coltello: se si usa il coltello e la propria sanità mentale è sotto 30, si uccidono tutti gli altri membri nella zona in
cui ci si trova (se ci sono).
adrenalina: se si usa adrenalina si può avanzare una volta in più (chiamare avanza()).
Infine, per ogni azione compiuta da un giocatore, c’è una probabilità del 20% che la sanità mentale decresca
di 15 punti.
*/

    //Al termine di una partita, vinta o persa, si può ritornare al menu iniziale e reimpostare il gioco e rigiocare. Ricordarsi prima di deallocare tutta la memoria dinamica allocata nella partita precedente
    return 0;
}

int termina_gioco(){
    //saluta i giocatori
    //svuota memoria
    return 0;
}


