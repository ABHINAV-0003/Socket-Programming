This repository contains the code for a basic client-server communication program using socket programming in C.
Files Included

    server.c: Contains the server-side implementation.
    client.c: Contains the client-side implementation.

Description

The server listens on port 5432 for incoming connections. When a client connects, it echoes back any message received from the client. The client sends messages to the server and displays the echoed response.
Usage

    Server:
        Compile and run server.c.
        The server will start listening for incoming connections on port 5432.

    Client:
        Compile and run client.c.
        Provide the hostname (or IP address) of the server as a command-line argument.
        Type a message and press Enter to send it to the server.
        The client will display the message sent to the server and the response received from the server.

Example

Assuming the server is running on localhost:

    Start the server: ./server
    Start the client: ./client localhost
    Type a message in the client terminal and observe the echo response from the server.

Notes

    Ensure both client and server are compiled using a C compiler (e.g., gcc).
    This code assumes the server and client are running on the same machine for testing purposes.
