enum Tipo_oggetto_iniziale {EMF = 0,spirit_box = 1, videocamera = 2, calmanti = 3, sale = 4};
enum Tipo_oggetto_zona {adrenalina = 10, cento_dollari = 11, coltello = 12, nessun_oggetto = 13};
enum Tipo_zona {caravan = 29, cucina = 20, soggiorno = 21, camera = 22, bagno = 23, garage = 24, seminterrato = 25};
enum Tipo_prova {prova_EMF = 30, prova_spirit_box = 31, prova_videocamera = 32, nessuna_prova = 33};

struct Giocatore{
    char nome_giocatore[65];
    unsigned char sanita_mentale;
    struct Zona_mappa* posizione;
    unsigned char zaino[4];
};

struct Zona_mappa{
    enum Tipo_zona zona;
    enum Tipo_oggetto_zona oggetto_zona;
    enum Tipo_prova prova;
    struct Zona_mappa* prossima_zona;
};

int imposta_gioco();
int gioca();
int termina_gioco();
void istruzioni();