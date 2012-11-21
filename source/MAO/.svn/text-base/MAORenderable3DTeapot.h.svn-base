/*
 * MAORenderable3DTeacup.h
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#ifndef MAORENDERABLETEAPOT_H_
#define MAORENDERABLETEAPOT_H_

#include <string>
#include <MAO/MAORenderable3D.h>

#include <GL/glut.h>

class MAORenderable3DTeapot: public MAORenderable3D {
public:
	MAORenderable3DTeapot(const std::string& name, const float& size);
	MAORenderable3DTeapot(const MAORenderable3DTeapot& o);
	virtual ~MAORenderable3DTeapot();

	void generateCollisionShape(int type);

	void drawGeometryWithTexture();
	void drawGeometryWithoutTexture();
protected:

};

#endif /* MAORENDERABLETEAPOT_H_ */
