#include "world.h"
#include <cstdlib>
#include <cmath>

World::World(){
  teamname = "unknown";
  playmode = "unknown";
  unum = 0;
  side = UNKNOWN;
  isMatch = false;
}

World::~World(){
  while(deqPerception.size()>0){
    for(std::deque<Perception*>::iterator it=deqPerception.begin()
	  ;it!=deqPerception.end();++it){
      delete (*it);
    }
    deqPerception.clear();
  }
}

World::Perception::Perception(const std::string& msg){
  setJointMap();
  setSeenMap();

  parseGamestate(msg);
  parseJointValue(msg);
  parseSeen(msg, "G1L");
  parseSeen(msg, "G2L");
  parseSeen(msg, "G1R");
  parseSeen(msg, "G2R");
  parseSeen(msg, "F1L");
  parseSeen(msg, "F2L");
  parseSeen(msg, "F1R");
  parseSeen(msg, "F2R");
  parseSeen(msg, "B");
  parseGYR(msg);
  parseACC(msg);
  parseFRP(msg);
  parseMYPOS(msg);
  parseBALLPOS(msg);
  getPlayer(msg, "friend");
  getPlayer(msg, "enemy");
  parseSide(msg);
  parseUnum(msg);
  // calc

}

World::Perception::~Perception(){}

void World::update(const std::string& msg){
  Perception* perc;
  perc = new Perception(msg);

  deqPerception.push_back(perc);// input the pointer

  while(deqPerception.size()>1000){
    if(deqPerception.empty()) break;
    std::cout << "deqPerception: too much data!" << std::endl;
    delete (deqPerception.front());
    deqPerception.pop_front();
  }
}

void World::dump(){
  // here dumping joint values
  std::cout << "hj1 : " << getAngle("hj1") 
  	    << ", hj2 : " << getAngle("hj2") << std::endl;
  std::cout << "laj1 : " << getAngle("laj1")
  	    << ", laj2 : " << getAngle("laj2")
  	    << ", laj3 : " << getAngle("laj3")
  	    << ", laj4 : " << getAngle("laj4") << std::endl;
  std::cout << "raj1 : " << getAngle("raj1")
  	    << ", raj2 : " << getAngle("raj2")
  	    << ", raj3 : " << getAngle("raj3")
  	    << ", raj4 : " << getAngle("raj4") << std::endl;
  std::cout << "llj1 : " << getAngle("llj1")
  	    << ", llj2 : " << getAngle("llj2")
  	    << ", llj3 : " << getAngle("llj3")
  	    << ", llj4 : " << getAngle("llj4")
  	    << ", llj5 : " << getAngle("llj5")
  	    << ", llj6 : " << getAngle("llj6") << std::endl;
  std::cout << "rlj1 : " << getAngle("rlj1")
  	    << ", rlj2 : " << getAngle("rlj2")
  	    << ", rlj3 : " << getAngle("rlj3")
  	    << ", rlj4 : " << getAngle("rlj4")
  	    << ", rlj5 : " << getAngle("rlj5")
  	    << ", rlj6 : " << getAngle("rlj6") << std::endl;
  std::cout << std::endl;

}

double World::getAngle(std::string jointname){
  if(deqPerception.empty()) return 0.0;

  return (*(deqPerception.back())).jointValue[jointname];
}

void World::Perception::setJointMap(){
  jointMap.clear();

  jointMap["hj1"] = hj1;
  jointMap["hj2"] = hj2;
  jointMap["laj1"] = laj1;
  jointMap["raj1"] = raj1;
  jointMap["laj2"] = laj2;
  jointMap["raj2"] = raj2;
  jointMap["laj3"] = laj3;
  jointMap["raj3"] = raj3;
  jointMap["laj4"] = laj4;
  jointMap["raj4"] = raj4;
  jointMap["llj1"] = llj1;
  jointMap["rlj1"] = rlj1;
  jointMap["llj2"] = llj2;
  jointMap["rlj2"] = rlj2;
  jointMap["llj3"] = llj3;
  jointMap["rlj3"] = rlj3;
  jointMap["llj4"] = llj4;
  jointMap["rlj4"] = rlj4;
  jointMap["llj5"] = llj5;
  jointMap["rlj5"] = rlj5;
  jointMap["llj6"] = llj6;
  jointMap["rlj6"] = rlj6;
}

void World::Perception::setSeenMap(){
  seenMap.clear();

  seenMap["G1L"] = g1l;
  seenMap["G2L"] = g2l;
  seenMap["G1R"] = g1r;
  seenMap["G2R"] = g2r;
  seenMap["F1L"] = f1l;
  seenMap["F2L"] = f2l;
  seenMap["F1R"] = f1r;
  seenMap["F2R"] = f2r;
  seenMap["B"] = bal;
}

