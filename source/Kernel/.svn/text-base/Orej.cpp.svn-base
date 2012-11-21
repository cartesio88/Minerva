/*
 * Orej.cpp
 *
 *  Created on: 02/04/2011
 *      Author: cesar
 */

#include "Orej.h"

Orej::Orej(std::string& pathOrej, std::string& pathTex, float scale) {
	_pathOrej = pathOrej;
	_pathTex = pathTex;
	_scale = scale;
	_playingAnim = false;
	_currentFrame = 0;
	_animDirection = 1;
	_hasTexture = true;

	loadTexture();
	loadModel();

}

Orej::Orej(const Orej& o) {
	_pathOrej = o._pathOrej;
	_pathTex = o._pathTex;
	_scale = o._scale;
	_playingAnim = o._playingAnim;
	_currentFrame = o._currentFrame;
	_animDirection = o._animDirection;
	_textureId = o._textureId;
	_vertex = o._vertex;
	_faces = o._faces;
	_nFaces = o._nFaces;
	_nVertex = o._nVertex;
	_nFrames = o._nFrames;
	_listMesh = o._listMesh;
	_texHeight = o._texHeight;
	_animType = o._animType;
	_collisionShape = o._collisionShape;
	_animMatrix = o._animMatrix;
	_hasTexture = o._hasTexture;
}

void Orej::loadTexture() {
	SDL_Surface* img = NULL;
	GLenum textureFormat;

	if(_pathTex==""){
	  _hasTexture = false;
	  return;
	}

	//boost::filesystem::path bPath = boost::filesystem::path(_pathTex);

	img = IMG_Load(_pathTex.c_str());

	if (img == NULL) {
		Logger::getInstance()->error("Error Loading the texture: " + _pathTex);
		Logger::getInstance()->error(IMG_GetError());
		throw "Error Loading the texture: " + _pathTex;
	}

	_texHeight = img->h;


	switch (img->format->BytesPerPixel) {
	case 4: //With alpha channel
		if (img->format->Rmask == 0x000000ff) {
			textureFormat = GL_RGBA;
		} else {
			textureFormat = GL_BGRA;
		}
		break;

	case 3: // Without alpha channel
		if (img->format->Rmask == 0x000000ff) {
			textureFormat = GL_RGB;
		} else {
			textureFormat = GL_BGR;
		}
		break;
	default:
		Logger::getInstance()->error(
				"Error determining the texture format. Bytes per pixel: "
						+ img->format->BitsPerPixel);
	}

	glGenTextures(1, &_textureId);


	if (_textureId == GL_INVALID_OPERATION) {
		Logger::getInstance()->error("Error processing an OreJ texture");
		throw "Error processing an OreJ texture";
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, img->format->BytesPerPixel, img->w, img->h,
			0, textureFormat, GL_UNSIGNED_BYTE, img->pixels);

	SDL_FreeSurface(img);
}

