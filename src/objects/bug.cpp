
#include "bug.hpp"

// the static event, or any static variable, must be initialized outside of the class definition.
ofEvent<Bug> Bug::birth = ofEvent<Bug>();
ofEvent<Bug> Bug::bloom = ofEvent<Bug>();

Bug::Bug(){
    lifeSpan = 700;
    childNum = 0;
    maxChildNum = 3;
    age = 0;
    seed = ofRandom(1);
    initialRadius = 100;
    radius = initialRadius;
    color = ofFloatColor(1, 1, 1);
    flowerNum = 0;
    maxFlowerNum = 1;
}

void Bug::setup(const glm::vec3 &_pos, const glm::vec3 &_dir, const int &_generation){
    pos = _pos;
    dir = _dir;
    generation = _generation;
}

void Bug::update(){
    
    float theta = ofSignedNoise(seed*1000, ofGetFrameNum()*0.2) * 5;
    dir = ofVec3f(dir).getRotated(theta, ofVec3f(0,0,1));
    dir = glm::normalize(dir);
    glm::vec3 v = dir;
    pos += v;
    
    radius = 1 + initialRadius * (1.-age/float(lifeSpan));
    
    //特定の条件下で産む
    if (ofRandom(1) < 0.01 && generation < 3 && childNum < maxChildNum) {
        this->bear(*this);
    }
    if (ofRandom(1) < 0.0005 && flowerNum < maxFlowerNum) {
        flowerNum ++;
        ofNotifyEvent(bloom, *this); //花を咲かせるよう命令
    }
    
    age ++;
}

void Bug::display(){
    ofDrawCircle(pos, 1);
}


void Bug::bear(Bug _child){
    childNum ++;
    
    ofNotifyEvent(birth, _child);
}


void Bug::inherited(const Bug &_bug){
    this->pos = _bug.pos;
    this->dir = _bug.dir;
    this->initialRadius = _bug.radius;
    this->generation = _bug.generation + 1;
    this->color = _bug.color;
    this->lifeSpan = _bug.lifeSpan;
}









