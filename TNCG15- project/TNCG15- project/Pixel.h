#pragma once
#include "ColorDbl.h"
#include "Vertex.h"
struct Pixel {

	Pixel() : color(ColorDbl()), MiddlePos(Vertex()) {}

	Pixel(ColorDbl colorIn, Vertex VertIn) {
		color = colorIn;
		MiddlePos = VertIn;

	}
		ColorDbl color;
		Vertex MiddlePos;

};