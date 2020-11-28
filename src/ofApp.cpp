#include "ofApp.h"

//--------------------------------------------------------------プログラム実行時の最初の一度のみ実行される
void ofApp::setup() {
	ofSetBackgroundColor(255);
	ofEnableAntiAliasing();
	ofSetFrameRate(30);

	//-------------------------------スクリーンサイズ等の初期化
	WIDTH = 1280;
	HEIGHT = 1024;
	currentHEIGHT = ofGetHeight() - 50;
	wideWIDTH = WIDTH * 2;
	rollScreen.init(wideWIDTH, HEIGHT);

	//-------------------------------お花用イベントセットアップ
	ofAddListener(Bug::birth, this, &ofApp::bear);
	ofAddListener(Bug::bloom, this, &ofApp::bloom);

	//-------------------------------植物関係のGUIセットアップ
	plantsGui.setup();
	plantsGui.setName("plants");
	plantsGui.add(g_lifeSpan.setup("lifeSpan", 450, 100, 2000));
	plantsGui.add(g_initialRadius.setup("radius", 45, 5, 200));
	plantsGui.add(g_plantColor.setup("color", ofFloatColor(1), ofFloatColor(0), ofFloatColor(1)));
	plantsGui.add(g_limit.setup("limit", 500, 0, 2000));
	plantsGui.setPosition(240, 120);
	//-------------------------------スクリーン関係のGUIセットアップ
	screenGui.setup();
	screenGui.setName("screen");
	screenGui.add(g_meltVal.setup("melt", 0, 0, 1));
	screenGui.add(g_fade.setup("fade", 0.000, 0, 0.001));
	screenGui.add(g_speed.setup("speed", 1, 0, 5));
	screenGui.add(g_offSetX_A.setup("offSetX_A", 0, -WIDTH, WIDTH));
	screenGui.add(g_offSetX_B.setup("offSetX_B", 0, -WIDTH, WIDTH));
	screenGui.add(g_screenAlph_A.setup("screenAlph_A", 255, 0, 255));
	screenGui.add(g_screenAlph_B.setup("screenAlph_B", 255, 0, 255));
	screenGui.setPosition(20, 120);

	//-------------------------------マルチディスプレイ用のFBO
	for (int i = 0; i < 2; i++) {
		displayFbo[i].allocate(WIDTH, HEIGHT);
	}
}

//--------------------------------------------------------------毎フレーム実行される
void ofApp::update() {

	//------------------------screenにguiの値を渡す
	rollScreen.g_meltVal = g_meltVal;
	rollScreen.g_fade = g_fade;
	rollScreen.g_speed = g_speed;

	//------------------------rollScreenに書き込み
	for (int i = 0; i < bugs.size(); i++) {
		bugs[i].update();
		pRenderer.addPoint(bugs[i].pos, bugs[i].color, bugs[i].radius);
		if (bugs[i].age > bugs[i].lifeSpan) {
			bugs.erase(bugs.begin() + i);
		}
	}
	for (int i = 0; i < flowers.size(); i++) {
		flowers[i].update();
		pRenderer.addPoints(flowers[i].vertices, flowers[i].colors, flowers[i].pointSizes);
		flowers[i].clear();
		if (flowers[i].age > flowers[i].lifeSpan) {
			flowers.erase(flowers.begin() + i);
		}
	}
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	rollScreen.drawIn([&]() {pRenderer.draw(); }); //こいつにdraw()入れたらオッケー
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	pRenderer.clear(); //頂点バッファをクリア

	//------------------------rollScreenをアップデート
	rollScreen.update();

}

