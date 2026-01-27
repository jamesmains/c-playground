#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello World!";

    // Create socket (IPv4, TCP)
    server_fd = socket(AF_INET, SOCK_STREAM,0);

    // Set up address struct
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    address.sin_port = htons(8080);       // Port 8080

    // Bind the socket to the port
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Start listening
    listen(server_fd, 3);
    printf("Server listening on port 8080...\n");

    while(1){
        // Wait for a connection
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        // Read the request (skip parsing)
        char buffer[1024] = {0};
        read(new_socket,buffer,1024);
        printf("Request received:\n%s\n", buffer);

        // Send the response
        write(new_socket, hello, strlen(hello));

        // Close the connection
        close(new_socket);
    }

    return 0;
}