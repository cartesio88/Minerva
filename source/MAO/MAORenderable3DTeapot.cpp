/*
 * MAORenderable3DTeacup.cpp
 *
 *  Created on: 21/02/2011
 *      Author: cesar
 */

#include "MAORenderable3DTeapot.h"

MAORenderable3DTeapot::MAORenderable3DTeapot(const std::string& name,
		const float& size) :
	MAORenderable3D(name, size) {
	_type = T_MAORENDERABLE3DTEAPOT;

}

MAORenderable3DTeapot::MAORenderable3DTeapot(const MAORenderable3DTeapot& o) :
	MAORenderable3D(o) {
	_type = o._type;
}

void MAORenderable3DTeapot::generateCollisionShape(int type) {
	switch (type) {
	case MAO_BOX_SHAPE:{
		float s = getSize();
		_collisionShape = new btBoxShape(btVector3(s, s, s));
		_collisionShapeType = MAO_BOX_SHAPE;
		break;
	}
	case MAO_SPHERE_SHAPE:
		Logger::getInstance()->error(
				"Sphere Collision Shape not defined for Teapots! Bye!");
		throw "Sphere Collision Shape not defined for Teapots! Bye!";
		break;
	case MAO_CYLINDER_SHAPE:
		Logger::getInstance()->error(
				"Cylinder Collision Shape not defined for Teapots! Bye!");
		throw "Cylinder Collision Shape not defined for Teapots! Bye!";

		break;
	case MAO_CONVEXTRIANGLEMESH_SHAPE:
		Logger::getInstance()->error(
				"Triangle Mesh Collision Shape not defined for Teapots! Bye!");
		throw "Triangle Mesh Collision Shape not defined for Teapots! Bye!";
		break;
	}
}

void MAORenderable3DTeapot::drawGeometryWithoutTexture(){
	drawGeometryWithTexture();
}

void MAORenderable3DTeapot::drawGeometryWithTexture() {
	glutSolidTeapot(getSize());

}

MAORenderable3DTeapot::~MAORenderable3DTeapot() {
}

