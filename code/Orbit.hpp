/*
 * File: Orbit.hpp
 * File Created: 29th December 2019
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
#include "Vector.hpp"
#include <math.h>

namespace planets
{
	using toolkit::Vector2f;


	class Orbit
	{
	private:
		
		const float pi2 = 6.283185f;

		float x_axis;
		float y_axis;

		float foci_displacement;
		float progress;
		float orbit_angle;		

	public:

		Orbit()
		{
			x_axis = 0;
			y_axis = 0;

			foci_displacement	= 0;
			progress			= 0;
			orbit_angle			= 0;
		}

		Orbit(float x_axis, float y_axis, float foci_displacement, float angle) : x_axis(x_axis), y_axis(y_axis), foci_displacement(foci_displacement), orbit_angle(angle)
		{
			progress = 0;
		}

		float get_foci_displacement()
		{
			return foci_displacement;
		}

		Vector2f Evaluate(float delta)
		{
			if (progress < 0.001f)
			{
				progress = 0.001f;
			}

			orbit_angle += lerp(0, 360, delta * 0.0002f);

			progress += delta * 0.01f;
			progress = fmod(progress, 1.0f);

			float angle = pi2 * progress;
			Vector2f xy = Vector2f({ sin(angle) * x_axis, cos(angle) * y_axis });

			return Vector2f({ xy.coordinates().get_values()[0] * cos(orbit_angle) + xy.coordinates().get_values()[1] * sin(orbit_angle),
							  xy.coordinates().get_values()[1] * cos(orbit_angle) - xy.coordinates().get_values()[0] * sin(orbit_angle) });
		}

		Vector2f EvaluateWithoutUpdate(float delta)
		{
			float angle = pi2 * (progress + delta);
			Vector2f xy = Vector2f({ sin(angle) * x_axis, cos(angle) * y_axis });

			return Vector2f({ xy.coordinates().get_values()[0] * cos(orbit_angle) + xy.coordinates().get_values()[1] * sin(orbit_angle), 
							  xy.coordinates().get_values()[1] * cos(orbit_angle) - xy.coordinates().get_values()[0] * sin(orbit_angle) });
		}

		float lerp(float a, float b, float f)
		{
			return a + f * (b - a);
		}


	};
}