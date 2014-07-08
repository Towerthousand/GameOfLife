#include "Player.hpp"
#include "DeferredContainer.hpp"

Player::Player() : cam(nullptr), pos(0.0f), renderer(nullptr) {
	renderer = (DeferredContainer*) getGame()->getObjectByName("deferred");
	model.program = Programs.get("deferredModel");
	model.mesh = Meshes.get("monkey");
	cam = new Camera("playerCam",vec3f(0,0,20));
	cam->projection = glm::perspective(60.0f, float(Environment::getScreen()->getWidth())/float(Environment::getScreen()->getHeight()), 0.1f, 10000.0f);
	cam->addTo(this);
}

Player::~Player() {
}

void Player::update(float deltaTime) {
	(void) deltaTime;
	transform = glm::translate(mat4f(1.0f), pos);
}

void Player::draw() const {
	if(renderer->getMode() != DeferredContainer::Deferred) return;
	model.program->uniform("MVP")->set(cam->projection*cam->getView()*glm::scale(glm::rotate(fullTransform,360*float(sin(Environment::getClock())),vec3f(0,1,0)), vec3f(5.0f)));
	model.program->uniform("M")->set(glm::scale(glm::rotate(fullTransform,360*float(sin(Environment::getClock())),vec3f(0,1,0)), vec3f(5.0f)));
	model.program->uniform("V")->set(cam->getView());
	model.program->uniform("ambient")->set(0.1f);
	model.program->uniform("specular")->set(1.0f);
	model.program->uniform("diffuseTex")->set(Textures2D.get("nullWhite"));
	model.draw();
}
