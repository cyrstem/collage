#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#define PORT 12345
typedef std::shared_ptr<class Pieces>PiecesRef;
class Pieces {
public:
    Pieces();
    Pieces(float x, float y, ofImage &cpy);

    void update();
    void draw();
    ofPoint pos;
    ofImage reference;
    int age;
};

//--------------------------------------------------------------
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
        ofxOscReceiver reciver;
    ofImage img;

    float numPieces;
    vector<PiecesRef>p;


    
};
