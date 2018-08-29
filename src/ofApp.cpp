
using namespace ofxCv;
using namespace cv;
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
    img.resize(img.getWidth()/2, img.getHeight()/2);
    time =ofGetElapsedTimeMillis();
    //p = new Pieces(0,0,img);
    int numPieces =10;
//    for (int i =0; i<numPieces; i++) {
//            //apuntar a image no copiar imagen
//        auto m =PiecesRef(new Pieces(ofRandom(0,400),ofRandom(0,400),img));
//        p.push_back(m);
//    }
    
    //Cv user
    cam.setup(720, 480);
    cFinder.setMinAreaRadius(1);
    cFinder.setMaxAreaRadius(300);
    cFinder.setThreshold(150);
    //espera medio segundo y olvidalo
    cFinder.getTracker().setPersistence(15);
     //un objeto se pudde mover 32 pxls por frame
    cFinder.getTracker().setMaximumDistance(32);

  showLabels = true;
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

        }
    }
    for (auto movp :p){
        movp->update();
        if(movp->age==100){
            cout<<p.size()<<endl;
            movp.reset();
            p.clear();
            //            movp.reset();
            //            ofBackground(55);
        }

    }
//    for ( it -> p.begin(); it != p.end(); ){
//            if( (*it)->lifetime==true)
//                delete * it;
//        it = p.erase(it);
//        }
//    }
    
    
     //open Cv
    cam.update();
    if (cam.isFrameNew()) {
        blur(cam, 10);
        cFinder.findContours(cam);
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    for (auto movp :p){
        movp->draw();
       
    }
    
    ofSetBackgroundAuto(showLabels);
    RectTracker& tracker = cFinder.getTracker();
    
        ofSetColor(255);
        //cam.draw(0, 0);
        //cFinder.draw();
        for(int i = 0; i < cFinder.size(); i++) {
            ofPoint center = toOf(cFinder.getCenter(i));
            ofPushMatrix();
            ofTranslate(center.x, center.y);
            int label = cFinder.getLabel(i);
            string msg = ofToString(label) + ":" + ofToString(tracker.getAge(label));
            ofDrawBitmapString(msg, 0, 0);
            ofVec2f velocity = toOf(cFinder.getVelocity(i));
            ofScale(5, 5);
            ofDrawRectangle(0, 0, 10+velocity.x, 10+velocity.y);
            
            //ofDrawLine(0, 0, velocity.x, velocity.y);
            ofPopMatrix();
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
