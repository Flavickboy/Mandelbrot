#include "ComplexPlane.h"

int main()
{

	//Calculate Aspect Ratio
	double screenwidth = VideoMode::getDesktopMode().width;
	double screenheight = VideoMode::getDesktopMode().height;
	double aspectRatio = screenwidth/screenheight;

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

	//Event declaration
	Event event;


	while (window.isOpen())
	{

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		while (window.pollEvent(event)){

			if (event.type == Event::Closed)
			{
   				 window.close();
			}

			if (event.type == Event::MouseButtonPressed)
			{
				//Find mouse Clicked coordinate
				Vector2i mouse_pos;
				Vector2f mouse_Coord;

				mouse_pos = window.mapCoordsToPixel(Vector2f(event.mouseButton.x, event.mouseButton.y), complex_p.getView());

				mouse_Coord= Vector2f(mouse_pos);


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

				status= windowStatus::CALCULATING;

			}

			if(event.type == Event::MouseMoved)
			{
				//Find Cursor Coordinate
				Vector2i mouse_pos;
				Vector2f mouse_Coord;

				mouse_pos = window.mapCoordsToPixel(Vector2f(event.mouseMove.x, event.mouseMove.y), complex_p.getView());
				mouse_Coord= Vector2f(mouse_pos);

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





		/*
		****************************************
		Draw the scene
		****************************************
		*/

		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(messageText);

		// Show everything we just drew
		window.display();


	}

	return 0;
}
