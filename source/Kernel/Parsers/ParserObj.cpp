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

	stringstream streamFile(file);

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
		} else if (symbol == "vt") { // Vertex texture
			MAOVector2 vt;
			streamLine >> vt.x;
			streamLine >> vt.y;
		} else if (symbol == "vn") { // Vertex normal
			MAOVector3 vn;
			streamLine >> vn.x;
			streamLine >> vn.y;
			streamLine >> vn.z;
		} else if (symbol == "f") { // Face
			MAOFace f;
			//streamLine >> vn.x;
			//streamLine >> vn.y;
			//streamLine >> vn.z;
		} else if (symbol == "mtllib") { // Declaring material

		} else if (symbol == "usemtl") { // Using material

		} else if (symbol == "#") { // Comment
			/* Ignore it */
		} else {
			Logger::getInstance()->warning(
					"[ParserObj] Symbol not supported: " + symbol);
		}
	}
}

ParserObj::~ParserObj() {
}

