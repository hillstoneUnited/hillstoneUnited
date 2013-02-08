#include "rcss3dsocket.hpp"
#include <rcssnet/exception.hpp>

#include <string.h>
#include <errno.h>

//#include <sys/socket.h>
#include <netinet/in.h>
//#include <arpa/inet.h>

using namespace rcss::net;

rcss3dSocket::rcss3dSocket(){
  //  std::cout << "make socket class(not connected)" << std::endl;
}

rcss3dSocket::rcss3dSocket(int port_arg, std::string host_arg): port(port_arg), host(host_arg){
  std::cout << "connect to TCP " << host << ":" << port << std::endl;

  try{
    Addr local(INADDR_ANY, INADDR_ANY);
    soc.bind(local);
  }catch(BindErr error){
    std::cerr << "failed to bind socket with '" << error.what() << "'" << std::endl;

    soc.close();
  }

  try{
    Addr server(port, host);
    soc.connect(server);
  }catch(ConnectErr error){
    std::cerr << "connection failed with: '" << error.what() <<"'" << std::endl;

    soc.close();
  }
}

rcss3dSocket::~rcss3dSocket(){
  soc.close();
  std::cout << "closed connection to " << host << ":" << port << std::endl;
}

void rcss3dSocket::PutMessage(const std::string &msg){
  if(msg.empty()){
    return;
  }

  //prefix the message with it's payload length
  unsigned int len = htonl(msg.size());
  std::string prefix((const char*)&len, sizeof(unsigned int));
  std::string str = prefix + msg;
  // std::cout << "PutMessage\n" << str << std::endl;
  soc.send(str.data(), str.size());
}

bool rcss3dSocket::GetMessage(std::string &msg){
  static char buffer[16*1024];
  unsigned int bytesRead = 0;
  while(bytesRead < sizeof(unsigned int)){
    SelectInput();
    int readResult = soc.recv(buffer+bytesRead, sizeof(unsigned int)-bytesRead);

    if(readResult < 0)
      continue;

    bytesRead += readResult;
  }

  unsigned int msgLen = ntohl(*(unsigned int*)buffer);
  if(sizeof(unsigned int)+msgLen > sizeof(buffer)){
    std::cout << buffer << std::endl;
    std::cerr << "message too long: abortion" << std::endl;
    abort();
  }

  unsigned int msgRead = bytesRead - sizeof(unsigned int);

  char *offset = buffer + bytesRead;

  while(msgRead < msgLen){
    if(! SelectInput()){
      return false;
    }

    int readLen = sizeof(buffer) - msgRead;

    if(readLen > msgLen - msgRead)
      readLen = msgLen - msgRead;

    int readResult = soc.recv(offset, readLen);

    if(readResult < 0)
      continue;

    msgRead += readResult;
    offset += readResult;
  }

  (*offset) = 0;
  msg = std::string(buffer+sizeof(unsigned int));

  // std::cout << "GetMessage" << std::endl << msg << std::endl;
  return true;
}

void rcss3dSocket::Done(){
  soc.close();
  std::cout << "closed connection to " << host << ":" << port << std::endl;
}

bool rcss3dSocket::Connect(int port_arg, std::string host_arg){
  host = host_arg;
  port = port_arg;

  std::cout << "connect to TCP " << host << ":" << port << std::endl;

  try{
    Addr local(INADDR_ANY, INADDR_ANY);
    soc.bind(local);
  }catch(BindErr error){
    std::cerr << "failed to bind socket with '" << error.what() << "'" << std::endl;

    soc.close();
    return false;
  }

  try{
    Addr server(port, host);
    soc.connect(server);
  }catch(ConnectErr error){
    std::cerr << "connection failed with: '" << error.what() << "'" << std::endl;

    soc.close();
    return false;
  }

  return true;
}

bool rcss3dSocket::SelectInput(){
  fd_set readfds;
  struct timeval tv = {60, 0};
  FD_ZERO(&readfds);
  FD_SET(soc.getFD(), &readfds);

  while(1){
    switch(select(soc.getFD()+1, &readfds, 0, 0, &tv)){
    case 1:
      return 1;
    case 0:
      std::cerr << "(SelectInput) select failed " << strerror(errno) << std::endl;
      abort();
      return 0;
    default:
      if(errno == EINTR)
	continue;
      std::cerr << "(SelectInput) select failed " << strerror(errno) << std::endl;
      abort();
      return 0;
    }
  }
}
