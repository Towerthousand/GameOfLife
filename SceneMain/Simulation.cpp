#include "Simulation.hpp"

Simulation::Simulation(int width, int height) : simTarget(nullptr), WIDTH(width), HEIGHT(height), current(0) {
	setName("simulation");
	textures[0] = Texture2D::createEmpty(WIDTH,HEIGHT,Texture::RGBA8);
	textures[1] = Texture2D::createEmpty(WIDTH,HEIGHT,Texture::RGBA8);
	simTarget = new RenderTarget();
	simTarget->addCustomTexture(RenderTarget::COLOR0, textures[1]); //OUTPUT
	simTarget->build();
	simTarget->getTextureForAttachment(RenderTarget::COLOR0)->setFilter(GL_NEAREST, GL_NEAREST);
	model.mesh = Meshes.get("quad");
	model.program = Programs.get("simulation");
}

Simulation::~Simulation() {
	delete simTarget;
}

void Simulation::update(float deltaTime) {
	(void) deltaTime;
	//model.program->uniform("inputTex")->set(textures[current]);
	RenderTarget* curr = RenderTarget::getCurrent();
	RenderTarget::bind(simTarget);
	model.draw();
	RenderTarget::bind(curr);
	simTarget->destroy();
	current = (current+1)%2;
	simTarget->setCustomTexture(RenderTarget::COLOR0, textures[current]);
	simTarget->build();
}

Texture2D*Simulation::getSimTex() {
	return textures[1];
}

