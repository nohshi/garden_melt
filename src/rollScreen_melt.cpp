//
//  rollScreen_melt.cpp
//  rollScreenMelt
//
//  Created by 藤田　恭輔 on 2019/05/30.
//

#include "rollScreen_melt.hpp"

RollScreen_melt::RollScreen_melt(){
    /*
    gui.setup();
    gui.setName("screen");
    gui.add(g_meltVal.setup("melt", 0, 0,1));
    gui.add(g_fade.setup("fade", 0.0010, 0,1));
    gui.add(g_speed.setup("speed", 1, 0,5));
    gui.setPosition(10, 10);
     */
}

void RollScreen_melt::init(const int &_width, const int &_height){
    screenWidth = _width;
    
    ofFbo::Settings setting;
    setting.width = screenWidth;
    setting.height = _height;
    setting.internalformat = GL_RGB32F;
    setting.numSamples = 0;
    setting.wrapModeVertical = GL_REPEAT;
    setting.wrapModeHorizontal = GL_REPEAT;
    setting.textureTarget = GL_TEXTURE_2D;
    
    backgroundColor = ofFloatColor(0,0,0,1);
    for (int i=0; i<2; i++) {
        fbFbo[i].allocate(setting);
        fbFbo[i].begin();
        ofClear(backgroundColor);
        fbFbo[i].end();
    }
    shader.load("meltShaders/melt");
}

void RollScreen_melt::begin(){
    fbFbo[0].begin();
}

void RollScreen_melt::end(){
    fbFbo[0].end();
}

float RollScreen_melt::getScreenPositionX(const float &_posX){
    return _posX-scrollingX;
}

void RollScreen_melt::clear(){
    fbFbo[0].begin();
    ofClear(backgroundColor);
    fbFbo[0].end();
}

void RollScreen_melt::drawIn(const function<void()> &_draw){
    fbFbo[0].begin();
    _draw();
    ofPushMatrix();
    ofTranslate(-screenWidth, 0);
    _draw();
    ofPopMatrix();
    fbFbo[0].end();
}

void RollScreen_melt::update(){
    scrollingX -= g_speed;
    scrollingX = ofWrap(scrollingX, -screenWidth, 0);
    
    //-----------------------------feedbackテクスチャに書き込み
    fbFbo[1].begin();
    shader.begin();
    // here is where the fbo is passed to the shader
    shader.setUniformTexture("tex1", fbFbo[1].getTexture(), 1 );
    shader.setUniform2f("u_resolution", fbFbo[0].getWidth(), fbFbo[0].getHeight());
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform1f("u_meltVal", g_meltVal);
    shader.setUniform1f("u_fadeVal", g_fade);
    shader.setUniform3f("u_backColor", backgroundColor.r, backgroundColor.g, backgroundColor.b);
    fbFbo[0].draw(0,0);
    shader.end();
    fbFbo[1].end();
}

void RollScreen_melt::draw(const float &_width, const float &_height){
    
    ofPushStyle();
    ofSetColor(255);
    ofPushMatrix();
    ofScale(_width/fbFbo[1].getWidth(), _height/fbFbo[1].getHeight());
    fbFbo[1].draw(scrollingX, 0);
    fbFbo[1].draw(scrollingX + screenWidth, 0);
    ofPopMatrix();
    ofPopStyle();
    
    //-----------デバッグ用
    //drawRectFrame(_width, _height);
}

void RollScreen_melt::drawRectFrame(const float &_width, const float &_height){
    ofPushStyle();
    ofNoFill();
    ofSetColor(0, 0, 255);
    ofPushMatrix();
    ofScale(_width/fbFbo[1].getWidth(), _height/fbFbo[1].getHeight());
    ofDrawRectangle(scrollingX, 0, screenWidth, fbFbo[1].getHeight());
    ofDrawRectangle(scrollingX + screenWidth, 0, screenWidth, fbFbo[1].getHeight());
    ofPopMatrix();
    ofPopStyle();
}

//------毎フレームこれ呼ばないとだめ
void RollScreen_melt::swapBuffers(){
    swap(fbFbo[0], fbFbo[1]); //二つのfboの中身を入れ替える
}

/*
void RollScreen_melt::drawGui(){
    gui.draw();
}
*/
