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
    float x, y, z;
    float radius;
    ofColor linecol, fillcol;
    float alph;
    float xmove, ymove, zmove;
    int crad;
    int cId;
    float bounce;
    int totDist;
    ofParameter<bool> drawMesh;
    
    ofMesh meshPrimary;
    ofMesh meshConnection;
    
    void setId(int _id) {
        cId = _id;
        bounce = true;
    }
    
    Scene9Particle() {
        x = ofRandom(appWinW);
        y = ofRandom(appWinH);
        z = ofRandom(-500, 500);
        radius = ofRandom(100,110);
        linecol = ofColor::white;
        fillcol = ofColor::white;
        alph = ofRandom(255);
        
        xmove = ofRandom(0.01,3);
        ymove = ofRandom(0.01,3);
        zmove = ofRandom(0.005, 3);
        
        crad = ofRandom(2,4);
        totDist = ofRandom(10,200);
        
        drawMesh = true;
    }
    
    
    
    ~Scene9Particle() {}
    
    void update() {
        x += xmove;
        y += ymove;
        z += zmove;
        
        if(!bounce) {
            if (x > (appWinW + radius)) {
                x = 0 -radius;
            }
            
            if (x < (0 - radius)) {
                x = appWinW + radius;
            }
            
            if (y > (appWinH + radius)) {
                y = 0 - radius;
            }
            
            if (y < (0 - radius)) {
                y = appWinH + radius;
            }
            
            if (z > 500) {
                z = -500;
            }
            
            if (z < -500) {
                y = 500;
            }
            
        }else{
            if (x > (appWinW + radius)) {
                xmove = xmove * -1;
            }
            
            if (x < (0 - radius)) {
                xmove = xmove * -1;
            }
            
            if (y > (appWinH + radius)) {
                ymove = ymove * -1;
            }
            
            if (y < (0 - radius)) {
                ymove = ymove * -1;
            }
            
            if (z > 500) {
                zmove = zmove * -1;
            }
            
            if (z < -500) {
                zmove = zmove * -1;
            }
            
        }
        
    }
    
    
    void draw(vector<Scene9Particle> & _particles) {
        
        for(int i = 0; i < _particles.size(); i ++) {
            if (i != cId) {
                float dis = ofDist(x, y, z, _particles.at(i).x, _particles.at(i).y, _particles.at(i).z);
                //float overlap = dis - radius - _particles.at(i).radius;
                if (dis < totDist && !drawMesh) {
                    ofSetColor(linecol, ofMap(dis,0,totDist,255,0));
                    ofDrawLine(x,y,z,_particles.at(i).x,_particles.at(i).y,_particles.at(i).z);
                }
                
                if(dis < totDist && drawMesh ){
                    for(int j = 0; j < _particles.size(); j ++) {
                        float dis2 = ofDist( _particles.at(j).x, _particles.at(j).y, _particles.at(j).z, _particles.at(i).x, _particles.at(i).y, _particles.at(i).z);
                        
                        if(dis2 < totDist - 100) {
                            ofSetColor(linecol, ofMap(dis,0,totDist,255,0));
                            ofDrawTriangle(x, y, z, _particles.at(i).x, _particles.at(i).y, _particles.at(i).z, _particles.at(j).x, _particles.at(j).y, _particles.at(j).z);
                            ofSetColor(linecol, ofMap(dis,0,totDist,255,50));
                            ofDrawLine(x,y,z, _particles.at(i).x,_particles.at(i).y,_particles.at(i).z);
                        }
                        
                    }
                }
                
            }
        }
        
        ofSetColor(fillcol);
        //ofDrawEllipse(x, y, z, crad, crad, crad);
        ofDrawSphere(x, y, z, crad);
    }
    
};
#endif
