/*
 * Parser3ds.cpp
 *
 *  Created on: 14/02/2013
 *      Author: cesar
 */

#include <Kernel/Parsers/Parser3ds.h>

using namespace std;

Parser3ds::Parser3ds() {
}

void Parser3ds::loadModel(const boost::filesystem::path& file,
		MAORenderable3DModel& model) {

	Lib3dsFile *file3ds;
	file3ds = _load3dsFile(file);

	int nMeshes = 0;
	for (Lib3dsMesh* m = file3ds->meshes; m != NULL; m = m->next)
		nMeshes++;
	// Load the geometry!
	cout << "There are meshes: " << nMeshes << endl;

	// Maybe at the end?
	lib3ds_file_free(file3ds);
}

Lib3dsFile* Parser3ds::_load3dsFile(const boost::filesystem::path& file) {
	Lib3dsFile *file3ds;
	Lib3dsIo *io;

	Resource& r = ResourcesManager::getInstance()->getResource(file);

	file3ds = lib3ds_file_new();
	if (!file3ds) {
		Logger::getInstance()->error(
				"[Parser3ds] Error loading the 3ds file "
						+ file.generic_string());
		exit(-1);
	}

	std::istringstream stream(string(r.getData(), r.getSize()));

	io = lib3ds_io_new(&stream, Parser3ds::_IoErrorFunc, _IoSeekFunc,
			_IoTellFunc, _IoReadFunc, NULL);

	if (!io) {
		lib3ds_file_free(file3ds);
		Logger::getInstance()->error(
				"[Parser3ds] Error creating the 3ds buffer "
						+ file.generic_string());
		exit(-1);
	}

	if (!lib3ds_file_read(file3ds, io)) {
		delete file3ds;
		lib3ds_io_free(io);
		Logger::getInstance()->error(
				"[Parser3ds] Error reading the 3ds buffer "
						+ file.generic_string());
		exit(-1);
	}

	lib3ds_io_free(io);

	return file3ds;
}

Lib3dsBool Parser3ds::_IoErrorFunc(void *self) {
	stringstream *s = (stringstream*) self;

	return s->bad();
}

long Parser3ds::_IoSeekFunc(void *self, long offset, Lib3dsIoSeek origin) {
	stringstream *s = (stringstream*) self;

	ios_base::seekdir o;
	switch (origin) {
	case LIB3DS_SEEK_SET:
		o = ios_base::beg;
		break;
	case LIB3DS_SEEK_CUR:
		o = ios_base::cur;
		break;
	case LIB3DS_SEEK_END:
		o = ios_base::end;
		break;
	default:
		Logger::getInstance()->error("[Parser3ds] Error in SEEK function");
		return (0);
	}

	s->seekg(offset, o);

	return s->bad();
}

long Parser3ds::_IoTellFunc(void *self) {
	stringstream *s = (stringstream*) self;

	return s->tellg();
}

size_t Parser3ds::_IoReadFunc(void *self, void *buffer, size_t size) {
	stringstream *s = (stringstream*) self;

	s->read((char*) buffer, size);

	return s->gcount();
}

Parser3ds::~Parser3ds() {
}

