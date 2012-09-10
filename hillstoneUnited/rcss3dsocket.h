#ifndef RCSS3DSOCKET_H
#define RCSS3DSOCKET_H

#include <iostream>
#include <rcssnet/tcpsocket.hpp>

/*
  RoboCup Soccer Simulation 3d Socket class
  This class is wrapper of "TCPSocket", rcssnet library socket
  By this class, "content of message" and "method of comunicate server" is divided
*/
class rcss3dSocket
{
 public:
  rcss3dSocket(); // only make instance. you should Connect() before use socket
  rcss3dSocket(int port_arg, std::string host_arg); // connect rcssserver3d in host_arg by port_arg
  ~rcss3dSocket();


  void PutMessage(const std::string &msg); // send argument message to server
  bool GetMessage(std::string &msg); // copy message from server in argument string.

  void Done();

  bool Connect(int port_arg, std::string host_arg); // connect server. return true:succeed  false:failed

 private:
  rcss::net::TCPSocket soc;
  int port;
  std::string host;
  bool SelectInput();
};

#endif
