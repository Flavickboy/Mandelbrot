// Include important C++ libraries here

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

	Text messageText;
    Font font;

    font.loadFromFile("fonts/KOMIKAP_.ttf");
    messageText.setFont(font);

    messageText.setString("cheese, Gromit!");
    messageText.setCharacterSize(20);
    messageText.setFillColor(Color::Magenta);
    messageText.setPosition(30, 30);




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