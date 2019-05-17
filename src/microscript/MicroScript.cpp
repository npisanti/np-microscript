
#include "MicroScript.h"

#include "bindings/us.h"
#include "bindings/lfo.h"

extern "C" {
	int luaopen_us(lua_State* L);
    int luaopen_lfo(lua_State* L);
}


int np::MicroScript::constructed = 0;

np::MicroScript::MicroScript(){
    loaded = false;

	script.addListener(this);
    before = 0.0f;
    speed = 1.0f;
    
    parameters.add( speed.set("speed", 1.0f, 0.0f, 2.0f) );
    
    clock = 0.0f;
    
    if( constructed==0 ){
        us::init();
    }
    
    constructed++;
}

np::MicroScript::~MicroScript(){
    if(loaded){
        script.scriptExit();
    }    
    script.clear();
    
    constructed--;
    if(constructed==0){
        us::exit();
    }
}

void np::MicroScript::reload(){
    if(loaded){
        script.scriptExit();
    }
    script.init(true);
    luaopen_us(script); 
    luaopen_lfo(script); 
    script.doScript( filepath, true);
    script.scriptSetup();
    loaded = true;
    before = ofGetElapsedTimef();
    
    filename = ofFilePath::getFileName( filepath ); 
}
    
void np::MicroScript::render( ofFbo & fbo ){
    
    aspect = float( fbo.getWidth() ) / float( fbo.getHeight() );
    
    float now = ofGetElapsedTimef();
    clock += (now-before) * (speed*speed*speed);
    before = now;
    lfo::setPlayHead( clock );

    fbo.begin();
        ofSetColor(255);
        us::beginFrame( fbo.getWidth(), fbo.getHeight() );
        script.scriptUpdate();
        script.scriptDraw();
        us::endFrame();
    fbo.end();

}

void np::MicroScript::draw( int x, int y, int w, int h ){
    ofPushMatrix();
    ofTranslate( x, y );
        aspect = float( w ) / float( h );
        
        float now = ofGetElapsedTimef();
        clock += (now-before) * (speed*speed*speed);
        before = now;
        lfo::setPlayHead( clock );

        ofSetColor(255);
        us::beginFrame( w, h );
        script.scriptUpdate();
        script.scriptDraw();
        us::endFrame();
    ofPopMatrix();
}

void np::MicroScript::errorReceived(std::string& msg) {
	ofLogNotice() << "[ "<<filename<<" ] got a script error: " << msg;
}
