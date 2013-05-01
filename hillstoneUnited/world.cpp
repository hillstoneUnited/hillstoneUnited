#include "world.hpp"
#include <cstdlib>
#include <math.h>
#include <string.h>

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

World::Perception::Perception(const std::string& msg, World& world){
  setJointMap();
  setSeenMap();


  parseGamestate(msg, world);
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
  getPlayer(msg, "friend", world);
  getPlayer(msg, "enemy", world);
  parseSide(msg, world);
  parseUnum(msg, world);

}

World::Perception::~Perception(){}

///////////////////////////////////////////////////////////////
// World::update and dump
//   Update data from Agent's Perceptor every cicles
//   Dump the data Perception deque contains
///////////////////////////////////////////////////////////////

void World::update(const std::string& msg){
  Perception* perc;
  perc = new Perception(msg, *this);


  deqPerception.push_back(perc);
  perc->calcuratePerception(*this);
  while(deqPerception.size()>DEQUE_SIZE){
    if(deqPerception.empty()) break;
    //    std::cout << "deqPerception: too much data!" << std::endl;
    delete (deqPerception.front());
    deqPerception.pop_front();
  }
}

void World::dump(){

  // static int count = 0;
  // std::cout << "this is " << ++count << " times of DUMP" << std::endl;


  // std::cout << "hj1 : " << getAngle("hj1") << ", "
  // 	    << "hj2 : " << getAngle("hj2") << std::endl;
  // std::cout << "laj1 : " << getAngle("laj1") << ", "
  // 	    << "laj2 : " << getAngle("laj2") << ", "
  // 	    << "laj3 : " << getAngle("laj3") << ", "
  // 	    << "laj4 : " << getAngle("laj4") << std::endl;
  // std::cout << "raj1 : " << getAngle("raj1") << ", "
  // 	    << "raj2 : " << getAngle("raj2") << ", "
  // 	    << "raj3 : " << getAngle("raj3") << ", "
  // 	    << "raj4 : " << getAngle("raj4") << std::endl;
  // std::cout << "llj1 : " << getAngle("llj1") << ", "
  // 	    << "llj2 : " << getAngle("llj2") << ", "
  // 	    << "llj3 : " << getAngle("llj3") << ", "
  // 	    << "llj4 : " << getAngle("llj4") << ", "
  // 	    << "llj5 : " << getAngle("llj5") << ", "
  // 	    << "llj6 : " << getAngle("llj6") << std::endl;
  // std::cout << "rlj1 : " << getAngle("rlj1") << ", "
  // 	    << "rlj2 : " << getAngle("rlj2") << ", "
  // 	    << "rlj3 : " << getAngle("rlj3") << ", "
  // 	    << "rlj4 : " << getAngle("rlj4") << ", "
  // 	    << "rlj5 : " << getAngle("rlj5") << ", "
  // 	    << "rlj6 : " << getAngle("rlj6") << std::endl;
  // std::cout << std::endl;

  // std::cout << "MGL : "
  // 	    << getMGL(0) << ", "
  // 	    << getMGL(1) << ", "
  // 	    << getMGL(2) << std::endl;
  // std::cout << "MGR : "
  // 	    << getMGR(0) << ", "
  // 	    << getMGR(1) << ", "
  // 	    << getMGR(2) << std::endl;
  // std::cout << "EGL : "
  // 	    << getEGL(0) << ", "
  // 	    << getEGL(1) << ", "
  // 	    << getEGL(2) << std::endl;
  // std::cout << "EGR : "
  // 	    << getEGR(0) << ", "
  // 	    << getEGR(1) << ", "
  // 	    << getEGR(2) << std::endl;
  // std::cout << "MFL : "
  // 	    << getMFL(0) << ", "
  // 	    << getMFL(1) << ", "
  // 	    << getMFL(2) << std::endl;
  // std::cout << "MFR : "
  // 	    << getMFR(0) << ", "
  // 	    << getMFR(1) << ", "
  // 	    << getMFR(2) << std::endl;
  // std::cout << "EFL : "
  // 	    << getEFL(0) << ", "
  // 	    << getEFL(1) << ", "
  // 	    << getEFL(2) << std::endl;
  // std::cout << "EFR : "
  // 	    << getEFR(0) << ", "
  // 	    << getEFR(1) << ", "
  // 	    << getEFR(2) << std::endl;
  // std::cout << "BAL : "
  // 	    << getBAL(0) << ", "
  // 	    << getBAL(1) << ", "
  // 	    << getBAL(2) << std::endl;
  // std::cout << std::endl;

  // std::cout << "FRP_RC :"
  // 	    << getFRP_RC(0) << ", "
  // 	    << getFRP_RC(1) << ", "
  // 	    << getFRP_RC(2) << std::endl;
  // std::cout << "FRP_RF :"
  // 	    << getFRP_RF(0) << ", "
  // 	    << getFRP_RF(1) << ", "
  // 	    << getFRP_RF(2) << std::endl;
  // std::cout << "FRP_LC :"
  // 	    << getFRP_LC(0) << ", "
  // 	    << getFRP_LC(1) << ", "
  // 	    << getFRP_LC(2) << std::endl;
  // std::cout << "FRP_LF :"
  // 	    << getFRP_LF(0) << ", "
  // 	    << getFRP_LF(1) << ", "
  // 	    << getFRP_LF(2) << std::endl;

  // std::cout << "GYR :"
  // 	    << getGYR(0) << ", "
  // 	    << getGYR(1) << ", "
  // 	    << getGYR(2) << std::endl;
  // std::cout << "ACC :"
  // 	    << getACC(0) << ", "
  // 	    << getACC(1) << ", "
  // 	    << getACC(2) << std::endl;
  // std::cout << "MYPOS :"
  // 	    << getMYPOS(0) << ", "
  // 	    << getMYPOS(1) << ", "
  // 	    << getMYPOS(2) << std::endl;

  // std::cout << "BALLPOS :"
  // 	    << getBALLPOS(0) << ", "
  // 	    << getBALLPOS(1) << ", "
  // 	    << getBALLPOS(2) << std::endl;
  // std::cout << "FRIEND(1) :"
  // 	    << getFRIEND(1,0) << ", "
  // 	    << getFRIEND(1,1) << ", "
  // 	    << getFRIEND(1,2) << std::endl;
  // std::cout << "ENEMY(1) :"
  // 	    << getENEMY(1,0) << ", "
  // 	    << getENEMY(1,1) << ", "
  // 	    << getENEMY(1,2) << std::endl;

  // std::cout << "XY :"
  // 	    << getXY(0) << ", "
  // 	    << getXY(1) << std::endl;
  // std::cout << "BXY :"
  // 	    << getBXY(0) << ", "
  // 	    << getBXY(1) << std::endl;
  // std::cout << "ABSANGLE :"
  // 	    << getABSANGLE() << std::endl;
  // std::cout << "BANGLE :"
  // 	    << getBANGLE() << std::endl;

  // std::cout << "ACC_Sum :"
  // 	    << getACC_Sum(0, 10) << ", "
  // 	    << getACC_Sum(1, 10) << ", "
  // 	    << getACC_Sum(2, 10) << std::endl;

  // std::cout << unum << std::endl;
  // std::cout << side << std::endl;
  // std::cout << playmode << std::endl;

  // std::cout << std::endl;

}

