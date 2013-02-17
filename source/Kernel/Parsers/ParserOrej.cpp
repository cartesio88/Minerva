/*
 * ParserOrej.cpp
 *
 *  Created on: 02/04/2011
 *      Author: cesar
 */

#include <Kernel/Parsers/ParserOrej.h>

using namespace std;

ParserOrej::ParserOrej() {
}

void ParserOrej::loadModel(const std::string& file,
		MAORenderable3DModel& model) {

	model._file = file;

	_loadTexture(file, model);
	_loadGeometry(file, model);
}

void ParserOrej::_loadTexture(const std::string& file,
		MAORenderable3DModel& model) {

	model._texIds.push_back((GLuint) -1);
	model._texHeights.push_back(0);

	// Compatible formats
	string formats[] = { string(".ppm"), string(".tga"), string(".png"), string(
			".jpg") };

	// Get the file format
	int dotPos = file.find_last_of('.');
	string fileTex;

	// Formats supported
	for (int i = 0; i < 4; i++) {
		fileTex = file.substr(0, dotPos) + formats[i];
		if(_loadResourceToTexture(fileTex, model._texIds.back(), model._texHeights.back()))
			break;
	}

}

void ParserOrej::_loadGeometry(const std::string& file,
		MAORenderable3DModel& model) {
	std::stringstream stream;
	int nLine = 0;
	char line[256];
	list<MAOFace>::iterator ptrFace;
	bool processingUV = false;

	Resource& r = ResourcesManager::getInstance()->getResource(file);
	stream << string(r.getData());

	if (stream.bad()) {
		Logger::getInstance()->error("Error loading the Modelfile: " + file);
		throw "Error loading the OreJ file: " + file;
	}

	while (!stream.eof()) {
		stream.getline(line, 256);
		nLine++;

		switch (line[0]) {
		case '#':
			break;
		case 'f': {

			int v1, v2, v3;
			model._faces.push_back(MAOFace());

			sscanf(&line[2], "%d %d %d", &v1, &v2, &v3);

			if (v1 < 0 || v2 < 0 || v3 < 0) {
				Logger::getInstance()->error(
						"Format error in OreJ! Line: " + nLine);
				throw "Format error in OreJ! Line: " + nLine;
			}

			model._faces.back().vertex[0].x = model._vertex[v1 - 1].x;
			model._faces.back().vertex[0].y = model._vertex[v1 - 1].y;
			model._faces.back().vertex[0].z = model._vertex[v1 - 1].z;

			model._faces.back().vertex[1].x = model._vertex[v2 - 1].x;
			model._faces.back().vertex[1].y = model._vertex[v2 - 1].y;
			model._faces.back().vertex[1].z = model._vertex[v2 - 1].z;

			model._faces.back().vertex[2].x = model._vertex[v3 - 1].x;
			model._faces.back().vertex[2].y = model._vertex[v3 - 1].y;
			model._faces.back().vertex[2].z = model._vertex[v3 - 1].z;

			break;
		}
		case 'v': {
			model._vertex.push_back(MAOVector3());
			sscanf(&line[2], "%f %f %f", &model._vertex.back().x,
					&model._vertex.back().y, &model._vertex.back().z);

			model._vertex.back().x *=
					model.getProperty("size").getValue<float>();
			model._vertex.back().y *=
					model.getProperty("size").getValue<float>();
			model._vertex.back().z *=
					model.getProperty("size").getValue<float>();

			break;
		}
		case 't':
			if (!processingUV) { // Start assigning textures
				ptrFace = model._faces.begin();
				processingUV = true;
			}
			MAOVector2 uv[3];

			sscanf(&line[2], "%f %f %f %f %f %f", &uv[0].x, &uv[0].y, &uv[1].x,
					&uv[1].y, &uv[2].x, &uv[2].y);

			ptrFace->uv[0].x = uv[0].x;
			ptrFace->uv[0].y = uv[0].y;
			ptrFace->uv[1].x = uv[1].x;
			ptrFace->uv[1].y = uv[1].y;
			ptrFace->uv[2].x = uv[2].x;
			ptrFace->uv[2].y = uv[2].y;

			ptrFace++;
			break;

		case 'm':
			if(model._anims.size() == 0)
				model._anims.push_back(MAOAnimation());
		{
			float* m = new float[16];
			sscanf(&line[2], "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
					&m[0], &m[1], &m[2], &m[3], &m[4], &m[5], &m[6], &m[7],
					&m[8], &m[9], &m[10], &m[11], &m[12], &m[13], &m[14],
					&m[15]);
			model._anims.back().frames.push_back(m);
		}

			break;

		default:
			break;
		}
	}

	model._listMesh = glGenLists(1);
	glNewList(model._listMesh, GL_COMPILE);

	/* Here is where is fixed the "Origin problem"
	 * OpenGl uses a bottom-left and Blender uses an upper-left origin!
	 */
	list<MAOFace>::iterator facePtr;
	for (facePtr = model._faces.begin(); facePtr != model._faces.end();
			facePtr++) {
		glBegin(GL_TRIANGLES);
		glTexCoord2f(facePtr->uv[2].x, model._texHeights.back() - facePtr->uv[2].y);
		glVertex3f(facePtr->vertex[0].x, facePtr->vertex[0].y,
				facePtr->vertex[0].z);

		glTexCoord2f(facePtr->uv[1].x, model._texHeights.back() - facePtr->uv[1].y);
		glVertex3f(facePtr->vertex[1].x, facePtr->vertex[1].y,
				facePtr->vertex[1].z);

		glTexCoord2f(facePtr->uv[0].x, model._texHeights.back() - facePtr->uv[0].y);
		glVertex3f(facePtr->vertex[2].x, facePtr->vertex[2].y,
				facePtr->vertex[2].z);

		glEnd();
	}
	glEndList();

}

ParserOrej::~ParserOrej() {
}
