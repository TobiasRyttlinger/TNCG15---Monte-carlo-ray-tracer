#pragma once
#include "ColorDbl.h"
#include "Vertex.h"
struct Pixel {

	Pixel() : color(ColorDbl()), MiddlePos(Vertex()) {}

	Pixel(ColorDbl colorIn, Vertex VertIn) {
		color = colorIn;
		MiddlePos = VertIn;

	}

	void GetNewColor(ColorDbl c) {
		color.r = c.r;
		color.g = c.g;
		color.b = c.b;

	}
		ColorDbl color;
		Vertex MiddlePos;

};