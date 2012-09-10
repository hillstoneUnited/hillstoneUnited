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


  // update and dump World data
  void update(const std::string& msg);
  void dump  ();


  // getter for Perception parameters
  double  getAngle(std::string jointname) const;

  double* getMGL() const;
  double* getMGR() const;
  double* getEGL() const;
  double* getEGR() const;
  double* getMFL() const;
  double* getMFR() const;
  double* getEFL() const;
  double* getEFR() const;
  double* getBAL() const;

  double* getFRP_RC  () const;
  double* getFRP_RF  () const;
  double* getFRP_LC  () const;
  double* getFRP_LF  () const;
  double* getGYR     () const;
  double* getACC     () const;
  double* getMYPOS   () const;
  double* getBALLPOS () const;
  double* getFRIEND  (int unum) const;
  double* getENEMY   (int unum) const;
 
  double* getXY      () const;
  double* getBXY     () const;
  double  getABSANGLE() const;
  double  getBANGLE  () const;

  // getter for sum of parameter
  double* getACC_Sum(int num) const;

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
