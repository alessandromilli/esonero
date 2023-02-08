#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "gamelib.h"
#include <string.h>

unsigned char exitCode;
int playerNumber;
struct Giocatore* giocatori[4];
struct Zona_mappa* pFirst;
struct Zona_mappa* pLast;
// Difficulty Level
int level;
struct Zona_mappa* zona_caravan;
enum Tipo_prova prove_raccolte[3];
time_t start, end;
//--------------------------------------------------------------------------------------------------------
static void color(char c){
    switch (c) {
        case 'R':
        case 'r':
            printf("\033[0;31m");
            // Red
            break;
        case 'G':
        case 'g':
            printf("\033[0;32m");
            // Green
            break;
        case 'Y':
        case 'y':
            printf("\033[0;33m");
            // Yellow
            break;
        case 'B':
        case 'b':
            printf("\033[0;34m");
            // Blue
            break;
        case 'P':
        case 'p':
            printf("\033[0;35m");
            // Purple
            break;
        case 'C':
        case 'c':
            printf("\033[0;36m");
            // Cyan
            break;
        case 'X':
        case 'x':
            // Random
            switch (rand() % 6) {
                case 0:
                    printf("\033[0;31m");
                    // Red
                    break;
                case 1:
                    printf("\033[0;32m");
                    // Green
                    break;
                case 2:
                    printf("\033[0;33m");
                    // Yellow
                    break;
                case 3:
                    printf("\033[0;34m");
                    // Blue
                    break;
                case 4:
                    printf("\033[0;35m");
                    // Purple
                    break;
                case 5:
                    printf("\033[0;36m");
                    // Cyan
                    break;
            }
            break;
        case 'W':
        case 'w':
        default:
            printf("\033[0;37m");
            // White
            break;
    }
}

static void cls(){
    printf("\e[1;1H\e[2J");
}

static void str_spacer(char *str, int req_len){
    /*
     * This function takes a string and adds a space to the beginning and then one at the end of the string
     * until it reaches the required length then add \0
     * */

    // Check the length of the string
    int strlen;
    int tmp;
    bool loom = true;
    for (strlen = 0; str[strlen] != '\0'; strlen++);
    // if the string is already of the required length (or even more, although it couldn't be), no spaces shall be added
    if(strlen <= req_len){
        while(strlen < req_len){
            // Add a space to the right
            if(loom == true){
                str[strlen] = 32;
                str[strlen+1] = '\0';
                loom=false;
            } else {
                // Add a space to the left
                loom=true;
                tmp = strlen;
                while(tmp>=0){
                    str[tmp+1] = str[tmp];
                    tmp--;
                }
                str[0] = 32;
            }
            strlen++;
        }
    }
    str[req_len] = '\0';
}

static void turn_manager(int *turns){
    bool valid;
    int i, z;
    int RanPlr;

    // Initialize array
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
                // Extracted player has been already assigned to another turn
                valid = false;
            }
            z++;
        }
        if(valid == true){
            // Extracted player hasn't been assigned to a turn yet, he will play the i-th turn
            turns[i] = RanPlr;
            i++;
        }
    }
}

static int genera_zona(){
    // enum Tipo_zona {caravan = 29, cucina = 20, soggiorno = 21, camera = 22, bagno = 23, garage = 24, seminterrato = 25};
    // It can be any kind of zone (apart from caravan), with equal chances

    int ret = (rand() % 6) + 20;

    return ret;
}

static int genera_ogg_zona(){
    // enum Tipo_oggetto_zona {adrenalina = 10, cento_dollari = 11, coltello = 12, nessun_oggetto = 13};rand() % 5
    /*
     * 2/5 (40%) probability that it will be nessun_oggetto
     * 1/5 (20%) probability that it will be adrenalina
     * 1/5 (20%) probability that it will be cento_dollari
     * 1/5 (20%) probability that it will be coltello
     * */
    // Breaks are useless here, the return will end the switch
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
        default:{
            return 13;
        }
    }
}

static int genera_prova(){
    // enum Tipo_prova {prova_EMF = 30, prova_spirit_box = 31, prova_videocamera = 32, nessuna_prova = 33};
    /*
     * 2/5 (40%) probability that it will be nessuna_prova
     * 1/5 (20%) probability that it will be prova_EMF
     * 1/5 (20%) probability that it will be prova_spirit_box
     * 1/5 (20%) probability that it will be prova_videocamera
     * */
    switch (rand() % 5) {
        case 0:{
            // prova_EMF
            return 30;
        }
        case 1:{
            // prova_spirit_box
            return 31;
        }
        case 2:{
            // prova_videocamera
            return 32;
        }
        default:{
            // nessuna_prova
            // case 3 and 4
            return 33;
        }
    }
}

static int genera_ogg_iniziale(){
    // enum Tipo_oggetto_iniziale {EMF = 0,spirit_box = 1, videocamera = 2, calmanti = 3, sale = 4};
    switch (rand() % 5) {
        case 0:{
            // EMF
            return 0;
        }
        case 1:{
            // spirit_box
            return 1;
        }
        case 2:{
            // videocamera
            return 2;
        }
        case 3:{
            // calmanti
            return 3;
        }
        default:{
            // case 4
            // sale
            return 4;
        }
    }
}

