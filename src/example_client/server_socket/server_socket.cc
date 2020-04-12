#include "include/server_socket.h"
#include "../../utils/include/util_functions.h"

ServerSocket::ServerSocket(const bool &debug, const int &socket_port) {
  m_portno = socket_port;
  m_debug = debug;
  setupSocket(m_portno, m_debug);
}

ServerSocket::~ServerSocket() {
  util_func::debug_log("Destroying server socket", m_debug);
  closeOpenSocket(m_master_sock_fd);
  closeOpenSocket(m_temp_sock_fd);
#ifndef _WIN32
  WSACleanup();
#endif
}

void ServerSocket::setupSocket(const int &socket_port, const bool &debug) {
  util_func::debug_log("Starting socket server on port: ", m_portno, m_debug);

// initialize WinSock
#ifdef _WIN32
  WSAData win_data;
  WORD win_ver = MAKEWORD(2, 2);
  int ws_sock = WSAStartup(win_ver, &win_data);
  if (ws_sock != 0) {
    util_func::err_log("Could not start WinSock, err#: ", WSAGetLastError(),
                       true);
    exit(1);
  }
#endif

  // creating socket file descriptor
  m_master_sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  // make socket non blocking
#ifdef _WIN32
  // 1 to enable non-blocking socket
  u_long block_sock_flag = 1;
  ioctlsocket(m_master_sock_fd, FIONBIO, &block_sock_flag);
#else
  fcntl(m_master_sock_fd, F_SETFL, O_NONBLOCK);
#endif

  // open socket
  if (m_master_sock_fd < 0) {
    util_func::err_log("Could not open socket", true);
    exit(1);
  }
  FD_ZERO(&m_master_fds);
  FD_ZERO(&m_temp_fds);
  util_func::debug_log("Opened socket", m_debug);

  // bind socket
  if (bindSocket() < 0) {
    util_func::err_log("Could not bind socket", true);
    exit(1);
  }
  // insert the master socket file-descriptor into the master fd-set
  FD_SET(m_master_sock_fd, &m_master_fds);
  // set the current known maximum file descriptor count
  m_max_fd = m_master_sock_fd;
  util_func::debug_log("Max fd value is ", m_max_fd, m_debug);
  util_func::debug_log("Bound socket to address and port", m_debug);

  // listen on port
  if (listenPort() < 0) {
    util_func::err_log("Could not listen to port ", m_portno, true);
    exit(1);
  }
}

int ServerSocket::bindSocket() {
  memset(&m_server_addr, 0, sizeof(m_server_addr));
  m_server_addr.sin_family = AF_INET;
  m_server_addr.sin_port = htons(m_portno);
#ifdef _WIN32
  m_server_addr.sin_addr.S_un.S_addr = INADDR_ANY;
#else
  m_server_addr.sin_addr.s_addr = INADDR_ANY;
#endif

  // zero input buffer before use to avoid random data appearing in first
  // receives
  memset(input_buffer, 0, INPUT_BUFFER_SIZE);

  return bind(m_master_sock_fd, (struct sockaddr *)&m_server_addr,
              sizeof(m_server_addr));
}

int ServerSocket::listenPort() { return listen(m_master_sock_fd, SOMAXCONN); }

void ServerSocket::closeOpenSocket(int open_socket) {
  util_func::debug_log("Closing socket ", open_socket, m_debug);
#ifdef _WIN32
  closesocket(open_socket);
#else
  close(open_socket);
#endif
}

