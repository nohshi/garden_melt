
#include "bug_leader.hpp"

void Bug_leader::update(){
    
    glm::vec3 v = dir;
    pos += v;
    
    if (pos.x < 0 || pos.x > ofGetWidth()) {
        dir.x = -dir.x;
    }
    if (pos.y < 0 || pos.y > ofGetHeight()) {
        dir.y = -dir.y;
    }
    
    //特定の条件下で子(枝)を産む
    if (ofRandom(1) < 0.02 && generation < 3 ) {
        this->bear(*this);
    }
    
    
    age ++;
}

void Bug_leader::display(){
    ofDrawCircle(pos, 1);
}


void Bug_leader::bear(Bug _child){
    childNum ++;
    
    _child.age = 0;
    _child.generation ++;
    _child.seed = ofRandom(10000);
    _child.childNum = 0;
    _child.maxChildNum = 2;
    _child.lifeSpan = this->lifeSpan * 0.8;
    
    ofNotifyEvent(birth, _child, this);
}


