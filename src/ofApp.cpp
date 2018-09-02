#include "ofApp.h"
Pieces::Pieces()
{
    pos.x = 0;
    pos.y = 0;
    age =0;
    lifetime =100.0;
    isAlive = false;
}
Pieces::Pieces(float x, float y,ofImage &cpy)
{
    reference = cpy;
    pos.x = x;
    pos.y = y;
    isAlive =true;
}

Pieces::~Pieces(){

}

void Pieces::update()
{
    age++;
    if(age <lifetime){
        isAlive =false;
        
    cout<<"are particles alive"<< isAlive<<endl;
        
    }
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
    
    img.load("1.jpg");
    img2.load("2.jpg");
  
    img.resize(img.getWidth()/2, img.getHeight()/2);
    img2.resize(img2.getWidth()/2, img2.getHeight()/2);
    time =ofGetElapsedTimeMillis();
    int numPieces =10;



}

//--------------------------------------------------------------
void ofApp::update(){
    while (reciver.hasWaitingMessages()) {
        ofxOscMessage m;
        reciver.getNextMessage(m);
        ofLog() << " got  " << reciver;
        
        if (m.getAddress() == "/push") {
            int numPieces =10;
            for (int i =0; i<numPieces; i++) {
                //apuntar a image no copiar imagen
                auto m =PiecesRef(new Pieces(ofRandom(0,img.getWidth()),ofRandom(0,img.getHeight()),img));
                p.push_back(m);
            }
            
            for (int i =0; i<numPieces; i++) {
                //apuntar a image no copiar imagen
                auto m =PiecesRef(new Pieces(ofRandom(0,img2.getWidth()),ofRandom(0,img2.getHeight()),img2));
                p2.push_back(m);
            }

        }
    }
    for (auto movp :p){
        movp->update();
        if(movp->age==100){
            cout<<p.size()<<endl;
            movp.reset();
            p.clear();
        }

    }

    for (auto movp :p2){
        movp->update();
        if(movp->age==100){
            cout<<p2.size()<<endl;
            movp.reset();
            p2.clear();
        }
        
    }


}

//--------------------------------------------------------------
void ofApp::draw(){

    for (auto movp :p){
        movp->draw();
       
    }
    for (auto movp :p2){
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
