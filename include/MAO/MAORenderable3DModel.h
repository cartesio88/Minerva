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

enum AnimType {SIMPLE, LOOP, PINGPONG};

struct MAOAnimation{
	int type;
	bool playing;
	int dir;
	std::vector<float*> frames;
	int currentFrame;

	MAOAnimation(): type(SIMPLE), playing(false), dir(1), currentFrame(0){}
};

struct MAOVector3{
	float x,y,z;

	MAOVector3(): x(0), y(0), z(0) {}
	MAOVector3(float xx, float yy, float zz): x(xx), y(yy), z(zz){}
};

struct MAOVector2{
	float x,y;

	MAOVector2(): x(0), y(0) {}
	MAOVector2(float xx, float yy): x(xx), y(yy){}
};

struct MAOFace{
	MAOVector3 vertex[3];
	MAOVector2 uv[3];
	MAOVector3 normal[3];
};

class MAORenderable3DModel: public MAORenderable3D {
	boost::filesystem::path _file;

	/* Maybe, dont really need them */
	std::vector<MAOVector3> _vertex;
	std::vector<MAOVector2> _uv;
	std::vector<MAOVector3> _normals;
	std::list<MAOFace> _faces;

	std::vector<MAOAnimation> _anims;

	std::vector<int> _texHeights;
	std::vector<GLuint> _texIds;
	GLuint _listMesh;

public:
	friend class Parser;
	friend class ParserOrej;
	friend class ParserObj;
	friend class Parser3ds;

	MAORenderable3DModel(const std::string& name, const boost::filesystem::path& file, float scale = 1.0f);
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
