#pragma once

#include "ofMain.h"
#include "ofxDOF.h"
#include "Scene9Particle.h"
#include "ofxGui.h"


class triangleMeshes {
public:
    vector<glm::vec3> points;
    ofMesh meshTriangles;
    ofColor baseColor;
    
    void setup() {
        meshTriangles.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        baseColor = ofColor(255,255,255,10);
    }
    
    void clear() {
        meshTriangles.clear();
        this->points.clear();
    }
    
    void addTriangle(vector<glm::vec3> & points, ofColor cl) {
        this->points = points;
        
        if(this->points.size() > 2)
        {
            meshTriangles.addColor(cl);
            meshTriangles.addVertex(this->points[0]);
            meshTriangles.addColor(cl);
            meshTriangles.addVertex(this->points[1]);
            meshTriangles.addColor(cl);
            meshTriangles.addVertex(this->points[2]);
        }
    }
    
    void draw() {
        
        meshTriangles.draw();
    }
    
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
    int particleNum;
    vector<Scene9Particle> particles;
    triangleMeshes triangleMesh;
    ofParameter<bool> gDrawConLine;
    ofxDOF depthOfField;
    ofEasyCam cam;
    ofFbo fbo;
    
    ofxPanel gui;
    ofParameter<float> gFocalDist;
    ofParameter<float> gFocalRange;
    ofParameter<int> gBlurAmt;
    ofParameter<int> totDist;
    ofParameter<glm::vec3> gNoiseVals;
    ofParameter<float> gSpeed;
    ofParameter<bool> gRotateWorld;
    ofParameter<int> gDrawMode;
    bool isDebug;
    
    ofMesh meshTriangles;
    ofMesh meshConnection;
};

