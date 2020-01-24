#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    glCreateShader(GL_GEOMETRY_SHADER);
    
    ofLogToConsole();
    ofEnableDepthTest();
    
    appWinW = 1000;
    appWinH = 1000;
    
    ofxGuiSetFont( "../../../../../../assets/DIN.otf", 8 );
    ofxGuiSetDefaultWidth( 300 );
    ofxGuiSetFillColor(ofColor(255,204,0,200));
    
    string xmlSettingsPath = "settings.xml";
    gui.setup( "Distance lines", xmlSettingsPath );
    gui.setPosition(ofGetWidth() - 300,0);
    gui.add(gFocalRange.set("Focal Range", 50, 0, 2500));
    gui.add(gFocalDist.set("Focal Distance", 150, -1500, 1500));
    gui.add(gBlurAmt.set("Blur Amount", 1, 0, 20));
    gui.add(gDrawConLine.set("Draw Line Connections", true));
    gui.add(gRotateWorld.set("Rotate World", false));
    gui.add(totDist.set("distance Threshold", 20, 5, 500));
    gui.add(gSpeed.set("Animation Speed", 1, 0.00001, 2));
    gui.add(gNoiseVals.set("Noise Multipliers", glm::vec3(0.002), glm::vec3(0.00001, 0.00001, 0.00001), glm::vec3(20)));
    gui.add(gDrawMode.set("Drawing Mode", 2, 0, 5));
    
    
    gui.loadFromFile(xmlSettingsPath);
    
    // Init dof
    depthOfField.setup(ofGetWidth(), ofGetHeight());
    
    particleNum = 600;
    
    
    particles.resize(particleNum);
    for(int i = 0; i < particleNum; i++) {
        particles.at(i) = Scene9Particle();
        particles.at(i).setId(i);
        particles.at(i).linecol = ofColor::white;
    }
    
    // Enable debug gui
    isDebug = true;
    
    ofBackground(0, 0, 0);
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    //swim the depth of field
    //depthOfField.setFocalDistance(ofMap(sin(ofGetElapsedTimef()/4),-1,1, -300, 300));
    depthOfField.setFocalDistance(gFocalDist);
    depthOfField.setFocalRange(gFocalRange);
    depthOfField.setBlurAmount(gBlurAmt);
    
    for(int i = 0; i < particleNum; i++) {
        particles.at(i).update();
        particles.at(i).mult = gSpeed;
        particles.at(i).mode = gDrawMode;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    depthOfField.begin();                               // DOF begin
    cam.begin(depthOfField.getDimensions());            // virtual cam begin
    ofPushMatrix();
    if(gRotateWorld)
        ofRotateDeg(ofGetElapsedTimef() * 20, 1, 1, 0);
    
    if(isDebug) {
        
        
    }
    
    ofPushStyle();
    ofNoFill();
    ofSetColor(255, 0, 0, 255);
    ofDrawBox(appWinW, appWinH, 1000);
    
    ofSetColor(255, 0, 0,130);
    ofDrawBox(appWinW + 200, appWinH + 200, 1000 + 200);
    
    ofSetColor(255, 0, 0,90);
    ofDrawBox(appWinW + 400, appWinH + 400, 1000 + 400);
    
    ofSetColor(255, 0, 0,40);
    ofDrawBox(appWinW + 600, appWinH + 600, 1000 + 600);
    
    ofSetColor(255, 0, 0,30);
    ofDrawBox(appWinW + 800, appWinH + 800, 1000 + 800);
    
    ofPopStyle();
    
    //ofTranslate(-ofGetWidth() * 0.5, -ofGetHeight() * 0.5);
    
    Scene9Particle p1, p2;
    
    
    meshConnection.clear();
    triangleMesh.clear();
    
    float dist, op;
    for(int i = 0; i < particleNum; i++) {
        
        ofColor cl = ofColor(particles.at(i).linecol.r,particles.at(i).linecol.g,particles.at(i).linecol.b, 255);
        p1.pos = particles[i].pos;
        p1.bros = vector<glm::vec3>();
        p1.bros.push_back(p1.pos);
        
        for (int j = i + 1; j < particleNum; j++) {
            p2.pos = particles[j].pos;
            
            dist = glm::length(p1.pos - p2.pos);
            
            
            if(gDrawConLine) {
                float ss;
                if(dist > 0 && dist < totDist)
                {
                    op = ofMap(dist, 0, totDist, 255, 0);
                    cl.a = op;
                    
                    meshConnection.setMode(OF_PRIMITIVE_LINES);
                    meshConnection.addColor(cl);
                    meshConnection.addVertex(p2.pos);
                    
                    meshConnection.addColor(cl);
                    meshConnection.addVertex(p1.pos);
                    
                    //particles[i].isContacting = true;
                    //particles[j].isContacting = true;
                    
                    //ss += 0.00006;
                    
                    
                        
                    p1.bros.push_back(p2.pos);
                    
                }else{
                    //particles[i].isContacting = false;
                    particles[j].isContacting = false;
                }
            }
            
            
            //ofDrawBox(particles[j].pos, 20, 20, 20);
        }
        
        
        
        if(p1.bros.size() > 1)
        {
            triangleMesh.addTriangle(p1.bros, ofColor(255,0,0,cl.a));
            
            
        }
        
    }
    

    triangleMesh.draw();
    
   

    
    meshConnection.draw();
    
    for(int i = 0; i < particleNum; i++) {
        //particles.at(i).draw(particles);
        particles[i].draw();
        
        
    }
    

    meshTriangles.draw();

    
    ofPopMatrix();
    cam.end();              // virtual cam end
    depthOfField.end();     // DOF end
    
    
    
    if(ofGetKeyPressed('i')){
        depthOfField.drawFocusAssist(0, 0);
    }
    else{
        depthOfField.getFbo().draw(0, 0);
    }
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);
    
    
    if(isDebug) {
        gui.draw();
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'd') {
        isDebug = !isDebug;
    }else if(key == 'f') {
        ofToggleFullscreen();
        
    }
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
    gui.setPosition(ofGetWidth() - 300,0);
    //appWinW = w;
    //appWinH = h;
    // Init dof
    depthOfField.setup(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
