
#include "ComplexPlane.h"


ComplexPlane::ComplexPlane(float aspectRatio){

    m_aspectratio = aspectRatio; 
    m_view.setSize(BASE_WIDTH, -BASE_HEIGHT*m_aspectratio);
    m_view.setCenter(0.0, 0.0);
    m_zoomcount=0;

}

void ComplexPlane::zoomIn(){

    m_zoomcount++;

    float x= BASE_WIDTH*(pow(BASE_ZOOM, m_zoomcount));
    float y= BASE_HEIGHT* m_aspectratio*(pow(BASE_ZOOM, m_zoomcount));

    m_view.setSize(x,y);

}

void ComplexPlane::zoomOut(){

    m_zoomcount--;

    float x= BASE_WIDTH*(pow(BASE_ZOOM, m_zoomcount));
    float y= BASE_HEIGHT* m_aspectratio*(pow(BASE_ZOOM, m_zoomcount));

    m_view.setSize(x,y);

}

void ComplexPlane::setCenter(Vector2f coord){
    m_view.setCenter(coord);
}

void ComplexPlane::setMouseLocation(Vector2f coord){
    m_mouselocation= coord;
}

void ComplexPlane::loadText(Text& text){

    text.setString("cheese, Gromit!");
    text.setCharacterSize(20);
    text.setFillColor(Color::Magenta);
    text.setPosition(500, 500);


}

size_t ComplexPlane::countIterations(Vector2f coord){




}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b){



}

