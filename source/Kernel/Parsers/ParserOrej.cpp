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
	SDL_Surface* img = NULL;
	GLenum textureFormat;

	// Compatible formats
	string formats[] = { string(".ppm"), string(".tga"), string(".png"), string(
			".jpg") };

	// Get the file format
	int dotPos = file.find_last_of('.');
	string fileTex;

	// Formats supported
	for (int i = 0; i < 4; i++) {
		fileTex = file.substr(0, dotPos) + formats[i];

		try {
			Resource& r = ResourcesManager::getInstance()->getResource(fileTex);

			SDL_RWops *rw = SDL_RWFromMem((void*)r.getData(),r.getSize());
			img = IMG_Load_RW(rw, 1);
			if (img != NULL)
				break;
		} catch (std::string& e) {

		}
	}

	if (img == NULL) {
		Logger::getInstance()->error("Error Loading the texture: " + fileTex);
		Logger::getInstance()->error(IMG_GetError());
		model._hasTexture = false;
		return;
	}

	ResourcesManager::getInstance()->addResource(fileTex);

	model._texHeight = img->h;

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

	glGenTextures(1, &model._textureId);

	if (model._textureId == GL_INVALID_OPERATION) {
		Logger::getInstance()->error("Error processing an OreJ texture");
		throw "Error processing an OreJ texture";
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, model._textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, img->format->BytesPerPixel, img->w, img->h,
			0, textureFormat, GL_UNSIGNED_BYTE, img->pixels);

	SDL_FreeSurface(img);
}

void ParserOrej::_loadGeometry(const std::string& file,
		MAORenderable3DModel& model) {
	std::stringstream stream;
	int nLine = 0;
	char line[256];
	int iVertex = 0;
	int iFrames = 0;
	int iUV = 0;
	float a, b, c, d, e, f;

	Resource& r = ResourcesManager::getInstance()->getResource(file);
	stream<<string(r.getData());

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

			model._faces.push_back(MAOFace());
			a = b = c = d = -1;
			sscanf(&line[2], "%f %f %f", &a, &b, &c);

			if (a < 0 || b < 0 || c < 0) {
				Logger::getInstance()->error(
						"Format error in OreJ! Line: " + nLine);
				throw "Format error in OreJ! Line: " + nLine;
			}

			model._faces.back().vertex[0] = &model._vertex[(int) --a];
			model._faces.back().vertex[1] = &model._vertex[(int) --b];
			model._faces.back().vertex[2] = &model._vertex[(int) --c];

			//iFaces++;
			break;
		}
		case 'v': {
			model._vertex.push_back(Vector3());
			sscanf(&line[2], "%f %f %f", &model._vertex.at(iVertex).x,
					&model._vertex.at(iVertex).y, &model._vertex.at(iVertex).z);

			model._vertex.at(iVertex).x *= model.getProperty("size").getValue<
					float>();
			model._vertex.at(iVertex).y *= model.getProperty("size").getValue<
					float>();
			model._vertex.at(iVertex).z *= model.getProperty("size").getValue<
					float>();

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
			model._faces[iUV].uv[0].x = a;
			model._faces[iUV].uv[0].y = b;
			model._faces[iUV].uv[1].x = c;
			model._faces[iUV].uv[1].y = d;
			model._faces[iUV].uv[2].x = e;
			model._faces[iUV].uv[2].y = f;

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
			model._animMatrix.push_back(m);
		}
			iFrames++;

			break;
		default:
			break;
		}
	}

	model._nFaces = iFaces;
	model._nVertex = iVertex;
	model._nFrames = iFrames;

	model._listMesh = glGenLists(1);

	glNewList(model._listMesh, GL_COMPILE);

	/* Here is where is fixed the "Origin problem"
	 * OpenGl uses a bottom-left and Blender uses an upper-left origin!
	 */

	for (int i = 0; i < model._nFaces; i++) {
		glBegin(GL_TRIANGLES);
		glTexCoord2f(model._faces.at(i).uv[2].x,
				model._texHeight - model._faces.at(i).uv[2].y);
		glVertex3f(model._faces.at(i).vertex[0]->x,
				model._faces.at(i).vertex[0]->y,
				model._faces.at(i).vertex[0]->z);

		glTexCoord2f(model._faces.at(i).uv[1].x,
				model._texHeight - model._faces.at(i).uv[1].y);
		glVertex3f(model._faces.at(i).vertex[1]->x,
				model._faces.at(i).vertex[1]->y,
				model._faces.at(i).vertex[1]->z);

		glTexCoord2f(model._faces.at(i).uv[0].x,
				model._texHeight - model._faces.at(i).uv[0].y);
		glVertex3f(model._faces.at(i).vertex[2]->x,
				model._faces.at(i).vertex[2]->y,
				model._faces.at(i).vertex[2]->z);

		glEnd();
	}
	glEndList();

	if (model._nFrames == 0) {
		Logger::getInstance()->warning(
				"There is 0 frames for the OreJ. This may incquiry problems!");
	}

}

ParserOrej::~ParserOrej() {
}
