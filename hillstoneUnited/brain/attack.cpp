#include "attack.hpp"

Attack::Attack(World& w, double _initpos[]) {
    finish_flag = false;
    initpos[0] = _initpos[0];
    initpos[1] = _initpos[1];
}

bool Attack::isFinished() {
    return finish_flag;
}

std::string Attack::getNextAngle(World& w) {
    // hogehoge
}