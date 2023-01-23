#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> //bho
#include "gamelib.h"

//Ubuntu 20.4 gcc 9.3.0
int main() {
    //Logo

    time_t t;
    srand((unsigned) time( & t));
    unsigned char exitCode;
    int usrChoice;
    bool valid, set;
    switch (rand() % 5) {
        case 0:
            printf("\n"
                   "   ▄▄▄· ▄ .▄ ▄▄▄· ▄▄▌  .▄▄ ·        ▄▄▄· ▄ .▄      ▄▄▄▄· ▪   ▄▄▄·\n"
                   "  ▐█ ▄███▪▐█▐█ ▀█ ██•  ▐█ ▀. ▪     ▐█ ▄███▪▐█▪     ▐█ ▀█▪██ ▐█ ▀█\n"
                   "   ██▀·██▀▐█▄█▀▀█ ██▪  ▄▀▀▀█▄ ▄█▀▄  ██▀·██▀▐█ ▄█▀▄ ▐█▀▀█▄▐█·▄█▀▀█\n"
                   "  ▐█▪·•██▌▐▀▐█ ▪▐▌▐█▌▐▌▐█▄▪▐█▐█▌.▐▌▐█▪·•██▌▐▀▐█▌.▐▌██▄▪▐█▐█▌▐█ ▪▐▌\n"
                   "  .▀   ▀▀▀ · ▀  ▀ .▀▀▀  ▀▀▀▀  ▀█▄▀▪.▀   ▀▀▀ · ▀█▄▀▪·▀▀▀▀ ▀▀▀ ▀  ▀\n"
                   "                          a game in C\n");
            break;
        case 1:
            printf("\n"
                   "  __________.__           .__              __________.__          ___.   .__        \n"
                   "  \\______   \\  |__ _____  |  |   __________\\______   \\  |__   ____\\_ |__ |__|____   \n"
                   "   |     ___/  |  \\\\__  \\ |  |  /  ___/  _ \\|     ___/  |  \\ /  _ \\| __ \\|  \\__  \\  \n"
                   "   |    |   |   Y  \\/ __ \\|  |__\\___ (  <_> )    |   |   Y  (  <_> ) \\_\\ \\  |/ __ \\_\n"
                   "   |____|   |___|  (____  /____/____  >____/|____|   |___|  /\\____/|___  /__(____  /\n"
                   "                 \\/     \\/          \\/                    \\/           \\/        \\/ \n"
                   "                                   a game in C\n");
            break;
        case 2:
            printf("\n"
                   "      ____  __          __           ____  __          __    _      \n"
                   "     / __ \\/ /_  ____ _/ /________  / __ \\/ /_  ____  / /_  (_)___ _\n"
                   "    / /_/ / __ \\/ __ `/ / ___/ __ \\/ /_/ / __ \\/ __ \\/ __ \\/ / __ `/\n"
                   "   / ____/ / / / /_/ / (__  ) /_/ / ____/ / / / /_/ / /_/ / / /_/ / \n"
                   "  /_/   /_/ /_/\\__,_/_/____/\\____/_/   /_/ /_/\\____/_.___/_/\\__,_/  \n"
                   "                           a game in C\n");
            break;
        case 3:
            printf("\n"
                   "   ██▓███   ██░ ██  ▄▄▄       ██▓      ██████  ▒█████   ██▓███   ██░ ██  ▒█████   ▄▄▄▄    ██▓ ▄▄▄      \n"
                   "  ▓██░  ██▒▓██░ ██▒▒████▄    ▓██▒    ▒██    ▒ ▒██▒  ██▒▓██░  ██▒▓██░ ██▒▒██▒  ██▒▓█████▄ ▓██▒▒████▄    \n"
                   "  ▓██░ ██▓▒▒██▀▀██░▒██  ▀█▄  ▒██░    ░ ▓██▄   ▒██░  ██▒▓██░ ██▓▒▒██▀▀██░▒██░  ██▒▒██▒ ▄██▒██▒▒██  ▀█▄  \n"
                   "  ▒██▄█▓▒ ▒░▓█ ░██ ░██▄▄▄▄██ ▒██░      ▒   ██▒▒██   ██░▒██▄█▓▒ ▒░▓█ ░██ ▒██   ██░▒██░█▀  ░██░░██▄▄▄▄██ \n"
                   "  ▒██▒ ░  ░░▓█▒░██▓ ▓█   ▓██▒░██████▒▒██████▒▒░ ████▓▒░▒██▒ ░  ░░▓█▒░██▓░ ████▓▒░░▓█  ▀█▓░██░ ▓█   ▓██▒\n"
                   "  ▒▓▒░ ░  ░ ▒ ░░▒░▒ ▒▒   ▓▒█░░ ▒░▓  ░▒ ▒▓▒ ▒ ░░ ▒░▒░▒░ ▒▓▒░ ░  ░ ▒ ░░▒░▒░ ▒░▒░▒░ ░▒▓███▀▒░▓   ▒▒   ▓▒█░\n"
                   "  ░▒ ░      ▒ ░▒░ ░  ▒   ▒▒ ░░ ░ ▒  ░░ ░▒  ░ ░  ░ ▒ ▒░ ░▒ ░      ▒ ░▒░ ░  ░ ▒ ▒░ ▒░▒   ░  ▒ ░  ▒   ▒▒ ░\n"
                   "  ░░        ░  ░░ ░  ░   ▒     ░ ░   ░  ░  ░  ░ ░ ░ ▒  ░░        ░  ░░ ░░ ░ ░ ▒   ░    ░  ▒ ░  ░   ▒   \n"
                   "            ░  ░  ░      ░  ░    ░  ░      ░      ░ ░            ░  ░  ░    ░ ░   ░       ░        ░  ░\n"
                   "                                                                                       ░               \n"
                   "                                            a game in C\n");
            break;
        case 4:
            printf("\n"
                   "  █ ▄▄   ▄  █ ██   █      ▄▄▄▄▄   ████▄ █ ▄▄   ▄  █ ████▄ ███   ▄█ ██   \n"
                   "  █   █ █   █ █ █  █     █     ▀▄ █   █ █   █ █   █ █   █ █  █  ██ █ █  \n"
                   "  █▀▀▀  ██▀▀█ █▄▄█ █   ▄  ▀▀▀▀▄   █   █ █▀▀▀  ██▀▀█ █   █ █ ▀ ▄ ██ █▄▄█ \n"
                   "  █     █   █ █  █ ███▄ ▀▄▄▄▄▀    ▀████ █     █   █ ▀████ █  ▄▀ ▐█ █  █ \n"
                   "   █       █     █     ▀                 █       █        ███    ▐    █ \n"
                   "    ▀     ▀     █                         ▀     ▀                    █  \n"
                   "               ▀                                                    ▀   \n"
                   "                          a game in C\n");
            break;
        default:
            printf("\n           PhalsoPhobia:\n            a game in C");
            break;

    }
    //Menu

    do {
        //Menu and selection validation
        do {
            printf("1)Set Game\n"
                   "2)Play\n"
                   "3)Exit\n"
                   "Your Choice:");
            exitCode = scanf("%d", &usrChoice);
            scanf("%*[^\n]%*c");
            //This "flushes" the stdin buffer up until the \n
            /* the %*[^\n] part scans the buffer until it finds a \n
             * the * part discards whatever was just scanned
             * The %*c scans and discards the \n left by the first part
             * */
            if (exitCode==1 && usrChoice >= 1 && usrChoice <= 3) {
                //The selection made by the user is actually a valid one
                valid = true;
            } else {
                //the selection made by the user is either an invalid type or not an option
                valid = false;
                printf("\n\nAN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN\n\n");

            }
        } while (!valid);

        //qui metti tutto (switch)
        switch (usrChoice) {
            case 1:
                /* Si può impostare il gioco più volte di fila prima di combattere
                 * (liberare ogni volta tutta la memoria dinamica allocata precedentemente)
                 */
                imposta_gioco();
                set = true;
                break;
            case 2:
                if(set){
                    gioca();
                    /*
                     * Non si può combattere se prima non è stato impostato il gioco.
                     * Una volta che il combattimento è finito, si torna sempre a questo menu
                     * */
                    //Una volta terminato il combattimento
                    set = false;
                } else {
                    printf("You have to set the game before you can play!\n");
                }
                break;
            case 3:
                termina_gioco();
                break;
            default:
                printf("Some Unknown Error Happened, Try Again\n");
                break;

        }

        //rivedi, perché il gioco va terminato conla funzione terminagioco()
    } while (usrChoice != 3);
    return 0;
}