using namespace std;

void World::Perception::parseGamestate(std::string message){
  string::size_type from, until;
  std::string mode;

  string msg(message);

  from = msg.find("now");
  if(from == string::npos){
    return;
  }
  until = msg.find(")", from);

  from = msg.find("GS");
  if(from == string::npos){
    return;
  }
  until = msg.find(")", from);

  from = msg.find("pm", from);
  if(from == string::npos){
    return;
  }
  until = msg.find(")", from);
  mode = msg.substr(from + 3, until - (from + 3));

  setPlaymode(mode);
}

double World::Perception::parseJoint(std::string message, std::string id){
  //if use jointID, we need string id to find...
  string::size_type find_id, from, until;
  string current_angle;
  tempJointMap::iterator tjmap;

  string msg(message);

  find_id = msg.find(id);

  if(find_id == string::npos){
    return 0.0;
  }

  from = msg.find("ax", find_id);
  until = msg.find(")", from);

  current_angle = msg.substr(from + 3, until - (from + 3));

  tjmap = (jointMap).find(id);
  switch(tjmap->second){
  case hj1: return atof(current_angle.c_str());
  case hj2: return atof(current_angle.c_str());
  case laj1: return atof(current_angle.c_str());
  case raj1: return atof(current_angle.c_str());
  case laj2: return atof(current_angle.c_str());
  case raj2: return atof(current_angle.c_str());
  case laj3: return atof(current_angle.c_str());
  case raj3: return atof(current_angle.c_str());
  case laj4: return atof(current_angle.c_str());
  case raj4: return atof(current_angle.c_str());
  case llj1: return atof(current_angle.c_str());
  case rlj1: return atof(current_angle.c_str());
  case llj2: return atof(current_angle.c_str());
  case rlj2: return atof(current_angle.c_str());
  case llj3: return atof(current_angle.c_str());
  case rlj3: return atof(current_angle.c_str());
  case llj4: return atof(current_angle.c_str());
  case rlj4: return atof(current_angle.c_str());
  case llj5: return atof(current_angle.c_str());
  case rlj5: return atof(current_angle.c_str());
  case llj6: return atof(current_angle.c_str());
  case rlj6: return atof(current_angle.c_str());
  default:
    //std::cout << "Not find ID : " << id << " !!" << std::endl;
    break;
  }
  return 0.0;
}

void World::Perception::parseJointValue(std::string msg){

  jointValue.clear();
  //can use for(;;)?
  jointValue["hj1"] = parseJoint(msg, "hj1");
  jointValue["hj2"] = parseJoint(msg, "hj2");
  jointValue["laj1"] = parseJoint(msg, "laj1");
  jointValue["raj1"] = parseJoint(msg, "raj1");
  jointValue["laj2"] = parseJoint(msg, "laj2");
  jointValue["raj2"] = parseJoint(msg, "raj2");
  jointValue["laj3"] = parseJoint(msg, "laj3");
  jointValue["raj3"] = parseJoint(msg, "raj3");
  jointValue["laj4"] = parseJoint(msg, "laj4");
  jointValue["raj4"] = parseJoint(msg, "raj4");
  jointValue["llj1"] = parseJoint(msg, "llj1");
  jointValue["rlj1"] = parseJoint(msg, "rlj1");
  jointValue["llj2"] = parseJoint(msg, "llj2");
  jointValue["rlj2"] = parseJoint(msg, "rlj2");
  jointValue["llj3"] = parseJoint(msg, "llj3");
  jointValue["rlj3"] = parseJoint(msg, "rlj3");
  jointValue["llj4"] = parseJoint(msg, "llj4");
  jointValue["rlj4"] = parseJoint(msg, "rlj4");
  jointValue["llj5"] = parseJoint(msg, "llj5");
  jointValue["rlj5"] = parseJoint(msg, "rlj5");
  jointValue["llj6"] = parseJoint(msg, "llj6");
  jointValue["rlj6"] = parseJoint(msg, "rlj6");
}