//////////////////////////////////////////////////////////////
// World::Perception::set**
//   parse and set parameters into Perception deque
//////////////////////////////////////////////////////////////

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

void World::Perception::parseGamestate(std::string message, World& world){
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

  setPlaymode(mode, world);
}

double World::Perception::parseJoint(std::string message, std::string id){

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
    std::cout << "Cannot find ID : " << id << " !!" << std::endl;
    break;
  }
  return 0.0;
}

void World::Perception::parseJointValue(std::string msg){

  jointValue.clear();
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

    updatevalue[0] = atof(data[0].c_str());
    updatevalue[1] = atof(data[1].c_str()) + parseJoint(message, "hj1");
    updatevalue[2] = atof(data[2].c_str());
  }

  tsmap = seenMap.find(id);

  switch(tsmap->second){
  case g1l:
    for(int i = 0; i < 3; i++)
      G1L[i] = updatevalue[i];
    break;
  case g2l:
    for(int i = 0; i < 3; i++)
      G2L[i] = updatevalue[i];
    break;
  case g1r: 
    for(int i = 0; i < 3; i++)
      G1R[i] = updatevalue[i];
    break;
  case g2r:
    for(int i = 0; i < 3; i++)
      G2R[i] = updatevalue[i];
    break;
  case f1l:
    for(int i = 0; i < 3; i++)
      F1L[i] = updatevalue[i];
    break;
  case f2l:
    for(int i = 0; i < 3; i++)
      F2L[i] = updatevalue[i];
    break;
  case f1r:
    for(int i = 0; i < 3; i++)
      F1R[i] = updatevalue[i];
    break;
  case f2r:
    for(int i = 0; i < 3; i++)
      F2R[i] = updatevalue[i];
    break;
  case bal:
    for(int i = 0; i < 3; i++)
      BAL[i] = updatevalue[i];
    break;
  default:
    break;
  }
}

void World::Perception::parsePlayer(std::string message, std::string id, double player[][4], World& world){
  static string enemyname;
  string::size_type find_id, from, until;
  string team_id, data[11][4];
  int i, s, j, player_num;

  string msg(message);

  if(id == "enemy"){
    find_id = msg.find("team");
    while(find_id != string::npos){
      from = find_id + strlen("team ");
      until = msg.find(")", from);

      enemyname = msg.substr(from, until - from);
      if(enemyname != world.teamname) break;
      find_id = msg.find("team", until);
    }
  }

  if(id == "enemy" && (enemyname == world.teamname || enemyname == "left" || enemyname == "right")) return;

  player_num = 0;

  for(i=0; i<11; i++){
    for(j=0; j<4; j++){
      data[i][j] = "0";
    }
  }

  if(id == "friend"){
    team_id = world.teamname;
  }
  else if(id == "enemy"){
    team_id = enemyname;
  }

  find_id = msg.find("team " + team_id);

  while(find_id != string::npos){
    player_num++;

    // player ID
    from = msg.find("id", find_id);
    until = msg.find(")", from + strlen("id "));
    data[player_num - 1][3] = msg.substr(from + strlen("id "), until - (from + strlen("id ")));

    // player data
    from = msg.find("pol", find_id);
    until = msg.find(" ", from  + strlen("pol "));
    data[player_num - 1][0] = msg.substr(from + strlen("pol "), until - (from + strlen("pol ")));

    from = until + strlen(" ");
    until = msg.find(" ", from);
    data[player_num - 1][1] = msg.substr(from, until - from);

    from = until + strlen(" ");
    until = msg.find(")", from);
    data[player_num - 1][2] = msg.substr(from, until - from);

    find_id = msg.find("team " + team_id, until);

    if(player_num >= 11) break;
  }

  // copy data
  while(player_num > 0){
    i = player_num - 1;
    s = atof(data[i][3].c_str()) - 1;
    if(id == "enemy" || (atof(data[i][3].c_str()) != world.unum)){
      player[s][0] = atof(data[i][0].c_str());
      player[s][1] = atof(data[i][1].c_str());
      player[s][2] = atof(data[i][2].c_str());
      player[s][3] = atof(data[i][3].c_str());
    }
    player_num = player_num - 1;
  }
}

