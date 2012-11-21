/*
 * World.h
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include <opencv/cv.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <Python.h>

#include <MAO/MAORenderable3D.h>
#include <Controllers/PhysicsController.h>
#include <Factories/VideoFactory.h>
#include <Factories/MAOFactory.h>
#include <Kernel/Logger.h>
#include <Kernel/Singleton.h>

class World: public Singleton<World> {
public:
	World();
	virtual ~World();
	void initWorld(int width, int height);
	void drawWorld();

	int getWidth();
	int getHeight();

	SDL_Surface& getScreen();
	void enable2D();
	void disable2D();

private:
	void drawBackground();
	void drawShadows();
	void drawGround();
	SDL_Surface* _screen;
	int _width;
	int _height;
};


#endif /* WORLD_H_ */
