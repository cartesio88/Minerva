/*
 * MAORenderable3DOrj.cpp
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#include "MAORenderable3DOrj.h"

MAORenderable3DOrj::MAORenderable3DOrj(const std::string& name, float scale,
		const std::string& pathOrj, const std::string& pathTex) :
	MAORenderable3D(name, scale) {
	_pathOrj = pathOrj;
	_pathTex = pathTex;
	_scale = scale;

	_type = T_MAORENDERABLE3DORJ;

	_orj = new Orej(_pathOrj, _pathTex, _scale);

}

MAORenderable3DOrj::MAORenderable3DOrj(const MAORenderable3DOrj& o) :
	MAORenderable3D(o) {
	_pathOrj = o._pathOrj;
	_pathTex = o._pathTex;
	_scale = o._scale;
	_type = o._type;
	_orj = new Orej(*o._orj);
	//TODO: Para los MAO instanciados se utiliza el MISMO objeto Orej. Si no se quiere esto, cambiarlo en el constructor de copia de MAORenderable3DOrj
	//_orj = o._orj;
}

void MAORenderable3DOrj::generateCollisionShape(int type) {
  if(_collisionShape==NULL){
	switch (type) {
	case MAO_BOX_SHAPE:
		_orj->generateBoxShape();
		setBoxShape(_orj->getCollisionShape());
		break;
	case MAO_SPHERE_SHAPE:
		_orj->generateSphereShape();
		setSphereShape(_orj->getCollisionShape());
		break;
	case MAO_CYLINDER_SHAPE:
		_orj->generateCylinderShape();
		setCylinderShape(_orj->getCollisionShape());
		break;

		break;
	case MAO_CONVEXTRIANGLEMESH_SHAPE:
		_orj->generateConvexTriangleMeshShape();
		setConvexTriangleMeshShape(_orj->getCollisionShape());
		break;

		break;
	default:
	  Logger::getInstance()->warning("MAO has not defined a Collision Shape type: "+getName());
	  break;
	}
  }
}

void MAORenderable3DOrj::drawGeometryWithoutTexture(){
	_orj->drawGeometryWithoutTexture();
}

void MAORenderable3DOrj::drawGeometryWithTexture() {
	_orj->drawGeometryWithTexture();
}

std::string& MAORenderable3DOrj::getPathOrj() {
	return _pathOrj;
}

std::string& MAORenderable3DOrj::getPathTex() {
	return _pathTex;
}

void MAORenderable3DOrj::playAnim(int animType) {
	_orj->playAnim(animType);
}

void MAORenderable3DOrj::pauseAnim() {
	_orj->pauseAnim();
}

void MAORenderable3DOrj::stopAnim() {
	_orj->stopAnim();
}

MAORenderable3DOrj::~MAORenderable3DOrj() {
	//TODO Cuidar estos constructores! Quién elimina objetos compartidos si nadie sabe quién es el papi!!
	//delete _orj;
}
