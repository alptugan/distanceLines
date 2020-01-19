//
//  Scene9.h
//  rawVisualv2
//
//  Created by alp tugan on 14/02/16.
//
//

#ifndef rawVisualv2_Scene9_h
#define rawVisualv2_Scene9_h

#include "ofxScene.h"
#include "Scene9Particle.h"

class Scene9 : public ofxScene {
public:
    //--------------------------------------------------------------
    // VARIABLES
    //--------------------------------------------------------------
    int particleNum;
    vector<Scene9Particle> particles;
    //--------------------------------------------------------------
    // METHODS
    //--------------------------------------------------------------
    Scene9(int _particleNum = 30) {
        particleNum = _particleNum;
    };
    
    ~Scene9() {};
    
    void setup() {
        particles.resize(particleNum);
        for(int i = 0; i < particleNum; i++) {
            particles.at(i) = Scene9Particle();
            particles.at(i).setId(i);
        }
    }
    void update(float dt) {
        for(int i = 0; i < particleNum; i++) {
            particles.at(i).update();
        }
    }
    void draw() {
        
        
        for(int i = 0; i < particleNum; i++) {
            particles.at(i).draw(particles);
        }
    }
    void exit() {};
    
    //scene notifications
    void sceneWillAppear( ofxScene * fromScreen ) {}
    void sceneWillDisappear( ofxScene * toScreen ) {}
    
    void sceneDidAppear( ofxScene * toScreen) { };
    void sceneDidDisappear( ofxScene * fromScreen ) {  };
    
};


#endif
