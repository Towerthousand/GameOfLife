#include "SimScreen.hpp"
#include "DeferredContainer.hpp"
#include "Simulation.hpp"

SimScreen::SimScreen() : pos(0.0f), renderer(nullptr), sim(nullptr) {
	renderer = (DeferredContainer*) getGame()->getObjectByName("deferred");
	sim = new Simulation(100,100);
	sim->addTo(this);
	model.program = Programs.get("simDeferred");
	model.mesh = Meshes.get("quad");
}

SimScreen::~SimScreen() {
}

void SimScreen::update(float deltaTime) {
	(void) deltaTime;
	transform = glm::translate(mat4f(1.0f), pos);
	transform = glm::scale(transform, vec3f(5.0f));
}

void SimScreen::draw() const {
	Camera* cam = (Camera*)getGame()->getObjectByName("playerCam");
	if(renderer->getMode() != DeferredContainer::Deferred) return;
	model.program->uniform("MVP")->set(cam->projection*cam->getView()*fullTransform);
	model.program->uniform("M")->set(fullTransform);
	model.program->uniform("V")->set(cam->getView());
	model.program->uniform("ambient")->set(0.1f);
	model.program->uniform("specular")->set(1.0f);
	model.program->uniform("diffuseTex")->set(Textures2D.get("nullWhite"));
	model.program->uniform("simTex")->set(sim->getSimTex());
	model.draw();
}
