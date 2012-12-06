#include "sequencemovement.hpp"

SequenceMovement::SequenceMovement(std::string _name){
  name = _name;
  timeStamp = 0;
  
  setNewSequence(name);
}


SequenceMovement::~SequenceMovement(){};

std::string SequenceMovement::getNextAngle(World& w){

//    std::cout << "SequenceMovement::getNextAngle" << std::endl;

    resetAngleMap();

    /*
      for(poses[0] -> poses[num]){ // actually, "for" cannot use!
        set poses[timeStamp]
        if(all set() return false(it means, any joints are moved)){
          timeStamp++;
          // set poses[new timeStamp] ?  // be careful not to access poses[more_than_10]

        }
      }

      if(timeStamp >= seq.num){
        // action finished
        act.setFinished(true);
        timeStamp = 0;
      }

      */

    if(timeStamp < seq.getNum()){
        // check seq.poses[timeStamp]
        Pose tempPose = seq.getPose(timeStamp);
        double *tempTarget = tempPose.getTarget();
        double tempGain = tempPose.getGain();
//        std::cout << "SeqenceMovement::getNextAngle : seq.num = " << seq.getNum() << std::endl;
//        std::cout << "SeqenceMovement::getNextAngle : timeStamp = " << timeStamp << std::endl;
        // do that pose
        // check return value of set()


        /*
        if( // all joint return false(not need to move joint)
                !set(w, hj1, tempTarget[0], tempGain) ||
                !set(w, hj2, tempTarget[1], tempGain) ||
                !set(w, laj1, tempTarget[2], tempGain) ||
                !set(w, raj1, tempTarget[3], tempGain) ||
                !set(w, laj2, tempTarget[4], tempGain) ||
                !set(w, raj2, tempTarget[5], tempGain) ||
                !set(w, laj3, tempTarget[6], tempGain) ||
                !set(w, raj3, tempTarget[7], tempGain) ||
                !set(w, laj4, tempTarget[8], tempGain) ||
                !set(w, raj4, tempTarget[9], tempGain) ||
                !set(w, llj1, tempTarget[10], tempGain) ||
                !set(w, rlj1, tempTarget[11], tempGain) ||
                !set(w, llj2, tempTarget[12], tempGain) ||
                !set(w, rlj2, tempTarget[13], tempGain) ||
                !set(w, llj3, tempTarget[14], tempGain) ||
                !set(w, rlj3, tempTarget[15], tempGain) ||
                !set(w, llj4, tempTarget[16], tempGain) ||
                !set(w, rlj4, tempTarget[17], tempGain) ||
                !set(w, llj5, tempTarget[18], tempGain) ||
                !set(w, rlj5, tempTarget[19], tempGain) ||
                !set(w, llj6, tempTarget[20], tempGain) ||
                !set(w, rlj6, tempTarget[21], tempGain)
                ){
            }
        */

        bool jointMove[22];
        for(int i=0; i<22; i++){
            jointMove[i] = false;
        }

        jointMove[0] = set(w, hj1, tempTarget[0], tempGain);
        jointMove[1] = set(w, hj2, tempTarget[1], tempGain);
        jointMove[2] = set(w, laj1, tempTarget[2], tempGain);
        jointMove[3] = set(w, raj1, tempTarget[3], tempGain);
        jointMove[4] = set(w, laj2, tempTarget[4], tempGain);
        jointMove[5] = set(w, raj2, tempTarget[5], tempGain);
        jointMove[6] = set(w, laj3, tempTarget[6], tempGain);
        jointMove[7] = set(w, raj3, tempTarget[7], tempGain);
        jointMove[8] = set(w, laj4, tempTarget[8], tempGain);
        jointMove[9] = set(w, raj4, tempTarget[9], tempGain);
        jointMove[10] = set(w, llj1, tempTarget[10], tempGain);
        jointMove[11] = set(w, rlj1, tempTarget[11], tempGain);
        jointMove[12] = set(w, llj2, tempTarget[12], tempGain);
        jointMove[13] = set(w, rlj2, tempTarget[13], tempGain);
        jointMove[14] = set(w, llj3, tempTarget[14], tempGain);
        jointMove[15] = set(w, rlj3, tempTarget[15], tempGain);
        jointMove[16] = set(w, llj4, tempTarget[16], tempGain);
        jointMove[17] = set(w, rlj4, tempTarget[17], tempGain);
        jointMove[18] = set(w, llj5, tempTarget[18], tempGain);
        jointMove[19] = set(w, rlj5, tempTarget[19], tempGain);
        jointMove[20] = set(w, llj6, tempTarget[20], tempGain);
        jointMove[21] = set(w, rlj6, tempTarget[21], tempGain);

        bool allJointNotMove = true;
        for(int i=0; i<22; i++){
            if(jointMove[i] == true){
                allJointNotMove = false;
            }
        }

        if(allJointNotMove == true){
            timeStamp++;
        }
    }

    if(timeStamp >= seq.getNum()){ // after timeStamp (may) is added, robot want to check if action is finished in same cycle.
        // all action finished. reset
		finish_flag = true;
        timeStamp = 0;
    }
    // std::cout << "timeStamp: " << timeStamp << std::endl;

//    std::cout << "angleToString() : " << angleToString() << std::endl;
    return angleToString();
}

