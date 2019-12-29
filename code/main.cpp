
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
using namespace toolkit;
using namespace planets;

int main ()
{
	float window_height = 1080;
	float window_width	= 1920;
    RenderWindow window(VideoMode(window_width, window_height), "Animation Examples: Transformations", sf::Style::Default, ContextSettings(32));

    window.setVerticalSyncEnabled (true);

    bool running = true;

	Planet Sun{10,  50.0f};
	Sun.set_position      (window_width * 0.5f,  window_height *0.5f);
	Sun.set_angular_speed (0.01f    );
	Sun.set_linear_speed  (0.f);

	Planet Mercury{6,  14.0f, Sun, Orbit{178,70,0, 30} };
	Mercury.set_angular_speed(0.03f);
	Mercury.set_linear_speed(0.06f);
	
	Planet Venus{ 6,  22.0f, Sun,  Orbit{260,100,40, 120} };
	Venus.set_angular_speed(0.03f);
	Venus.set_linear_speed(0.06f);
	
	Planet Earth{6, 22.0f, Sun, Orbit{330, 200, 90, 195}};
	Earth.set_angular_speed(0.01f);
	Earth.set_linear_speed(0.14f);

	Planet Moon{ 6, 13.f, Earth, Orbit{50,30,0, 60} };
	Moon.set_angular_speed(0.08f);
	Moon.set_linear_speed(0.16f);	

	Planet Mars{6, 16.0f, Sun, Orbit{487,250, 150, -45}};
	Mars.set_angular_speed (0.03f);
	Mars.set_linear_speed  (0.10f);

	Planet Fobos{6, 8.f, Mars, Orbit{46,25,0,90}};
	Fobos.set_angular_speed (0.08f);
	Fobos.set_linear_speed  (0.5f);

	Planet Deimos{6, 5.f, Mars, Orbit{33,15,0,0}};
	Deimos.set_angular_speed(0.08f);
	Deimos.set_linear_speed(0.3f);
	
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
