#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <map>
#include <deque>

#include "util.hpp"

/*
  World class hold sensor data.
  parse string from server, and hold included data(ex.object seen, gyro sensor).
 */

class World{
 public:

  World();
  ~World();


  // update and dump World data
  void update(const std::string& msg);
  void dump  ();


  // getter for Perception parameters
  double getAngle(std::string jointname) const;

  double getMGL(int index) const;
  double getMGR(int index) const;
  double getEGL(int index) const;
  double getEGR(int index) const;
  double getMFL(int index) const;
  double getMFR(int index) const;
  double getEFL(int index) const;
  double getEFR(int index) const;
  double getBAL(int index) const;

  double getFRP_RC  (int index) const;
  double getFRP_RF  (int index) const;
  double getFRP_LC  (int index) const;
  double getFRP_LF  (int index) const;
  double getGYR     (int index) const;
  double getACC     (int index) const;
  double getMYPOS   (int index) const;
  double getBALLPOS (int index) const;
  double getFRIEND  (int unum, int index) const;
  double getENEMY   (int unum, int index) const;

  double getXY      (int index) const;
  double getBXY     (int index) const;
  double getABSANGLE() const;
  double getBANGLE  () const;

  // getter for sum of parameter
  double getACC_Sum(int index, int num) const;

  // check confidence(how old the memories are)
  int confMGL     () const;
  int confMGR     () const;
  int confEGL     () const;
  int confEGR     () const;
  int confMFL     () const;
  int confMFR     () const;
  int confEFL     () const;
  int confEFR     () const;
  int confBAL     () const;
  int confFRP_RC  () const;
  int confFRP_RF  () const;
  int confFRP_LC  () const;
  int confFRP_LF  () const;
  int confGYR     () const;
  int confACC     () const;
  int confMYPOS   () const;
  int confBALLPOS () const;
  int confFRIEND  (int unum) const;
  int confENEMY   (int unum) const;

  int confXY      () const;
  int confBXY     () const;
  int confABSANGLE() const;
  int confBANGLE  () const;


  // access method for World private parameters
  void        setUnum    (int num);
  void        setIsMatch (bool which);
  void        setTeamname(std::string name);
  void        setPlaymode(std::string mode);

  int         getUnum    () const;
  bool        getIsMatch () const;
  std::string getTeamname() const;
  std::string getPlaymode() const;

  double      getGoalLength  () const;
  double      getFieldLengthX() const;
  double      getFieldLengthY() const;

 private:

  static const double goal_length    =  2.1;
  static const double field_length_x = 21.0;
  static const double field_length_y = 14.0;


  int         unum;
  std::string teamname;
  std::string playmode;
  bool        isMatch;
  enum Side   side;


  typedef std::map<std::string, jointID> tempJointMap;
  typedef std::map<std::string, double > tempJointValue;
  typedef std::map<std::string, seenID > tempSeenMap;


  // this class contains one scene data got from perceptor
  class Perception{
  public:
    Perception(const std::string& msg, World& world);
    ~Perception();


    tempJointMap   jointMap;
    tempJointValue jointValue;
    tempSeenMap    seenMap;

    double BAL[3];
    double G1L[3], G2L[3], G1R[3], G2R[3];
    double F1L[3], F2L[3], F1R[3], F2R[3];

    double FRP_RC[3], FRP_RF[3], FRP_LC[3], FRP_LF[3];
    double GYR[3], ACC[3];
    double MYPOS[3], BALLPOS[3];
    double FRIEND[11][4], ENEMY[11][4];

    double XY[2], BXY[2];
    double ABSANGLE, BANGLE;


    // setter and parser, used in constructor, set parameters
    void   setJointMap();
    void   setSeenMap();

    void   parseGamestate (std::string msg, World& world);
    double parseJoint     (std::string msg, std::string id);
    void   parseJointValue(std::string msg);
    void   parseSeen      (std::string msg, std::string id);
    void   parsePlayer    (std::string msg, std::string id,
			   double player[][4], World& world);
    void   parseFRP       (std::string msg);
    void   parseGYR       (std::string msg);
    void   parseACC       (std::string msg);
    void   parseMYPOS     (std::string msg);
    void   parseBALLPOS   (std::string msg);
    void   parseSide      (std::string msg, World& world);
    void   parseUnum      (std::string msg, World& world);
    void   getPlayer      (std::string msg, std::string id, World& world);

    void   setPlaymode(std::string mode, World& world);

    // calcurate using Perception parameters
    void calcuratePerception(World& world);

    // getter, for checking confidence
    int confMGL(World& world) const;
    int confMGR(World& world) const;
    int confEGL(World& world) const;
    int confEGR(World& world) const;
    int confMFL(World& world) const;
    int confMFR(World& world) const;
    int confEFL(World& world) const;
    int confEFR(World& world) const;
    int confBAL(World& world) const;


  };
  std::deque<Perception*> deqPerception;
  static const int DEQUE_SIZE = 300;


};

#endif
