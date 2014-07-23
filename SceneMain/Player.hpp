#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "commons.hpp"

class Player : public GameObject {
	public:
		Player();
		~Player();

		void update(float deltaTime);
	private:
		Camera* cam;
		vec3f pos;
};

#endif // PLAYER_HPP