void ServerSocket::handleNewConnection() {
  util_func::debug_log("Handling new client connection", m_debug);

  socklen_t addr_len = sizeof(m_client_addr);
  m_temp_sock_fd =
      accept(m_master_sock_fd, (struct sockaddr *)&m_client_addr, &addr_len);

  if (m_temp_sock_fd < 0) {
    util_func::err_log("Accepting [accept()] new client failed", true);
  } else {
    FD_SET(m_temp_sock_fd, &m_master_fds);

    // increment the maximum known file descriptor (select() needs it)
    if (m_temp_sock_fd > m_max_fd) {
      util_func::debug_log("Max fd changed from " +
                               util_func::custom_to_string(m_max_fd) + " to ",
                           m_temp_sock_fd, m_debug);
      m_max_fd = m_temp_sock_fd;
    }

    // get ip address of client
    char serv_ip_addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(m_server_addr.sin_addr), serv_ip_addr,
              INET_ADDRSTRLEN);

    // get info - used in send and receive commands
    std::string new_conn_print =
        "\nNew connection, socket fd is " +
        util_func::custom_to_string(m_temp_sock_fd) + ", ip is " +
        serv_ip_addr + ", port is " +
        util_func::custom_to_string(ntohs(m_server_addr.sin_port));
    util_func::debug_log(new_conn_print, true);

    // send connection successful message to client
    std::string conn_success_msg = "Successful connection to port " +
                                   util_func::custom_to_string(m_portno);
    int send_err = send(m_temp_sock_fd, conn_success_msg.c_str(),
                        conn_success_msg.size() + 1, 0);
    if (send_err == -1) {
      util_func::err_log(
          "Could not send successful connection message to client socket ",
          m_temp_sock_fd, true);
    }
  }
}

long long ServerSocket::recvAll(const int &sock_fd, char *input_buffer,
                                std::string &client_msg) {
  long long all_bytes_recv = 0;
  int bytes_read = 0;
  bytes_read = recv(sock_fd, input_buffer, INPUT_BUFFER_SIZE, 0);
  if (bytes_read <= 0) {
    util_func::err_log(
        "0 bytes read, while receiving part of message from socket: ", sock_fd,
        m_debug);
    return 0;
  }

  while (bytes_read > 0) {
    all_bytes_recv += bytes_read;
    client_msg.append(input_buffer, bytes_read);
    bytes_read = recv(sock_fd, input_buffer, INPUT_BUFFER_SIZE, 0);
  }

  return all_bytes_recv;
}

void ServerSocket::recvFromExistingClient(int sock_fd) {
  // wait for client to send all data
  std::string client_msg = "";
  long long byte_recv = recvAll(sock_fd, input_buffer, client_msg);

  if (byte_recv <= 0) {
    util_func::debug_log("Data from socket fd #: ", sock_fd, m_debug);
    util_func::debug_log("Received bytes: ", (long long)byte_recv, m_debug);
    util_func::debug_log("If received bytes is 0, then client disconnected, "
                         "otherwise its an error in recv().",
                         m_debug);
    // drop client
    closeOpenSocket(sock_fd);
    FD_CLR(sock_fd, &m_master_fds);
  } else {
    // echo message back to client
    util_func::debug_log("Data from socket fd #: ", sock_fd, m_debug);
    util_func::debug_log("Received bytes: ", (long long)byte_recv, m_debug);
    util_func::debug_log("Received message: " + client_msg + "\n", m_debug);
    int send_err = send(sock_fd, client_msg.c_str(), sizeof(client_msg), 0);
    if (send_err == -1) {
      util_func::err_log(
          "Could not send successful connection message to client socket ",
          m_temp_sock_fd, true);
    }
  }
}

void ServerSocket::keepAcceptingAndListening() {
  std::string const_listening_msg =
      "Currently listening and accepting clients on port " +
      util_func::custom_to_string(m_portno) + "...";
  util_func::debug_log(const_listening_msg, m_debug);

  while (true) {
    // create a copy since select() destroys the socket/file descriptor
    m_temp_fds = m_master_fds;

    // wait for an activity on one of the sockets, timeout is NULL, wait forever
    int client_activity =
        select(m_max_fd + 1, &m_temp_fds, nullptr, nullptr, nullptr);

    if (client_activity < 0) {
      util_func::err_log("select() didn't work.", true);
    }

    // go through all client sockets and check which socket has interactions
    // available
    for (int i = 0; i <= m_max_fd; ++i) {
      // if socket has activity pending
      if (FD_ISSET(i, &m_temp_fds)) {
        // new connection
        if (m_master_sock_fd == i) {
          handleNewConnection();
        }
        // existing connection has new data
        else {
          recvFromExistingClient(i);
        }
      }
    }
  }
}
