#ifndef SIMULATION_HPP
#define SIMULATION_HPP
#include "commons.hpp"

class Simulation : public GameObject {
	public:
		Simulation(std::string inputFile);
		~Simulation();

		void update(float deltaTime);
		Texture2D* getSimTex();

	private:
		Model model;
		RenderTarget* simTarget;
		int WIDTH;
		int HEIGHT;
		Texture2D* textures[2];
		int current;
};

#endif // SIMULATION_HPP
