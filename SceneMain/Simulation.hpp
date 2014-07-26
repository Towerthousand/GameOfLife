#ifndef SIMULATION_HPP
#define SIMULATION_HPP
#include "commons.hpp"

class Simulation {
	public:
		Simulation(std::string inputFile);
		~Simulation();

		Texture2D* getSimTex();
		int getCurrentFrame() {return currentFrame;}
		void setFrame(int frame);

		const int NUM_FRAMES = 60;
	private:
		int currentFrame = 0;
		int WIDTH = 0;
        int HEIGHT = 0;
        Texture2D* tex = nullptr;
        unsigned char* data = nullptr;
};

#endif // SIMULATION_HPP
