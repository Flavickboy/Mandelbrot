#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>


int main()
{

	//Calculate Aspect Ratio
	float screenwidth = VideoMode::getDesktopMode().width;
	float screenheight = VideoMode::getDesktopMode().height;
	float aspectRatio = screenwidth/screenheight;

	// Create a video mode object
	VideoMode vm(screenwidth, screenwidth);
	


	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot", Style::Default);

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



	cout<< "we good here before loop"<<endl;


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

					cout<< "Right Mouse works, X and y coord:"<< mouse_Coord.x<< " "<< event.mouseButton.y<< endl; 


				}
				//Left click zooms in
				if (event.mouseButton.button == Mouse::Left)
    			{
					complex_p.zoomIn();
					complex_p.setCenter(mouse_Coord);
					cout<< "Left Mouse works, X and y coord:"<< mouse_Coord.x<< " "<< mouse_Coord.y<< endl; 


				}

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
			window.close();
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/

		if (status == windowStatus::CALCULATING)
		{

			for (float j=0.0; j< screenwidth; j++)
			{
			for (float i=0.0;i<screenheight; i++)
				{
					Uint8 r, g, b;
					Vector2f pixelCoord;
					size_t count = 0;

					vArray[j+i*screenwidth].position={(float)j,(float)i};
					pixelCoord = window.mapPixelToCoords(Vector2i(j, i),complex_p.getView());

					count= complex_p.countIterations(pixelCoord);

					complex_p.iterationsToRGB(count,r,g,b);

					vArray[j+i*screenwidth].color={r,g,b};

					if (j>1920.0 && i>1080.0){
						break;
					}

				}
			}

			status = windowStatus::DISPLAYING;
			complex_p.loadText(messageText);

		}

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		// Clear everything from the last frame
		window.clear();

		//Draw vertex array

		window.draw(vArray);

		window.draw(messageText);
		
		// Show everything we just drew
		window.display();


	}

	return 0;
}