void World::Perception::parseFRP(std::string msg){
  double FRP_RC[3];
  double FRP_RF[3];
  double FRP_LC[3];
  double FRP_LF[3];

  for(int i=0; i<3; i++){
    FRP_RC[i] = sqrt(-1);
    FRP_RF[i] = sqrt(-1);
    FRP_LC[i] = sqrt(-1);
    FRP_LF[i] = sqrt(-1);
  }

  string s = string(msg);
  string temp1, tempfrp_rc[3];
  string temp2, tempfrp_rf[3];
  string temp3, tempfrp_lc[3];
  string temp4, tempfrp_lf[3];
  string::size_type rc;
  string::size_type rf;
  string::size_type lc;
  string::size_type lf;

  if(s.find("(FRP") != string::npos){
    if(s.find("rf) (c") != string::npos){
      rc = s.find("rf) (c ", s.find("FRP"));
      temp1 = s.substr(rc + strlen("rf) (c "), s.find(") (f", rc) - (rc + strlen("rf) (c ")));
      rf = s.find(") (f ", s.find("FRP"));
      temp2 = s.substr(rf + strlen(") (f "), s.find("))", rf) - (rf + strlen(") (f ")));


      for(int i=0; i<3; i++){
	tempfrp_rc[i] = temp1.substr(0, temp1.find(" "));
	temp1 = temp1.substr(temp1.find(" ") + 1);
	tempfrp_rf[i] = temp2.substr(0, temp2.find(" "));
	temp2 = temp2.substr(temp2.find(" ") + 1);
      }
      for(int i=0; i<3; i++){
	FRP_RC[i] = atof(tempfrp_rc[i].c_str());
	FRP_RF[i] = atof(tempfrp_rf[i].c_str());
      }

    }
    if(s.find("lf) (c") != string::npos){
      lc = s.find("lf) (c ", s.find("FRP"));
      temp3 = s.substr(lc + strlen("lf) (c "), s.find(") (f", lc) - (lc + strlen("lf) (c ")));
      lf = s.find(") (f ", s.find("FRP"));
      temp4 = s.substr(lf + strlen(") (f "), s.find("))", lf) - (lf + strlen(") (f ")));


      for(int i=0; i<3; i++){
	tempfrp_lc[i] = temp3.substr(0, temp3.find(" "));
	temp3 = temp3.substr(temp3.find(" ") + 1);
	tempfrp_lf[i] = temp4.substr(0, temp4.find(" "));
	temp4 = temp4.substr(temp4.find(" ") + 1);
      }
      for(int i=0; i<3; i++){
	FRP_LC[i] = atof(tempfrp_lc[i].c_str());
	FRP_LF[i] = atof(tempfrp_lf[i].c_str());
      }
    }
  }

  for(int i=0; i<3; i++){
    this->FRP_RC[i] = FRP_RC[i];
    this->FRP_RF[i] = FRP_RF[i];
    this->FRP_LC[i] = FRP_LC[i];
    this->FRP_LF[i] = FRP_LF[i];
  }
}

void World::Perception::parseGYR(std::string msg){
  double GYR[3];
  for(int i=0; i<3; i++){
    GYR[i] = sqrt(-1);
  }

  string s = string(msg);
  string temp1, tempgyr[3];
  string::size_type torso;

  if(s.find("(GYR") != string::npos){
    if(s.find("torso) (rt") != string::npos){
      torso = s.find("torso) (rt ", s.find("GYR"));
      temp1 = s.substr(torso + strlen("torso) (rt "), s.find("))", torso) - (torso + strlen("torso) (rt ")));
      for(int i=0; i<3; i++){
	tempgyr[i] = temp1.substr(0, temp1.find(" "));
	temp1 = temp1.substr(temp1.find(" ") + 1);
      }
      for(int i=0; i<3; i++){
	GYR[i] = atof(tempgyr[i].c_str());
      }
    }
  }
  for(int i=0; i<3; i++){
    this->GYR[i] = GYR[i];
  }
}

void World::Perception::parseACC(std::string msg){
  double ACC[3];
  for(int i=0; i<3; i++){
    ACC[i] = sqrt(-1);
  }

  string s = string(msg);
  string temp1, tempacc[3];
  string::size_type torso;

  if(s.find("(ACC") != string::npos){
    if(s.find("torso) (a") != string::npos){
	torso = s.find("torso) (a ", s.find("ACC"));
	temp1 = s.substr(torso + strlen("torso) (a "), s.find("))", torso) - (torso + strlen("torso) (a ")));
	for(int i=0; i<3; i++){
	  tempacc[i] = temp1.substr(0, temp1.find(" "));
	  temp1 = temp1.substr(temp1.find(" ") + 1);
	}
	for(int i=0; i<3; i++){
	  ACC[i] = atof(tempacc[i].c_str());
	}
    }
  }
  for(int i=0; i<3; i++){
    this->ACC[i] = ACC[i];
  }
}


