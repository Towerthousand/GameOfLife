#include "Simulation.hpp"

Simulation::Simulation(std::string inputFile) : simTarget(nullptr), current(0) {
	setName("simulation");
	textures[0] = Texture2D::createFromFile(inputFile,Texture::RGBA,Texture::UNSIGNED_BYTE,Texture::RGB8);
	WIDTH = textures[0]->getWidth();
	HEIGHT = textures[0]->getHeight();
	textures[1] = Texture2D::createEmpty(WIDTH,HEIGHT,Texture::RGB8);
	for(int i = 0; i < 2; ++i) textures[i]->setFilter(GL_NEAREST, GL_NEAREST);
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

