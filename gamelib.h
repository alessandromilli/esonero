#ifndef ESONERO_GAMELIB_H
#define ESONERO_GAMELIB_H

#endif //ESONERO_GAMELIB_H

//dichiarazioni enum
enum Tipo_oggetto_iniziale {EMF = 0,spirit_box = 1, videocamera = 2, calmanti = 3, sale = 4};
enum Tipo_oggetto_zona {adrenalina = 10, cento_dollari = 11, coltello = 12, nessun_oggetto = 13};
enum Tipo_zona {caravan = 29, cucina = 20, soggiorno = 21, camera = 22, bagno = 23, garage = 24, seminterrato = 25};
enum Tipo_prova {prova_EMF = 30, prova_spirit_box = 31, prova_videocamera = 32, nessuna_prova = 33};


//dichiarazioni struct
struct Giocatore{
    char nome_giocatore[65];
    // array di caratteri che rappresenta il nome del giocatore 64 lettere + terminatore di stringa
    unsigned char sanita_mentale;
    //sanità che parte da 100 per ogni giocatore
    struct Zona_mappa* posizione;
    // contenente il puntatore alla zona dove si trova il giocatore
    unsigned char zaino[4];
    /*
     * una posizione dell’array può memorizzare il valore che identifica l’oggetto enum Tipo_oggetto_iniziale,
     * enum Tipo_oggetto_zona,
     * enum Tipo_prova corrispondente all’oggetto/prova presente in quello slot dello zaino. Da notare che uno slot può essere anche
     * “vuoto” non presente in nessuno dei tre enum che possono trovarsi in uno slot (aggiungere a piacere).
     * Per esempio, se zaino[1] vale 1, e 1 rappresenta il coltello, allora nella seconda posizione dello zaino si
     * trova il coltello.
     * */
};
struct Zona_mappa{
    enum Tipo_zona zona;
    enum Tipo_oggetto_zona oggetto_zona;
    enum Tipo_prova prova;
    struct Zona_mappa* prossima_zona;
};


//dicharazioni tre funzioni
int imposta_gioco();
int gioca();
int termina_gioco();