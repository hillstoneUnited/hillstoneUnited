//
//  ticktackbase.cpp
//  
//
//  Created by Yoshihiro Nagano on 2012/09/12.
//
//

#include "ticktackbase.hpp"

int TicktackBase::ts = 0;

TicktackBase::TicktackBase(std::string _name){
    t = ts * M_PI / 180.0;
    name = _name;
    
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
      m_llj4 += L * (-2.0);  r=0.997143;wX=0.012308;wY=0.2;Threshold=0.0;Gain=0.0;// cycle 30
      H = 0;
      cycle = 30.0;
      L = (1.0 - cos(cycle * t)) * wY;
      m_llj2 += L;
      m_llj6 -= L;
      m_rlj2 -= L;
      m_rlj6 += L;  
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

std::string TicktackBase::getNextAngle(World& w){
    /** Init **/
    resetAngleMap();
    
    m_rlj1 = 0.0; m_rlj2 = 0.0; m_rlj3 = 0.0;
    m_rlj4 = 0.0; m_rlj5 = 0.0; m_rlj6 = 0.0;
  
    m_llj1 = 0.0; m_llj2 = 0.0; m_llj3 = 0.0;
    m_llj4 = 0.0; m_llj5 = 0.0; m_llj6 = 0.0;
    
    /** calculation part **/
    if(name=="FORWARD"){  
        r=0.905714;wX=0.314335;wY=1.819048;Threshold=2.381232;Gain=1.383409;
          // cycle 20 -> upright
        cycle = 20.0;
        S = wY * 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
        L = S * cos(cycle * t);
        m_rlj3 -= L;
        m_rlj5 += L;
        m_llj3 += L;
        m_llj5 -= L;
        // std::cout << "FORWARD" << std::endl;
        
    }else if(name=="SLOW_FORWARD"){
        r=0.771261;wX=0.072772;wY=0.998240;Threshold=3.560117;Gain=1.294408;
        // cycle 20
        max_H = 3;
        cycle = 20.0;
        S = wY * 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
        L = S * cos(cycle * t);
        m_rlj3 -= L;
        m_rlj5 += L;
        m_llj3 += L;
        m_llj5 -= L;
        
    }else if(name=="DRIBBLE"){
        r=0.586667;wX=0.0131187;wY=0.666667;Threshold=1.175953;Gain=1.286168;
        //max_H = 3;
        cycle = 20.0;
        S = wY * 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
        L = S * cos(cycle * t);
        m_rlj3 -= L;
        m_rlj5 += L;
        m_llj3 += L;
        m_llj5 -= L;
        
    }else if(name=="R_DRIBBLE"){
        r=0.771261;wX=0.072772;wY=0.998240;Threshold=3.560117;Gain=1.294408;
        // cycle 20
        //max_H = 3;
        cycle = 20.0;
        S = 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
        L = S * cos(cycle * t);
        m_llj3 += L * wY;
        m_llj5 -= L * wY;
        m_rlj3 -= L * wY * 0.1;
        m_rlj5 += L * wY * 0.1;
        
    }else if(name=="L_DRIBBLE"){
        r=0.771261;wX=0.072772;wY=0.998240;Threshold=3.560117;Gain=1.294408;
        // cycle 20
        //max_H = 3;
        cycle = 20.0;
        S = 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
        L = S * cos(cycle * t);
        m_rlj3 -= L * wY;
        m_rlj5 += L * wY;
        m_llj3 += L * wY * 0.1;
        m_llj5 -= L * wY * 0.1;
        
    }else if(name=="R_DRIBBLE_SHARP"){
        r=0.586667;wX=0.013187;wY=0.666667;Threshold=1.175953;Gain=1.286168;
        //28,9 --> OK!
        //max_H = 3;
        cycle = 20.0;
        S = 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
        L = S * cos(cycle * t);
        m_llj3 += L * wY;
        m_llj5 -= L * wY;
        m_rlj3 -= L * wY * 0.1;
        m_rlj5 += L * wY * 0.1; 
        
    }else if(name=="L_DRIBBLE_SHARP"){
        r=0.586667;wX=0.013187;wY=0.666667;Threshold=1.175953;Gain=1.286168;
        //max_H = 3;
        cycle = 20.0;
        S = 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
        L = S * cos(cycle * t);
        m_rlj3 -= L * wY;
        m_rlj5 += L * wY;
        m_llj3 += L * wY * 0.1;
        m_llj5 -= L * wY * 0.1;
        
    }else if(name=="BACK"){
        r=0.771261;wX=0.072772;wY=0.998240;Threshold=3.560117;Gain=1.294408;
        // cycle 20
        cycle = 20.0;
        S = wY * 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
        L = S * cos(cycle * t);
        m_rlj3 += L;
        m_rlj5 -= L;
        m_llj3 -= L;
        m_llj5 += L;
        
    }else if(name=="SLOW_BACK"){
        r=0.771261;wX=0.072772;wY=0.998240;Threshold=3.560117;Gain=1.294408;
        // cycle 20
        max_H = 2;
        cycle = 20.0;
        S = wY * 1.0 / (1.0 + exp((-1.0)*(double)H*Gain + Threshold));
        L = S * cos(cycle * t);
        m_rlj3 += L;
        m_rlj5 -= L;
        m_llj3 -= L;
        m_llj5 += L;
        
    }else if(name=="TLEFT"){
        r=0.997143;wX=0.012308;wY=0.25;Threshold=0.0;Gain=0.0;// cycle 30
        H = 0;
        cycle = 30.0;
        L = (1.0 - cos(cycle * t - M_PI)) * wY;
        // Set angle
        m_rlj1 = -L;
        m_llj1 = -L;
        // std::cout << "TLEFT" << std::endl;
        
    }else if(name=="TRIGHT"){
        r=0.997143;wX=0.012308;wY=0.25;Threshold=0.0;Gain=0.0;// cycle 30
        H = 0;
        cycle = 30.0;
        // Right direction
        L = (1.0 - cos(cycle * t)) * wY;
        // Set angle
        m_rlj1 = -L;
        m_llj1 = -L;
        // std::cout << "TRIGHT" << std::endl;
        
    }else if(name=="TLEFT_IN"){
        r=0.727619;wX=0.034286;wY=0.075;Threshold=0.0;Gain=0.35;// cycle 30
        H = 0;
        cycle = 30.0;
        L = (1.0 - cos(cycle * t - M_PI)) * wY;
        m_rlj2 -= L;
        m_rlj6 += L;
        m_llj2 += L;
        m_llj6 -= L;
        L = Gain * cos(cycle * t - M_PI);
        m_rlj3 -= L;
        m_rlj5 += L;
        m_llj3 -= L;
        m_llj5 += L;
        
    }else if(name=="TRIGHT_IN"){
        r=0.727619;wX=0.034286;wY=0.075;Threshold=0.0;Gain=0.35;// cycle 30
        H = 0;
        cycle = 30.0;
        L = (1.0 - cos(cycle * t)) * wY;
        m_llj2 += L;
        m_llj6 -= L;
        m_rlj2 -= L;
        m_rlj6 += L;
        L = Gain * cos(cycle * t);
        m_rlj3 -= L;
        m_rlj5 += L;
        m_llj3 -= L;
        m_llj5 += L;
        
    }else if(name=="SLEFT"){
        r=0.997143;wX=0.012308;wY=0.2;Threshold=0.0;Gain=0.0;// cycle 30
        H = 0;
        cycle = 30.0;
        L = (1.0 - cos(cycle * t - M_PI)) * wY;
        m_rlj2 -= L;
        m_rlj6 += L;
        m_llj2 += L;
        m_llj6 -= L;
        
    }else if(name=="SRIGHT"){
        r=0.997143;wX=0.012308;wY=0.2;Threshold=0.0;Gain=0.0;// cycle 30
        H = 0;
        cycle = 30.0;
        L = (1.0 - cos(cycle * t)) * wY;
        m_llj2 += L;
        m_llj6 -= L;
        m_rlj2 -= L;
        m_rlj6 += L;
        
    }else{
        std::cout << "BAD argument in: new TicktackBase(BAD)" << std::endl;
    }
    
    setAngle(w);
    
    /** step count **/
    if(ts > cycle*100){
        finish_flag = true;
        // ts = 0;
    }
    ts++;
    t = ts * M_PI / 180.0;
    std::cout << "t:" << t << std::endl;
    return angleToString();
}
