#pragma once

#include "ofMain.h"

//花を描画するクラス
class Flower {
public:
	Flower(const glm::vec3 &_pos, const glm::vec3 &_dir);
	glm::mat4 translate; //ワールド座標用
	float pointSize;
	ofFloatColor color;

	glm::vec2 pos = glm::vec2(0, 0); //ローカル座標用の変数
	float angle; //向き
	int age;
	float lifeSpan;

	float myWave(float _x);
	void update();
	void clear();
	vector<glm::vec3> vertices;
	vector<ofFloatColor> colors;
	vector<float> pointSizes;
};
