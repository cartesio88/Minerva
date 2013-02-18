/*
 * ParserObj.cpp
 *
 *  Created on: 14/02/2013
 *      Author: cesar
 */

#include <Kernel/Parsers/ParserObj.h>

using namespace std;

ParserObj::ParserObj() {
}

void ParserObj::loadModel(const std::string& file,
		MAORenderable3DModel& model) {
	model._file = file;

	stringstream streamFile;

	Resource& r = ResourcesManager::getInstance()->getResource(file);
	streamFile << string(r.getData());

	if (streamFile.bad()) {
		Logger::getInstance()->error("Error loading the Modelfile: " + file);
		throw "Error loading the Obj file: " + file;
	}

	while (!streamFile.eof()) {
		string line;
		getline(streamFile, line);
		stringstream streamLine;
		streamLine << line;

		string symbol;
		streamLine >> symbol;

		if (symbol == "v") { // Vertex
			MAOVector3 v;
			streamLine >> v.x;
			streamLine >> v.y;
			streamLine >> v.z;

			v.x *= model.getProperty("size").getValue<float>();
			v.y *= model.getProperty("size").getValue<float>();
			v.z *= model.getProperty("size").getValue<float>();

			model._vertex.push_back(v);
		} else if (symbol == "vt") { // Vertex texture
			MAOVector2 vt;
			streamLine >> vt.x;
			streamLine >> vt.y;

			model._uv.push_back(vt);
		} else if (symbol == "vn") { // Vertex normal
			MAOVector3 vn;
			streamLine >> vn.x;
			streamLine >> vn.y;
			streamLine >> vn.z;

			model._normals.push_back(vn);
		} else if (symbol == "f") { // Face
			MAOFace f;
			std::string index;

			getline(streamLine, index);
			stringstream streamindex;
			index = index.substr(1); // Removes the first blank

			int v, vt, vn;

			for (int i = 0; i < 3; i++) {
				int pos = index.find(' ');
				string s = index.substr(0, pos);
				index = index.substr(pos + 1);

				_getFaceIndices(s, v, vt, vn);
				if (v > 0) {
					f.vertex[i].x = model._vertex[v - 1].x;
					f.vertex[i].y = model._vertex[v - 1].y;
					f.vertex[i].z = model._vertex[v - 1].z;
				}
				if (vt > 0) {
					f.uv[i].x = model._uv[vt - 1].x;
					f.uv[i].y = model._uv[vt - 1].y;
				}
				if (vn > 0) {
					f.normal[i].x = model._normals[vn - 1].x;
					f.normal[i].y = model._normals[vn - 1].y;
					f.normal[i].z = model._normals[vn - 1].z;
				}
			}
			model._faces.push_back(f);
		} else if (symbol == "mtllib") { // Declaring material
			std::string pwd = file.substr(0, file.find_last_of("/") + 1);
			std::string fname;
			getline(streamLine, fname);
			fname = fname.substr(1, fname.length() - 2); // Remove the first blank, and last character
			string path = pwd + fname;

			ResourcesManager::getInstance()->addResource(path); //MTLIBFILE

			_loadTextureFile(path, model);
		} else if (symbol == "usemtl") { // Using material

		} else if (symbol == "#") { // Comment
			/* Ignore it */
		} else {
			Logger::getInstance()->warning(
					"[ParserObj] Symbol not supported: " + symbol);
		}
	}

	_generateCallList(model);
}

void ParserObj::_loadTextureFile(const std::string& file, MAORenderable3DModel& model) {
	stringstream streamFile;

	Resource& r = ResourcesManager::getInstance()->getResource(file);
	streamFile << string(r.getData());

	if (streamFile.bad()) {
		Logger::getInstance()->error(
				"Error loading the Material lib file: " + file);
		throw "Error loading the Obj file: " + file;
	}

	while (!streamFile.eof()) {
		string line;
		getline(streamFile, line);
		stringstream streamLine;
		streamLine << line;

		string symbol;
		streamLine >> symbol;

		if (symbol == "map_Kd") {
			std::string pwd = file.substr(0, file.find_last_of("/") + 1);
			std::string fname;
			getline(streamLine, fname);
			fname = fname.substr(1, fname.length() - 2); // Remove the first blank, and last character
			string path = pwd + fname;

			model._texIds.push_back((GLuint) -1);
			model._texHeights.push_back(0);

			_loadResourceToTexture(path, model._texIds.back(), model._texHeights.back());

		} else if (symbol == "#") { // Comment
			/* Ignore it */
		} else {
			Logger::getInstance()->warning(
					"[ParserObj] Symbol not supported: " + symbol);
		}
	}
}

void ParserObj::_getFaceIndices(std::string& line, int& v, int& vt, int& vn) {
	v = vt = vn = -1;
	int pos = 0;

	string number;
	pos = line.find("/");
	number = line.substr(0, pos);
	if (number.length() > 0)
		sscanf(number.c_str(), "%d", &v);
	line = line.substr(pos + 1);

	pos = line.find("/");
	number = line.substr(0, pos);
	if (number.length() > 0)
		sscanf(number.c_str(), "%d", &vt);
	line = line.substr(pos + 1);

	pos = line.find("/");
	number = line.substr(0, pos);
	if (number.length() > 0)
		sscanf(number.c_str(), "%d", &vn);
}

ParserObj::~ParserObj() {
}

