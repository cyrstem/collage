#include "ofApp.h"
Pieces::Pieces()
{
    pos.x = 0;
    pos.y = 0;
    
}
Pieces::Pieces(float x, float y,ofImage &cpy)
{
    reference = cpy;
    pos.x = x;
    pos.y = y;
    
    
}
void Pieces::update()
{
    
}
void Pieces::draw()
{
    reference.drawSubsection(pos.x, pos.y, 100, 100, pos.x, pos.y);
    
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(55);
    ofSetWindowShape(800, 800);
    ofSetFrameRate(60);
    reciver.setup(PORT);
    ofLog() << "listening for osc messages on port " << PORT;
    img.load("2.jpg");
    img.resize(img.getWidth()/2, img.getHeight()/2);
    
    p = new Pieces (0,0,img);
}

//--------------------------------------------------------------
void ofApp::update(){
    while (reciver.hasWaitingMessages()) {
        ofxOscMessage m;
        reciver.getNextMessage(m);
        ofLog() << " got  " << reciver;
        
        if (m.getAddress() == "/push") {
            p  = new Pieces(ofRandom(0,img.getWidth()), ofRandom(-0,ofGetWidth()),img);
        }
    }
    p->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //img.draw(0, 0);
    p->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_LEFT) {
        p  = new Pieces(ofRandom(0,img.getWidth()), ofRandom(-0,ofGetWidth()),img);
    }

}
