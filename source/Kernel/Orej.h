/*
 * Orej.h
 *
 *  Created on: 02/04/2011
 *      Author: cesar
 */
/*
 * This is a Re-Write version of the OreJ importer
 * made by César Mora for The-Minerva Project!
 *
 */

#ifndef OREJ_H_
#define OREJ_H_

#include <iostream>
#include <fstream>

#ifdef WIN32
#include <windows.h>
#define GL_BGRA 0x80E1
#define GL_BGR 0x80E0
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.h>
//#include <boost/filesystem.hpp>

#include <Kernel/Logger.h>

//Defining the Animation Types!
#define SIMPLE 0
#define LOOP 1
#define PINGPONG 2

struct Vector3{
	float x,y,z;
};

struct Vector2{
	float x,y;
};

struct Face{
	Vector3* vertex[3];
	Vector2 uv[3];
	Vector3 normal;
};

class Orej {
public:
	Orej(std::string& pathOrej, std::string& pathTex, float scale = 1.);
	Orej(const Orej& o);
	virtual ~Orej();
	void drawGeometryWithTexture();
	void drawGeometryWithoutTexture();

	btCollisionShape* getCollisionShape();
	void generateBoxShape();
	void generateConvexTriangleMeshShape();
	void generateCylinderShape();
	void generateSphereShape();


	void playAnim(int animType = 0);
	void stopAnim();
	void pauseAnim();

private:
	std::string _pathOrej;
	std::string _pathTex;
	float _scale;
	GLuint _textureId;
	std::vector<Vector3> _vertex;
	std::vector<Face> _faces;
	std::vector<float*> _animMatrix;
	int _nFaces, _nVertex, _nFrames;
	int _currentFrame;
	GLuint _listMesh;
	int _texHeight;
	int _animType;
	int _playingAnim;
	int _animDirection;
	btCollisionShape* _collisionShape;
	bool _hasTexture;

	void loadModel();
	void loadTexture();



};

#endif /* OREJ_H_ */
