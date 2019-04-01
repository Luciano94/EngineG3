#include "Shape.h"

Shape::Shape(Renderer * render) :Entity(render){
	shouldDispose = false;
	material = NULL;
	bufferId = -1;
	vertexCount = -1;
	shouldDisposeColor = false;
	colorBufferId = -1;
	colorVertexCount = -1;
}

void Shape::DrawMesh(int typeDraw){
	render->LoadIMatrix();
	render->SetWMatrix(WorldMatrix);

	if (material != NULL) {
		material->BindProgram();
		material->Bind("WVP");
		material->SetMatrixProperty(render->GetWVP());
	}

	render->BeginDraw(0);
	render->BindBuffer(0, bufferId,3);
	render->BeginDraw(1);
	render->BindBuffer(1, colorBufferId,3);
	render->DrawBuffer(vertexCount, typeDraw);
	render->EndDraw(0);
	render->EndDraw(1);
}

void Shape::SetVertices(float * vertices, int count){
	Dispose();

	vertexCount = count;
	shouldDispose = true;
	bufferId = render->GenBuffer(vertices, sizeof(float)* count * 3);
}

void Shape::SetColorVertex(float * vertices, int count){
	DisposeColor();

	colorVertexCount = count;
	shouldDisposeColor = true;
	colorBufferId = render->GenBuffer(vertices, sizeof(float)* count * 3);
}

void Shape::SetMaterial(Material * material){
	this->material = material;
}

void Shape::Dispose(){
	if (shouldDispose) {
		render->DestroyBuffer(bufferId);
		shouldDispose = false;
	}
}

void Shape::DisposeColor(){
	if (shouldDisposeColor) {
		render->DestroyBuffer(colorBufferId);
		shouldDisposeColor = false;
	}
}

Shape::~Shape(){
	Dispose();
	DisposeColor();
}
