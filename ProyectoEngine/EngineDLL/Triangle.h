#pragma once
#include "Shape.h"
#include "Material.h"

class ENGINEDLL_API Triangle: public Shape
{
public:
	void Draw() override;
	Triangle(Renderer * render);
	~Triangle();
};

