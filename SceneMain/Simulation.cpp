#include "Simulation.hpp"

Simulation::Simulation(int width, int height) : simTarget(nullptr), WIDTH(width), HEIGHT(height), current(0) {
	setName("simulation");
	for(int i = 0; i < 2; ++i) {
		if(i != 0) textures[i] = Texture2D::createEmpty(WIDTH,HEIGHT,Texture::RGB8);
		else textures[i] = Texture2D::createFromFile("data/inputs/accornglider.png",Texture::RGBA,Texture::UNSIGNED_BYTE,Texture::RGB8);
		textures[i]->setFilter(GL_NEAREST, GL_NEAREST);
	}
	simTarget = new RenderTarget(WIDTH, HEIGHT);
	simTarget->addCustomTexture(RenderTarget::COLOR0, textures[1]); //OUTPUT
	simTarget->ensureValid();
	GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT));
	model.mesh = Meshes.get("quad");
	model.program = Programs.get("simulation");
}

Simulation::~Simulation() {
	delete simTarget;
}

void Simulation::update(float deltaTime) {
	(void) deltaTime;
	if(!Environment::getKeyboard()->isKeyHeld(Keyboard::Return)) return;
	model.program->uniform("input")->set(textures[current]);
	current = (current+1)%2;
	simTarget->setCustomTexture(RenderTarget::COLOR0, textures[current]);
	model.program->uniform("width")->set(WIDTH);
	model.program->uniform("height")->set(HEIGHT);
	RenderTarget* curr = RenderTarget::getCurrent();
	RenderTarget::bind(simTarget);
	GL_ASSERT(glBlendFunc(GL_ONE,GL_ONE));
	GL_ASSERT(glClear(GL_COLOR_BUFFER_BIT));
	model.draw();
	RenderTarget::bind(curr);
}

Texture2D*Simulation::getSimTex() {
	return textures[current];
}

