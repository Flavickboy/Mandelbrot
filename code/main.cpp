#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>

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

	messageText.setString("cheese, Gromit!");
    messageText.setCharacterSize(20);
    messageText.setFillColor(Color::Magenta);
    messageText.setPosition(500, 500);


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
			cout<<"poll event is working"<< endl;

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
					cout<<"right click works"<<endl;


				}
				//Left click zooms in
				if (event.mouseButton.button == Mouse::Left)
    			{
					complex_p.zoomIn();
					complex_p.setCenter(mouse_Coord);
					cout<<"left click works"<<endl;

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

		if (status == windowStatus::CALCULATING)
		{

			for (double j=0.0; j< screenwidth; j++)
			{
			for (double i=0.0;i<screenheight; i++)
				{
					Uint8 r, g, b;
					Vector2i pixelPos;
					Vector2f pixelCoord;
					size_t count = 0;

					vArray[j+i*screenwidth].position={(float)j,(float)i};
					pixelPos = window.mapCoordsToPixel(Vector2f(j, i), complex_p.getView());
					pixelCoord = Vector2f(pixelPos);

					cout<< "pixel positioning is good: " << pixelCoord.x << "x, "<< pixelCoord.y<< "y."<< endl;

					count= rand()%63 ;
					//complex_p.countIterations(pixelCoord)
					

					cout<< "Count iter is good, itercount: "<< count << endl;

					complex_p.iterationsToRGB(count,r,g,b);
					cout<< "Iter to rgb func is good"<< endl; 

					vArray[j+i*screenwidth].color={r,g,b};

					cout<< "rgb to varray func is good"<< endl; 

					cout<< r << " " << g <<" " << b << " "<< endl;
				}
			}

			status = windowStatus::DISPLAYING;
			complex_p.loadText(messageText);
		}
		cout<<"after calc is good"<< endl;


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
