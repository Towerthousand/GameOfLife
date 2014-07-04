#include "Player.hpp"
#include "DeferredContainer.hpp"

Player::Player() : cam(nullptr), pos(0.0f), renderer(nullptr) {
	renderer = (DeferredContainer*) getGame()->getObjectByName("deferred");
	model.program = Programs.get("deferredModel");
	model.mesh = Meshes.get("quad");
	cam = new Camera("playerCam",vec3f(0,0,20));
	cam->projection = glm::perspective(60.0f, float(Environment::getScreen()->getWidth())/float(Environment::getScreen()->getHeight()), 0.1f, 10000.0f);
	cam->addTo(this);
}

Player::~Player() {
}

void Player::update(float deltaTime) {
	float vel = 30.0f;
	transform = glm::translate(mat4f(1.0f), pos);
}

void Player::draw() const {
	if(renderer->getMode() != DeferredContainer::Deferred) return;
	model.program->uniform("MVP")->set(cam->projection*cam->getView()*glm::scale(fullTransform, vec3f(0.1f)));
	model.program->uniform("M")->set(fullTransform);
	model.program->uniform("V")->set(cam->getView());
	model.program->uniform("ambient")->set(0.5f);
	model.program->uniform("specular")->set(1.0f);
	model.program->uniform("diffuseTex")->set(Textures2D.get("nullGreen"));
	model.draw();
}