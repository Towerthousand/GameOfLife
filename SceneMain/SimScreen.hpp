#ifndef SIMSCREEN_HPP
#define SIMSCREEN_HPP
#include "commons.hpp"

class Simulation;
class MotionBlurContainer;
class SimScreen : public GameObject
{
	public:
		SimScreen();
		~SimScreen();

		void update(float deltaTime);
		void draw() const;

	private:
		Model model;
		vec3f pos;
		MotionBlurContainer* renderer;
		Simulation* sim;
};

#endif // SIMSCREEN_HPP
