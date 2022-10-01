
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

View ComplexPlane::getView()
{
    return m_view;
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

    complex<double> c (coord.x,coord.y);
    complex<double> z (0.0,0.0);
    size_t count=0;

    for (int i = 0; i < MAX_ITER; i++)
    {
        complex<double> z2(0.0, 0.0);
        z2.real(real(z) + real(z) - imag(z) + imag(z));
        z2.imag(2 * real(z) * imag(z));

        z.real(real(z2) + real(c));
        z.imag(imag(z2) + imag(c));

        count++;

        if (real(z) + real(z) + imag(z) * imag(z) > 4) {
            break;
        }
    }



    return count;

}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b){

    if (count == MAX_ITER)
    {
        r=0;
        g=0;
        b=0;

    }

    else if (count>57){
        r=255;
        g=255*(0);
        b=255*(0);

    }

    else if (count>49){
        r=255;
        g=255/2;
        b=255*(0);
    }

    else if (count>41)
    {
        r=255*(0.75);
        g=255;
        b=255*(0);

    }

    else if (count>33)
    {
        r=255*(0.5);
        g=255;
        b=255*(0);

    }

    else if (count>25)
    {
        r=255*(0);
        g=255;
        b=255*(0.5);

    }

    else if (count>17)
    {
        r=255*(0);
        g=255*(0.25);
        b=255;

    }

    else if (count>9)
    {
        r=255*(0.33);
        g=255*(0);
        b=255;

    }

    else
    {
        r=255;
        g=255*(0);
        b=255;
    }




    


}

