
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on november of 2017                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "Planet.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace planets;

int main ()
{
    RenderWindow window(VideoMode(900, 800), "Animation Examples: Transformations", sf::Style::Default, ContextSettings(32));

    window.setVerticalSyncEnabled (true);

    bool running = true;

	Planet Sun {5,  50.0f };

	Sun.set_position      (400,  300);
	Sun.set_angular_speed (0.01f    );
	Sun.set_linear_speed  (0.f);

	Planet Earth{ 7, 20.0f, 100, Sun};
	Earth.set_angular_speed(0.03f);
	Earth.set_linear_speed(0.02f);

    do
    {
        // Process window events:

        Event event;

        while (window.pollEvent (event))
        {
            if (event.type == Event::Closed)
            {
                running = false;
            }
        }

		Sun.update (0);

        // Render:

        window.clear ();

		Sun.render (window);

        window.display ();
    }
    while (running);

    return EXIT_SUCCESS;
}