static void stampa_giocatore(struct Giocatore* p){

    int z;

    char name[65];
    // Player name 64 characters + \0
    char ms[4];
    // Mental health 3 digits + \0
    char bckpk[4][18];
    // The name of the 4 elements contained in the backpack (item with the longest name has 17 letters + \0)

    strcpy(name, p->nome_giocatore);

    sprintf(ms, "%d", (int)p->sanita_mentale);
    // cast mental health to int and then to string

    for(z = 0 ; z < 4 ; z++){
        switch (p->zaino[z]) {
            case EMF:{
                strcpy(bckpk[z], "EMF");
                // EMF
                break;
            }
            case spirit_box:{
                strcpy(bckpk[z], "Spirit Box");
                // spirit_box
                break;
            }
            case videocamera:{
                strcpy(bckpk[z], "VideoCamera");
                // videocamera
                break;
            }
            case calmanti:{
                strcpy(bckpk[z], "Calmanti");
                // calmanti
                break;
            }
            case sale:{
                strcpy(bckpk[z], "Sale");
                // sale
                break;
            }
            case adrenalina:{
                strcpy(bckpk[z], "Adrenalina");
                // adrenalina
                break;
            }
            case cento_dollari:{
                strcpy(bckpk[z], "100 Dollari");
                // cento dollari
                break;
            }
            case coltello:{
                strcpy(bckpk[z], "Coltello");
                // coltello
                break;
            }
            case nessun_oggetto:{
                strcpy(bckpk[z], "Vuoto");
                // nessun_oggetto
                break;
            }
            case prova_EMF:{
                strcpy(bckpk[z], "Prova EMF");
                // prova_EMF
                break;
            }
            case prova_spirit_box:{
                strcpy(bckpk[z], "Prova Spirit Box");
                // prova_spirit_box
                break;
            }
            case prova_videocamera:{
                strcpy(bckpk[z], "Prova Videocamera");
                // prova_videocamera
                break;
            }
            // nessuna_prova isn't a viable case since it is impossible that it will be contained in a Player's backpack
        }
        str_spacer(bckpk[z], 17);
    }
    str_spacer(name, 64);
    str_spacer(ms, 3);
    printf("\n\n           __________________________________________________________________________________"
           "\n          |     ___                                  NOME:                                   |"
           "\n          |    /.,.\\    %s     |"//64
           "\n          |  __\\ - /__                          SANITA' MENTALE:                             |"
           "\n          | |         |                               %s                                    |"//3
           "\n          | | |     | |                              ZAINO:                                  |"
           "\n          | | |     | |                      ---------------------                           |"
           "\n          | |_|     |_|                      | %s |                           |"//17
           "\n          |   |  |  |                        | %s |                           |"//17
           "\n          |   |  |  |                        | %s |                           |"//17
           "\n          |   |  |  |                        | %s |                           |"//17
           "\n          |   |__|__|                        |___________________|                           |"
           "\n          |__________________________________________________________________________________|\n\n", name, ms, bckpk[0], bckpk[1], bckpk[2], bckpk[3]);
}

static void stampa_zona(struct Zona_mappa *z){
    if(z != pFirst){
        char zona[13];
        char ogg[12];
        char prova[18];

        switch (z->zona) {
            case cucina:{
                strcpy(zona, "CUCINA");
                break;
            }
            case soggiorno:{
                strcpy(zona, "SOGGIORNO");
                break;
            }
            case camera:{
                strcpy(zona, "CAMERA");
                break;
            }
            case bagno:{
                strcpy(zona, "BAGNO");
                break;
            }
            case garage:{
                strcpy(zona, "GARAGE");
                break;
            }
            case seminterrato:{
                strcpy(zona, "SEMINTERRATO");
                break;
            }
            default:{
                strcpy(zona, "ERRORE");
                break;
            }
        }
        switch (z->oggetto_zona) {
            case adrenalina:{
                strcpy(ogg, "Adrenalina");
                break;
            }
            case cento_dollari:{
                strcpy(ogg, "100 Dollari");
                break;
            }
            case coltello:{
                strcpy(ogg, "Coltello");
                break;
            }
            case nessun_oggetto:{
                strcpy(ogg, "Niente");
                break;
            }
        }
        switch (z->prova) {
            case prova_EMF:{
                strcpy(prova, "Prova EMF");
                break;
            }
            case prova_spirit_box:{
                strcpy(prova, "Prova Spirit Box");
                break;
            }
            case prova_videocamera:{
                strcpy(prova, "Prova Videocamera");
                break;
            }
            case nessuna_prova:{
                strcpy(prova, "Nessuna Prova");
                break;
            }
        }

        str_spacer(zona, 12);
        str_spacer(ogg, 11);
        str_spacer(prova, 17);

        printf("\n\n                                  ____________________________________"
               "\n                                 |           -%s-           |"
               "\n                                 |                                    |"
               "\n                                 |              OGGETTO:              |"
               "\n                                 |             %s            |"
               "\n                                 |               PROVA:               |"
               "\n                                 |          %s         |"
               "\n                                 |____________________________________|\n", zona, ogg, prova);
    } else {
        char prova[18];
        switch (z->prova) {
            case prova_EMF:{
                strcpy(prova, "Prova EMF");
                break;
            }
            case prova_spirit_box:{
                strcpy(prova, "Prova Spirit Box");
                break;
            }
            case prova_videocamera:{
                strcpy(prova, "Prova Videocamera");
                break;
            }
            case nessuna_prova:{
                strcpy(prova, "Nessuna Prova");
                break;
            }
        }
        str_spacer(prova, 17);
        printf("\n\n                                  ____________________________________"
               "\n                                 |           -ZONA INIZIALE-          |"
               "\n                                 |               PROVA:               |"
               "\n                                 |          %s         |"
               "\n                                 |____________________________________|\n", prova);
    }
}

static void inserisci_zona(){
    struct Zona_mappa* tmp_zona = malloc(sizeof(struct Zona_mappa));
    pLast->prossima_zona = tmp_zona;
    tmp_zona->prossima_zona = pFirst;
    tmp_zona->zona = (enum Tipo_zona) genera_zona();
    tmp_zona->oggetto_zona = (enum Tipo_oggetto_zona) genera_ogg_zona();
    tmp_zona->prova = nessuna_prova;
    pLast = tmp_zona;
    printf("\n                                        Nuova zona Inserita!\n");
    stampa_zona(pLast);
}

static void cancella_zona(){
    // Check if it isn't the only zone
    if(pLast->prossima_zona != pFirst->prossima_zona){
        // There are at least 2 zones
        struct Zona_mappa* tmp_penultima = pFirst;
        while(tmp_penultima->prossima_zona != pLast){
            tmp_penultima = tmp_penultima->prossima_zona;
        }
        tmp_penultima->prossima_zona = pFirst;
        pLast = tmp_penultima;
        printf("\n                                          Zona Cancellata!\n");
    } else {
        // Player is trying to delete the only zone, it's not possible
        printf("\n                       Purtroppo non e' possibile cancellare la zona iniziale!\n");
    }
}

