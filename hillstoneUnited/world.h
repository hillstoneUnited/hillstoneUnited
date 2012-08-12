#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <map>
#include <deque>

#include "util.h"

/*
  World class hold sensor data.
  parse string from server, and hold included data(ex.object seen, gyro sensor).
 */
class World{
 public:
  World();
  ~World();

  // update and dump world
  void update(const std::string& msg);
  void dump();

  // to get an angle value in latest joint data
  double getAngle(std::string jointname);

  // access method for private parameters
  void setUnum(int num);
  int getUnum();
  void setTeamname(std::string name);
  std::string getTeamname();
  //  void setPlaymode(std::string mode);
  std::string getPlaymode();
  void setIsMatch(bool which);
  bool getIsMatch();

 private:
  static const double goal_length = 2.1;
  static const double field_length_x = 21.0;
  static const double fiele_length_y = 14.0;

  int unum;
  std::string teamname;
  std::string playmode;
  bool isMatch; // during match or not
  enum Side side;


  typedef std::map<std::string, jointID> tempJointMap;
  typedef std::map<std::string, double> tempJointValue;
  typedef std::map<std::string, seenID> tempSeenMap;

  // this structure contains one scene data got from perceptor
  class Perception{
  public:
    Perception(const std::string& msg);
    ~Perception();

    tempJointMap jointMap;
    tempJointValue jointValue;
    tempSeenMap seenMap;

    double BAL[3];
    double G1L[3], G2L[3], G1R[3], G2R[3];
    double F1L[3], F2L[3], F1R[3], F2R[3];

    double FRP_RC[3], FRP_RF[3], FRP_LC[3], FRP_LF[3];
    double GYR[3], ACC[3];
    double MYPOS[3], BALLPOS[3];
    double FRIEND[11][4], ENEMY[11][4];

    double XY[2], BXY[2];
    double ABSANGLE, BANGLE;

    // setter
    void setJointMap();
    void setSeenMap();

    void parseGamestate(std::string msg);
    double parseJoint(std::string msg, std::string id);
    void parseJointValue(std::string msg);
    void parseSeen(std::string msg, std::string id);
    void parsePlayer(std::string msg, std::string id, double player[][4]);
    void parseFRP(std::string msg);
    void parseGYR(std::string msg);
    void parseACC(std::string msg);
    void parseMYPOS(std::string msg);
    void parseBALLPOS(std::string msg);
    void parseSide(std::string msg);
    void parseUnum(std::string msg);
    void getPlayer(std::string msg, std::string id);

    void setPlaymode(std::string mode);

    // getter
    double* getMGL(Side side);
    double* getMGR(Side side);
    double* getEGL(Side side);
    double* getEGR(Side side);
    double* getMFL(Side side);
    double* getMFR(Side side);
    double* getEFL(Side side);
    double* getEFR(Side side);
    double* getBAL();
  };
  std::deque<Perception*> deqPerception;

};

#endif
