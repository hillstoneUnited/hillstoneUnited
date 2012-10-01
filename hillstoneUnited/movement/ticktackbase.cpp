//
//  ticktackbase.cpp
//  
//
//  Created by Yoshihiro Nagano on 2012/09/12.
//
//

#include "ticktackbase.h"

void TicktackBase::renew(int& ts){
  t = ts * M_PI / 180.0;
  
  // Init
  m_rlj1 = 0.0; m_rlj2 = 0.0; m_rlj3 = 0.0;
  m_rlj4 = 0.0; m_rlj5 = 0.0; m_rlj6 = 0.0;

  m_llj1 = 0.0; m_llj2 = 0.0; m_llj3 = 0.0;
  m_llj4 = 0.0; m_llj5 = 0.0; m_llj6 = 0.0;

  lj26 = 0.0;
  
  m_hj1 = 0.0; m_hj2 = 0.0; headSpeed = 0.0;
  
  L = 0.0; S = 0.0; cycle = 0.0;
  drive = true;
  max_H = 7;

  wX = 0.0; wY = 0.0; r = 0.0;
  Gain = 0.0; Threshold = 0.0;

  H = 1; dummy_H = 1; max_H = 7;
  start = false;

  current = -1;
}

void TicktackBase::setAngle(World& w){
  // Gravity
  lj26 = wX * sin(cycle * t);
  // Spring
  L = (1.0 - cos(cycle*2.0 * t)) * r;
  if(lj26 > 0.0){
      m_rlj3 += L;
      m_rlj4 += L * (-2.0);
      m_rlj5 += L;
  }else{
      m_llj3 += L;
      m_llj4 += L * (-2.0);
      m_llj5 += L;
  }
  if(m_rlj4 >= 0.0) m_rlj4 = 0.0;
  if(m_llj4 >= 0.0) m_llj4 = 0.0;
  
  // Set angle
  set(w, rlj3, m_rlj3 * 180.0/M_PI);
  set(w, rlj4, m_rlj4 * 180.0/M_PI);
  set(w, rlj5, m_rlj5 * 180.0/M_PI);
  set(w, llj3, m_llj3 * 180.0/M_PI);
  set(w, llj4, m_llj4 * 180.0/M_PI);
  set(w, llj5, m_llj5 * 180.0/M_PI);
  // Move gravity point
  set(w, rlj2, (-lj26 + m_rlj2) * 180.0/M_PI);
  set(w, rlj6, ( lj26 + m_rlj6) * 180.0/M_PI);
  set(w, llj2, (-lj26 + m_llj2) * 180.0/M_PI);
  set(w, llj6, ( lj26 + m_llj6) * 180.0/M_PI);
  // Turn angle
  set(w, rlj1, m_rlj1 * 180.0/M_PI);
  set(w, llj1, m_llj1 * 180.0/M_PI);

  //  t += M_PI/180.0; <- added in nextAngle()
  if(t >= (double)dummy_H * 2.0*M_PI/cycle){
      dummy_H++;
      if(drive && H < max_H) H++;
      if(!drive && H > 1) H--;
  } 
}
