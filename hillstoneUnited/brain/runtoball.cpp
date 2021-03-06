#include "runtoball.hpp"

// pos[2]
// pos[0]: zengo
// pos[1]: sayuu

RunToBall::RunToBall(World& w){
    finish_flag = false;
    
    for(int i=0; i<2; i++){
      ballpos[i] = w.getBXY_AVE(i);
      bal[i] = w.getBAL(i);
    }
    conf_ballpos = w.confBXY();
    conf_bal = w.confBAL();
    x = w.getXY_AVE(0);
    y = w.getXY_AVE(1);
    conf_XY = w.confXY();

    t_count = abs(15 * bal[1] / 360);

    elementList.push_back(new SequenceMovement("LAROUNDREADY"));
    updateFinishFlag(w);
}

void RunToBall::judgement(World& w){
    for(int i=0; i<2; i++){
      ballpos[i] = w.getBXY_AVE(i);
      bal[i] = w.getBAL(i);
    }
    conf_ballpos = w.confBXY();
    conf_bal = w.confBAL();
    x = w.getXY_AVE(0);
    y = w.getXY_AVE(1);
    conf_XY = w.confXY();

    t_count = abs(15 * bal[1] / 360);
    if(t_count == 0){
      t_count = 1;
    }

    judgeStandup(w);

    if (conf_ballpos == 300 || (ballpos[0] - x) == 0.0 || (ballpos[1] - y) == 0.0 || w.confABSANGLE() >= 200){
        elementList.push_back(new TicktackBase("TLEFT", 2));
        elementList.push_back(new SequenceMovement("LAROUNDREADY"));
    } else {

        if(bal[0] > 6){
            if(bal[1] > 20){
                elementList.push_back(new TicktackBase("TLEFT", t_count));
            } else if(bal[1] > -20){
                elementList.push_back(new SequenceMovement("READY"));
                //elementList.push_back(new TicktackBase("FORWARD", 1));
                elementList.push_back(new GABase("GA_FORWARD", bal[0] * 10)); // 200
            } else {
                elementList.push_back(new TicktackBase("TRIGHT", t_count));
            }
        }else if(bal[0] > 3){
            if(bal[1] > 10){
                elementList.push_back(new TicktackBase("TLEFT", t_count));
            }else if(bal[1] > -10){
                elementList.push_back(new SequenceMovement("READY"));
                //elementList.push_back(new TicktackBase("FORWARD", 1));
                elementList.push_back(new GABase("GA_FORWARD", 100)); // 100
            }else{
                elementList.push_back(new TicktackBase("TRIGHT", t_count));
            }
        }else{
            if(bal[1] > 10){
                elementList.push_back(new TicktackBase("TLEFT", t_count));
            }else if(bal[1] > -10){
                elementList.push_back(new SequenceMovement("READY"));
                elementList.push_back(new TicktackBase("FORWARD", 5));
                elementList.push_back(new SequenceMovement("READY"));
                elementList.push_back(new SequenceMovement("LAROUND"));
            }else{
                elementList.push_back(new TicktackBase("TRIGHT", t_count));
            }
        }
    }
}

void RunToBall::updateFinishFlag(World& w)
{
    if (abs(w.getBAL(0)) < 2 &&
        w.confBAL() <= 150)
    {
        finish_flag = true;
    } else {
        finish_flag = false;
        judgement(w);
    }
}
