
#include "flower.hpp"


Flower::Flower(const glm::vec3 &_pos, const glm::vec3 &_dir){
    vertices.reserve(30);
    colors.reserve(30);
    pointSizes.reserve(30);
    
    translate = glm::translate(_pos);
    lifeSpan = 200; //lifeSpan = 花の大きさ
    pointSize = 10;
    age = -20; //age==0以上の時花が描画される
    color = ofFloatColor(1,0.5,0.5,1);
    
    angle = glm::atan(_dir.x, _dir.y);
}


float Flower::myWave(float _x){ //0<_x<1
    _x = ofClamp(_x, 0, 1);
    _x = _x*2 - 1;
    float y;
    if (_x<0) {
        y = 1. - pow(abs(_x), 2.5);
    } else {
        y = sin(PI/2 + PI/2*_x);
    }
    return y;
}


void Flower::update(){
    
    glm::mat4 transform;
    glm::mat4 rotate;
    glm::vec4 p(0,0,0,1);
    
    if (age > -1) {
        
        float nnum = 6;
        for (int n=0; n<nnum; n++) {
            rotate = glm::rotate(float(2.*PI/nnum*n+angle), glm::vec3(0,0,1));
            transform = translate * rotate * glm::translate(glm::vec3(pos.x,  pos.y, 0));
            vertices.push_back(glm::vec3(transform * p));
            colors.push_back(color);
            pointSizes.push_back(pointSize*1.4);
            transform = translate * rotate * glm::translate(glm::vec3(pos.x, -pos.y, 0));
            vertices.push_back(glm::vec3(transform * p));
            colors.push_back(color);
            pointSizes.push_back(pointSize*1.4);
            float inum = 3;
            for (int i=0; i<inum; i++) {
                transform = translate * rotate * glm::translate(glm::vec3(pos.x,  pos.y/inum*i, 0));
                vertices.push_back(glm::vec3(transform * p));
                colors.push_back(color);
                pointSizes.push_back(pointSize);
                transform = translate * rotate * glm::translate(glm::vec3(pos.x, -pos.y/inum*i, 0));
                vertices.push_back(glm::vec3(transform * p));
                colors.push_back(color);
                pointSizes.push_back(pointSize);
            }
        }
        
        pos.x = age;
        pos.y = myWave(pos.x/lifeSpan) * lifeSpan/4.;
    }
    age ++;
}

//クリアしないとメモリリークする
void Flower::clear() {
    vertices.clear();
    colors.clear();
    pointSizes.clear();
}



