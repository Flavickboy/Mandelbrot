
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

    double coord_x = coord.x;
    double coord_y = coord.y;
    complex<double> c (coord_x,coord_y);
    complex<double> z (0.0,0.0);
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

    else if(count<= (MAX_ITER-1) && count>=((MAX_ITER/2)+1))//yellow to red
    {
        r= 255;
        g= (255-((255/((MAX_ITER-1)-(MAX_ITER/2)+1))*(count - ((MAX_ITER/2)+1))));
        b= 0;

    }
    else if(count<=(MAX_ITER/2) && count >= ((MAX_ITER/4)+1))// green to yellow
    {
        r= ((255/((MAX_ITER/2)-(MAX_ITER/4)+1))*(count-(MAX_ITER/4)+1)); 
        g= 255;
        b= 0;

    }

    else if(count<=(MAX_ITER/4) && count >= (MAX_ITER/16)+1)//turquoise to green
    {
        r= 0;
        g= 255;
        b= (255-((255/((MAX_ITER/4)-(MAX_ITER/16)+1))*(count -((MAX_ITER/16)+1)))); // 0 at the low end

    }

    else if(count <= (MAX_ITER/16) && count >=0)// blue to turquiose
    {
        r= 0;
        g= (255/(MAX_ITER/16))*((MAX_ITER/16)-count); // 255 at the low end
        b= 255;
    }


}