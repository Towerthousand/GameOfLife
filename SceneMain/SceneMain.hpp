#ifndef SCENEMAIN_HPP
#define SCENEMAIN_HPP
#include "commons.hpp"

class SceneMain : public GameObject {
	public:
		SceneMain();
		~SceneMain();

	private:
		void update(float deltaTime);
		void loadResources();

		float debugCounter;
		int fpsCount;
		SoundBuffer sb;
		Sound s;
};

#endif // SCENEMAIN_HPP
