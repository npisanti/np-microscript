
#pragma once

#include <iostream>
#include "ofMain.h"
#include "nanovg/src/nanovg.h"

namespace us {

    void size( int w, int h );
    void framerate( int value );
    
    void clear();
    void background( double r, double g, double b, double a );
    void fade( double speed );

    void setColorA( double r, double g, double b );
    void setColorB( double r, double g, double b );

    void stroke( double r, double g, double b, double a );
    void strokeA();
    void strokeB();
    void strokeA( double alpha );
    void strokeB( double alpha );
    void stroke( double white );
    void stroke( double white, double alpha );
    void stroke();
    
    void fill( double r, double g, double b, double a );
    void fill();
    void fillA();
    void fillB();
    void fillA( double alpha );
    void fillB( double alpha );
    void fill( double white );
    void fill( double white, double alpha );
    
    void holes();
    
    void strokeWidth( double width );
    
    void setCapButt();
    void setCapRound();
    void setCapSquare();

    void setJoinMiter();
    void setJoinRound();
    void setJoinBevel();
    
    void circle( double x, double y, double radius );
	void arc( double cx, double cy, double r, double a0, double a1 );
	void arc( double cx, double cy, double r, double a0, double a1, int dir );
	void rect( double x, double y, double w, double h );
    void rect( double x, double y, double w, double h, double r );
	void ellipse( double cx, double cy, double rx, double ry );

    void poly( double cx, double cy, double radius, int N, double theta=-M_PI_2 );

    void begin();
    void close();
    
	void moveTo( double x, double y );
	void lineTo( double x, double y );
	void bezierTo( double c1x, double c1y, double c2x, double c2y, double x, double y );
	void arcTo( double x1, double y1, double x2, double y2, double radius );
    

    double map( double input, double inmin, double inmax, double outmin, double outmax );
    
    double random();
    double random( double max );
    double random( double min, double max );
    bool chance( double value );
        
        
    void push();
    void pop();
    void reset();
    void translate( double x, double y );
    void rotate( double rad );
    void scale( double x, double y );
    double ratio();
 
    void relative(); // relative mode, translate to center and values in pct
    

    // ---------- used from np::lua::VectorGraphics ------------

    void init();

    void beginFrame( int width, int height );
    void endFrame();

    void exit();
}
