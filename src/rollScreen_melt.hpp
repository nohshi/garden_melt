#pragma once
//
//  rollScreen_melt.hpp
//  rollScreenMelt
//
//  Created by 藤田　恭輔 on 2019/05/30.
//

#ifndef rollScreen_melt_hpp
#define rollScreen_melt_hpp

#include "ofMain.h"
#include "ofxGui.h"

class RollScreen_melt {
public:
	RollScreen_melt();
	void init(const int &_width, const int &_height);

	void begin(); //begin()とend()で挟んだところに描画すると書き込める
	void end();   //
	float getScreenPositionX(const float &_posX);
	void clear();
	void drawIn(const function<void()> &_draw); //draw関数を受け取ってfboに書き込むやつ

	void update(); //毎フレーム呼ぶ
	void draw(const float &_width, const float &_height);
	void drawRectFrame(const float &_width, const float &_height); //fbo(四角)の枠を表示(デバッグ用)
	void swapBuffers(); //draw()の後に毎フレーム呼ぶ

	int screenWidth;
	float scrollingX = 0;
	ofFloatColor backgroundColor;

	ofFbo fbFbo[2];
	ofShader shader;

	float g_meltVal, g_fade, g_speed;

};

#endif /* rollScreen_melt_hpp */