static void stampa_mappa(){
    struct Zona_mappa* tmp = pFirst;
    printf("\n                                           Stampo Mappa...");
    do {
        stampa_zona(tmp);
        tmp = tmp->prossima_zona;
    } while(tmp != pFirst);
}

static int fantasma(){
    /*
     * Level can have the following values:
     * Dilettante -> 30
     * Intermedio -> 50
     * Incubo -> 70
     * This function extracts a number from 0 to 99, if said number is lower than level value (30,50,70), the ghost spawns,
     * if not, then it doesn't.
     * By doing that we have
     * 30% chance in Dilettante
     * 50% chance in Intermedio
     * 70% chance in
     * For every piece of evidence that gets picked up, there is a 5% increased possibility that a ghost will spawn
     * */
    if(rand() % 100 < level){
        // Ghost Spawned
        printf("\n                                          .-."
               "\n                                        .'   `."
               "\n                                        :g g   :"
               "\n                                        : o    `."
               "\n                                        :         ``."
               "\n                                       :             `."
               "\n                                      :  :         .   `."
               "\n                                      :   :          ` . `."
               "\n                                       `.. :            `. ``;"
               "\n                                          `:;             `:'"
               "\n                                             :              `."
               "\n                                              `.              `.     ."
               "\n                                                `'`'`'`---..,___`;.-'");
        printf("\n                                          E' comparso un fantasma!\n");
        // 3 second sleep
        time(&start);
        do time(&end); while(difftime(end, start) <= 3);
        cls();
        return 1;
    } else {
        // Ghost did not Spawn
        return 0;
    }
}

static int raccogli_oggetto(struct Giocatore* p){
    int i;
    if(p->posizione->oggetto_zona != nessun_oggetto){
        for(i=0;i<4;i++){
            if(p->zaino[i] == nessun_oggetto){
                // Checks all the slots in the players backpack, if an empty one is found, the item is placed there and removed from the zone
                p->zaino[i] = p->posizione->oggetto_zona;
                p->posizione->oggetto_zona = nessun_oggetto;
                break;
            }
        }
        if(p->posizione->oggetto_zona != nessun_oggetto){
            // If there is still an item in the current zone, it means that it hasn't been picked up and the backpack is full
            printf("\n                   Non e' stato possibile raccogliere l'oggetto, lo zaino e' pieno!\n");
            return -1;
        } else {
            // The item has been picked up correctly
            printf("\n                                      Hai raccolto l'oggetto!\n");
            return 1;
        }
    } else {
        // Current zone hasn't got any items to pick up
        printf("\n                       Non c'e' nessun oggetto da raccogliere in questa zona!\n");
        return 0;
    }
}

static int raccogli_prova(struct Giocatore* p){
    int i;
    if(p->posizione->prova != nessuna_prova){
        /*
         * There is some kind of evidence to pick up
         * Check if player has the right item to pick up the evidence
         * prova_EMF (30) --> EMF (0)
         * prova_spirit_box (31) --> spirit_box(1)
         * prova_videocamera(32) --> videocamera(2)
         * */
        for(i=0;i<4;i++){
            if(p->zaino[i] == (int) p->posizione->prova-30){
                // Checks all the slots in the players backpack, if the correct "evidence picker" is found for this kind of evidence, then it will be swapped for the piece of evidence and the current zone will have no evidence
                p->zaino[i] = p->posizione->prova;
                p->posizione->prova = nessuna_prova;
                break;
            }
        }
        if(p->posizione->prova != nessuna_prova){
            // The evidence could not be picked up, the player hasn't got the correct "evidence picker"
            printf("\n            Non e' stato possibile raccogliere la prova, non si ha l'oggetto corrispondente!\n");
            return 0;
        } else {
            // Evidence collected correctly!
            printf("\n                              La prova e' stata raccolta con successo!\n");
            return 1;
        }
    } else {
        // The current zone hasn't got any evidence to pick up
        printf("\n                               Non c'e' nessuna prova da raccogliere!\n");
        return 0;
    }
}

static void decrementa_sanita(struct Giocatore* p){
    // The Assignment states that whenever the player does something, there is a 20% chance that the player's mental health will decrease by 15 points
    if(rand() % 5 == 0){
        color('r');
        // Decrease the player mental health
        if(p->sanita_mentale<15){
            // The mental health value can't be lower than zero
            p->sanita_mentale = 0;
        } else {
            p->sanita_mentale = p->sanita_mentale - 15;
        }
        switch (rand() % 5) {
            case 0:{
                printf("\n%s sbatte il mignolino su di un mobile infestato, la sua sanita' mentale scende di 15 punti!\n", p->nome_giocatore);
                break;
            }
            case 1:{
                printf("\n%s viene morso da un ragno, la sua sanita' mentale scende di 15 punti!\n", p->nome_giocatore);
                break;
            }
            case 2:{
                printf("\n%s inciampa e cade a terra, la sua sanita' mentale scende di 15 punti!\n", p->nome_giocatore);
                break;
            }
            case 3:{
                printf("\n%s per sbaglio pesta una cacca, la sua sanita' mentale scende di 15 punti!\n", p->nome_giocatore);
                break;
            }
            case 4:{
                printf("\nUna zanzara non la smette di ronzare intorno alle orecchie di %s, la sua sanita' mentale scende di 15 punti!\n", p->nome_giocatore);
                break;
            }
        }
        color('w');
    }
}

