
#include "lvg.h"

#ifdef __ARM_ARCH
    #ifndef NANOVG_GLES2_IMPLEMENTATION
    #define NANOVG_GLES2_IMPLEMENTATION	// Use GLES2 on ARM
    #endif
#else
    #ifndef NANOVG_GL2_IMPLEMENTATION
    #define NANOVG_GL2_IMPLEMENTATION	// Use GL2 implementation.
    #endif
#endif

#include "nanovg/src/nanovg_gl.h"

namespace lvg {

    struct NVGcontext* _vg;
    int w;
    int h;
    int bFill;
    NVGcolor sColor;
    NVGcolor fColor;
    int ar;
    int ag;
    int ab;
    int br;
    int bg;
    int bb;
    double aspect;
    

    void init(){
        ofLogNotice()<<"[miscela] initializing nanovg Lua bindings";

        #ifdef NANOVG_GL3_IMPLEMENTATION
        _vg = nvgCreateGL3( NVG_ANTIALIAS | NVG_STENCIL_STROKES );
        #elif defined NANOVG_GL2_IMPLEMENTATION
        _vg = nvgCreateGL2( NVG_ANTIALIAS | NVG_STENCIL_STROKES );
        #elif defined NANOVG_GLES2_IMPLEMENTATION
        _vg = nvgCreateGLES2( NVG_ANTIALIAS | NVG_STENCIL_STROKES );
        #endif  
        ar = ab = ag = br = bg = bb = 120;
        fColor = sColor = nvgRGBA(255,255,255,255);
    }
    
    void exit(){
        ofLogNotice()<<"[miscela] deleting nanovg context";
        #ifdef NANOVG_GL3_IMPLEMENTATION
        nvgDeleteGL3( _vg );
        #elif defined NANOVG_GL2_IMPLEMENTATION
        nvgDeleteGL2( _vg );
        #elif defined NANOVG_GLES2_IMPLEMENTATION
        nvgDeleteGLES2( _vg );
        #endif       
    }

    void beginFrame( int width, int height ){
        nvgBeginFrame( _vg, width, height, 1 );
        w = width;
        h = height;
        aspect = double(width)/double(height);
        // reset defaults
        nvgReset( _vg );
        nvgScale( _vg, height, -height );
        nvgTranslate( _vg, 0.0, -1.0 );
        bFill = 0;
        nvgStrokeWidth( _vg, 0.05 );
        
        // change blending for nvg alpha
        //nvgGlobalCompositeBlendFunc( _vg, NVG_SRC_ALPHA, NVG__DST_ALPHA);   
        //nvgGlobalCompositeOperation( _vg, NVG_SOURCE_OVER );
    }

    void endFrame(){
        nvgEndFrame( _vg );
    }
    
    void setColorA( double r, double g, double b ){
        ar = r * 255.0;
        ag = g * 255.0;
        ab = b * 255.0;
    }
    
    void setColorB( double r, double g, double b ){
        br = r * 255.0;
        bg = g * 255.0;
        bb = b * 255.0;
    }

    void size( int w, int h ){
        ofSetWindowShape( w, h );
    }
    
    void framerate( int value ){
        ofSetFrameRate( value );
    }
    
    void background( double r, double g, double b, double a ){
        ofClear( r*255.0, g*255.0, b*255.0, a*255.0 );
    }

    void clear(){
        ofClear( 0, 0, 0, 0 );
    }
    
    void fade( double speed ){
        ofPushStyle();
            ofSetColor( 0, 0, 0, speed*speed*255 );
            ofFill();
            ofDrawRectangle( 0, 0, w, h );
        ofPopStyle();
    }

    void stroke( double r, double g, double b, double a ){
        sColor = nvgRGBA( r*255.0, g*255.0, b*255.0, a*255.0 );
        bFill = 0;
    }
    
    void stroke( double white, double alpha ){
        int w = white * 255.0;
        sColor = nvgRGBA( w, w, w, alpha*255 );
        bFill = 0;
    }
    
    void stroke( double white ){
        int w = white * 255.0;
        sColor = nvgRGBA( w, w, w, 255 );
        bFill = 0;
    }
        
    void strokeA( double alpha ){
        sColor = nvgRGBA( ar, ag, ab, alpha*255.0 );
        bFill = 0;
    }    
    
    void strokeB( double alpha ){
        sColor = nvgRGBA( br, bg, bb, alpha*255.0 );
        bFill = 0;
    }    
        
    void strokeA(){
        sColor = nvgRGBA( ar, ag, ab, 255 );
        bFill = 0;
    }    
    
    void strokeB(){
        sColor = nvgRGBA( br, bg, bb, 255);
        bFill = 0;
    }    
        
    void stroke(){
        sColor = nvgRGBA( 255, 255, 255, 255 );
        bFill = 0;
    }
    
    void fill( double r, double g, double b, double a ){
        fColor = nvgRGBA( r*255.0, g*255.0, b*255.0, a*255.0 );
        bFill = 1;
    }
    
