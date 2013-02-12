/*
 * MAORenderable3DModel.cpp
 *
 *  Created on: 04/02/2013
 *      Author: cesar
 */

#include <MAO/MAORenderable3DModel.h>

MAORenderable3DModel::MAORenderable3DModel(const std::string& name,
		const std::string& file, float size): MAORenderable3D(name, size), _file(file) {
	_playingAnim = false;
	_currentFrame = 0;
	_animDirection = 1;
	_hasTexture = true;

	_type = T_MAORENDERABLE3DMODEL;
}


btCollisionShape* MAORenderable3DModel::getCollisionShape() {
	return _collisionShape;
}

void MAORenderable3DModel::generateCollisionShape(int type) {
  if(_collisionShape==NULL){
	switch (type) {
	case MAO_BOX_SHAPE:
		generateBoxShape();
		setBoxShape(getCollisionShape());
		break;
	case MAO_SPHERE_SHAPE:
		generateSphereShape();
		setSphereShape(getCollisionShape());
		break;
	case MAO_CYLINDER_SHAPE:
		generateCylinderShape();
		setCylinderShape(getCollisionShape());
		break;

		break;
	case MAO_CONVEXTRIANGLEMESH_SHAPE:
		generateConvexTriangleMeshShape();
		setConvexTriangleMeshShape(getCollisionShape());
		break;

		break;
	default:
	  Logger::getInstance()->warning("MAO has not defined a Collision Shape type: "+getName());
	  break;
	}
  }
}

void MAORenderable3DModel::generateBoxShape() {
	//For box shape ;)
	float x[] = { 100, -100 };
	float y[] = { 100, -100 };
	float z[] = { 100, -100 };

	for (unsigned int i = 0; i < _vertex.size(); i++) {
		float& vx = _vertex.at(i).x;
		float& vy = _vertex.at(i).y;
		float& vz = _vertex.at(i).z;

		//Box Shapes
		if (vx < x[0])
			x[0] = vx;
		else if (vx > x[1])
			x[1] = vx;

		if (vy < y[0])
			y[0] = vy;
		else if (vy > y[1])
			y[1] = vy;

		if (vz < z[0])
			z[0] = vz;
		else if (vz > z[1])
			z[1] = vz;

		_collisionShape = new btBoxShape(btVector3((x[1] - x[0]) / 2, (y[1]
				- y[0]) / 2, (z[1] - z[0]) / 2));
	}
}
void MAORenderable3DModel::generateConvexTriangleMeshShape() {
  /*btTriangleMesh* triangleMesh = new btTriangleMesh(true, false);
  //triangleMesh->m_weldingThresold = 0.0f; // Test here
	for (unsigned int i = 0; i < _faces.size(); i++) {
		//To build the triangle mesh shape
		btVector3 v1(_faces.at(i).vertex[0]->x, _faces.at(i).vertex[0]->y, _faces.at(i).vertex[0]->z);
		btVector3 v2(_faces.at(i).vertex[1]->x, _faces.at(i).vertex[1]->y, _faces.at(i).vertex[1]->z);
		btVector3 v3(_faces.at(i).vertex[2]->x, _faces.at(i).vertex[2]->y, _faces.at(i).vertex[2]->z);

		triangleMesh->addTriangle(v1, v2, v3, true);
	}

	_collisionShape = new btBvhTriangleMeshShape(triangleMesh, true);
	((btBvhTriangleMeshShape*)_collisionShape)->recalcLocalAabb();*/

  btConvexHullShape* ch = new btConvexHullShape();
  ch->setMargin(btScalar(0.005f));
  for(unsigned int i=0;i<_vertex.size();i++){
    ((btConvexHullShape*)ch)->addPoint(btVector3(_vertex.at(i).x,_vertex.at(i).y,_vertex.at(i).z));
  }

  _collisionShape = ch;
  /*btTransform t;
  t.setOrigin(btVector3(0,0,0.5));
  ((btCompoundShape*)_collisionShape)->addChildShape(t,ch);
  ((btCompoundShape*)_collisionShape)*/

}

void MAORenderable3DModel::generateCylinderShape() {
	Logger::getInstance()->error(
			"Generating Cylinder Shapes for Models is not implemented yet!!");
	throw "Generating Cylinder Shapes from Models is not implemented yet!!";

}
void MAORenderable3DModel::generateSphereShape() {
	Logger::getInstance()->error(
			"Generating Sphere Shapes from Models is not implemented yet!!");
	throw "Generating Sphere Shapes from Models is not implemented yet!!";
}

void MAORenderable3DModel::drawGeometryWithTexture(){
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	//if(_hasTexture){
	  glBindTexture(GL_TEXTURE_2D, _textureId);
	  //}else{
	  //glColor3f(1.0,0.0,0.0);
	  //}
	glPolygonMode(GL_FRONT, GL_FILL);

	drawGeometryWithoutTexture();

	glDisable(GL_TEXTURE_2D);
	//glClear(GL_COLOR_BUFFER_BIT);
}

void MAORenderable3DModel::drawGeometryWithoutTexture() {
	glPushMatrix();

	//Refresh anim!
	glMultMatrixf(_animMatrix.at(_currentFrame));
	if (_playingAnim) {
		_currentFrame += _animDirection;
		if (_currentFrame == (_nFrames - 1)) {
			switch (_animType) {
			case SIMPLE:
				stopAnim();
				break;
			case LOOP:
				_currentFrame = 0;
				break;
			case PINGPONG:
				_animDirection *= -1;
				break;
			}
		}

		//For Ping-Pong mode!
		if (_currentFrame == -1) {
			_animDirection *= -1;
		}
	}

	glCallList(_listMesh);
	glPopMatrix();
}

void MAORenderable3DModel::playAnim(int animType) {
	if (!_playingAnim) {
		_playingAnim = true;
	}
}

void MAORenderable3DModel::pauseAnim() {
	if (_playingAnim) {
		_playingAnim = false;
	}
}

void MAORenderable3DModel::stopAnim() {
	if (_playingAnim) {
		_playingAnim = false;
	}
	_currentFrame = 0;
	_animDirection = 1;
}

MAORenderable3DModel::~MAORenderable3DModel() {

}

