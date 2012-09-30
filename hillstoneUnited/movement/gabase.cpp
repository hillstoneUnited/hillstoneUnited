#include "gabase.h"

void GABase::renew(int& ts){
  t = ts * M_PI / 180.0;
  
  // Init
  for(int i=0; i<17; i++){
    for(int j=0; j<3; j++){
      ga_param[i][j] = 0;
    }
  }
  ga_W = 0;
  ga_I = 0;
  ga_Gain = 0;

  m_hj1 = 0.0; m_hj2 = 0.0;

  m_raj1 = 0.0; m_raj2 = 0.0; m_raj3 = 0.0; m_raj4 = 0.0;

  m_laj1 = 0.0; m_laj2 = 0.0; m_laj3 = 0.0; m_laj4 = 0.0;

  m_rlj1 = 0.0; m_rlj2 = 0.0; m_rlj3 = 0.0;
  m_rlj4 = 0.0; m_rlj5 = 0.0; m_rlj6 = 0.0;

  m_llj1 = 0.0; m_llj2 = 0.0; m_llj3 = 0.0;
  m_llj4 = 0.0; m_llj5 = 0.0; m_llj6 = 0.0;

}

void GABase::updateAngle(){
  //Head
  m_hj1 = ga_param[0][0]*sin((ga_W*t)+M_PI/180*ga_param[0][1]);
  m_hj2 = ga_param[1][0]*sin((ga_W*t)+M_PI/180*ga_param[1][1]);
  //Right
  //Arms
  m_raj1 = ga_param[2][0]*sin((ga_W*t)+M_PI/180*ga_param[2][1]);
  m_raj2 = ga_param[3][0]*sin((ga_W*t)+M_PI/180*ga_param[3][1]);
  m_raj3 = ga_param[4][0]*sin((ga_W*t)+M_PI/180*ga_param[4][1]);
  m_raj4 = ga_param[5][0]*sin((ga_W*t)+M_PI/180*ga_param[5][1]);
  //Legs
  m_rlj1 = ga_param[6][0]*sin((ga_W*t)+M_PI/180*ga_param[6][1]);
  m_rlj2 = ga_param[7][0]*sin((ga_W*t)+M_PI/180*ga_param[7][1]);
  m_rlj3 = ga_param[8][0]*sin((ga_W*t)+M_PI/180*ga_param[8][1]);
  m_rlj4 = ga_param[9][0]*sin((ga_W*t)+M_PI/180*ga_param[9][1]);
  m_rlj5 = ga_param[10][0]*sin((ga_W*t)+M_PI/180*ga_param[10][1]);
  m_rlj6 = ga_param[11][0]*sin((ga_W*t)+M_PI/180*ga_param[11][1]);
  //Left
  //Arms
  m_laj1 = ga_param[2][0]*sin((ga_W*t)+M_PI/180*ga_param[2][1]+M_PI);
  m_laj2 = ga_param[3][0]*sin((ga_W*t)+M_PI/180*ga_param[3][1]+M_PI);
  m_laj3 = ga_param[4][0]*sin((ga_W*t)+M_PI/180*ga_param[4][1]+M_PI);
  m_laj4 = ga_param[5][0]*sin((ga_W*t)+M_PI/180*ga_param[5][1]+M_PI);
  //Legs
  m_llj1 = ga_param[6][0]*sin((ga_W*t)+M_PI/180*ga_param[6][1]+M_PI);
  m_llj2 = ga_param[12][0]*sin((ga_W*t)+M_PI/180*ga_param[12][1]+M_PI);
  m_llj3 = ga_param[13][0]*sin((ga_W*t)+M_PI/180*ga_param[13][1]+M_PI);
  m_llj4 = ga_param[14][0]*sin((ga_W*t)+M_PI/180*ga_param[14][1]+M_PI);
  m_llj5 = ga_param[15][0]*sin((ga_W*t)+M_PI/180*ga_param[15][1]+M_PI);
  m_llj6 = ga_param[16][0]*sin((ga_W*t)+M_PI/180*ga_param[16][1]+M_PI);

  //  std::cout << "t : " << t << std::endl;
  if(t < ga_I){
    //    std::cout << "t < ga_I" << std::endl;
    //Head
    m_hj1 = m_hj1*t/ga_I;
    m_hj2 = m_hj2*t/ga_I;
    //Right
    //Arms
    m_raj1 = m_raj1*t/ga_I;
    m_raj2 = m_raj2*t/ga_I;
    m_raj3 = m_raj3*t/ga_I;
    m_raj4 = m_raj4*t/ga_I;
    //Legs
    m_rlj1 = m_rlj1*t/ga_I;
    m_rlj2 = m_rlj2*t/ga_I;
    m_rlj3 = m_rlj3*t/ga_I;
    m_rlj4 = m_rlj4*t/ga_I;
    m_rlj5 = m_rlj5*t/ga_I;
    m_rlj6 = m_rlj6*t/ga_I;
    //Left
    //Arms
    m_laj1 = m_laj1*t/ga_I;
    m_laj2 = m_laj2*t/ga_I;
    m_laj3 = m_laj3*t/ga_I;
    m_laj4 = m_laj4*t/ga_I;
    //Legs
    m_llj1 = m_llj1*t/ga_I;
    m_llj2 = m_llj2*t/ga_I;
    m_llj3 = m_llj3*t/ga_I;
    m_llj4 = m_llj4*t/ga_I;
    m_llj5 = m_llj5*t/ga_I;
    m_llj6 = m_llj6*t/ga_I;
  }

  //Head
  m_hj1 += ga_param[0][2];
  m_hj2 += ga_param[1][2];
  //Right
  //Arms
  m_raj1 += ga_param[2][2];
  m_raj2 += ga_param[3][2];
  m_raj3 += ga_param[4][2];
  m_raj4 += ga_param[5][2];
  //Legs
  m_rlj1 += ga_param[6][2];	
  m_rlj2 += ga_param[7][2];
  m_rlj3 += ga_param[8][2];
  m_rlj4 += ga_param[9][2];
  m_rlj5 += ga_param[10][2];
  m_rlj6 += ga_param[11][2];
  //Left
  //Arms
  m_laj1 += ga_param[2][2];
  m_laj2 += ga_param[3][2];
  m_laj3 -= ga_param[4][2];
  m_laj4 -= ga_param[5][2];
  //Legs
  m_llj1 += ga_param[6][2];
  m_llj2 += ga_param[12][2];
  m_llj3 += ga_param[13][2];
  m_llj4 += ga_param[14][2];
  m_llj5 += ga_param[15][2];
  m_llj6 += ga_param[16][2];

}