void Orej::loadModel() {
	std::ifstream file;
	int nLine = 0;
	char line[256];
	int iVertex = 0;
	int iFaces = 0;
	int iFrames = 0;
	int iUV = 0;
	float a, b, c, d, e, f;


	//boost::filesystem::path bPath = boost::filesystem::path(_pathOrej);

	file.open(_pathOrej.c_str());

	if (file.bad()) {
		Logger::getInstance()->error("Error loading the OreJ file: "
				+ _pathOrej);
		throw "Error loading the OreJ file: "+ _pathOrej;
	}

	while (!file.eof()) {
		file.getline(line, 256);
		nLine++;

		switch (line[0]) {
		case '#':
			break;
		case 'f': {
			_faces.push_back(Face());
			a = b = c = d = -1;
			sscanf(&line[2], "%f %f %f", &a, &b, &c);

			if (a < 0 || b < 0 || c < 0) {
				Logger::getInstance()->error("Format error in OreJ! Line: "
						+ nLine);
				throw "Format error in OreJ! Line: "+ nLine;
			}

			_faces.at(iFaces).vertex[0] = &_vertex[(int) --a];
			_faces.at(iFaces).vertex[1] = &_vertex[(int) --b];
			_faces.at(iFaces).vertex[2] = &_vertex[(int) --c];

			iFaces++;
			break;
		}
		case 'v': {
			_vertex.push_back(Vector3());
			sscanf(&line[2], "%f %f %f", &_vertex.at(iVertex).x, &_vertex.at(
					iVertex).y, &_vertex.at(iVertex).z);

			_vertex.at(iVertex).x *= _scale;
			_vertex.at(iVertex).y *= _scale;
			_vertex.at(iVertex).z *= _scale;

			iVertex++;
			break;
		}
		case 't':
			a = b = c = d = e = f = -1;
			if (iUV > iFaces) {
				Logger::getInstance()->error(
						"UV value not associated to any face!");
				throw "UV value not associated to any face!";
			}
			sscanf(&line[2], "%f %f %f %f %f %f", &a, &b, &c, &d, &e, &f);
			_faces[iUV].uv[0].x = a;
			_faces[iUV].uv[0].y = b;
			_faces[iUV].uv[1].x = c;
			_faces[iUV].uv[1].y = d;
			_faces[iUV].uv[2].x = e;
			_faces[iUV].uv[2].y = f;

			if (a < 0 || b < 0 || c < 0 || d < 0 || e < 0 || f < 0) {
				Logger::getInstance()->error("Invalid UV value!");
				throw "Invalid UV value!";
			}

			iUV++;
			break;

			break;
		case 'm':

		{
			float* m = new float[16];
			sscanf(&line[2], "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
					&m[0], &m[1], &m[2], &m[3], &m[4], &m[5], &m[6], &m[7],
					&m[8], &m[9], &m[10], &m[11], &m[12], &m[13], &m[14],
					&m[15]);
			_animMatrix.push_back(m);
		}
			iFrames++;

			break;
		default:
			break;
		}
	}

	_nFaces = iFaces;
	_nVertex = iVertex;
	_nFrames = iFrames;

	file.close();

	_listMesh = glGenLists(1);

	glNewList(_listMesh, GL_COMPILE);

	/* Here is where is fixed the "Origin problem"
	 * OpenGl uses a bottom-left and Blender uses an upper-left origin!
	 */

	for (int i = 0; i < _nFaces; i++) {
		glBegin( GL_TRIANGLES);
		glTexCoord2f(_faces.at(i).uv[2].x, _texHeight - _faces.at(i).uv[2].y);
		glVertex3f(_faces.at(i).vertex[0]->x, _faces.at(i).vertex[0]->y,
				_faces.at(i).vertex[0]->z);

		glTexCoord2f(_faces.at(i).uv[1].x, _texHeight - _faces.at(i).uv[1].y);
		glVertex3f(_faces.at(i).vertex[1]->x, _faces.at(i).vertex[1]->y,
				_faces.at(i).vertex[1]->z);

		glTexCoord2f(_faces.at(i).uv[0].x, _texHeight - _faces.at(i).uv[0].y);
		glVertex3f(_faces.at(i).vertex[2]->x, _faces.at(i).vertex[2]->y,
				_faces.at(i).vertex[2]->z);

		glEnd();
	}
	glEndList();

	if (_nFrames == 0) {
		Logger::getInstance()->warning(
				"There is 0 frames for the OreJ. This may incquiry problems!");
	}


}

btCollisionShape* Orej::getCollisionShape() {
	return _collisionShape;
}

void Orej::generateBoxShape() {
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
void Orej::generateConvexTriangleMeshShape() {
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

void Orej::generateCylinderShape() {
	Logger::getInstance()->error(
			"Generating Cylinder Shapes from Orej's not implemented yet!!");
	throw "Generating Cylinder Shapes from Orej's not implemented yet!!";

}
void Orej::generateSphereShape() {
	Logger::getInstance()->error(
			"Generating Sphere Shapes from Orej's not implemented yet!!");
	throw "Generating Sphere Shapes from Orej's not implemented yet!!";
}

void Orej::drawGeometryWithTexture(){
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

void Orej::drawGeometryWithoutTexture() {
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

void Orej::playAnim(int animType) {
	if (!_playingAnim) {
		_playingAnim = true;
	}
}

void Orej::pauseAnim() {
	if (_playingAnim) {
		_playingAnim = false;
	}
}

void Orej::stopAnim() {
	if (_playingAnim) {
		_playingAnim = false;
	}
	_currentFrame = 0;
	_animDirection = 1;
}

Orej::~Orej() {
	/*TODO Implementar bien el destructor OreJ */
	//Delete the anim matrix

	//for (unsigned int i = 0; i < _animMatrix.size(); i++) {
	//float* m = _animMatrix.at(i);
	//delete m;
	//}

}
