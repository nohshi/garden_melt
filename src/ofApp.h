#pragma once

#include "ofMain.h"

#include "rollScreen_melt.hpp"
#include "pointsRenderer.hpp"
#include "flower.hpp"
#include "bug.hpp"
#include "bug_leader.hpp"

#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup(); //初期化
    void update(); //毎フレーム呼ばれるやつ
    void draw(); //毎フレーム呼ばれるやつ、メインディスプレイへの描画用
    
    void drawDisplay_A(ofEventArgs & args); //サブウィンドウAに描画する
    void drawDisplay_B(ofEventArgs & args); //サブウィンドウBに描画する
    
    //以下マウス、キーイベント関数
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseScrolled(int x, int y, float scrollX, float scrollY);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int WIDTH, HEIGHT, wideWIDTH; //WIDTH,HEIGHTはウインドウサイズwideWIDTHはループスクリーン本体の大きさ
    int currentHEIGHT; //mainウインドウのスクリーンの今の縦幅
    
    RollScreen_melt rollScreen; //ロールスクリーン
    PointsRenderer pRenderer; //ポイントスプライト
    
    //---------------植物用のイベントとか
    void bear(Bug & _bug); //枝が生まれる時のイベント
    deque<Bug> bugs; //枝の配列
    deque<Flower> flowers; //花の配列
    void bloom(Bug & _bug); //花が咲く時のイベント
    
    //--------------------------------GUIオブジェクト
    //---------------植物関係のGUI
    ofxPanel plantsGui;
    ofxIntSlider g_lifeSpan; //枝の寿命 長さに影響
    ofxFloatSlider g_initialRadius; //初期の枝の半径
    ofxFloatColorSlider g_plantColor; //色
    ofxIntSlider g_limit; //bugの数の上限
    
    //--------ほんとはやりたくないけどrollScreenの中のofxGuiがうまく動かないから無理やりこっちで呼び出す
    ofxPanel screenGui;
    ofxFloatSlider g_meltVal, g_fade, g_speed; //溶け具合、フェードアウト具合、動くスピード
    ofxFloatSlider g_offSetX_A, g_offSetX_B; //ついでにプロジェクション対応用のスクリーンのオフセット値
    ofxFloatSlider g_screenAlph_A, g_screenAlph_B; //それぞれのスクリーンのアルファ値
    
    //--------------別スクリーンに渡す用のfbo
    ofFbo displayFbo[2];

};