static void stampa_zaino(struct Giocatore* p){
    char bckpk[4][18];
    int z;
    for(z = 0 ; z < 4 ; z++){
        switch (p->zaino[z]) {
            case EMF:{
                strcpy(bckpk[z], "EMF");
                // EMF
                break;
            }
            case spirit_box:{
                strcpy(bckpk[z], "Spirit Box");
                // spirit_box
                break;
            }
            case videocamera:{
                strcpy(bckpk[z], "VideoCamera");
                // videocamera
                break;
            }
            case calmanti:{
                strcpy(bckpk[z], "Calmanti");
                // calmanti
                break;
            }
            case sale:{
                strcpy(bckpk[z], "Sale");
                // sale
                break;
            }
            case adrenalina:{
                strcpy(bckpk[z], "Adrenalina");
                // adrenalina
                break;
            }
            case cento_dollari:{
                strcpy(bckpk[z], "100 Dollari");
                // cento_dollari
                break;
            }
            case coltello:{
                strcpy(bckpk[z], "Coltello");
                // coltello
                break;
            }
            case nessun_oggetto:{
                strcpy(bckpk[z], "Vuoto");
                // nessun_Oggetto
                break;
            }
            case prova_EMF:{
                strcpy(bckpk[z], "Prova EMF");
                // prova_EMF
                break;
            }
            case prova_spirit_box:{
                strcpy(bckpk[z], "Prova Spirit Box");
                // prova_spirit_box
                break;
            }
            case prova_videocamera:{
                strcpy(bckpk[z], "Prova Videocamera");
                // prova_videocamera
                break;
            }
                // nessuna_prova isn't a viable case since it is impossible that it will be contained in a Player's backpack
        }
        str_spacer(bckpk[z], 17);
    }
    printf("\n                                     _____________________________"
           "\n                                    |                             |"
           "\n                                    |1|     %s     |"
           "\n                                    |2|     %s     |"
           "\n                                    |3|     %s     |"
           "\n                                    |4|     %s     |"
           "\n                                    |0|           ESCI            |"
           "\n                                    |_____________________________|", bckpk[0], bckpk[1], bckpk[2], bckpk[3]);

}

static int usa_oggetto(struct Giocatore* p){
    /*
     * Return Values:
     * 1 Item has been used successfully
     * -1 no item has been used (Error or Player Selection)
     * 2 Salt
     * 3 Adrenaline
     * */
    int usrChoice = -1;
    int i;
    bool kill;
    stampa_zaino(p);
    printf("\n                                   Quale oggetto desideri utilizzare:");
    do{
        exitCode = scanf("%d", &usrChoice);
        if (exitCode==1 && playerNumber >= 0 && playerNumber <= 4) {
            // The selection made by the player is actually a valid one
            if(usrChoice == 0){
                // Leave
                return -1;
            } else {
                switch (p->zaino[usrChoice-1]) {
                    case 3:{
                        // calmanti
                        // Mental health value can't go above 200
                        if(p->sanita_mentale+40 <= 200){
                            p->sanita_mentale = p->sanita_mentale + 40;
                        } else {
                            p->sanita_mentale = 200;
                        }
                        printf("\n                        Hai usato i Calmanti, la tua salute mentale e' ora %d!\n", p->sanita_mentale);
                        p->zaino[usrChoice-1] = (int) nessun_oggetto;
                        return 1;
                    }
                    case 4:{
                        // sale
                        printf("\n                     Hai usato il Sale, se comparira' un Fantasma sarai al sicuro!\n");
                        p->zaino[usrChoice-1] = (int) nessun_oggetto;
                        return 2;
                    }
                    case 10:{
                        // adrenalina
                        printf("\n                            Hai usato l'Adrenalina, potrai avanzare due volte!\n");
                        p->zaino[usrChoice-1] = (int) nessun_oggetto;
                        return 3;
                    }
                    case 11:{
                        // cento_dollari
                        if(rand() % 2 == 0){
                            // calmanti
                            p->zaino[usrChoice-1] = 3;
                            printf("\n                     Hai usato i 100 Dollari, in cambio hai ricevuto dei Calmanti!\n");
                        } else {
                            // sale
                            p->zaino[usrChoice-1] = 4;
                            printf("                        Hai usato i 100 Dollari, in cambio hai ricevuto del Sale!\n");
                        }
                        return 1;
                    }
                    case 12:{
                        // coltello
                        printf("\nHai usato il Coltello, ");
                        if(p->sanita_mentale < 30){
                            for(i=0; i< playerNumber; i++){
                                if(giocatori[i] != p){
                                    if(giocatori[i]->posizione == p->posizione){
                                        if(!kill){
                                            printf("in un attacco di rabbia uccidi ");
                                            kill = true;
                                        }
                                        giocatori[i]->sanita_mentale = 0;
                                        printf("%s ", giocatori[i]->nome_giocatore);
                                    }
                                }
                                printf("\n");
                            }
                            if(!kill){
                                printf("hai avuto un attacco di rabbia!\nFortunatamente non c'era nessuno nelle vicinanze.\n");
                            } else {
                                printf("!\n");
                            }
                        } else {
                            printf("non succede niente...\n");
                        }
                        p->zaino[usrChoice-1] = (int) nessun_oggetto;
                        return 1;
                    }
                    default:{
                        printf("\nNon e' possibile usare l'oggetto selezionato!\n");
                        usrChoice = -1;
                    }
                }
            }
        } else {
            //the selection made by the player is either an invalid type or not an option
            printf("\n\n                            AN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN!\n\n");
            scanf("%*[^\n]%*c");
            //This "flushes" the stdin buffer up until the \n
            /* the %*[^\n] part scans the buffer until it finds a \n
             * the * part discards whatever was just scanned
             * The %*c scans and discards the \n left by the first part
             * */
        }
    }while(1);
}

static void avanza(struct Giocatore* p){
    p->posizione = p->posizione->prossima_zona;
    p->posizione->prova = (enum Tipo_prova) genera_prova();
}

