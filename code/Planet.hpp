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

#pragma once

#include <vector>
#include "Point.hpp"
#include "Vector.hpp"
#include <math.h>
#include <list>
#include "Orbit.hpp"

namespace sf { class RenderWindow; }

namespace planets
{

	using toolkit::Point3f;
	using toolkit::Vector2f;
	using namespace std;

	class Planet
	{
		typedef std::vector< Point3f > Vertex_Buffer;

		
		Vertex_Buffer	local_vertices;
		Vertex_Buffer	transformed_vertices;
		
		Vector2f		position;
		float			angle;
		float			scale;
			
		float			linear_speed;
		float			angular_speed;		
		
		list <Planet*>	childs;
		Planet*			parent = nullptr;

		float			radius;
		Orbit			orbit;			

	public:		

		Planet	( const int	number_vertex, const float	radius) : radius(radius)
		{
			local_vertices.reserve(number_vertex);
			set_vertex(number_vertex);
			transformed_vertices.resize(local_vertices.size());
						
			set_position(0, 0);
			
			set_angle(0);
			set_scale(1);

			set_linear_speed(0);
			set_angular_speed(0);
		}

		Planet(
			const int	number_vertex,
			const float	radius,
			Planet &	parent,
			Orbit  &	orbit
		)
			: radius(radius), parent(&parent), orbit(orbit)
		{
			local_vertices.reserve(number_vertex);
			set_vertex(number_vertex);
			transformed_vertices.resize(local_vertices.size());

			
			set_position(0, 0);			

			set_angle(0);
			set_scale(1);

			set_linear_speed(0);
			set_angular_speed(0);

			this->parent->add_child_planet(*this);
		}

		void set_position(float x, float y)
		{
			position = Vector2f({ x, y });
		}

		Vector2f get_position()
		{
			return position;
		}

		void set_angle(float new_angle)
		{
			angle = new_angle;
		}

		float get_angle()
		{
			return angle;
		}

		void set_scale(float new_scale)
		{
			scale = new_scale;
		}

		void set_linear_speed(float speed)
		{
			linear_speed = speed;
		}

		void set_angular_speed(float speed)
		{
			angular_speed = speed;
		}

		void set_parent(Planet & parent_reference)
		{
			parent = &parent_reference;
		}

		void add_child_planet(Planet& child)
		{
			childs.push_back(&child);
		}

		void update(float delta)
		{
			
			if (parent != nullptr)
			{			
				Vector2f new_position = orbit.Evaluate(linear_speed);
				float x = new_position.coordinates().get_values()[0];
				float y = new_position.coordinates().get_values()[1];
								
				x += parent->get_position().coordinates().get_values()[0] - orbit.get_foci_displacement();
				y += parent->get_position().coordinates().get_values()[1];
				
				set_position(x, y);
			}
			

			angle += angular_speed;

			for (Planet* planet : childs)
			{
				planet->update(delta);
			}
		}

		void render(sf::RenderWindow& renderer);
		void set_vertex(int count);
		
	};

}