void SequenceMovement::setNewSequence(Sequence newSeq){
    seq = newSeq;
}

void SequenceMovement::setNewSequence(std::string name){
  if(name == "LAROUND"){

    Pose laround1;
    laround1.setTarget(hj1, -120);
    laround1.setTarget(hj2, -30);
    laround1.setTarget(laj1, -90);
    laround1.setTarget(raj1, -90);
    laround1.setTarget(laj3, -90);
    laround1.setTarget(raj3, 90);
    laround1.setTarget(laj4, -90);
    laround1.setTarget(raj4, 90);
    laround1.setGain(0.2);
    Pose laround2;
    laround2.setTarget(hj1, 120);
    laround2.setTarget(hj2, -30);
    laround2.setTarget(laj1, -90);
    laround2.setTarget(raj1, -90);
    laround2.setTarget(laj3, -90);
    laround2.setTarget(raj3, 90);
    laround2.setTarget(laj4, -90);
    laround2.setTarget(raj4, 90);
    laround2.setGain(0.2);
    Pose laround3;
    laround3.setTarget(hj1, 0);
    laround3.setTarget(hj2, -30);
    laround3.setTarget(laj1, -90);
    laround3.setTarget(raj1, -90);
    laround3.setTarget(laj3, -90);
    laround3.setTarget(raj3, 90);
    laround3.setTarget(laj4, -90);
    laround3.setTarget(raj4, 90);
    laround3.setGain(0.2);

    Sequence laround;
    //  laround.addPose(laround0);
    laround.addPose(laround1);
    laround.addPose(laround2);
    laround.addPose(laround3);

    setNewSequence(laround); // <- over write member
    
  } else if(name == "DUMMY"){
    Pose dummy1;
    dummy1.setTarget(raj1, -100.0);
    dummy1.setTarget(laj1, -100.0);
    dummy1.setTarget(raj2, 0.0);
    dummy1.setTarget(laj2, 0.0);
    dummy1.setTarget(raj3, 90.0);
    dummy1.setTarget(laj3, -90.0);
    dummy1.setTarget(raj4, 90.0);
    dummy1.setTarget(laj4, -90.0);
    
    //set gain?
    dummy1.setTarget(rlj1, 0.0);
    dummy1.setTarget(llj1, 0.0);
    dummy1.setTarget(rlj2, 0.0);
    dummy1.setTarget(llj2, 0.0);
    dummy1.setTarget(rlj3, 0.0);
    dummy1.setTarget(llj3, 0.0);
    dummy1.setTarget(rlj4, 0.0);
    dummy1.setTarget(llj4, 0.0);
    dummy1.setTarget(rlj5, 0.0);
    dummy1.setTarget(llj5, 0.0);
    dummy1.setTarget(rlj6, 0.0);
    dummy1.setTarget(llj6, 0.0);
    
    /*
      set(w, rlj1, 0.0, 0.01);
      set(w, llj1, 0.0, 0.01);
      set(w, rlj2, 0.0, 0.05);
      set(w, llj2, 0.0, 0.05);
      set(w, rlj3, 0.0, 0.02);
      set(w, llj3, 0.0, 0.02);
      set(w, rlj4, 0.0, 0.02);
      set(w, llj4, 0.0, 0.02);
      set(w, rlj5, 0.0, 0.02);
      set(w, llj5, 0.0,     dummy.setTarget(rlj1, 0.0);
    dummy.setTarget(llj1, 0.0);
    dummy.setTarget(rlj2, 0.0);
    dummy.setTarget(llj2, 0.0);0.02);
      set(w, rlj6, 0.0, 0.05);
      set(w, llj6, 0.0, 0.05);
     */
    
    Sequence dummy;
    dummy.addPose(dummy1);
    
    setNewSequence(dummy);
    
  } else if(name == "FLEFT"){
      /*
      Pose fleft0;
      fleft0.setTarget(laj1, -90);
      fleft0.setTarget(raj1, -90);
      fleft0.setTarget(laj3, -90);
      fleft0.setTarget(raj3, 90);
      fleft0.setTarget(laj4, -90);
      fleft0.setTarget(raj4, 90);
      */
      Pose fleft1;
      fleft1.setTarget(laj1, 90);
      fleft1.setTarget(raj1, -90);
      fleft1.setTarget(laj3, -90);
      fleft1.setTarget(raj3, 90);
      fleft1.setTarget(raj4, 90);
      fleft1.setTarget(llj2, -10);
      fleft1.setTarget(rlj2, -10);
      fleft1.setTarget(llj6, 25);
      fleft1.setTarget(rlj6, 45);
      Pose fleft2;
      fleft2.setTarget(laj1, -90);
      fleft2.setTarget(raj1, -90);
      fleft2.setTarget(laj3, -90);
      fleft2.setTarget(raj3, 90);
      fleft2.setTarget(llj2, -10);
      fleft2.setTarget(rlj2, -10);
      fleft2.setTarget(llj6, 25);
      fleft2.setTarget(rlj6, 45);
      fleft2.setGain(0.5);
      Sequence fleft;
      //    fleft.addPose(fleft0);
      fleft.addPose(fleft1);
      fleft.addPose(fleft2);
  
      setNewSequence(fleft);
    //    ~~~;
  }else if(name == "FRIGHT"){
    /*
    Pose fright0;
    fright0.setTarget(laj1, -90);
    fright0.setTarget(raj1, -90);
    fright0.setTarget(laj3, -90);
    fright0.setTarget(raj3, 90);
    fright0.setTarget(laj4, -90);
    fright0.setTarget(raj4, 90);
    */
    Pose fright1;
    fright1.setTarget(laj1, -90);
    fright1.setTarget(raj1, 90);
    fright1.setTarget(laj3, -90);
    fright1.setTarget(raj3, 90);
    fright1.setTarget(laj4, -90);
    fright1.setTarget(llj2, 10);
    fright1.setTarget(rlj2, 10);
    fright1.setTarget(llj6, -45);
    fright1.setTarget(rlj6, -25);
    Pose fright2;
    fright2.setTarget(laj1, -90);
    fright2.setTarget(raj1, -90);
    fright2.setTarget(laj3, -90);
    fright2.setTarget(raj3, 90);
    fright2.setTarget(laj4, -90);
    fright2.setTarget(llj2, 10);
    fright2.setTarget(rlj2, 10);
    fright2.setTarget(llj6, -45);
    fright2.setTarget(rlj6, -25);
    fright2.setGain(0.5);
    Sequence fright;
    //    fright.addPose(fright0);
    fright.addPose(fright1);
    fright.addPose(fright2);

    setNewSequence(fright);
  } else {
      std::cout << "BAD argument in: new SequenceMovement(BAD)" << std::endl;
  }

}
