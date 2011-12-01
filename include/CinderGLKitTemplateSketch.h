#pragma once

#include "CinderGLSketch.h"

#include "cinder/gl/GlslProg.h"
#include "Vbo.h"

#include "cinder/Vector.h"
#include "cinder/Camera.h"
#include "cinder/Perlin.h"

#include "HtmlOverlay.h"

using namespace ci;

class CinderGLKitTemplateSketch : public CinderGLSketch {
public:
    
    void setup();
    void update();
    void draw(const Area &area);
    
    void touchesBegan( app::TouchEvent event );
    void touchesMoved( app::TouchEvent event );
    void touchesEnded( app::TouchEvent event );
    
    gl::VboRef m_vbo;
    
    gl::GlslProg m_color_shader;
    
    CameraOrtho m_camera;
    
    Perlin m_perlin;
    
    HtmlOverlayRef mHtmlOverlay;
};