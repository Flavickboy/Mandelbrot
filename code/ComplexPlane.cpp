
#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>


ComplexPlane::ComplexPlane(float aspectRatio){

    m_aspectratio = aspectRatio; 
    m_view.setSize(BASE_WIDTH, (-BASE_HEIGHT)*m_aspectratio);
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

View ComplexPlane::getView()
{
    return m_view;
}

void ComplexPlane::setMouseLocation(Vector2f coord){
    m_mouselocation= coord;
}

void ComplexPlane::loadText(Text& text){

    ostringstream textLayout;
    Vector2f currCenter = m_view.getCenter();



    textLayout << "Mandelbrot Set"<< endl 
    << "Center: ("<< currCenter.x << ", "<< currCenter.y<< ")"<< endl
    << "Cursor: ("<< m_mouselocation.x << ", "<< m_mouselocation.y<< ")"<< endl
    << "Left click to zoom in" << endl << "Right click to zoom out"; 

    string output = textLayout.str();


    text.setString(output);
    text.setCharacterSize(30);
    text.setFillColor(Color::Magenta);
    text.setPosition(50,40);


}

size_t ComplexPlane::countIterations(Vector2f coord){

    complex<float> c (coord.x,coord.y);
    complex<float> z (0.0,0.0);
    size_t count =0;

    while (count< MAX_ITER && abs(z)<2)
    {
        z= z*z +c;
        count++;
    }

    return count;

}

void ComplexPlane::iterationsToRGB(size_t Count, Uint8& r, Uint8& g, Uint8& b){

    float count = (float)Count;

    if (count == MAX_ITER)
    {
        r=0;
        g=0;
        b=0;

    }

    else if(count<= 63 && count>=33)//yellow to red
    {
        r= 255;
        g= (255-(8.5*(count - 33)));
        b= 0;

    }
    else if(count<=32 && count >= 17)// green to yellow
    {
        r= (17*(count-17)); 
        g= 255;
        b= 0;

    }

    else if(count<=16 && count >= 5)//turquoise to green
    {
        r= 0;
        g= 255;
        b= (255 - 23*(count -5)); // 0 at the low end

    }

    else if(count <= 4 && count >=0)// blue to turquiose
    {
        r= 0;
        g= 63*(4-count); // 255 at the low end
        b= 255;
    }


}