static int torna_caravan(struct Giocatore* p){
    // return 1 if all the evidence has been "deposited" and the game is over,
    // return 0 if this piece of evidence has been "deposited" correctly
    // return -1 if no piece of evidence has been "deposited"
    int i, x;
    bool alr_dep, all_dep, tof;
    int ret = -1;

    p->posizione = zona_caravan;
    alr_dep = false;
    tof= false;

    printf("\n\n%s decide di tornare al caravan!", p->nome_giocatore);

    for(i=0;i<4;i++){
        // For every position of the player's backpack
        if(p->zaino[i] >= 30 && p->zaino[i] <= 32){
            // Check if the i-th element of the Player is a piece of evidence
            switch (p->zaino[i]) {
                case 30:{
                    printf("\nHa raccolto una prova con l'EMF!");
                    break;
                }
                case 31:{
                    printf("\nHa raccolto una prova con lo Spirit Box!");
                    break;
                }
                case 32:{
                    printf("\nHa registrato una prova con la Videocamera");
                    break;
                }
            }

            for(x=0; x<3; x++){
                // Check if the evidence has been deposited already
                if(p->zaino[i] == (int) prove_raccolte[x]){
                    // The Piece of evidence has been already deposited
                    alr_dep = true;
                }
            }
            if(!alr_dep){
                // The evidence hasn't been deposited yet
                // Find the first empty position of the prove_raccolte array and place the evidence there
                for(x=0; x<3;x++){
                    if(prove_raccolte[x] == nessuna_prova){
                        prove_raccolte[x] = p->zaino[i];
                        ret = 0;
                        printf("\nLa prova viene lasciata nel Caravan per essere analizzata!");
                        level += 5;
                        break;
                    }
                }
            } else {
                printf("\nUna prova identica era gia' stata trovata, %s la butta nel secchio", p->nome_giocatore);
            }
            p->zaino[i]=nessun_oggetto;
            tof= true;
            alr_dep = false;
        }
    }

    all_dep = true;
    // Check if all the pieces of evidence have been deposited
    for (i = 0; i < 3; i++){
        if(prove_raccolte[i] == nessuna_prova){
            // There is at least one piece of evidence that has yet to be "deposited"
            all_dep = false;
            ret = 0;
            break;
        }
    }
    if(all_dep){
        // All the evidence has been "deposited"
        ret = 1;
        printf("\nQuesta era l'ultima prova!\n");
    } else if (ret == -1){
        printf("\n%s non ha prove da depositare, beve un caffe'!\n", p->nome_giocatore);
    } else if (tof){
        //At least one piece of evidence is yet to be found
        for (x = 0; x < 4; x++) {
            // For each position of the Player's backpack
            if(p->zaino[x] == (int) nessun_oggetto){
                for (int y = 0; y < 20; ++y) {
                    i = rand() % 3;
                    if(i+30 != prove_raccolte[0] && i+30 != prove_raccolte[1] && i+30 != prove_raccolte[2]){
                        p->zaino[x] = i;
                        switch (i) {
                            case 0:{
                                printf("\n%s in un cassetto del Caravan trova un EMF e lo raccoglie\n", p->nome_giocatore);
                                break;
                            }
                            case 1:{
                                printf("\n%s per terra davanti al Caravan trova uno Spirit Box e lo raccoglie\n", p->nome_giocatore);
                                break;
                            }
                            case 2:{
                                printf("\n%s in un ripiano del Caravan trova una videocamera e la raccoglie\n", p->nome_giocatore);
                                break;
                            }
                        }
                        break;
                    }
                }

                break;
            }
        }
    }
    p->posizione = pFirst;
    return ret;
}

