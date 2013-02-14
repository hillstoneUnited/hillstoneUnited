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

#ifndef DRAWING_H
#define DRAWING_H

#include <string>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "world.hpp"

//using namespace std;

class Drawing{

 public:
  Drawing();
  ~Drawing();

  void draw(World& w);
  void renderAnimatedShapes(World& w);
  void renderStaticShapes(World& w);
  void renderAgentShapes(World& w);
  void runTest();


  //buffer
  inline int writeCharToBuf(unsigned char* buf, unsigned char value);
  inline int writeFloatToBuf(unsigned char* buf, float value);
  inline int writeColorToBuf(unsigned char* buf,
			     const float* color, int channels);
  inline int writeStringToBuf(unsigned char* buf, const std::string* text);

  //inits
  unsigned char* newBufferSwap(const std::string* name, int* bufSize);
  unsigned char* newCircle(const float* center, float radius, float thickness,
			   const float* color, const std::string* setName,
			   int* bufSize);
  unsigned char* newLine(const float* a, const float* b, float thickness,
			 const float* color, const std::string* setName,
			 int* bufSize);
  unsigned char* newPoint(const float* p, float size, const float* color, 
			  const std::string* setName, int* bufSize);
  unsigned char* newSphere(const float* p, float radius, const float* color, 
			   const std::string* setName, int* bufSize);
  unsigned char* newPolygon(const float* v, int numVerts, const float* color,
			    const std::string* setName, int* bufSize);
  unsigned char* newAnnotation(const std::string* text, const float* p,
			       const float* color, const std::string* setName,
			       int* bufSize);
  unsigned char* newAgentAnnotation(const std::string* text, bool leftTeam,
				    int agentNum, const float* color,
				    int* bufSize);

  //swap buffers
  void swapBuffers(const std::string* setName);

  //drawings
  void drawLine(float x1, float y1, float z1, float x2, float y2, float z2,
		float thickness, float r, float g, float b,
		const std::string* setName);
  void drawCircle(float x, float y, float radius, float thickness,
		  float r, float g, float b, const std::string* setName);
  void drawSphere(float x, float y, float z, float radius,
		  float r, float g, float b, const std::string* setName);
  void drawPoint(float x, float y, float z, float size,
		 float r, float g, float b, const std::string* setName);
  void drawPolygon(const float* v, int numVerts, float r, float g, float b,
		   float a, const std::string* setName);
  void drawAnnotation(const std::string* text, float x, float y, float z,
		      float r, float g, float b, const std::string* setName);


  float maxf(float a, float b);

 private:
  int sockfd;
  struct addrinfo* p;
  //double angle = 0.0;

  struct addrinfo hints, *servinfo;

  const std::string ROBOVIS_HOST;// = "localhost";
  const std::string ROBOVIS_PORT;// = "32769";
  //static const int TEST_DURATION = 10000;

};

#endif