void World::Perception::parseMYPOS(std::string msg){
  double mypos[3];
  for(int i=0; i<3; i++){
    mypos[i] = sqrt(-1);
  }

  string s = string(msg);
  string temp1, tempmypos[3];
  string::size_type mypospoint;

  if(s.find("(mypos") != string::npos){
    mypospoint = s.find("(mypos ");
    temp1 = s.substr(mypospoint + strlen("(mypos "), s.find("))", mypospoint) - (mypospoint + strlen("(mypos")));

    for(int i=0; i<3; i++){
      tempmypos[i] = temp1.substr(0, temp1.find(" "));
      temp1 = temp1.substr(temp1.find(" ") + 1);
    }
    for(int i=0; i<3; i++){
      mypos[i] = atof(tempmypos[i].c_str());
    }
  }
  for(int i=0; i<3; i++){
    MYPOS[i] = mypos[i];
  }
}

void World::Perception::parseBALLPOS(std::string msg){
  double ballpos[3];
  for(int i=0; i<3; i++){
    ballpos[i] = sqrt(-1);
  }

  string s = string(msg);
  string temp1, tempballpos[3];
  string::size_type ballpospoint;

  if(s.find("(ballpos") != string::npos){
    ballpospoint = s.find("(ballpos ");
    temp1 = s.substr(ballpospoint + strlen("(ballpos "), s.find("))", ballpospoint) - (ballpospoint + strlen("(ballpos ")));

    for(int i=0; i<3; i++){
      tempballpos[i] = temp1.substr(0, temp1.find(" "));
      temp1 = temp1.substr(temp1.find(" ") + 1);
    }
    for(int i=0; i<3; i++){
      ballpos[i] = atof(tempballpos[i].c_str());
    }

  }
  for(int i=0; i<3; i++){
    BALLPOS[i] = ballpos[i];
  }
}

void World::Perception::parseSide(std::string msg, World& world){

  string s = string(msg);
  if(world.side == UNKNOWN){
    if(s.find("team left") != string::npos){
      world.side = LEFT;
    }else if(s.find("team right") != string::npos){
      world.side = RIGHT;
    }
  }
}

void World::Perception::parseUnum(std::string msg, World& world){

  string s = string(msg);

  if(world.unum == 0){
    if(s.find("(unum ") != string::npos){
      world.unum = atof(s.substr(s.find("unum ") + strlen("unum "), s.find(" ") - (s.find("unum ") + strlen("unum "))).c_str());
    }
  }
}

void World::Perception::getPlayer(std::string message, std::string id, World& world){
  if(id == "friend"){
    double friends[11][4];

    for(int i=0; i<11; i++){
      for(int j=0; j<4; j++){
	friends[i][j] = sqrt(-1);
      }
    }
    parsePlayer(message, id, friends, world);
    for(int i=0; i<11; i++){
      for(int j=0; j<4; j++){
	FRIEND[i][j] = friends[i][j];
      }
    }
  }else if(id == "enemy"){
    double enemies[11][4];

    for(int i=0; i<11; i++){
      for(int j=0; j<4; j++){
	enemies[i][j] = sqrt(-1);
      }
    }
    parsePlayer(message, id, enemies, world);
    for(int i=0; i<11; i++){
      for(int j=0; j<4; j++){
	ENEMY[i][j] = enemies[i][j];
      }
    }
  }else{
    std::cout << "Not find team!" << std::endl;
    return;
  }
}

