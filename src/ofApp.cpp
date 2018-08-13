#include "ofApp.h"
Pieces::Pieces()
{
    pos.x = 0;
    pos.y = 0;
    age =0;
    
}
Pieces::Pieces(float x, float y,ofImage &cpy)
{
    reference = cpy;
    pos.x = x;
    pos.y = y;
    
    
}
void Pieces::update()
{
    age++;
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
    
    //p = new Pieces(0,0,img);
    int numPieces =10;
//    for (int i =0; i<numPieces; i++) {
//            //apuntar a image no copiar imagen
//        auto m =PiecesRef(new Pieces(ofRandom(0,400),ofRandom(0,400),img));
//        p.push_back(m);
//    }


}

//--------------------------------------------------------------
void ofApp::update(){
    while (reciver.hasWaitingMessages()) {
        ofxOscMessage m;
        reciver.getNextMessage(m);
        ofLog() << " got  " << reciver;
        
        if (m.getAddress() == "/push") {
            for (int i =0; i<numPieces; i++) {
                //apuntar a image no copiar imagen
                auto m =PiecesRef(new Pieces(ofRandom(0,img.getWidth()),ofRandom(0,img.getHeight()),img));
                p.push_back(m);
            }

        }
    }
    
    

}

//--------------------------------------------------------------
void ofApp::draw(){

    for (auto movp :p){
        movp->draw();
    }
    


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_LEFT) {
        int numPieces =10;
        for (int i =0; i<numPieces; i++) {
            //apuntar a image no copiar imagen
            auto m =PiecesRef(new Pieces(ofRandom(0,img.getWidth()),ofRandom(0,img.getHeight()),img));
            p.push_back(m);
        }

    }

}
