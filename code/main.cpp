#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>

/*
	Programer: Derek Vergara
	Class: cisp 400
	Professor: Ryan Hermle
	Due Date: 10/4/2022

*/

void calculation(float screenwidth, float screenheight, ComplexPlane &complex_p, RenderWindow &window, VertexArray &vArray, float section)
{
	float screenSectionSize= (screenwidth/THREADS);
	float screenSectiontop= screenSectionSize*section;
	float screenSectionbottom= screenSectiontop-screenSectionSize;

for (float j=screenSectionbottom; j< screenSectiontop; j++)
{
for (float i=0.0; i< screenheight; i++)
	{
	Uint8 r, g, b;
	Vector2f pixelCoord;
	size_t count = 0;

	vArray[j+i*screenwidth].position={(float)j,(float)i};
	pixelCoord = window.mapPixelToCoords(Vector2i(j, i),complex_p.getView());

	count= complex_p.countIterations(pixelCoord);

	complex_p.iterationsToRGB(count,r,g,b);

	vArray[j+i*screenwidth].color={r,g,b};

		if (j>screenSectiontop&& i> screenheight)
		{
			break;
		}

	}
}

}


int main()
{

	//Calculate Aspect Ratio
	float screenwidth = VideoMode::getDesktopMode().width;
	float screenheight = VideoMode::getDesktopMode().height;
	float aspectRatio = (screenheight/screenwidth);

	// Create a video mode object
	VideoMode vm(screenwidth, screenheight);
	

	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot!!!", Style::Default);

	//Declare ComplexPlane object
	ComplexPlane complex_p(aspectRatio);

	//Declare Font and Text objects, Set font of messageText
	Text messageText;
    Font font;

    font.loadFromFile("fonts/calibri.ttf");
    messageText.setFont(font);

	//Declare Vertex Array, Set primitive type points, Set to size of screen
	VertexArray vArray;
	vArray.setPrimitiveType(Points);
	vArray.resize(screenwidth*screenheight);

	// Set Enum class to Calculating
	windowStatus status= windowStatus::CALCULATING;

	// Test outputs
	cout<< "Screenwidth: "<< screenwidth << endl << "Screenheight: "<< screenheight<< endl << "AspectRatio: "<< aspectRatio <<endl;



	while (window.isOpen())
	{
		

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		//Event declaration
		Event event;

		while (window.pollEvent(event)){

			if (event.type == Event::Closed)
			{
   				 window.close();
			}

			if (event.type == Event::MouseButtonPressed)
			{
				//Find mouse Clicked coordinate
				Vector2f mouse_Coord;

				mouse_Coord = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y), complex_p.getView());


				// Right click zooms out
				if (event.mouseButton.button == Mouse::Right)
    			{
					complex_p.zoomOut();
					complex_p.setCenter(mouse_Coord);



				}
				//Left click zooms in
				if (event.mouseButton.button == Mouse::Left)
    			{
					complex_p.zoomIn();
					complex_p.setCenter(mouse_Coord);


				}

				//Start calculating process
				status= windowStatus::CALCULATING;
				

			}

			if(event.type == Event::MouseMoved)
			{
				//Find Cursor Coordinate
				Vector2f mouse_Coord;

				mouse_Coord = window.mapPixelToCoords(Vector2i(event.mouseMove.x, event.mouseMove.y), complex_p.getView());

				complex_p.setMouseLocation(mouse_Coord);
			}

		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			//Self explanatory
			window.close();
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/

		if (status == windowStatus::CALCULATING)
		{

			// Threads split the calculation part into 16 different columns of the screen

			thread thr1 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),1.0};
			thread thr2 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),2.0};
			thread thr3 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),3.0};
			thread thr4 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),4.0};
			thread thr5 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),5.0};
			thread thr6 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),6.0};
			thread thr7 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),7.0};
			thread thr8 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),8.0};
			thread thr9 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),9.0};
			thread thr10 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),10.0};
			thread thr11 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),11.0};
			thread thr12 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),12.0};
			thread thr13 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),13.0};
			thread thr14 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),14.0};
			thread thr15 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),15.0};
			thread thr16 {calculation, screenwidth, screenheight, ref(complex_p), ref(window), ref(vArray),16.0};

			// Threads join at the end to ensure smooth frames. 
			thr1.join();
			thr2.join();
			thr3.join();
			thr4.join();
			thr5.join();
			thr6.join();
			thr7.join();
			thr8.join();
			thr9.join();
			thr10.join();
			thr11.join();
			thr12.join();
			thr13.join();
			thr14.join();
			thr15.join();
			thr16.join();

			status = windowStatus::DISPLAYING;

		}
		complex_p.loadText(messageText);

		/*
		****************************************
		Draw the scene
		****************************************
		*/
		

		// Clear everything from the last frame
		window.clear();

		//Draw vertex array

		window.draw(vArray);

		//dra

		window.draw(messageText);
		
		// Show everything we just drew
		window.display();


	}

	return 0;
}