void World::Perception::calcuratePerception(World& world){

  if((world.deqPerception).empty()) return;


  double xy[2]    = {sqrt(-1), sqrt(-1)};
  double bxy[2]   = {sqrt(-1), sqrt(-1)};
  double absangle = sqrt(-1);
  double bangle   = sqrt(-1);

  double remain_side = 0;
  double cos_temp    = 0;


  if(confMGL(world) == 0 && confMGR(world) == 0){

    double mgl[3];
    double mgr[3];
    switch(world.side){
    case LEFT:
      for(int i=0;i<3;i++){
	mgl[i] = G1L[i];
	mgr[i] = G2L[i];
      }
      break;
    case RIGHT:
      for(int i=0; i<3; i++){
	mgl[i] = G2R[i];
	mgr[i] = G1R[i];
      }
      break;
    default:
      std::cout << "UNKNOWN SIDE!" << std::endl;
      break;
    }
    remain_side = goal_length;
    cos_temp = (mgl[0]*mgl[0] + remain_side*remain_side - mgr[0]*mgr[0])
      / (2*mgl[0]*remain_side);
    xy[0] = -(field_length_x/2) + mgl[0]*(sqrt(1-cos_temp*cos_temp));
    xy[1] = (goal_length/2) - mgl[0]*cos_temp;
    absangle = 180.0 - (mgl[1] + (90.0 - (acos(cos_temp))*180.0/M_PI));
    if(confBAL(world) == 0){
      double *ball = BAL;
      bangle = absangle + ball[1];
      bxy[0] = xy[0] + cos(bangle*M_PI/180)*ball[0];
      bxy[1] = xy[1] + sin(bangle*M_PI/180)*ball[0];
    }
  }else if(confMGL(world) == 0 && confMFL(world) == 0){

    double mgl[3];
    double mfl[3];
    switch(world.side){
    case LEFT:
      for(int i=0; i<3; i++){
	mgl[i] = G1L[i];
	mfl[i] = F1L[i];
      }
      break;
    case RIGHT:
      for(int i=0; i<3; i++){
	mgl[i] = G2R[i];
	mfl[i] = F2R[i];
      }
      break;
    default:
      std::cout << "UNKNOWN SIDE!" << std::endl;
      break;
    }
    remain_side = (field_length_y - goal_length) / 2;
    cos_temp = (mgl[0]*mgl[0] + remain_side*remain_side - mfl[0]*mfl[0])
      / (2 * mgl[0] * remain_side);
    xy[0] = - (field_length_x/2) + mgl[0]*(sqrt(1-cos_temp*cos_temp));
    xy[1] = (goal_length/2) + mgl[0]*cos_temp;
    cos_temp = (mfl[0]*mfl[0] + remain_side*remain_side - mgl[0]*mgl[0])
      / (2 * mfl[0] * remain_side);
    absangle = 180.0 - (mfl[1] + (90.0 - (acos(cos_temp))*(180.0/M_PI)));
    if(confBAL(world) == 0){
      double *ball = BAL;
      bangle = absangle + ball[1];
      bxy[0] = xy[0] + cos(bangle*M_PI/180)*ball[0];
      bxy[1] = xy[1] + sin(bangle*M_PI/180)*ball[0];
    }
  }else if(confMGR(world) == 0 && confMFR(world) == 0){

    double mgr[3];
    double mfr[3];
    switch(world.side){
    case LEFT:
      for(int i=0; i<3; i++){
	mgr[i] = G2L[i];
	mfr[i] = F2L[i];
      }
      break;
    case RIGHT:
      for(int i=0; i<3; i++){
	mgr[i] = G1R[i];
	mfr[i] = F1R[i];
      }
      break;
    default:
      std::cout << "UNKNOWN SIDE!" << std::endl;
      break;
    }
    remain_side = (field_length_y - goal_length) / 2;
    cos_temp = (mgr[0]*mgr[0] + remain_side*remain_side - mfr[0]*mfr[0])
      / (2 * mgr[0] * remain_side);
    xy[0] = - (field_length_x/2) + mgr[0]*(sqrt(1-cos_temp*cos_temp));
    xy[1] = - (goal_length/2) - mgr[0]*cos_temp;
    absangle = 180.0 - (mgr[1] + (90.0 - (acos(cos_temp))*(180.0/M_PI)));
    if(confBAL(world) == 0){
      double *ball = BAL;
      bangle = absangle + ball[1];
      bxy[0] = xy[0] + cos(bangle*M_PI/180)*ball[0];
      bxy[1] = xy[1] + sin(bangle*M_PI/180)*ball[0];
    }
  }else if(confEGL(world) == 0 && confEGR(world) == 0){

    double egl[3];
    double egr[3];
    switch(world.side){
    case LEFT:
      for(int i=0; i<3; i++){
	egl[i] = G1R[i];
	egr[i] = G2R[i];
      }
      break;
    case RIGHT:
      for(int i=0; i<3; i++){
	egl[i] = G2L[i];
	egr[i] = G1L[i];
      }
      break;
    default:
      std::cout << "UNKNOWN SIDE!" << std::endl;
      break;
    }
    remain_side = goal_length;
    cos_temp = (egl[0]*egl[0] + remain_side*remain_side - egr[0]*egr[0])
      / (2 * egl[0] * remain_side);
    xy[0] = (field_length_x/2) - egl[0]*(sqrt(1-cos_temp*cos_temp));
    xy[1] = (goal_length/2) - egl[0]*cos_temp;
    absangle = -(egl[1] - (90.0 - (acos(cos_temp)) * 180.0/M_PI));
    if(confBAL(world) == 0){
      double *ball = BAL;
      bangle = absangle + ball[1];
      bxy[0] = xy[0] + ball[0] * cos(bangle*M_PI/180);
      bxy[1] = xy[1] + ball[0] * sin(bangle*M_PI/180);
    }
  }else if(confEGL(world) == 0 && confEFL(world) == 0){

    double egl[3];
    double efl[3];
    switch(world.side){
    case LEFT:
      for(int i=0; i<3; i++){
	egl[i] = G1R[i];
	efl[i] = F1R[i];
      }
      break;
    case RIGHT:
      for(int i=0; i<3; i++){
	egl[i] = G2L[i];
	efl[i] = F2L[i];
      }
      break;
    default:
      std::cout << "UNKNOWN SIDE!" << std::endl;
      break;
    }
    remain_side = (field_length_y - goal_length) / 2;
    cos_temp = (egl[0]*egl[0] + remain_side*remain_side - efl[0]*efl[0])
      / (2 * egl[0] * remain_side);
    xy[0] = (field_length_x/2) - egl[0]*(sqrt(1-cos_temp*cos_temp));
    xy[1] = (goal_length/2) + egl[0]*cos_temp;
    cos_temp = (efl[0]*efl[0] + remain_side*remain_side - egl[0]*egl[0])
      / (2 * efl[0] * remain_side);
    absangle = -(efl[1] - (90.0 - (acos(cos_temp) * 180.0/M_PI)));
    if(confBAL(world) == 0){
      double *ball = BAL;
      bangle = absangle + ball[1];
      bxy[0] = xy[0] + ball[0] * cos(bangle*M_PI/180);
      bxy[1] = xy[1] + ball[0] * sin(bangle*M_PI/180);
    }
  }else if(confEGR(world) == 0 && confEFR(world) == 0){

    double egr[3];
    double efr[3];
    switch(world.side){
    case LEFT:
      for(int i=0; i<3; i++){
	egr[i] = G2R[i];
	efr[i] = F2R[i];
      }
      break;
    case RIGHT:
      for(int i=0; i<3; i++){
	egr[i] = G1L[i];
	efr[i] = F1L[i];
      }
      break;
    default:
      std::cout << "UNKNOWN SIDE!" << std::endl;
      break;
    }
    remain_side = (field_length_y - goal_length) / 2;
    cos_temp = (egr[0]*egr[0] + remain_side*remain_side - efr[0]*efr[0])
      / (2 * egr[0] * remain_side);
    xy[0] = (field_length_x/2) - egr[0]*(sqrt(1-cos_temp*cos_temp));
    xy[1] = -(goal_length/2) - egr[0]*cos_temp;
    absangle = -(egr[1] - (90.0 - (acos(cos_temp)) * 180.0/M_PI));
    if(confBAL(world) == 0){
      double *ball = BAL;
      bangle = absangle + ball[1];
      bxy[0] = xy[0] + ball[0] * cos(bangle*M_PI/180);
      bxy[1] = xy[1] + ball[0] * sin(bangle*M_PI/180);
    }
  }

  if(absangle <= -180){
    absangle += 360;
  }else if(absangle > 180){
    absangle -= 360;
  }

  if(bangle <= -180){
    bangle += 360;
  }else if(bangle > 180){
    bangle -= 360;
  }


  for(int i=0; i<2; i++){
    XY[i] = xy[i];
    BXY[i] = bxy[i];
  }
  ABSANGLE = absangle;
  BANGLE = bangle;
}

