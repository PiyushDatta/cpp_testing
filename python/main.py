import socket
import errno
import binascii


def recv_all(sock, buff_size):
  data = b''
  while True:
    packet = sock.recv(buff_size)
    data += packet
    if len(packet) < buff_size:
      break
  return data


if __name__ == "__main__":
  # The server's hostname or IP address
  HOST = '127.0.0.1'
  # The port used by the server
  PORT = 13000
  # The amount of bytes we can send and receive
  INPUT_BUFFER_SIZE = 4096

  try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Connect to an IP with Port, could be a URL
    sock.connect((HOST, PORT))
    print("Socket connecting to host {0} and port {1}".format(HOST, PORT))

    # Get the first greeting message if any
    recv_msg = recv_all(sock, INPUT_BUFFER_SIZE)
    print("Received: {0}".format(recv_msg))
    # print("Received: {0}".format(recv_msg.decode('utf-8')))

    # Keep client connection open as long as user wants to write messages
    while True:
      send_msg = input()
      print("Sending")
      sock.sendall(send_msg.encode('utf-8'))
      recv_msg = recv_all(sock, INPUT_BUFFER_SIZE)
      try:
        print("Received: {0}".format(recv_msg))
        # print("Received: {0}".format(recv_msg.decode('utf-8', errors="ignore")))
      except UnicodeDecodeError as e:
        print(
            "Error: receving msg had a unicode decode error - {0}".format(repr(e)))
        continue
  except KeyboardInterrupt as e:
    print("Disconnecting")
  except ConnectionRefusedError as e:
    print("Error: Connection refused, make sure the server is up and running")
  except socket.timeout as e:
    print("Error: Socket timeout: {0}".format(repr(e.errno)))
  except IOError as e:
    if e.errno == errno.EPIPE:
      print("Error: Remote server disconnected")
    else:
      print("Error: IOError, some unknown error: {0}".format(e.errno))

  # Close the socket connection, no more data transmission
  sock.close()
