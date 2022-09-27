// Include important C++ libraries here

#include "ComplexPlane.h"

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot", Style::Default);

    Vector2f mousepos; 


	while (window.isOpen())
	{

		/*
		****************************************
		Handle the players input
		****************************************
		*/

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


		// Show everything we just drew
		window.display();


	}

	return 0;
}