//////////////////////////////////////////////////////
// World::Perception::conf**                        //
//   Methods for get Confidence in Perception       //
//////////////////////////////////////////////////////


int World::Perception::confMGL(World& world) const{
  int SIZE = (world.deqPerception).size();

  if(world.side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).G1L[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).G2R[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::Perception::confMGR(World& world) const{
  int SIZE = (world.deqPerception).size();

  if(world.side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).G2L[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).G1R[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::Perception::confEGL(World& world) const{
  int SIZE = (world.deqPerception).size();

  if(world.side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).G1R[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).G2L[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::Perception::confEGR(World& world) const{
  int SIZE = (world.deqPerception).size();

  if(world.side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).G2R[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).G1L[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::Perception::confMFL(World& world) const{
  int SIZE = (world.deqPerception).size();

  if(world.side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).F1L[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).F2R[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::Perception::confMFR(World& world) const{
  int SIZE = (world.deqPerception).size();

  if(world.side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).F2L[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).F1R[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::Perception::confEFL(World& world) const{
  int SIZE = (world.deqPerception).size();

  if(world.side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).F1R[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).F2L[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::Perception::confEFR(World& world) const{
  int SIZE = (world.deqPerception).size();

  if(world.side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).F2R[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(world.deqPerception[SIZE-i-1])).F1L[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::Perception::confBAL(World& world) const{
  int SIZE = (world.deqPerception).size();

  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(world.deqPerception[SIZE-i-1])).BAL[0])){
      return i;
    }
  }
  return DEQUE_SIZE;
}


//////////////////////////////////////////////////////
// World::get**     
//   Methods for getter
//////////////////////////////////////////////////////


double World::getAngle(std::string jointname) const{
  if(deqPerception.empty()) return 0.0;

  return (*(deqPerception.back())).jointValue[jointname];
}

double World::getMGL(int index) const{
  if(index > 3){
    std::cout << "getMGL:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G1L[index])){
	return ((*(deqPerception[SIZE-i-1])).G1L[index]);
      }
    }
    return 0.0;
  }else if(side == RIGHT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G2R[index])){
	return ((*(deqPerception[SIZE-i-1])).G2R[index]);
      }
    }
    return 0.0;
  }else{
    std::cout << "World::Perception::getMGL UNKNOWN SIDE!" << std::endl;
    return 0.0;
  }
}

double World::getMGR(int index) const{
  if(index > 3){
    std::cout << "getMGR:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G2L[index])){
	return ((*(deqPerception[SIZE-i-1])).G2L[index]);
      }
    }
    return 0.0;
  }else if(side == RIGHT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G1R[index])){
	return ((*(deqPerception[SIZE-i-1])).G1R[index]);
      }
    }
    return 0.0;
  }else{
    std::cout << "World::Perception::getMGR UNKNOWN SIDE!" << std::endl;

    return 0.0;
  }
}

double World::getEGL(int index) const{
  if(index > 3){
    std::cout << "getEGL:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G1R[index])){
	return ((*(deqPerception[SIZE-i-1])).G1R[index]);
      }
    }
    return 0.0;
  }else if(side == RIGHT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G2L[index])){
	return ((*(deqPerception[SIZE-i-1])).G2L[index]);
      }
    }
    return 0.0;
  }else{
    std::cout << "World::Perception::getEGL UNKNOWN SIDE!" << std::endl;
    return 0.0;
  }
}

double World::getEGR(int index) const{
  if(index > 3){
    std::cout << "getEGR:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G2R[index])){
	return ((*(deqPerception[SIZE-i-1])).G2R[index]);
      }
    }
    return 0.0;
  }else if(side == RIGHT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G1L[index])){
	return ((*(deqPerception[SIZE-i-1])).G1L[index]);
      }
    }
    return 0.0;
  }else{
    std::cout << "World::Perception::getEGR UNKNOWN SIDE!" << std::endl;
    return 0.0;
  }
}

