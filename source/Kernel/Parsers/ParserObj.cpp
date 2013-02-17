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

	stringstream stream(file);

	Resource& r = ResourcesManager::getInstance()->getResource(file);
	stream << string(r.getData());

	if (stream.bad()) {
		Logger::getInstance()->error("Error loading the Modelfile: " + file);
		throw "Error loading the Obj file: " + file;
	}

	string line;
	string token;
	while (!stream.eof()) {
		getline(stream, line);
		stream >> token;

		if (token == "v") { // Vertex
			MAOVector3 v;
			stream >> v.x;
			stream >> v.y;
			stream >> v.z;
		} else if (token == "vt") { // Vertex texture
			MAOVector2 vt;
			stream >> vt.x;
			stream >> vt.y;
		} else if (token == "vn") { // Vertex normal
			MAOVector3 vn;
			stream >> vn.x;
			stream >> vn.y;
			stream >> vn.z;
		} else {
			Logger::getInstance()->warning(
					"[ParserObj] Token not supported: " + token);
		}

	}

}

ParserObj::~ParserObj() {
}

