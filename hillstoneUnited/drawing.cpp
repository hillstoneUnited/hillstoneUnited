/*
 *  Copyright (C) 2011 Justin Stoecker
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/* 
 * This source file uses some basic datagram socket communication code from
 * Brian "Beej Jorgensen" Hall's Guide to Network Programming:
 * http://beej.us/guide/bgnet/output/html/multipage/clientserver.html#datagram
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <math.h>
#include "drawing.hpp"
#include "world.hpp"

#include <sstream>

using namespace std;

Drawing::Drawing():ROBOVIS_HOST("localhost"),ROBOVIS_PORT("32769"){
  //struct addrinfo hints, *servinfo;
  int rv;
  int numbytes;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  if ((rv = getaddrinfo(ROBOVIS_HOST.c_str(), ROBOVIS_PORT.c_str(), &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
  }

  // loop through all the results and make a socket
  for(p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype,
			 p->ai_protocol)) == -1) {
      perror("socket");
      continue;
    }
    break;
  }

  if (p == NULL) {
    fprintf(stderr, "failed to bind socket\n");
  }
}

Drawing::~Drawing(){
  freeaddrinfo(servinfo);
  close(sockfd);
}

void Drawing::draw(World& w){
  if(w.getUnum() > 0){
    renderAgentShapes(w);
  }
  // renderStaticShapes(w);
  // renderAnimatedShapes(w);
}

void Drawing::renderAgentShapes(World& w){

  // the agent xy coordination
  double my_x = w.getXY(0), my_y = w.getXY(1);
  std::stringstream AgentPos;
  AgentPos << "Agent.no" << w.getUnum() <<  "-XYposition";
   //  AgentPos << "A." << w.getUnum() <<  ".XYposition";
  const string cs_agentpos(AgentPos.str());
  drawCircle(my_x,my_y,0.2f,2,0,0,1,&cs_agentpos);

  // the agent xy coordination(average)
  double my_x_AVE = w.getXY_AVE(0), my_y_AVE = w.getXY_AVE(1);
  std::stringstream AgentPos_AVE;
  AgentPos_AVE << "Agent.no" << w.getUnum() <<  "-XY_AVEposition";
   //  AgentPos << "A." << w.getUnum() <<  ".XYposition";
  const string cs_agentpos_AVE(AgentPos_AVE.str());
  drawCircle(my_x_AVE,my_y_AVE,0.2f,2,1,1,1,&cs_agentpos_AVE);

  // the agent xy coordination (mypos true)
  double mypos_x = w.getMYPOS(0), mypos_y = w.getMYPOS(1);
  std::stringstream AgentMYPos;
  AgentMYPos << "Agent.no" << w.getUnum() <<  "-MYPOSXYposition";
  //  AgentMYPos << "A." << w.getUnum() <<  ".MYPOSXYposition";
  const string cs_agentmypos(AgentMYPos.str());
  drawCircle(mypos_x,mypos_y,0.2f,2,1,0,0,&cs_agentmypos);



  // the position of the ball
  double bal_x = w.getBXY(0), bal_y = w.getBXY(1);
  std::stringstream BXYPos;
  BXYPos << "Agent.no" << w.getUnum() << "-BXYposition";
  const string cs_bxypos(BXYPos.str());
  drawSphere(bal_x, bal_y,0, 0.1, 1, 0.5f, 0.5f, &cs_bxypos);

  // the position of the ball(average)
  double bal_x_AVE = w.getBXY_AVE(0), bal_y_AVE = w.getBXY_AVE(1);
  std::stringstream BXYPos_AVE;
  BXYPos_AVE << "Agent.no" << w.getUnum() << "-BXYposition_AVE";
  const string cs_bxypos_AVE(BXYPos_AVE.str());
  drawSphere(bal_x_AVE, bal_y_AVE,0, 0.1, 0.5, 0.5f, 0.5f, &cs_bxypos_AVE);


  // the position of the ball (ballpos true)
  double balpos_x = w.getBALLPOS(0), balpos_y = w.getBALLPOS(1);
  std::stringstream BallPos;
  BallPos << "Agent.no" << w.getUnum() << "-BALLposition";
  const string cs_ballpos(BallPos.str());
  drawSphere(balpos_x,balpos_y,0,0.1,1,1,0.5f, &cs_ballpos);


  // the position of the ball(sended by server)
  

  string staticSets("Agent");
  swapBuffers(&staticSets);
}


void Drawing::renderAnimatedShapes(World& w) {
  static double angle = 0.0;

  angle += 0.05;

  string n1("animated.points");
  for (int i = 0; i < 60; i++) {
    float p = i / 60.0f;
    float height = maxf(0, sin(angle + p * 18));
    drawPoint(-9 + 18 * p, p * 12 - 6, height, 5, 0,0,0,&n1);
  }

  float bx = cos(angle) * 2;
  float by = sin(angle) * 2;
  float bz = cos(angle) + 1.5f;

  string n2("animated.spinner");
  drawLine(0,0,0,bx,by,bz,5,1,1,0,&n2);
  drawLine(bx,by,bz,bx,by,0,5,1,1,0,&n2);
  drawLine(0,0,0,bx,by,0,5,1,1,0,&n2);

  string n3("animated.annotation");
  char tbuf[4];
  int result = snprintf(tbuf, 4, "%.1f", bz);
  string aText(tbuf);
  drawAnnotation(&aText, bx, by, bz, 0, 1, 0, &n3);

  string staticSets("animated");
  swapBuffers(&staticSets);
}

void Drawing::renderStaticShapes(World& w) {
  
  // draw 3D coordinate axes
  string n1("static.axes");
  drawLine(0,0,0,3,0,0,3,1,0,0,&n1);
  drawLine(0,0,0,0,3,0,3,0,1,0,&n1);
  drawLine(0,0,0,0,0,3,3,0,0,1,&n1);

  // draw 1 meter lines on field
  string n2("static.lines.field");
  drawLine(-9,-6,0,9,-6,0,1,0.6f,0.9f,0.6f,&n2);
  drawLine(-9,6,0,9,6,0,1,0.6f,0.9f,0.6f,&n2);
  for (int i = 0; i <= 18; i++)
    drawLine(-9+i,-6,0,-9+i,6,0,1,0.6f,0.9f,0.6f,&n2);

  // draw some circles
  string n3("static.circles");
  drawCircle(-5,0,3,2,0,0,1,&n3);
  drawCircle(5,0,3,2,0,0,1,&n3);

  // draw some spheres
  string n4("static.spheres");
  drawSphere(-5,0,2,0.5f,1,0,0.5f,&n4);
  drawSphere(5,0,2,0.5f,1,0,0.5f,&n4);

  // draw a polygon
  string n5("static.polygons");
  float v[] = {0,0,0, 1,0,0, 1,1,0, 0,3,0, -2,-2,0};
  drawPolygon(v, 4, 1, 1, 1, 0.5f, &n5); 

  string staticSets("static");
  swapBuffers(&staticSets);

}

void Drawing::swapBuffers(const string* setName) {
  int bufSize = -1;
  unsigned char* buf = newBufferSwap(setName, &bufSize);
  sendto(sockfd, buf, bufSize, 0, p->ai_addr, p->ai_addrlen);
  delete[] buf;
}

void Drawing::drawLine(float x1, float y1, float z1, float x2, float y2,
			 float z2, float thickness, float r, float g, float b,
			 const string* setName)
{
  float pa[3] = {x1,y1,z1};
  float pb[3] = {x2,y2,z2};
  float color[3] = {r,g,b};

  int bufSize = -1;
  unsigned char* buf = newLine(pa, pb, thickness, color, setName, &bufSize);
  sendto(sockfd, buf, bufSize, 0, p->ai_addr, p->ai_addrlen);
  delete[] buf;
}

void Drawing::drawCircle(float x, float y, float radius, float thickness,
			   float r, float g, float b, const string* setName)
{
  float center[2] = {x,y};
  float color[3] = {r,g,b};

  int bufSize = -1;

  unsigned char* buf = newCircle(center, radius, thickness, color, setName, &bufSize);

  sendto(sockfd, buf, bufSize, 0, p->ai_addr, p->ai_addrlen);
  delete[] buf;
}

void Drawing::drawSphere(float x, float y, float z, float radius,
			   float r, float g, float b, const string* setName)
{
  float center[3] = {x,y,z};
  float color[3] = {r,g,b};

  int bufSize = -1;
  unsigned char* buf = newSphere(center, radius, color, setName, &bufSize);
  sendto(sockfd, buf, bufSize, 0, p->ai_addr, p->ai_addrlen);
  delete[] buf;
}

void Drawing::drawPoint(float x, float y, float z, float size,
			  float r, float g, float b, const string* setName)
{
  float center[3] = {x,y,z};
  float color[3] = {r,g,b};

  int bufSize = -1;
  unsigned char* buf = newPoint(center, size, color, setName, &bufSize);
  sendto(sockfd, buf, bufSize, 0, p->ai_addr, p->ai_addrlen);
  delete[] buf;
}

void Drawing::drawPolygon(const float* v, int numVerts,
			    float r, float g, float b,
			    float a, const string* setName)
{
  float color[4] = {r,g,b,a};

  int bufSize = -1;
  unsigned char* buf = newPolygon(v, numVerts, color, setName, &bufSize);
  sendto(sockfd, buf, bufSize, 0, p->ai_addr, p->ai_addrlen);
  delete[] buf;
}

void Drawing::drawAnnotation(const string* text, float x, float y, float z,
			       float r, float g, float b,
			       const string* setName)
{
  float color[3] = {r,g,b};
  float pos[3] = {x,y,z};

  int bufSize = -1;
  unsigned char* buf = newAnnotation(text, pos, color, setName, &bufSize);
  sendto(sockfd, buf, bufSize, 0, p->ai_addr, p->ai_addrlen);
  delete[] buf;
}

float Drawing::maxf(float a, float b) {
  return a > b ? a : b;
}


inline int Drawing::writeCharToBuf(unsigned char* buf, unsigned char value) {
  *buf = value;
  return 1;
}

inline int Drawing::writeFloatToBuf(unsigned char* buf, float value) {
  char temp[20];
  sprintf(temp, "%6f", value);
  memcpy(buf, temp, 6);
  return 6;
}

inline int Drawing::writeColorToBuf(unsigned char* buf,
				      const float* color, int channels) {
  int i;
  for (i = 0; i < channels; i++)
    writeCharToBuf(buf+i, (unsigned char)(color[i]*255)); 
  return i;
}

inline int Drawing::writeStringToBuf(unsigned char* buf, const string* text) {
  long i = 0;
  if (text != NULL)
    i += text->copy((char*)buf+i, text->length(), 0); 
  i += writeCharToBuf(buf+i, 0);
  return i;
}

unsigned char* Drawing::newBufferSwap(const string* name, int* bufSize) {
  *bufSize = 3 + ((name != NULL) ? name->length() : 0);
  unsigned char* buf = new unsigned char[*bufSize];

  long i = 0;
  i += writeCharToBuf(buf+i, 0);
  i += writeCharToBuf(buf+i, 0);
  i += writeStringToBuf(buf+i, name);

  return buf;
}

unsigned char* Drawing::newCircle(const float* center, float radius,
				    float thickness,
				    const float* color, const string* setName,
				    int* bufSize) {

  *bufSize = 30 + ((setName != NULL) ? setName->length() : 0);
  unsigned char* buf = new unsigned char[*bufSize];
  
  long i = 0;
  i += writeCharToBuf(buf+i, 1);
  i += writeCharToBuf(buf+i, 0);
  i += writeFloatToBuf(buf+i, center[0]);
  i += writeFloatToBuf(buf+i, center[1]);
  i += writeFloatToBuf(buf+i, radius);
  i += writeFloatToBuf(buf+i, thickness);
  i += writeColorToBuf(buf+i, color, 3);
  i += writeStringToBuf(buf+i, setName);

  return buf;
}

unsigned char* Drawing::newLine(const float* a, const float* b,
				  float thickness,
				  const float* color, const string* setName,
				  int* bufSize) {
  
  *bufSize = 48 + ((setName != NULL) ? setName->length() : 0);
  unsigned char* buf = new unsigned char[*bufSize];

  long i = 0;
  i += writeCharToBuf(buf+i, 1);
  i += writeCharToBuf(buf+i, 1);
  i += writeFloatToBuf(buf+i, a[0]);
  i += writeFloatToBuf(buf+i, a[1]);
  i += writeFloatToBuf(buf+i, a[2]);
  i += writeFloatToBuf(buf+i, b[0]);
  i += writeFloatToBuf(buf+i, b[1]);
  i += writeFloatToBuf(buf+i, b[2]);
  i += writeFloatToBuf(buf+i, thickness);
  i += writeColorToBuf(buf+i, color, 3);
  i += writeStringToBuf(buf+i, setName);
  
  return buf;
}

unsigned char* Drawing::newPoint(const float* p, float size,
				   const float* color, 
				   const string* setName, int* bufSize) {
  
  *bufSize = 30 + ((setName != NULL) ? setName->length() : 0);
  unsigned char* buf = new unsigned char[*bufSize];

  long i = 0;
  i += writeCharToBuf(buf+i, 1);
  i += writeCharToBuf(buf+i, 2);
  i += writeFloatToBuf(buf+i, p[0]);
  i += writeFloatToBuf(buf+i, p[1]);
  i += writeFloatToBuf(buf+i, p[2]);
  i += writeFloatToBuf(buf+i, size);
  i += writeColorToBuf(buf+i, color, 3);
  i += writeStringToBuf(buf+i, setName);
  
  return buf;
}

unsigned char* Drawing::newSphere(const float* p, float radius,
				    const float* color, 
				    const string* setName, int* bufSize) {
  
  *bufSize = 30 + ((setName != NULL) ? setName->length() : 0);
  unsigned char* buf = new unsigned char[*bufSize];

  long i = 0;
  i += writeCharToBuf(buf+i, 1);
  i += writeCharToBuf(buf+i, 3);
  i += writeFloatToBuf(buf+i, p[0]);
  i += writeFloatToBuf(buf+i, p[1]);
  i += writeFloatToBuf(buf+i, p[2]);
  i += writeFloatToBuf(buf+i, radius);
  i += writeColorToBuf(buf+i, color, 3);
  i += writeStringToBuf(buf+i, setName);
  
  return buf;
}

unsigned char* Drawing::newPolygon(const float* v, int numVerts,
				     const float* color,
				     const string* setName, int* bufSize) {

  *bufSize = 18 * numVerts + 8 + ((setName != NULL) ? setName->length() : 0);
  unsigned char* buf = new unsigned char[*bufSize];

  long i = 0;
  i += writeCharToBuf(buf+i, 1);
  i += writeCharToBuf(buf+i, 4);
  i += writeCharToBuf(buf+i, numVerts);
  i += writeColorToBuf(buf+i, color, 4);
  
  for (int j = 0; j < numVerts; j++) {
    i += writeFloatToBuf(buf+i, v[j*3+0]);
    i += writeFloatToBuf(buf+i, v[j*3+1]);
    i += writeFloatToBuf(buf+i, v[j*3+2]);
  }

  i += writeStringToBuf(buf+i, setName);

  return buf;
}

unsigned char* Drawing::newAnnotation(const string* text, const float* p,
					const float* color,
					const string* setName, int* bufSize) {
  
  *bufSize = 25 + text->length() + setName->length();
  unsigned char* buf = new unsigned char[*bufSize];

  long i = 0;
  i += writeCharToBuf(buf+i, 2);
  i += writeCharToBuf(buf+i, 0);
  i += writeFloatToBuf(buf+i, p[0]);
  i += writeFloatToBuf(buf+i, p[1]);
  i += writeFloatToBuf(buf+i, p[2]);
  i += writeColorToBuf(buf+i, color, 3);
  i += writeStringToBuf(buf+i, text);
  i += writeStringToBuf(buf+i, setName);

  return buf;
}

unsigned char* Drawing::newAgentAnnotation(const string* text, bool leftTeam,
					     int agentNum, const float* color,
					     int* bufSize) {

  *bufSize = (text == NULL) ? 3 : 7 + text->length();
  unsigned char* buf = new unsigned char[*bufSize];

  long i = 0;
  i += writeCharToBuf(buf+i, 2);
  
  if (text == NULL) {
    i += writeCharToBuf(buf+i, 2);
    i += writeCharToBuf(buf+i, (leftTeam ? agentNum - 1 : agentNum + 127));
  } else {
    i += writeCharToBuf(buf+i, 1);
    i += writeCharToBuf(buf+i, (leftTeam ? agentNum - 1 : agentNum + 127));
    i += writeColorToBuf(buf+i, color, 3);
    i += writeStringToBuf(buf+i, text);
  }

  return buf;
}

