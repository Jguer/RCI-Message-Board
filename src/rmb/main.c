#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include "utils.h"
#include "identity.h"

void usage(char* name) {
    fprintf(stdout, "Example Usage: %s [-i siip] [-p sipt]\n", name);
    fprintf(stdout, "Arguments:\n"
            "\t-i\t\t[server ip]\n"
            "\t-p\t\t[server port]\n");
}

int main(int argc, char *argv[]) {
    int oc;
    char server_ip[STRING_SIZE] = "tejo.tecnico.ulisboa.pt";
    u_short server_port = 59000;

    // Treat options
    while ((oc = getopt(argc, argv, "i:p:")) != -1) {
        switch (oc) {
            case 'i':
                strcpy(server_ip, optarg);
                break;
            case 'p':
                server_port = (u_short)atoi(optarg);
                break;
            case ':':
                /* missing option argument */
                fprintf(stderr, "%s: option '-%c' requires an argument\n",
                        argv[0], optopt);
                break;
            case '?':
            default:
                usage(argv[0]);
                return EXIT_FAILURE;
        }
    }

    fprintf(stdout, KBLU "Identity Server:" KNRM " %s:%d\n", server_ip, server_port);

    char op[STRING_SIZE];
    char input_buffer[STRING_SIZE];
    char *response;
    // Interactive loop
    while (1) {
        memset( op, '\0', sizeof(char)*STRING_SIZE );
        memset( input_buffer, '\0', sizeof(char)*STRING_SIZE );

        fprintf(stdout, KGRN "Prompt > " KNRM);
        scanf("%s%*[ ]%126[^\t\n]" , op, input_buffer); // Grab word, then throw away space and finally grab until \n

        if (strcmp("show_servers", op) == 0) {
            response = show_servers(server_ip, server_port);
            puts(response);
            free(response);
        } else if (strcmp("exit", op) == 0) {
            return EXIT_SUCCESS;
        } else if (strcmp("publish", op) == 0) {
        } else if (strcmp("show_latest_messages", op) == 0) {
        } else {
            fprintf(stderr, KRED "%s is an unknown operation\n" KNRM, op);
        }
    }
    return EXIT_SUCCESS;
}

