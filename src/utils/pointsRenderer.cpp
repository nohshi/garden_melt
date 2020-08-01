//
//  pointsRenderer.cpp
//  bugsTrail
//
//  Created by 藤田　恭輔 on 2019/04/17.
//

#include "pointsRenderer.hpp"


PointsRenderer::PointsRenderer(){
    
    shader.load("pointsShader/shader");
    
    vboMesh.setMode(OF_PRIMITIVE_POINTS);
    
    pointsSize.reserve(50);
}
//-------------------------
void PointsRenderer::addVertex(const glm::vec3 &_p){
    vboMesh.addVertex(_p);
}

void PointsRenderer::addPointSize(const float &_pointSize){
    pointsSize.push_back(_pointSize);
}

void PointsRenderer::addColor(const ofFloatColor &_col){
    vboMesh.addColor(_col);
}

void PointsRenderer::addPoint(const glm::vec3 &_p, const ofFloatColor &_col, const float &_pointSize){
    this->addVertex(_p);
    this->addColor(_col);
    this->addPointSize(_pointSize);
}
//--------------------
void PointsRenderer::addvertices(const vector<glm::vec3> &_ps){
    vboMesh.addVertices(_ps);
}

void PointsRenderer::addPointSizes(const vector<float> &_pointSizes){
    for (int i=0; i<_pointSizes.size(); i++) {
        pointsSize.push_back(_pointSizes[i]);
    }
}

void PointsRenderer::addColors(const vector<ofFloatColor> &_cols){
    vboMesh.addColors(_cols);
}

void PointsRenderer::addPoints(const vector<glm::vec3> &_ps, const vector<ofFloatColor> &_cols, const vector<float> &_pointSizes){
    this->addvertices(_ps);
    this->addColors(_cols);
    this->addPointSizes(_pointSizes);
}
//--------------------
void PointsRenderer::draw(){
    if(doShader) {
        shader.begin();
        ofEnablePointSprites();
        ofEnableAlphaBlending();
    }
    
    //要素数変わるときは毎回setしなきゃいけない...あんまりいい作り方じゃないけど...まあ動くし...
    vboMesh.getVbo().setAttributeData(shader.getAttributeLocation("pointsize"), &pointsSize[0], 1, pointsSize.size(), GL_DYNAMIC_DRAW, sizeof(float));
    
    vboMesh.draw();
    
    if(doShader) {
        shader.end();
        ofDisablePointSprites();
    }
    
}

//毎フレームこれ呼ばないとメモリリークして死ぬ
void PointsRenderer::clear(){
    vboMesh.clear();
    pointsSize.clear();
}







