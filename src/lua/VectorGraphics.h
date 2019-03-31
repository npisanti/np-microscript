
#pragma once

#include "ofMain.h"

#include "ofxLua/src/ofxLua.h"
#include "nanovg/src/nanovg.h"

#include "FileWatcher.h"

namespace np{ namespace lua {
    
class VectorGraphics : public FileWatcher, public ofxLuaListener {
    
public:
    VectorGraphics();
    ~VectorGraphics();
    
    void render( ofFbo & fbo );
    void draw( int x, int y, int w, int h );

    void playhead( float clock ){ this->clock = clock; }

    ofParameter<float> speed;
        
private:

    bool loaded;

    ofxLua lua;    
    
    std::string filename;

    void errorReceived(std::string& msg);
    
    void reload() override;
    float clock;
    float before;

    static int constructed;
    
    float aspect;
};
    
}}