double World::getMFL(int index) const{
  if(index > 3){
    std::cout << "getMFL:: unexpected indexnumber : " << index << std::endl;;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F1L[index])){
	return ((*(deqPerception[SIZE-i-1])).F1L[index]);
      }
    }
    return 0.0;
  }else if(side == RIGHT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F2R[index])){
	return ((*(deqPerception[SIZE-i-1])).F2R[index]);
      }
    }
    return 0.0;
  }else{
    std::cout << "World::Perception::getMFL UNKNOWN SIDE!" << std::endl;

    return 0.0;
  }
}

double World::getMFR(int index) const{
  if(index > 3){
    std::cout << "getMFR:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F2L[index])){
	return ((*(deqPerception[SIZE-i-1])).F2L[index]);
      }
    }
    return 0.0;
  }else if(side == RIGHT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F1R[index])){
	return ((*(deqPerception[SIZE-i-1])).F1R[index]);
      }
    }
    return 0.0;
  }else{
    std::cout << "World::Perception::getMFR UNKNOWN SIDE!" << std::endl;
    return 0.0;
  }
}

double World::getEFL(int index) const{
  if(index > 3){
    std::cout << "getEFL:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F1R[index])){
	return ((*(deqPerception[SIZE-i-1])).F1R[index]);
      }
    }
    return 0.0;
  }else if(side == RIGHT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F2L[index])){
	return ((*(deqPerception[SIZE-i-1])).F2L[index]);
      }
    }
    return 0.0;
  }else{
    std::cout << "World::Perception::getEFL UNKNOWN SIDE!" << std::endl;

    return 0.0;
  }
}

double World::getEFR(int index) const{
  if(index > 3){
    std::cout << "getEFR:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F2R[index])){
	return ((*(deqPerception[SIZE-i-1])).F2R[index]);
      }
    }
    return 0.0;
  }else if(side == RIGHT){
    for(int i=0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F1L[index])){
	return ((*(deqPerception[SIZE-i-1])).F1L[index]);
      }
    }
    return 0.0;
  }else{
    std::cout << "World::Perception::getEFR UNKNOWN SIDE!" << std::endl;

    return 0.0;
  }
}

double World::getBAL(int index) const{

  if(index > 3){
    std::cout << "getBAL:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).BAL[index])){
      return ((*(deqPerception[SIZE-i-1])).BAL[index]);
    }
  }

  return 0.0;
}

double World::getFRP_RC(int index) const{
  if(index > 3){
    std::cout << "getFRP_RC:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).FRP_RC[index])){
      return ((*(deqPerception[SIZE-i-1])).FRP_RC[index]);
    }
  }

  return 0.0;
}

double World::getFRP_RF(int index) const{
  if(index > 3){
    std::cout << "getFRP_RF:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).FRP_RF[index])){
      return ((*(deqPerception[SIZE-i-1])).FRP_RF[index]);
    }
  }

  return 0.0;
}

double World::getFRP_LC(int index) const{
  if(index > 3){
    std::cout << "getFRP_LC:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).FRP_LC[index])){
      return ((*(deqPerception[SIZE-i-1])).FRP_LC[index]);
    }
  }

  return 0.0;
}

double World::getFRP_LF(int index) const{
  if(index > 3){
    std::cout << "getFRP_LF:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).FRP_LF[index])){
      return ((*(deqPerception[SIZE-i-1])).FRP_LF[index]);
    }
  }

  return 0.0;
}

double World::getGYR(int index) const{
  if(index > 3){
    std::cout << "getGYR:: unexpected indexnumber : " << index << std::endl; 
    return 0.0;
  }

  int SIZE = deqPerception.size();
  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).GYR[index])){
      return ((*(deqPerception[SIZE-i-1])).GYR[index]);
    }
  }

  return 0.0;
}

double World::getACC(int index) const{
  if(index > 3){
    std::cout << "getACC:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).ACC[index])){
      return ((*(deqPerception[SIZE-i-1])).ACC[index]);
    }
  }

  return 0.0;
}

double World::getMYPOS(int index) const{
  if(index > 3){
    std::cout << "getMYPOS:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).MYPOS[index])){
      return ((*(deqPerception[SIZE-i-1])).MYPOS[index]);
    }
  }

  return 0.0;
}
double World::getBALLPOS(int index) const{
  if(index > 3){
    std::cout << "getBALLPOS:: unexpected indexnumber  : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).BALLPOS[index])){
      return ((*(deqPerception[SIZE-i-1])).BALLPOS[index]);
    }
  }

  return 0.0;
}

double World::getFRIEND(int unum, int index) const{
  if(index > 3){
    std::cout << "getFRIEND:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).FRIEND[unum][index])){
      return ((*(deqPerception[SIZE-i-1])).FRIEND[unum][index]);
    }
  }

  return 0.0;
}

double World::getENEMY(int unum, int index) const{
  if(index > 3){
    std::cout << "getENEMY:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).ENEMY[unum][index])){
      return ((*(deqPerception[SIZE-i-1])).ENEMY[unum][index]);
    }
  }

  return 0.0;
}

double World::getXY(int index) const{
  if(index > 2){
    std::cout << "getXY:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).XY[index])){
      return ((*(deqPerception[SIZE-i-1])).XY[index]);
    }
  }

  return 0.0;
}

double World::getBXY(int index) const{
  if(index > 2){
    std::cout << "getBXY:: unexpected indexnumber : " << index << std::endl; 
    return 0.0;
  }

  int SIZE = deqPerception.size();
  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).BXY[index])){
      return ((*(deqPerception[SIZE-i-1])).BXY[index]);
    }
  }

  return 0.0;
}

