
#pragma once

#include "ofMain.h"

class PointsRenderer {
public:
    PointsRenderer();
    
    //you add points with these functions
    void addVertex(const glm::vec3 &_p);
    void addColor(const ofFloatColor &_col);
    void addPointSize(const float &_pointSize);
    void addPoint(const glm::vec3 &_p, const ofFloatColor &_col, const float &_pointSize);
    
    void addvertices(const vector<glm::vec3> &_ps);
    void addColors(const vector<ofFloatColor> &_cols);
    void addPointSizes(const vector<float> &_pointSizes);
    void addPoints(const vector<glm::vec3> &_ps, const vector<ofFloatColor> &_cols, const vector<float> &_pointSizes);
    
    //then draw added points
    void draw();
    void clear();
    
    ofVboMesh vboMesh;
    ofShader shader;
    bool doShader = true;
    vector<float> pointsSize;
    
private:
    bool bSetCustomAttributes = false;
};