int imposta_gioco(){
    time_t t;
    srand((unsigned)time(&t));


    int z, x, y;
    printf("\n-------------------------------------------------------------------------------------------------------------"
           "\n|                                                                                                            |"
           "\n|                                                                                                            |"
           "\n|                                                                                                            |"
           "\n|                                                                                                            |"
           "\n|                                                                                                            |"
           "\n|                                                                                                            |"
           "\n|                                                                                                            |"
           "\n|                                                                                                            |"
           "\n|               Modificare la finestra cosi' da renderla della stessa misura del rettangolo                  |"
           "\n|                                                                                                            |"
           "\n|                                    Poi premere INVIO per continuare                                        |"
           "\n|                                                                                                            |"
           "\n|                                                                                                            |"
           "\n|                                                                                                            |"
           "\n|                                                                                                            |"
           "\n|                                                                                                            |"
           "\n|____________________________________________________________________________________________________________|");
    while( getchar() != '\n' );
    // Dynamic memory deallocation
    if(giocatori[0] != NULL){
        free(zona_caravan);
        for(x=0;x<4;x++){
            free(giocatori[x]);
        }
        struct Zona_mappa* tmp = pFirst;
        for (x=0;tmp->prossima_zona != pFirst;x++) {
            tmp = tmp->prossima_zona;
        }
        for(y=x;y>0;y--){
            tmp = pFirst;
            for (z=0;z<y;z++) {
                tmp = tmp->prossima_zona;
            }
            free(tmp);
        }
        free(pFirst);
    }

    bool valid;
    int usrChoice = -1;
    level = 0;

    do {

        cls();
        printf("\n\n\n\n\n\n\n                                        Insert the number of players"
               "\n                                                    (1-4)"
               "\n\n\n\n\n\n\n\n\n>");
        exitCode = scanf("%d", &playerNumber);

        if (exitCode==1 && playerNumber >= 1 && playerNumber <= 4) {
            // The selection made by the player is actually a valid one
            valid = true;
        } else {
            // The selection made by the player is either an invalid type or not an option
            valid = false;
            printf("\n\n                            AN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN!\n\n");
            scanf("%*[^\n]%*c");
            // This "flushes" the stdin buffer up until the \n
            /* the %*[^\n] part scans the buffer until it finds a \n
             * the * part discards whatever was just scanned
             * The %*c scans and discards the \n left by the first part
             * */
        }
    } while (!valid);

    int turni[playerNumber];

    // Allocate memory and initialize the first zone of the map
    pFirst = malloc(sizeof(struct Zona_mappa));
    pLast = pFirst;
    pFirst->prossima_zona = pLast;
    pFirst->zona = (enum Tipo_zona) genera_zona();
    pFirst->oggetto_zona = nessun_oggetto;
    pFirst->prova = nessuna_prova;

    // Cleans Up buffer for the fgets after the scanf (which leaves an /n)
    while ((getchar()) != '\n');

    for(z=0; z<4;z++){
        if(z<playerNumber){
            // Allocate memory and initialize the z-th player
            giocatori[z] = malloc(sizeof(struct Giocatore));
            // Insert Name
            do {
                for (x=0;x<z;x++) {

                }
                printf("\nPlayer %d, Insert Your Name:", z+1);

                fgets(giocatori[z]->nome_giocatore, 64, stdin);
                // fgets reads up to and including a /n, which I have to remove
                for (x = 0; x < 64 && giocatori[z]->nome_giocatore[x] != 0; x++) {
                    if (giocatori[z]->nome_giocatore[x] == 10) {
                        // Terminate string at first \n
                        giocatori[z]->nome_giocatore[x] = 0;
                        break;
                    }
                }
                if (giocatori[z]->nome_giocatore[0] == 0 || giocatori[z]->nome_giocatore[0] == 10) {
                    // String is either empty or just made of an \n
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
                     * The printf prevents the player from having to press enter twice
                     * */
                }

            } while (!valid);



            // Everyone's mental health starts from 100
            giocatori[z]->sanita_mentale = 100;
            // Everyone starts from the first zone
            giocatori[z]->posizione = pFirst;
            // Backpack gets filled of nessun_oggetto
            for(x=0; x<4; x++){
                giocatori[z]->zaino[x] = 13;

            }

        } else {
            // z-th player isn't playing so it's NULL
            giocatori[z] = NULL;
        }
    }

    do {
        printf("\n\n Select Difficulty"
               "\n  1)Dilettante"
               "\n  2)Intermedio"
               "\n  3)Incubo"
               "\nLa tua Scelta:");
        exitCode = scanf("%d", &usrChoice);
        if (exitCode==1 && usrChoice >= 1 && 3 >= usrChoice) {
            //The selection made by the player is actually a valid one
            valid = true;
        } else {
            //the selection made by the player is either an invalid type or not an option
            valid = false;
            printf("\n\n                            AN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN!\n\n");
            scanf("%*[^\n]%*c");
            //This "flushes" the stdin buffer up until the \n
            /* the %*[^\n] part scans the buffer until it finds a \n
             * the * part discards whatever was just scanned
             * The %*c scans and discards the \n left by the first part
             * */
        }
        switch (usrChoice) {
            case 1:{
                level = 30;
                break;
            }
            case 2:{
                level = 50;
                break;
            }
            case 3:{
                level = 70;
                break;
            }

        }
    } while (!valid);


    // Generate starting items
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

    turn_manager(turni);

    printf("\nScelta degli oggetti iniziali:");
    for(z=0; z<playerNumber; z++){
        printf("\nGiocatore %d, %s:", turni[z]+1, giocatori[turni[z]]->nome_giocatore);
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
                case 99:{
                    printf("Oggetto gia preso");
                    break;
                }
            }
            printf("|");
        }
        do {
            printf("\nLa tua Scelta:");
            exitCode = scanf("%d", &usrChoice);
            if (exitCode==1 && usrChoice >= 1 && usrChoice <= playerNumber) {
                //The selection made by the player is actually a valid one
                valid = true;
                switch (oggetti_iniziali[usrChoice-1]) {
                    case 0:{
                        printf("\n\nGiocatore %d ha scelto EMF!\n\n", turni[z]+1);
                        giocatori[turni[z]]->zaino[0] = 0;
                        break;
                    }
                    case 1:{
                        printf("\n\nGiocatore %d ha scelto Spirit Box!\n\n", turni[z]+1);
                        giocatori[turni[z]]->zaino[0] = 1;
                        break;
                    }
                    case 2:{
                        printf("\n\nGiocatore %d ha scelto Videocamera\n\n", turni[z]+1);
                        giocatori[turni[z]]->zaino[0] = 2;
                        break;
                    }
                    case 3:{
                        printf("\n\nGiocatore %d ha scelto Calmanti\n\n", turni[z]+1);
                        giocatori[turni[z]]->zaino[0] = 3;
                        break;
                    }
                    case 4:{
                        printf("\n\nGiocatore %d ha scelto Sale\n\n", turni[z]+1);
                        giocatori[turni[z]]->zaino[0] = 4;
                        break;
                    }
                    case 99:{
                        valid = false;
                        printf("\n\nNon puoi avere un oggetto che e' gia' stato preso!\n\n");
                        break;
                    }
                    default:{
                        valid = false;
                        printf("\n\n                            AN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN!\n\n");
                        scanf("%*[^\n]%*c");
                        break;
                    }

                }
            } else {
                //the selection made by the player is either an invalid type or not an option
                valid = false;
                printf("\n\nAN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN\n\n");
                scanf("%*[^\n]%*c");
                //This "flushes" the stdin buffer up until the \n
                /* the %*[^\n] part scans the buffer until it finds a \n
                 * the * part discards whatever was just scanned
                 * The %*c scans and discards the \n left by the first part
                 * */
            }
            oggetti_iniziali[usrChoice-1] = 99;
        } while (!valid);
    }




    // Game master's Menu
    do {
        do {
            printf("\n\n Game Master, e' ora di generare la mappa di Gioco!"
                   "\n  1)Inserisci una Zona"
                   "\n  2)Cancella l'ultima zona"
                   "\n  3)Stampa La Mappa"
                   "\n  4)Termina e Salva"
                   "\nLa tua Scelta:");
            exitCode = scanf("%d", &usrChoice);

            if (exitCode==1 && usrChoice >= 1 && usrChoice <= 4) {
                //The selection made by the player is actually a valid one
                valid = true;
                scanf("%*[^\n]%*c");
                //This "flushes" the stdin buffer up until the \n
                /* the %*[^\n] part scans the buffer until it finds a \n
                 * the * part discards whatever was just scanned
                 * The %*c scans and discards the \n left by the first part
                 * */
                switch (usrChoice) {
                    case 1:{
                        inserisci_zona();
                        break;
                    }
                    case 2:{
                        cancella_zona();
                        break;
                    }
                    case 3:{
                        stampa_mappa();
                        break;
                    }
                }
            } else {
                //the selection made by the player is either an invalid type or not an option
                valid = false;
                printf("\n\n                            AN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN!\n\n");
                scanf("%*[^\n]%*c");
                //This "flushes" the stdin buffer up until the \n
                /* the %*[^\n] part scans the buffer until it finds a \n
                 * the * part discards whatever was just scanned
                 * The %*c scans and discards the \n left by the first part
                 * */
                usrChoice = -1;
            }

        } while (!valid);
        if(pLast->prossima_zona == pFirst->prossima_zona && usrChoice == 4){
            printf("\nNon e' possibile giocare solamente nella zona iniziale, inseriscine almeno un'altra\n");
            usrChoice = 0;
        }
    }while(usrChoice != 4);

    /*
     * It doesn't really make sense to actually make a caravan zone but the assignment is clear, it would be better off
     * just making the player think there is one and just directly place him on the pFirst zone.
     * */
    zona_caravan = malloc(sizeof(struct Zona_mappa));
    zona_caravan->prossima_zona = pFirst;
    zona_caravan->oggetto_zona = nessun_oggetto;
    zona_caravan->prova = nessuna_prova;
    zona_caravan->zona = caravan;

    //Initialize the collected evidences array
    for(x=0;x<3;x++){
        prove_raccolte[x] = nessuna_prova;
    }
    free(oggetti_iniziali);
    return 0;
}

