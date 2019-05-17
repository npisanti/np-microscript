
#pragma once

#include "ofMain.h"

#include "ofxLua/src/ofxLua.h"
#include "nanovg/src/nanovg.h"

#include "FileWatcher.h"

namespace np{ 
    
class MicroScript : public FileWatcher, public ofxLuaListener {
    
public:
    MicroScript();
    ~MicroScript();
    
    void render( ofFbo & fbo );
    void draw( int x, int y, int w, int h );

    void playhead( float clock ){ this->clock = clock; }

    void variable( std::string name, double value ){ script.setNumber( name, (lua_Number) value ); }
   
    void variable( std::string name, bool value ){ script.setBool( name, value ); }

    ofParameter<float> speed;
    
    ofxLua script;    
        
private:

    bool loaded;

    std::string filename;

    void errorReceived(std::string& msg);
    
    void reload() override;
    float clock;
    float before;

    static int constructed;
    
    float aspect;
};
    
}
