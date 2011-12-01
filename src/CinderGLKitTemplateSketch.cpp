#include "CinderGLKitTemplateSketch.h"

#include "cinder/ImageIO.h"
#include "cinder/app/App.h"

#import <UIKit/UIKit.h>

using namespace std;

void CinderGLKitTemplateSketch::setup()
{
    m_vbo = gl::Vbo::create(GL_LINE_STRIP);
    m_vbo->set(gl::Vbo::Attribute::create("position", 3));
    
    try{
        m_color_shader = gl::GlslProg(app::loadResource("color.vsh"), app::loadResource("color.fsh"));
    }catch(Exception &e){
        cout << "Shader Compile Failed: " << e.what() << endl;;
    }

    m_camera.setOrtho(0, 1, -1, 1, -1, 1);
}

void CinderGLKitTemplateSketch::update()
{
    float time = getElapsedSeconds() * 0.2f;

    vector<Vec3f> positions;
    for(int n = 100, i = 0; i < n; ++i){
        float t = i / (n - 1.0f);
        positions.push_back(Vec3f(t, m_perlin.fBm(t, time), 0));
    }
    
    m_vbo->get("position")->setData(positions);    
}

void CinderGLKitTemplateSketch::draw(const Area &area)
{
    gl::clear(ColorA(1, 1, 0, 1));
    
    glLineWidth(4);
    
    m_color_shader.bind();
    m_color_shader.uniform("u_mvp_matrix", m_camera.getProjectionMatrix() * m_camera.getModelViewMatrix());
    m_color_shader.uniform("u_color", Vec4f(0, 0, 0, 1));
    m_vbo->draw(m_color_shader);
}

void CinderGLKitTemplateSketch::touchesBegan( app::TouchEvent event )
{
    const static string begin = "<!DOCTYPE html><html><meta name=\"viewport\" content=\"width=300px, initial-scale=1, maximum-scale=1\"><style>html, body { width: 100%; height: 100%; padding: 0; margin: 0; } body { background-color: transparent; font-family: sans-serif; } p { margin: 10px; padding: 0; }</style><body><p>";
    const static string tweet = "RT @KuraFire: US judge orders hundreds of sites “de-indexed” from Google, Facebook etc. <a href=http://j.mp/u4KsNg>j.mp/u4KsNg</a> \n\nWhy wait for SOPA indeed… ...";
    const static string end = "</p></body></html>";
    mHtmlOverlay->setHtml( begin + tweet + end );
    
    Rectf rect = mHtmlOverlay->getRect();
    float width = rect.getWidth();
    rect.x1 = 0.0;
    rect.x2 = width;
    mHtmlOverlay->setRect( rect );
        
    touchesMoved( event );
    
    mHtmlOverlay->setShowing();    
}

void CinderGLKitTemplateSketch::touchesEnded( app::TouchEvent event )
{
    mHtmlOverlay->setHidden();
}

void CinderGLKitTemplateSketch::touchesMoved( app::TouchEvent event )
{
    app::TouchEvent::Touch firstTouch = event.getTouches()[0];

    Rectf rect = mHtmlOverlay->getRect();
    float width = rect.getWidth();
    float height = rect.getHeight();
    rect.x1 = firstTouch.getX() + 10.0;
    rect.x2 = rect.x1 + width;
    rect.y1 = firstTouch.getY() + 10.0;
    rect.y2 = rect.y1 + height;
    mHtmlOverlay->setRect( rect );
}