void World::Perception::parseSeen(std::string message, std::string id){
  string::size_type find_id, from, until;
  string data[3];
  double updatevalue[3];
  tempSeenMap::iterator tsmap;

  string msg(message);

  find_id = msg.find(id + " (");

  if(find_id == string::npos){
    for(int i=0; i<3; i++){
      updatevalue[i] = sqrt(-1);
    }
  }else{

    from = msg.find("pol", find_id);
    until = msg.find(" ", from + 4);
    data[0] = msg.substr(from + 4, until - (from + 4));

    from = until + 1;
    until = msg.find(" ",  from);
    data[1] = msg.substr(from, until - from);

    from = until + 1;
    until = msg.find(")", from);
    data[2] = msg.substr(from, until - from);

    //copy data[] (include value in msg or "nan")
    updatevalue[0] = atof(data[0].c_str());
    updatevalue[1] = atof(data[1].c_str()) + parseJoint(message, "hj1");
    updatevalue[2] = atof(data[2].c_str());
  }

  tsmap = seenMap.find(id);

  switch(tsmap->second){
  case g1l:
    for(int i = 0; i < 3; i++){
      G1L[i] = updatevalue[i];
    }
    break;
  case g2l:
    for(int i = 0; i < 3; i++){
      G2L[i] = updatevalue[i];
    }
    break;
  case g1r: 
    for(int i = 0; i < 3; i++){
      G1R[i] = updatevalue[i];
    }
    break;
  case g2r:
    for(int i = 0; i < 3; i++){
      G2R[i] = updatevalue[i];
    }
    break;
  case f1l:
    for(int i = 0; i < 3; i++){
      F1L[i] = updatevalue[i];
    }
    break;
  case f2l:
    for(int i = 0; i < 3; i++){
      F2L[i] = updatevalue[i];
    }
    break;
  case f1r:
    for(int i = 0; i < 3; i++){
      F1R[i] = updatevalue[i];
    }
    break;
  case f2r:
    for(int i = 0; i < 3; i++){
      F2R[i] = updatevalue[i];
    }
    break;
  case bal:
    for(int i = 0; i < 3; i++){
      BAL[i] = updatevalue[i];
    }
    break;
  default:
    break;
  }
}

void World::Perception::parsePlayer(std::string msg, std::string id, double player[][4]){
}

void World::Perception::parseFRP(std::string msg){
}

void World::Perception::parseGYR(std::string msg){
}

void World::Perception::parseACC(std::string msg){
}


void World::Perception::parseMYPOS(std::string msg){
}

void World::Perception::parseBALLPOS(std::string msg){
}

void World::Perception::parseSide(std::string msg){
}

void World::Perception::parseUnum(std::string msg){
}

void World::Perception::getPlayer(std::string msg, std::string id){
}

double* World::Perception::getMGL(Side side){
  if(side == LEFT){
    return G1L;
  }else if(side == RIGHT){
    return G2R;
  }else{
    std::cout << "World::Perception::getMGL UNKNOWN SIDE!" << std::endl;
    return NULL;
  }
}

double* World::Perception::getMGR(Side side){
  if(side == LEFT){
    return G2L;
  }else if(side == RIGHT){
    return G1R;
  }else{
    std::cout << "World::Perception::getMGR UNKNOWN SIDE!" << std::endl;
    return NULL;
  }
}

double* World::Perception::getEGL(Side side){
  if(side == LEFT){
    return G1R;
  }else if(side == RIGHT){
    return G2L;
  }else{
    std::cout << "World::Perception::getEGL UNKNOWN SIDE!" << std::endl;
    return NULL;
  }
}

double* World::Perception::getEGR(Side side){
  if(side == LEFT){
    return G2R;
  }else if(side == RIGHT){
    return G1L;
  }else{
    std::cout << "World::Perception::getEGR UNKNOWN SIDE!" << std::endl;
    return NULL;
  }
}

double* World::Perception::getMFL(Side side){
  if(side == LEFT){
    return F1L;
  }else if(side == RIGHT){
    return F2R;
  }else{
    std::cout << "World::Perception::getMFL UNKNOWN SIDE!" << std::endl;
    return NULL;
  }
}
double* World::Perception::getMFR(Side side){
  if(side == LEFT){
    return F2L;
  }else if(side == RIGHT){
    return F1R;
  }else{
    std::cout << "World::Perception::getMFR UNKNOWN SIDE!" << std::endl;
    return NULL;
  }
}

double* World::Perception::getEFL(Side side){
  if(side == LEFT){
    return F1R;
  }else if(side == RIGHT){
    return F2L;
  }else{
    std::cout << "World::Perception::getEFL UNKNOWN SIDE!" << std::endl;
    return NULL;
  }
}

double* World::Perception::getEFR(Side side){
  if(side == LEFT){
    return F2R;
  }else if(side == RIGHT){
    return F1L;
  }else{
    std::cout << "World::Perception::getEFR UNKNOWN SIDE!" << std::endl;
    return NULL;
  }
}

double* World::Perception::getBAL(){
  return BAL;
}

void World::setTeamname(std::string name){
  teamname = name;
}

std::string World::getTeamname(){
  return teamname;
}

void World::setUnum(int num){
  unum = num;
}

int World::getUnum(){
  return unum;
}

void World::Perception::setPlaymode(std::string mode){
  //  playmode = mode;
}

std::string World::getPlaymode(){
  return playmode;
}

void World::setIsMatch(bool which){
  isMatch = which;
}

bool World::getIsMatch(){
  return isMatch;
}
