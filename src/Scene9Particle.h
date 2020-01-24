//
//  Scene9Particle.h
//  rawVisualv2
//
//  Created by alp tugan on 14/02/16.
//
//

#ifndef rawVisualv2_Scene9Particle_h
#define rawVisualv2_Scene9Particle_h

#include "appConstants.h"

class Scene9Particle {
public:
    glm::vec3 pos;
    float radius;
    ofColor linecol, fillcol;
    float alph;
    float xmove, ymove, zmove;
    int crad;
    int cId;
    int mode;
    float mult;
    bool isContacting;
    glm::vec3 noiseVals;
    
    float sigma,r,b, bound,step,roff;
    vector<float> uni;

    
    vector<glm::vec3> bros;
    
    void setId(int _id) {
        cId = _id;
        
    }
    
    void resize() {
        
        
    }
    
    
    Scene9Particle() {
        pos.x = ofRandom(0, appWinW);
        pos.y = ofRandom(0, appWinH);
        pos.z = ofRandom(0, 1000);
        //radius = ofRandom(100,110);
        linecol = ofColor::white;
        fillcol = ofColor::white;
        alph = ofRandom(255);
        
        mode = 0;
        
        xmove = ofRandom(0,3);
        ymove = ofRandom(0,3);
        zmove = ofRandom(0,3);
        
        crad = ofRandom(1,1);
        
        mult = 1;
        ofSetSphereResolution(4);
        
        noiseVals = glm::vec3(0.001, 0.001, 0.001);
        
        uni.resize(3);
        
        uni[0] = ofRandom(-appWinW*0.5, appWinW*0.5);
        uni[1] = ofRandom(-appWinH*0.5, appWinH*0.5);
        uni[2] = ofRandom(-500, 500);
        
        sigma=10;
        r=28;
        b=(8/3);
        step=0.003;
        
        //int a[5][2] = { {0,0}, {1,2}, {2,4}, {3,6},{4,8}};
    }
    
    
    
    ~Scene9Particle() {}
    
    void update() {
        
        
        if(mode == 0) {
            pos = glm::vec3(0,0,0);
            /*pos.x +=(sigma*(pos.y-pos.x))*step;
            pos.y +=((-pos.x*pos.z)+(r*pos.x)-pos.y)*step;
            pos.z +=((pos.x*pos.y)-(b*pos.z))*step;*/
            
            pos.x = uni[0];
            pos.y = uni[1];
            pos.z = uni[2];
            
            uni[0] += (sigma*(pos.y-pos.x))*step;
            uni[1] += ((-pos.x*pos.z)+(r*pos.x)-pos.y)*step;
            uni[2] += ((pos.x*pos.y)-(b*pos.z))*step;
        
            //line(x,y,z,uni[i][0],uni[i][1],uni[i][2]);
            
        }else if(mode == 1){
            pos.x += xmove * mult;
            pos.y += ymove * mult;
            pos.z += zmove * mult;
            
            
            if (pos.x >= (appWinW * 0.5)) {
                xmove = xmove * -1;
            }
            
            if (pos.x <= -(appWinW * 0.5)) {
                xmove = xmove * -1;
            }
            
            if (pos.y >= (appWinH) * 0.5) {
                ymove = ymove * -1;
            }
            
            if (pos.y <= -appWinH * 0.5) {
                ymove = ymove * -1;
            }
            
            if (pos.z >= 500) {
                zmove = zmove * -1;
            }
            
            if (pos.z <= -500) {
                zmove = zmove * -1;
            }
        }else if(mode == 2) {
            float t = ofGetElapsedTimef() * mult;
            //t = cId;
            
            //glm::vec3(0.002), glm::vec3(0.00001, 0.00001, 0.00001), glm::vec3(20)
            
            pos.x = ofSignedNoise(noiseVals.x, 0, t) * 650;
            pos.y = ofSignedNoise(0, noiseVals.y, t) * 500;
            pos.z = ofSignedNoise(t, 0, noiseVals.z) * 500;
            
        }
        
    }
    
    
    void draw(/*vector<Scene9Particle> & _particles*/) {
        

        if(isContacting)
            ofSetColor(linecol);
        else
            ofSetColor(fillcol);
        //ofDrawEllipse(x, y, z, crad, crad, crad);
        ofNoFill();
        
        ofDrawSphere(pos.x, pos.y, pos.z, crad);
    }
    
};
#endif
