#include "SimScreen.hpp"
#include "MotionBlurContainer.hpp"
#include "Simulation.hpp"

SimScreen::SimScreen() : pos(0.0f), renderer(nullptr), sim(nullptr) {
	renderer = (MotionBlurContainer*) getGame()->getObjectByName("deferred");
	sim = new Simulation("data/inputs/accornglider.png");
	sim->addTo(this);
	model.program = Programs.get("textured");
	model.mesh = Meshes.get("quad");
}

SimScreen::~SimScreen() {
}

void SimScreen::update(float deltaTime) {
	(void) deltaTime;
	if(sim->getCurrentFrame() < sim->NUM_FRAMES-1) sim->setFrame(sim->getCurrentFrame()+1);
	transform = glm::translate(mat4f(1.0f), pos);
	float ratio = float(sim->getSimTex()->getWidth())/float(sim->getSimTex()->getHeight());
	transform = glm::scale(transform, vec3f(ratio*10.0f,10.0f,10.0f));
}

void SimScreen::draw() const {
	Camera* cam = (Camera*)getGame()->getObjectByName("playerCam");
	model.program->uniform("MVP")->set(cam->projection*cam->getView()*fullTransform);
	model.program->uniform("diffuse")->set(sim->getSimTex());
	model.draw();
}
