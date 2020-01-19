#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    glCreateShader(GL_GEOMETRY_SHADER);
    
    // Init dof
    depthOfField.setup(ofGetWidth(), ofGetHeight());
    
    particleNum = 250;
    appWinW = ofGetWidth();
    appWinH = ofGetHeight();
    particles.resize(particleNum);
    for(int i = 0; i < particleNum; i++) {
        particles.at(i) = Scene9Particle();
        particles.at(i).setId(i);
    }
    
    ofBackground(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    //swim the depth of field
    depthOfField.setFocalDistance(ofMap(sin(ofGetElapsedTimef()/4),-1,1, -300, 300));
    depthOfField.setFocalRange(100);
    for(int i = 0; i < particleNum; i++) {
        particles.at(i).update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    depthOfField.begin();                               // DOF begin
    cam.begin(depthOfField.getDimensions());            // virtual cam begin
    ofPushMatrix();
    ofRotateDeg(ofGetElapsedTimef() * 20, 1, 1, 0);
    ofTranslate(-ofGetWidth() * 0.5, -ofGetHeight() * 0.5);
    
    for(int i = 0; i < particleNum; i++) {
        particles.at(i).draw(particles);
    }
    ofPopMatrix();
    cam.end();              // virtual cam end
    depthOfField.end();     // DOF end
    
    if(ofGetKeyPressed('f')){
        depthOfField.drawFocusAssist(0, 0);
    }
    else{
        depthOfField.getFbo().draw(0, 0);
    }
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