    void fill( double white, double alpha ){
        int w = white * 255.0;
        fColor = nvgRGBA( w, w, w, alpha*255.0 );
        bFill = 1;
    }
    
    void fill( double white ){
        int w = white * 255.0;
        fColor = nvgRGBA( w, w, w, 255 );
        bFill = 1;
    }
        
    void fillA( double alpha ){
        fColor = nvgRGBA( ar, ag, ab, alpha*255.0 );
        bFill = 1;
    }    
    
    void fillB( double alpha ){
        fColor = nvgRGBA( br, bg, bb, alpha*255.0 );
        bFill = 1;
    }    
    
    void fillA(){
        fColor = nvgRGBA( ar, ag, ab, 255);
        bFill = 1;
    }    
    
    void fillB(){
        fColor = nvgRGBA( br, bg, bb, 255);
        bFill = 1;
    }    
    
    void fill(){
        fColor = nvgRGBA( 255, 255, 255, 255 );
        bFill = 1;
    }
    
    void strokeWidth( double width ){
        nvgStrokeWidth( _vg, width );
    }
    
    void begin(){
        nvgBeginPath(_vg);
    }
    
    void close(){
        switch( bFill ){
            default: case 0: 
                nvgStrokeColor(_vg, sColor );
                nvgStroke( _vg ); 
            break;
            case 1: 
                nvgFillColor(_vg, fColor );
                nvgFill( _vg ); 
            break;
        }
        nvgClosePath(_vg);        
    }
    
    void holes(){
        nvgPathWinding( _vg, NVG_HOLE );
    }

    void circle( double x, double y, double radius ){
        nvgCircle(_vg, x, y, radius);
    }
    
	void arc( double cx, double cy, double r, double a0, double a1, int dir){
        nvgArc(_vg, cx, cy, r, a0, a1, dir);
    }
    
	void arc( double cx, double cy, double r, double a0, double a1){
        nvgArc(_vg, cx, cy, r, a0, a1, 1);
    }
    
	void rect( double x, double y, double w, double h ){
        nvgRect( _vg, x, y, w, h );
    }
    
    void rect( double x, double y, double w, double h, double r ){
        nvgRoundedRect( _vg, x, y, w, h, r );
    }
    
	void ellipse( double cx, double cy, double rx, double ry ){
        nvgEllipse( _vg, cx, cy, rx, ry );
    }
    
    void poly( double cx, double cy, double radius, int N, double theta ){
        float step = M_TWO_PI / float(N);

        nvgSave( _vg );
        nvgTranslate( _vg, cx, cy );
            nvgMoveTo( _vg, cos(theta)*radius, sin(theta)*radius );
            for(int i=0; i<N; ++i ){
                theta += step;
                nvgLineTo( _vg, cos(theta)*radius, sin(theta)*radius );
            }
        nvgRestore( _vg );
    }

    void setCapButt(){ nvgLineCap(_vg, NVG_BUTT); }
    void setCapRound(){ nvgLineCap(_vg, NVG_ROUND); }
    void setCapSquare(){ nvgLineCap(_vg, NVG_SQUARE); }
    
    void setJoinRound(){ nvgLineJoin(_vg, NVG_ROUND); }
    void setJoinBevel(){ nvgLineJoin(_vg, NVG_BEVEL); }
    void setJoinMiter(){ nvgLineJoin(_vg, NVG_MITER); }

    void push(){
        nvgSave( _vg );
    }
    
    void pop(){
        nvgRestore( _vg );
    }
    
    void reset(){
        nvgReset( _vg );
    }

    double ratio(){
        return aspect;
    }

    void center(){
        nvgTranslate( _vg, aspect*0.5, 0.5 );
    }
    
    void translate( double x, double y ){
        nvgTranslate( _vg, x, y );
    }
    
    void rotate( double rad ){
        nvgRotate( _vg, rad );
    }
    
    void scale( double x, double y ){
        nvgScale( _vg, x, y );
    }

    void moveTo( double x, double y ){
        nvgMoveTo(_vg, x, y);
    }

    void lineTo( double x, double y ){
        nvgLineTo(_vg, x, y);
    }

    void bezierTo( double c1x, double c1y, double c2x, double c2y, double x, double y ){
        nvgBezierTo( _vg, c1x, c1y, c2x, c2y, x, y );
    }

    void arcTo( double x1, double y1, double x2, double y2, double radius ){
        nvgArcTo( _vg, x1, y1, x2, y2, radius );
    }

    
    bool chance( double value ){ return (ofRandomuf()<value); }
    
    double map( double input, double inmin, double inmax, double outmin, double outmax ){
        return ofMap( input, inmin, inmax, outmin, outmax, true );
    }
    
    double random(){
        return ofRandomuf();
    }
    
    double random( double max ){
        return ofRandom( max );
    }
    
    double random( double min, double max ){
        return ofRandom( min, max );
    }
}
