#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "gamelib.h"

int main() {
    time_t t;
    srand((unsigned) time( & t));
    unsigned char exitCode;
    int usrChoice;
    bool valid, set;
    //TODO OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
    //\a alarm
    // \r e \f da provare
    //For BOLD just replace the initial 0 before the ; with a 1. BOLD green would be\033[1;32m
    //Black \033[0;30m
    //Red \033[0;31m
    //Green \033[0;32m
    //Yellow \033[0;33m
    //Blue \033[0;34m
    //Purple \033[0;35m
    //Cyan \033[0;36m
    //White \033[0;37m
    printf("\n---------------------------------------------------------------------------------------------------------"
           "\n|                                                                                                    __  |"
           "\n|                                                                                                     /| |"
           "\n|                                                                                                    /   |"
           "\n|                                                                                                   /    |"
           "\n|                                                                                                  /     |"
           "\n|                                                                                                QUI     |"
           "\n|                                                                                                        |"
           "\n|                                                                                                        |"
           "\n|              Modificare la finestra cosi' da renderla della stessa misura del rettangolo               |"
           "\n|                                                                                                        |"
           "\n|                                    Poi premere INVIO per continuare                                    |"
           "\n|                                                                                                        |"
           "\n|                                                                                                        |"
           "\n|                                                                                                        |"
           "\n|                                                                                                        |"
           "\n|                                                                                                        |"
           "\n|________________________________________________________________________________________________________|");
    while(getchar()!='\n');
    getchar();
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
    printf("\e[1;1H\e[2J");
    printf("\n\n\n\n");
    switch (rand() % 5) {
        case 0:
            printf("\n"
                   "                   ▄▄▄· ▄ .▄ ▄▄▄· ▄▄▌  .▄▄ ·        ▄▄▄· ▄ .▄      ▄▄▄▄· ▪   ▄▄▄·\n"
                   "                  ▐█ ▄███▪▐█▐█ ▀█ ██•  ▐█ ▀. ▪     ▐█ ▄███▪▐█▪     ▐█ ▀█▪██ ▐█ ▀█\n"
                   "                   ██▀·██▀▐█▄█▀▀█ ██▪  ▄▀▀▀█▄ ▄█▀▄  ██▀·██▀▐█ ▄█▀▄ ▐█▀▀█▄▐█·▄█▀▀█\n"
                   "                  ▐█▪·•██▌▐▀▐█ ▪▐▌▐█▌▐▌▐█▄▪▐█▐█▌.▐▌▐█▪·•██▌▐▀▐█▌.▐▌██▄▪▐█▐█▌▐█ ▪▐▌\n"
                   "                  .▀   ▀▀▀ · ▀  ▀ .▀▀▀  ▀▀▀▀  ▀█▄▀▪.▀   ▀▀▀ · ▀█▄▀▪·▀▀▀▀ ▀▀▀ ▀  ▀\n"
                   "                                          a game in C\n");
            break;
        case 1:
            printf("\n"
                   "          __________.__           .__              __________.__          ___.   .__        \n"
                   "          \\______   \\  |__ _____  |  |   __________\\______   \\  |__   ____\\_ |__ |__|____   \n"
                   "           |     ___/  |  \\\\__  \\ |  |  /  ___/  _ \\|     ___/  |  \\ /  _ \\| __ \\|  \\__  \\  \n"
                   "           |    |   |   Y  \\/ __ \\|  |__\\___ (  <_> )    |   |   Y  (  <_> ) \\_\\ \\  |/ __ \\_\n"
                   "           |____|   |___|  (____  /____/____  >____/|____|   |___|  /\\____/|___  /__(____  /\n"
                   "                         \\/     \\/          \\/                    \\/           \\/        \\/ \n"
                   "                                           a game in C\n");
            break;
        case 2:
            printf("\n"
                   "                      ____  __          __           ____  __          __    _      \n"
                   "                     / __ \\/ /_  ____ _/ /________  / __ \\/ /_  ____  / /_  (_)___ _\n"
                   "                    / /_/ / __ \\/ __ `/ / ___/ __ \\/ /_/ / __ \\/ __ \\/ __ \\/ / __ `/\n"
                   "                   / ____/ / / / /_/ / (__  ) /_/ / ____/ / / / /_/ / /_/ / / /_/ / \n"
                   "                  /_/   /_/ /_/\\__,_/_/____/\\____/_/   /_/ /_/\\____/_.___/_/\\__,_/  \n"
                   "                                            a game in C\n");
            break;
        case 3:
            printf("\n"
                   "   ██▓███   ██░ ██  ▄▄▄       ██▓      ██████  ▒█████   ██▓███   ██░ ██  ▒█████   ▄▄▄▄    ██▓ ▄▄▄       \n"
                   "  ▓██░  ██▒▓██░ ██▒▒████▄    ▓██▒    ▒██    ▒ ▒██▒  ██▒▓██░  ██▒▓██░ ██▒▒██▒  ██▒▓█████▄ ▓██▒▒████▄     \n"
                   "  ▓██░ ██▓▒▒██▀▀██░▒██  ▀█▄  ▒██░    ░ ▓██▄   ▒██░  ██▒▓██░ ██▓▒▒██▀▀██░▒██░  ██▒▒██▒ ▄██▒██▒▒██  ▀█▄   \n"
                   "  ▒██▄█▓▒ ▒░▓█ ░██ ░██▄▄▄▄██ ▒██░      ▒   ██▒▒██   ██░▒██▄█▓▒ ▒░▓█ ░██ ▒██   ██░▒██░█▀  ░██░░██▄▄▄▄██  \n"
                   "  ▒██▒ ░  ░░▓█▒░██▓ ▓█   ▓██▒░██████▒▒██████▒▒░ ████▓▒░▒██▒ ░  ░░▓█▒░██▓░ ████▓▒░░▓█  ▀█▓░██░ ▓█   ▓██▒ \n"
                   "  ▒▓▒░ ░  ░ ▒ ░░▒░▒ ▒▒   ▓▒█░░ ▒░▓  ░▒ ▒▓▒ ▒ ░░ ▒░▒░▒░ ▒▓▒░ ░  ░ ▒ ░░▒░▒░ ▒░▒░▒░ ░▒▓███▀▒░▓   ▒▒   ▓▒█░ \n"
                   "  ░▒ ░      ▒ ░▒░ ░  ▒   ▒▒ ░░ ░ ▒  ░░ ░▒  ░ ░  ░ ▒ ▒░ ░▒ ░      ▒ ░▒░ ░  ░ ▒ ▒░ ▒░▒   ░  ▒ ░  ▒   ▒▒ ░ \n"
                   "  ░░        ░  ░░ ░  ░   ▒     ░ ░   ░  ░  ░  ░ ░ ░ ▒  ░░        ░  ░░ ░░ ░ ░ ▒   ░    ░  ▒ ░  ░   ▒    \n"
                   "            ░  ░  ░      ░  ░    ░  ░      ░      ░ ░            ░  ░  ░    ░ ░   ░       ░        ░  ░ \n"
                   "                                                                                       ░                \n"
                   "                                            a game in C\n");
            break;
        case 4:
            printf("\n"
                   "                 █ ▄▄   ▄  █ ██   █      ▄▄▄▄▄   ████▄ █ ▄▄   ▄  █ ████▄ ███   ▄█ ██   \n"
                   "                 █   █ █   █ █ █  █     █     ▀▄ █   █ █   █ █   █ █   █ █  █  ██ █ █  \n"
                   "                 █▀▀▀  ██▀▀█ █▄▄█ █   ▄  ▀▀▀▀▄   █   █ █▀▀▀  ██▀▀█ █   █ █ ▀ ▄ ██ █▄▄█ \n"
                   "                 █     █   █ █  █ ███▄ ▀▄▄▄▄▀    ▀████ █     █   █ ▀████ █  ▄▀ ▐█ █  █ \n"
                   "                  █       █     █     ▀                 █       █        ███    ▐    █ \n"
                   "                   ▀     ▀     █                         ▀     ▀                    █  \n"
                   "                              ▀                                                    ▀   \n"
                   "                                            a game in C\n");
            break;
        default:
            printf("\n                                           PhalsoPhobia:\n                                            a game in C");
            break;

    }

    // 2 second sleep
    time_t start, end;
    time(&start);
    do time(&end); while(difftime(end, start) <= 2);
    printf("\e[1;1H\e[2J");


    printf("\033[0;37m");
    do {
        do {
            printf("\n\n\n\n\n"
                   "                                        ___________________\n"
                   "                                       |1|     Set Game    |\n"
                   "                                       |2|       Play      |\n"
                   "                                       |3|    Istruzioni   |\n"
                   "                                       |4|       Esci      |\n"
                   "                                        -------------------\n\n"
                   "\n\n\n\n\nYour Choice>");
            exitCode = scanf("%d", &usrChoice);
            scanf("%*[^\n]%*c");
            //This "flushes" the stdin buffer up until the \n
            /* the %*[^\n] part scans the buffer until it finds a \n
             * the * part discards whatever was just scanned
             * The %*c scans and discards the \n left by the first part
             * */
            if (exitCode==1 && usrChoice >= 1 && usrChoice <= 4) {
                //The selection made by the user is actually a valid one
                valid = true;
            } else {
                //the selection made by the user is either an invalid type or not an option
                valid = false;
                printf("\n\n                            AN UNEXPECTED ERROR OCCURED, PLEASE TRY AGAIN!\n\n");
            }
        } while (!valid);

        switch (usrChoice) {
            case 1:
                imposta_gioco();
                set = true;
                break;
            case 2:
                if(set){
                    gioca();
                    set = false;
                } else {
                    printf("\n                            You have to set the game before you can play!\n");
                }
                break;
            case 3:
                istruzioni();
                break;
            case 4:
                termina_gioco();
                break;
            default:
                printf("\n                                Some Unknown Error Happened, Try Again\n");
                break;

        }

    } while (usrChoice != 4);
    return 0;
}