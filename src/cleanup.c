#include "irc.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void cleanup(int sig) {
    (void)sig;

    log_infos("Shutting down IRC client !");

    if (config.sockfd > 0) {
        send_command("QUIT : Client is shutting down !\r\n");

        if (config.input_thread)
            pthread_cancel(config.input_thread);

        if (config.server_thread)
            pthread_cancel(config.server_thread);

        close(config.sockfd);
    }

    exit(0);
}
