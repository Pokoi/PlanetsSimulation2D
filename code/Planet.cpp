/*
 * File: Planet.hpp
 * File Created: 28th December 2019
 * ––––––––––––––––––––––––
 * Author: Jesus Fermin, 'Pokoi', Villar  (hello@pokoidev.com)
 * ––––––––––––––––––––––––
 * MIT License
 *
 * Copyright (c) 2019 Pokoidev
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Planet.hpp"
#include "Scaling.hpp"
#include "Rotation.hpp"
#include "Translation.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace toolkit;

namespace planets
{

	void Planet::render(sf::RenderWindow& renderer)
	{
		Scaling2f        scale(scale);
		Rotation2f       rotation(angle);
		Translation2f    translation(position);
		Transformation2f transform(translation * rotation * scale);

		int number_of_vertices = local_vertices.size();

		for (size_t i = 0; i < number_of_vertices; ++i)
		{
			transformed_vertices[i] = Matrix33f(transform) * Matrix31f(local_vertices[i]);
		}

		ConvexShape sfml_polygon;


		sfml_polygon.setPointCount(number_of_vertices);
		sfml_polygon.setFillColor(Color::White);


		for (int i = 0; i < number_of_vertices; i++)
		{
			sfml_polygon.setPoint
			(
				i,
				sf::Vector2f
				(
					transformed_vertices[i][0],
					transformed_vertices[i][1]
				)
			);
		}

		//Draw orbit

		if (parent)
		{
			CircleShape sfml_circle;
			sfml_circle.setRadius(2.f);
			sfml_circle.setFillColor(Color::Green);
			
			for (float i = 0; i < 1; i += 0.02)
			{
				Vector2f new_position = orbit.EvaluateWithoutUpdate(i);
				float x = new_position.coordinates().get_values()[0];
				float y = new_position.coordinates().get_values()[1];

				x += parent->get_position().coordinates().get_values()[0] - orbit.get_foci_displacement();
				y += parent->get_position().coordinates().get_values()[1];
				
				sfml_circle.setPosition(x, y);
				renderer.draw(sfml_circle);
			}

		}


		renderer.draw(sfml_polygon);

		for (Planet* planet : childs)
		{
			planet->render(renderer);
		}
	}

	void Planet::set_vertex(int count)
	{
		float pi2 = 6.283185f;

		for (int i = 0; i < count; ++i)
		{
			local_vertices.push_back(Point3f({radius * cos(pi2 * i/count),radius * sin(pi2 * i / count), 1}));
		}		
	}
	
}