void GABase::setAngle(Action& act, World& w){
  /** Head **/
  set(w, hj1, m_hj1, ga_Gain);
  set(w, hj2, m_hj2, ga_Gain);

  /** Right **/
  //Arms
  set(w, raj1, m_raj1, ga_Gain);
  set(w, raj2, m_raj2, ga_Gain);
  set(w, raj3, m_raj3, ga_Gain);
  set(w, raj4, m_raj4, ga_Gain);
  //Legs
  set(w, rlj1, m_rlj1, ga_Gain);
  set(w, rlj2, m_rlj2, ga_Gain);
  set(w, rlj3, m_rlj3, ga_Gain);
  set(w, rlj4, m_rlj4, ga_Gain);
  set(w, rlj5, m_rlj5, ga_Gain);
  set(w, rlj6, m_rlj6, ga_Gain);

  /** Left **/
  //Arms
  set(w, laj1, m_laj1, ga_Gain);
  set(w, laj2, m_laj2, ga_Gain);
  set(w, laj3, m_laj3, ga_Gain);
  set(w, laj4, m_laj4, ga_Gain);
  //Legs
  set(w, llj1, m_llj1, ga_Gain);
  set(w, llj2, m_llj2, ga_Gain);
  set(w, llj3, m_llj3, ga_Gain);
  set(w, llj4, m_llj4, ga_Gain);
  set(w, llj5, m_llj5, ga_Gain);
  set(w, llj6, m_llj6, ga_Gain);
}