//--------------------------------------------------------------毎フレーム実行される
void ofApp::draw() {
	ofSetColor(255);
	//-------------------------サブスクリーンに渡す用のfboに書き込み
	displayFbo[0].begin();
	ofPushMatrix();
	ofTranslate(g_offSetX_A, 0);
	rollScreen.draw(wideWIDTH, HEIGHT);
	ofPopMatrix();
	displayFbo[0].end();

	displayFbo[1].begin();
	ofPushMatrix();
	ofTranslate(-WIDTH + g_offSetX_B, 0);
	rollScreen.draw(wideWIDTH, HEIGHT);
	ofPopMatrix();
	displayFbo[1].end();

	//-------------------コントロールウインドウにGUI書き込み
	rollScreen.draw(ofGetWidth(), currentHEIGHT);
	rollScreen.swapBuffers();

	//-------------------------gui関連
	plantsGui.draw();
	screenGui.draw();
	ofDrawBitmapString("fps : " + ofToString(ofGetFrameRate()), 20, 25);
	ofDrawBitmapString("bug_size : " + ofToString(bugs.size()) + "   limit : " + ofToString(float(g_limit)), 20, 45);
	ofDrawBitmapString("key:'c' to clear screen", 20, 65);
	ofDrawBitmapString("key:'x' to clear bugs and flowers", 20, 85);
	ofDrawBitmapString("key:'r' to resset offSet", 20, 105);
}

//-------------------------------------------ウインドウAに描画するもの
void ofApp::drawDisplay_A(ofEventArgs & args) {
	ofBackground(0);
	ofPushStyle();
	ofSetColor(255, g_screenAlph_A);
	displayFbo[0].draw(0, 0, ofGetWidth(), ofGetHeight());
	ofPopStyle();
}

//-------------------------------------------ウインドウBに描画するもの
void ofApp::drawDisplay_B(ofEventArgs & args) {
	ofBackground(0);
	ofPushStyle();
	ofSetColor(255, g_screenAlph_B);
	displayFbo[1].draw(0, 0, ofGetWidth(), ofGetHeight());
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::bear(Bug & _bug) {
	int limit = g_limit;
	if (bugs.size() < limit) {
		bugs.emplace_back();
		bugs[bugs.size() - 1].inherited(_bug);
	}
}

//--------------------------------------------------------------
void ofApp::bloom(Bug & _bug) {
	//_posAndDir contains pos.xy and dir.xy
	flowers.emplace_back(_bug.pos, _bug.dir);
	flowers[flowers.size() - 1].lifeSpan = _bug.initialRadius * 1;
	flowers[flowers.size() - 1].color = _bug.color;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'c':
		rollScreen.clear();
		break;

	case 'x':
		bugs.clear();
		flowers.clear();
		break;

	case 'r':
		g_offSetX_A = 0;
		g_offSetX_B = 0;
		break;

	default:
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
	rollScreen.scrollingX += scrollX;

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	glm::vec3 mouse = glm::vec3(x, y, 0);
	mouse.x *= float(wideWIDTH) / ofGetWidth();
	mouse.y *= float(HEIGHT) / currentHEIGHT;
	mouse.x = rollScreen.getScreenPositionX(mouse.x);

	if (button == 0) {
		glm::vec3 mouse = glm::vec3(x, y, 0);
		mouse.x *= float(wideWIDTH) / ofGetWidth();
		mouse.y *= float(HEIGHT) / currentHEIGHT;
		mouse.x = rollScreen.getScreenPositionX(mouse.x);

		bugs.emplace_back();
		bugs[bugs.size() - 1].setup(mouse, glm::vec3(0, -1., 0), 0);
		bugs[bugs.size() - 1].age = 0;
		bugs[bugs.size() - 1].generation++;
		bugs[bugs.size() - 1].seed = ofRandom(10000);
		bugs[bugs.size() - 1].childNum = 0;
		bugs[bugs.size() - 1].maxChildNum = 3;
		bugs[bugs.size() - 1].lifeSpan = g_lifeSpan;
		bugs[bugs.size() - 1].initialRadius = g_initialRadius;
		
		ofFloatColor col = g_plantColor;
		col.setHue(ofWrap(col.getHue() + ofRandom(-0.1, 0.1), 0, 1));
		bugs[bugs.size() - 1].color = col;
	}

	if (button == 2) {
		flowers.emplace_back(mouse, glm::vec3(ofRandom(1), ofRandom(1), 0));
		flowers[flowers.size() - 1].lifeSpan = g_initialRadius * 2;
		flowers[flowers.size() - 1].age = 0;
		ofFloatColor col = g_plantColor;
		col.setHue(ofWrap(col.getHue() + ofRandom(-0.1, 0.1), 0, 1));
		flowers[flowers.size() - 1].color = col;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	currentHEIGHT = ofGetHeight() - 50;

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
