/*
 * MAORenderable3DModel.h
 *
 *  Created on: 04/02/2013
 *      Author: cesar
 */

#ifndef MAORENDERABLE3DMODEL_H_
#define MAORENDERABLE3DMODEL_H_

#include <MAO/MAORenderable3D.h>


#ifdef WIN32
#include <windows.h>
#define GL_BGRA 0x80E1
#define GL_BGR 0x80E0
#endif


struct MAOVector3{
	float x,y,z;
};

struct MAOVector2{
	float x,y;
};

struct MAOFace{
	MAOVector3 vertex[3];
	MAOVector2 uv[3];
	MAOVector3 normal;
};

enum AnimType {SIMPLE, LOOP, PINGPONG};

class MAORenderable3DModel: public MAORenderable3D {
	std::string _file;

	std::vector<MAOVector3> _vertex;
	std::list<MAOFace> _faces;
	//int _nFaces, _nVertex, _nFrames;



	int _animType;
	int _playingAnim;
	int _animDirection;
	unsigned int _currentFrame;
	std::vector<float*> _anim;

	int _texHeight;
	GLuint _textureId;
	GLuint _listMesh;
	bool _hasTexture;


public:
	friend class ParserOrej;
	friend class ParserObj;

	MAORenderable3DModel(const std::string& name, const std::string& file, float scale = 1.0f);
	virtual ~MAORenderable3DModel();

	void drawGeometryWithTexture();
	void drawGeometryWithoutTexture();

	void generateCollisionShape(int type);

	btCollisionShape* getCollisionShape();
	void generateBoxShape();
	void generateConvexTriangleMeshShape();
	void generateCylinderShape();
	void generateSphereShape();

	void playAnim(int animType = SIMPLE);
	void stopAnim();
	void pauseAnim();
};

#endif /* MAORENDERABLE3DMODEL_H_ */
