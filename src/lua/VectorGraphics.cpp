
#include "VectorGraphics.h"

#include "bindings/lvg.h"
#include "bindings/lfo.h"

extern "C" {
	int luaopen_lvg(lua_State* L);
    int luaopen_lfo(lua_State* L);
}


int np::lua::VectorGraphics::constructed = 0;

np::lua::VectorGraphics::VectorGraphics(){
    loaded = false;

	lua.addListener(this);
    before = 0.0f;
    speed = 1.0f;
    
    parameters.add( speed.set("speed", 1.0f, 0.0f, 2.0f) );
    
    clock = 0.0f;
    
    if( constructed==0 ){
        lvg::init();
    }
    
    constructed++;
}

np::lua::VectorGraphics::~VectorGraphics(){
    if(loaded){
        lua.scriptExit();
    }    
    lua.clear();
    
    constructed--;
    if(constructed==0){
        lvg::exit();
    }
}

void np::lua::VectorGraphics::reload(){
    if(loaded){
        lua.scriptExit();
    }
    lua.init(true);
    luaopen_lvg(lua); 
    luaopen_lfo(lua); 
    lua.doScript( filepath, true);
    lua.scriptSetup();
    loaded = true;
    before = ofGetElapsedTimef();
    
    filename = ofFilePath::getFileName( filepath ); 
}
    
void np::lua::VectorGraphics::render( ofFbo & fbo ){
    
    aspect = float( fbo.getWidth() ) / float( fbo.getHeight() );
    
    float now = ofGetElapsedTimef();
    clock += (now-before) * (speed*speed*speed);
    before = now;
    lfo::setPlayHead( clock );

    fbo.begin();
        ofSetColor(255);
        lvg::beginFrame( fbo.getWidth(), fbo.getHeight() );
        lua.scriptUpdate();
        lua.scriptDraw();
        lvg::endFrame();
    fbo.end();

}

void np::lua::VectorGraphics::draw( int x, int y, int w, int h ){
    ofPushMatrix();
    ofTranslate( x, y );
        aspect = float( w ) / float( h );
        
        float now = ofGetElapsedTimef();
        clock += (now-before) * (speed*speed*speed);
        before = now;
        lfo::setPlayHead( clock );

        ofSetColor(255);
        lvg::beginFrame( w, h );
        lua.scriptUpdate();
        lua.scriptDraw();
        lvg::endFrame();
    ofPopMatrix();
}

void np::lua::VectorGraphics::errorReceived(std::string& msg) {
	ofLogNotice() << "[ "<<filename<<" ] got a script error: " << msg;
}
