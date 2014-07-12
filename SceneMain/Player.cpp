#include "Player.hpp"
#include "DeferredContainer.hpp"

Player::Player() : cam(nullptr), pos(0.0f) {
	cam = new Camera("playerCam",vec3f(0,0,20));
	cam->projection = glm::perspective(60.0f, float(Environment::getScreen()->getWidth())/float(Environment::getScreen()->getHeight()), 0.1f, 10000.0f);
	cam->addTo(this);
}

Player::~Player() {
}

void Player::update(float deltaTime) {
	float vel = 10.0f;
	if(Environment::getKeyboard()->isKeyHeld(Keyboard::A)) pos.x -= vel*deltaTime;
	if(Environment::getKeyboard()->isKeyHeld(Keyboard::D)) pos.x += vel*deltaTime;
	if(Environment::getKeyboard()->isKeyHeld(Keyboard::W)) pos.y += vel*deltaTime;
	if(Environment::getKeyboard()->isKeyHeld(Keyboard::S)) pos.y -= vel*deltaTime;
	if(Environment::getKeyboard()->isKeyHeld(Keyboard::LShift)) pos.z += vel*deltaTime;
	if(Environment::getKeyboard()->isKeyHeld(Keyboard::Space)) pos.z -= vel*deltaTime;
	transform = glm::translate(mat4f(1.0f), pos);
	transform = glm::rotate(transform,0.0f,vec3f(1,0,0));
}