int gioca(){
    int turni[playerNumber];
    bool valid, won, ghost, salt;
    int x, z, y, usrChoice, adv, ret;
    won = false;
    if(giocatori[0] == NULL|| pFirst == NULL || pLast == NULL){
        // Setup error
        printf("\nE' avvenuto un errore durante l'impostazione del Gioco");
        return -1;
    }
    do {
        valid = false;

        // Check if there is at least a player that is alive
        for(x=0;x<playerNumber && valid == false;x++){
            if(giocatori[x]->sanita_mentale>0){
                valid = true;
            }
        }
        if(!valid){
            break;
        }

        turn_manager(turni);
        for (x = 0; x < playerNumber && !won; x++) {
            if(giocatori[turni[x]]->sanita_mentale == 0){
                // If the player that should have played this turn is dead (0 Mental Health), then skip to the next one
                continue;
            }
            // The player is alive!
            adv=1;

            printf("\n\n%s (Player %d), it's your turn!", giocatori[turni[x]]->nome_giocatore, turni[x]+1);

            // Show Menu
            do {
                do {

                    printf("\n  1)Torna Al Caravan"
                           "\n  2)Mostra i dati del Giocatore"
                           "\n  3)Mostra la zona corrente"
                           "\n  4)Avanza alla prossima zona"
                           "\n  5)Raccogli la prova"
                           "\n  6)Raccogli l'oggetto"
                           "\n  7)Usa un Oggetto"
                           "\n  8)Passa"
                           "\nLa tua Scelta:");
                    exitCode = scanf("%d", &usrChoice);

                    if (exitCode==1 && usrChoice >= 1 && usrChoice <= 8) {
                        //The selection made by the player is actually a valid one
                        valid = true;
                        scanf("%*[^\n]%*c");
                        //This "flushes" the stdin buffer up until the \n
                        /* the %*[^\n] part scans the buffer until it finds a \n
                         * the * part discards whatever was just scanned
                         * The %*c scans and discards the \n left by the first part
                         * */
                        switch (usrChoice) {
                            case 1:{
                                if(torna_caravan(giocatori[turni[x]]) == 1){
                                    //All the evidence has been collected, the game is over
                                    won = true;
                                }
                                usrChoice = 8;
                                printf("\n%s (Player %d), alla prossima!", giocatori[turni[x]]->nome_giocatore, turni[x]+1);
                                break;
                            }
                            case 2:{
                                // Display Player data
                                stampa_giocatore(giocatori[turni[x]]);
                                break;
                            }
                            case 3:{
                                // Display current zone data
                                stampa_zona(giocatori[turni[x]]->posizione);
                                break;
                            }
                            case 4:{
                                if(adv>0){
                                    avanza(giocatori[turni[x]]);
                                    adv--;
                                    printf("\n%s avanza!\n", giocatori[turni[x]]->nome_giocatore);
                                    decrementa_sanita(giocatori[turni[x]]);
                                } else {
                                    printf("\nNon e' possibile avanzare ulteriormente in questo turno!\n");
                                }
                                break;
                            }
                            case 5:{
                                if(raccogli_prova(giocatori[turni[x]]) == 1){
                                    // Evidence Picked Up correctly
                                    if(fantasma() == 1){
                                        ghost = true;
                                    }
                                    decrementa_sanita(giocatori[turni[x]]);
                                }
                                break;
                            }
                            case 6:{
                                if(giocatori[turni[x]]->posizione == pFirst){
                                    printf("\nNon ci sono oggetti nella zona Iniziale!\n");
                                } else {
                                    if(raccogli_oggetto(giocatori[turni[x]]) == 1){
                                        decrementa_sanita(giocatori[turni[x]]);
                                    }
                                }
                                break;
                            }
                            case 7:{
                                ret = usa_oggetto(giocatori[turni[x]]);
                                if(ret == 2){
                                    // Player Used Salt
                                    salt = true;
                                } else if(ret == 3){
                                    // Player used Adrenaline, he will be able to advance one more time
                                    adv += 1;
                                } else if(ret == -1){
                                    // If usa_oggetto returns -1 it means that no item has been actually used, i don't consider that an action and so there is no point decrementing the player's mental health
                                    break;
                                }
                                decrementa_sanita(giocatori[turni[x]]);
                                break;
                            }
                            case 8:{
                                printf("\n%s (Player %d), alla prossima!", giocatori[turni[x]]->nome_giocatore, turni[x]+1);
                                break;
                            }
                            default:{
                                // Impossible to enter but better be safe than sorry
                                valid = false;
                                printf("\n\n                            AN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN!\n\n");
                                scanf("%*[^\n]%*c");
                                //This "flushes" the stdin buffer up until the \n
                                /* the %*[^\n] part scans the buffer until it finds a \n
                                 * the * part discards whatever was just scanned
                                 * The %*c scans and discards the \n left by the first part
                                 * */
                                usrChoice = -1;
                            }
                        }
                    } else {
                        //the selection made by the player is either an invalid type or not an option
                        valid = false;
                        printf("\n\n                            AN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN!\n\n");
                        scanf("%*[^\n]%*c");
                        //This "flushes" the stdin buffer up until the \n
                        /* the %*[^\n] part scans the buffer until it finds a \n
                         * the * part discards whatever was just scanned
                         * The %*c scans and discards the \n left by the first part
                         * */
                        usrChoice = -1;
                    }
                } while (!valid);
                if(ghost){
                    // A ghost has spawned
                    if(salt){
                        printf("\nIl Giocatore aveva usato il sale, il fantasma non ha nessun potere su di lui!\n");
                    } else {
                        if(level < 50){
                            // Dilettante
                            if(giocatori[turni[x]]->sanita_mentale <= (level - 20)){
                                giocatori[turni[x]]->sanita_mentale = 0;
                            } else {
                                giocatori[turni[x]]->sanita_mentale = giocatori[turni[x]]->sanita_mentale - (level - 20);

                            }
                            // The decrement of the players mental health will be 10 + 5 * (number of picked up evidence)
                        } else if(level < 70){
                            // Intermedio
                            if(giocatori[turni[x]]->sanita_mentale <= (level - 30)){
                                giocatori[turni[x]]->sanita_mentale = 0;
                            } else {
                                giocatori[turni[x]]->sanita_mentale = giocatori[turni[x]]->sanita_mentale - (level - 30);

                            }
                            // The decrement of the players mental health will be 20 + 5 * (number of picked up evidence)
                        } else {
                            // Incubo
                            if(giocatori[turni[x]]->sanita_mentale <= (level - 40)){
                                giocatori[turni[x]]->sanita_mentale = 0;
                            } else {
                                giocatori[turni[x]]->sanita_mentale = giocatori[turni[x]]->sanita_mentale - (level - 40);

                            }
                            // The decrement of the players mental health will be 30 + 5 * (number of picked up evidence)
                        }
                        printf("\n%s appena visto il Fantasma, da di matto, la sua sanita' mentale scende a %d\n", giocatori[turni[x]]->nome_giocatore, giocatori[turni[x]]->sanita_mentale);
                    }
                    ghost = false;
                }
                salt = false;
                if(giocatori[turni[x]]->sanita_mentale == 0){
                    // The player has just died
                    printf("\n\n%s (Player %d), e' impazzito e gli spiriti se lo sono preso!", giocatori[turni[x]]->nome_giocatore, turni[x]+1);
                    usrChoice = 8;
                }
            }while(usrChoice != 8);

            // If there is at least 1 player that has an item that can be used to pick up evidence, the game will continue, if not it won't
            valid = false;
            for (y=0;y<playerNumber;y++) {
                if(giocatori[y]->sanita_mentale > 0){
                    //Player is still alive
                    for (z=0;z<4;z++) {
                        if(giocatori[y]->zaino[z] >= 0 && giocatori[y]->zaino[z] <= 2){
                            valid = true;
                        }
                    }
                }
            }
            if(!valid){
                break;
            }
        }

    }while(valid && !won);
    if(won){
        printf("\n\n"
               "\n  _____                        __       __         _           _ __"
               "\n / ___/__  ___  ___ ________ _/ /___ __/ /__ ____ (_)__  ___  (_) /"
               "\n/ /__/ _ \\/ _ \\/ _ `/ __/ _ `/ __/ // / / _ `/_ // / _ \\/ _ \\/ /_/ "
               "\n\\___/\\___/_//_/\\_, /_/  \\_,_/\\__/\\_,_/_/\\_,_//__/_/\\___/_//_/_(_)  "
               "\n              /___/"
               "\n                    I Giocatori hanno vinto!");
    } else if(!valid){
        printf("\n\n"
               "\n _______  _______  __   __  _______    _______  __   __  _______  ______   "
               "\n|       ||   _   ||  |_|  ||       |  |       ||  | |  ||       ||    _ |  "
               "\n|    ___||  |_|  ||       ||    ___|  |   _   ||  |_|  ||    ___||   | ||  "
               "\n|   | __ |       ||       ||   |___   |  | |  ||       ||   |___ |   |_||_ "
               "\n|   ||  ||       ||       ||    ___|  |  |_|  ||       ||    ___||    __  |"
               "\n|   |_| ||   _   || ||_|| ||   |___   |       | |     | |   |___ |   |  | |"
               "\n|_______||__| |__||_|   |_||_______|  |_______|  |___|  |_______||___|  |_|"
               "\n                      I Giocatori sono impazziti!");
    }
    printf("\n     %s", giocatori[0]->nome_giocatore);
    for (x=1;x<playerNumber;x++) {
        printf(", %s", giocatori[x]->nome_giocatore);
    }
    printf(", Grazie per aver giocato a PhalsoPhobia!");

    // Dynamic memory deallocation
    free(zona_caravan);
    for(x=0;x<4;x++){
        free(giocatori[x]);
    }
    struct Zona_mappa* tmp = pFirst;
    for (x=0;tmp->prossima_zona != pFirst;x++) {
        tmp = tmp->prossima_zona;
    }
    for(y=x;y>0;y--){
        tmp = pFirst;
        for (z=0;z<y;z++) {
            tmp = tmp->prossima_zona;
        }
        free(tmp);
    }
    free(pFirst);

    return 0;
}

int termina_gioco(){
    printf("\nPhalsoPhobia - a game in C"
           "\nCoded by Milli Alessandro"
           "\n Bye!");
    return 0;
}

void istruzioni(){

}
