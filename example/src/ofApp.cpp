
#include "ofMain.h"
#include "lua/VectorGraphics.h"

class ofApp : public ofBaseApp{
    
// ---------- variables ----------------------------------------
        
np::lua::VectorGraphics lua;
ofFbo fbo;

//--------------------------------------------------------------
void setup(){
    ofBackground( 0 );

    lua.load( "/home/nicola/oF/addons/np-luavg/example/bin/data/sigil.lua" );
    fbo.allocate( ofGetWidth(), ofGetHeight() );
}

//--------------------------------------------------------------
void update(){
    
    lua.render( fbo );

}

//--------------------------------------------------------------
void draw(){
    fbo.draw( 0, 0 );
}

//--------------------------------------------------------------
void exit(){

}

//--------------------------------------------------------------
void keyPressed(int key){
    switch( key ){    
        case '1':  break;
        case '2':  break;
        case '3':  break;
    }
}

//--------------------------------------------------------------
void mousePressed(int x, int y, int button){}
void mouseDragged(int x, int y, int button){}
void mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void keyReleased(int key){}
void mouseMoved(int x, int y){}
void mouseEntered(int x, int y){}
void mouseExited(int x, int y){}
void windowResized(int w, int h){}
void gotMessage(ofMessage msg){}
void dragEvent(ofDragInfo dragInfo){ }
//--------------------------------------------------------------

}; // class ofApp

int main(){
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp() );
}
