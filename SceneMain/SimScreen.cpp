#include "SimScreen.hpp"
#include "DeferredContainer.hpp"
#include "Simulation.hpp"

SimScreen::SimScreen() : pos(0.0f), renderer(nullptr), sim(nullptr) {
	renderer = (DeferredContainer*) getGame()->getObjectByName("deferred");
	sim = new Simulation("data/inputs/accornglider.png");
	sim->addTo(this);
	model.program = Programs.get("deferredModel");
	model.mesh = Meshes.get("quad");
}

SimScreen::~SimScreen() {
}

void SimScreen::update(float deltaTime) {
	(void) deltaTime;
	transform = glm::translate(mat4f(1.0f), pos);
	float ratio = float(sim->getSimTex()->getWidth())/float(sim->getSimTex()->getHeight());
	transform = glm::scale(transform, vec3f(ratio*10.0f,10.0f,10.0f));
}

void SimScreen::draw() const {
	Camera* cam = (Camera*)getGame()->getObjectByName("playerCam");
	if(renderer->getMode() != DeferredContainer::Deferred) return;
	model.program->uniform("MVP")->set(cam->projection*cam->getView()*fullTransform);
	model.program->uniform("M")->set(fullTransform);
	model.program->uniform("V")->set(cam->getView());
	model.program->uniform("ambient")->set(1.0f);
	model.program->uniform("specular")->set(0.0f);
	model.program->uniform("diffuseTex")->set(sim->getSimTex());
	model.draw();
}
