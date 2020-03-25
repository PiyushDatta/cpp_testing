#include "example_client/server_socket/include/server_socket.h"
#include "utils/include/util_functions.h"

int main(int argc, char const *argv[]) {
  ServerSocket sock_server;
  sock_server.keepAcceptingAndListening();
  return 0;
}
