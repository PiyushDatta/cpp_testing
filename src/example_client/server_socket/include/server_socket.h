#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

// Windows or another OS
#ifdef _WIN32
#include <WS2tcpip.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#ifndef ALGO_SERVER_SOCK
#define ALGO_SERVER_SOCK

const int INPUT_BUFFER_SIZE = 4096;
const int DEFAULT_PORT = 13000;
const bool DEFAULT_DEBUG = true;

class ServerSocket {
public:
  ServerSocket(const bool &debug = DEFAULT_DEBUG,
               const int &socket_port = DEFAULT_PORT);
  ~ServerSocket();
  void keepAcceptingAndListening();

private:
  void setupSocket(const int &socket_port, const bool &debug);
  int bindSocket();
  int listenPort();
  void handleNewConnection();
  void recvFromExistingClient(int sock_fd);
  void closeOpenSocket(int open_socket);

  // master socket which receives new connections
  int m_master_sock_fd;

  // temporary socket file descriptor which holds new clients
  int m_temp_sock_fd;

  // fd_set file descriptor sets for use with FD_ macros
  fd_set m_master_fds;
  fd_set m_temp_fds;

  // unsigned integer to keep track of maximum fd value, required for select()
  int m_max_fd;

  // client connection data
  struct sockaddr_storage m_client_addr;
  // server socket details
  struct sockaddr_in m_server_addr;

  // input buffer
  char input_buffer[INPUT_BUFFER_SIZE];

  // port
  int m_portno;
  // debug
  bool m_debug;
};
#endif