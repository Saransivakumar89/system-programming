#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define PORT 8080

int main(void)
{
    int server_fd, client_fd;

    struct sockaddr_in my_addr;
    struct sockaddr_in con_addr;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        perror("socket");
        return 1;
    }

    // Clear structure
    memset(&my_addr, 0, sizeof(my_addr));

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind
    if (bind(server_fd,
             (struct sockaddr *)&my_addr,
             sizeof(my_addr)) < 0)
    {
        perror("bind");
        return 1;
    }

    // Listen
    if (listen(server_fd, 5) < 0)
    {
        perror("listen");
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    socklen_t size = sizeof(con_addr);

    // Accept
    client_fd = accept(server_fd,
                       (struct sockaddr *)&con_addr,
                       &size);

    if (client_fd < 0)
    {
        perror("accept");
        return 1;
    }

    char buff[100];

    int bytes = read(client_fd, buff, sizeof(buff) - 1);

    if (bytes < 0)
    {
        perror("read");
        return 1;
    }

    buff[bytes] = '\0';

    printf("Message from client %d: %s\n",
           client_fd,
           buff);

    close(client_fd);
    close(server_fd);

    return 0;
}
