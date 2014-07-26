#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "commons.hpp"

class Player : public GameObject {
	public:
		Player();
		~Player();
	private:
		void update(float deltaTime);

		Camera* cam;
		vec3f pos;
};

#endif // PLAYER_HPP