double World::getABSANGLE() const{

  int SIZE = deqPerception.size();
  static double sentinel[3] = {0};

  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).ABSANGLE)){
      return ((*(deqPerception[SIZE-i-1])).ABSANGLE);
    }
  }

  return sentinel[0];
}
double World::getBANGLE() const{

  int SIZE = deqPerception.size();
  static double sentinel[3] = {0};

  for(int i=0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).BANGLE)){
      return ((*(deqPerception[SIZE-i-1])).BANGLE);
    }
  }

  return sentinel[0];
}

double World::getACC_Sum(int index, int num) const{

  if(index > 3){
    std::cout << "getACC_Sum:: unexpected indexnumber : " << index << std::endl;
    return 0.0;
  }

  int SIZE = deqPerception.size();
  if(num > SIZE){
    num = SIZE;
  }

  double temp = 0;
  for(int i=0; i<num; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).ACC[index])){
      temp += ((*(deqPerception[SIZE-i-1])).ACC[index]);
    }
  }
  return temp;
}


//////////////////////////////////////////////////////
// World::conf**     
//   Methods for get confidence
//////////////////////////////////////////////////////


int World::confMGL() const{
  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G1L[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G2R[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::confMGR() const{
  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G2L[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G1R[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::confEGL() const{
  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G1R[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G2L[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::confEGR() const{
  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G2R[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).G1L[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::confMFL() const{
  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F1L[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F2R[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::confMFR() const{
  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F2L[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F1R[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::confEFL() const{
  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F1R[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F2L[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::confEFR() const{
  int SIZE = deqPerception.size();
  if(side == LEFT){
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F2R[0])){
	return i;
      }
    }
  }else{
    for(int i = 0; i<SIZE; i++){
      if(!isnan((*(deqPerception[SIZE-i-1])).F1L[0])){
	return i;
      }
    }
  }
  return DEQUE_SIZE;
}

int World::confBAL() const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).BAL[0])){
      return i;
    }
  }
  return DEQUE_SIZE;
}

int World::confFRP_RC() const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).FRP_RC[0])){
      return i;
    }
  }
  return DEQUE_SIZE;
}

int World::confFRP_RF() const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).FRP_RF[0])){
      return i;
    }
  }
  return DEQUE_SIZE;
}

int World::confFRP_LC() const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).FRP_LC[0])){
      return i;
    }
  }
  return DEQUE_SIZE;
}

int World::confFRP_LF() const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).FRP_LF[0])){
      return i;
    }
  }
  return DEQUE_SIZE;
}

int World::confGYR() const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).GYR[0])){
      return i;
    }
  }
  return DEQUE_SIZE;
}

int World::confACC() const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).ACC[0])){
      return i;
    }
  }
  return DEQUE_SIZE;
}

int World::confMYPOS() const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).MYPOS[0])){
      return i;
    }
  }
  return DEQUE_SIZE;
}

int World::confBALLPOS() const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).BALLPOS[0])){
      return i;
    }
  }
  return DEQUE_SIZE;
}

int World::confFRIEND(int unum) const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).FRIEND[unum][0])){
      return i;
    }
  }
  return DEQUE_SIZE;
}

int World::confENEMY(int unum) const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).ENEMY[unum][0])){
      return i;
    }
  }
  return DEQUE_SIZE;
}

int World::confXY() const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).XY[0])){
      return i;
    }
  }
  return DEQUE_SIZE;
}

int World::confBXY() const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).BXY[0])){
      return i;
    }
  }
  return DEQUE_SIZE;
}

int World::confABSANGLE() const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).ABSANGLE)){
      return i;
    }
  }
  return DEQUE_SIZE;
}

int World::confBANGLE() const{
  int SIZE = deqPerception.size();
  for(int i = 0; i<SIZE; i++){
    if(!isnan((*(deqPerception[SIZE-i-1])).BANGLE)){
      return i;
    }
  }
  return DEQUE_SIZE;
}

///////////////////////////////////////////////////////
// World::set** and get**
//   setter and getter for World's private parameter
///////////////////////////////////////////////////////


void World::setTeamname(std::string name){
  teamname = name;
}

void World::setUnum(int num){
  unum = num;
}

void World::Perception::setPlaymode(std::string mode, World& world){
  world.playmode = mode;
}

void World::setIsMatch(bool which){
  isMatch = which;
}

std::string World::getTeamname() const{
  return teamname;
}


int World::getUnum() const{
  return unum;
}

std::string World::getPlaymode() const{
  return playmode;
}

bool World::getIsMatch() const{
  return isMatch;
}

double World::getGoalLength() const{
  return goal_length;
}

double World::getFieldLengthX() const{
  return field_length_x;
}

double World::getFieldLengthY() const{
  return field_length_y;
}

bool World::isFalling() {
  const int TH = 10;
  double ACC_Sum[2];
  ACC_Sum[0] = getACC_Sum(0, TH);
  ACC_Sum[1] = getACC_Sum(1, TH);

  if((fabs(ACC_Sum[1]) > 9.0 * TH) && (fabs(ACC_Sum[1]) < 15.0 *TH)){
    // std::cout << "utsubuse or aomuke!" << std::endl;
    return true;
  }
  if((fabs(ACC_Sum[0]) > 9.0 * TH) && (fabs(ACC_Sum[0]) < 15.0 *TH)){
    std::cout << "yokomuki!" << std::endl;
    return true;
  }
  return false;
}
