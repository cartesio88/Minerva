/*
 * Parser3ds.cpp
 *
 *  Created on: 14/02/2013
 *      Author: cesar
 */

#include <Kernel/Parsers/Parser3ds.h>

Parser3ds::Parser3ds() {
}

void Parser3ds::loadModel(const boost::filesystem::path& file,
		MAORenderable3DModel& model) {

	/* Me myself has to load it :) */
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

	std::istringstream stream(std::string(r.getData()));

	// Aqui esta la miga!
	// Self is the FILE (rdbuf)
	/*typedef Lib3dsBool (*Lib3dsIoErrorFunc)(void *self);
	 typedef long (*Lib3dsIoSeekFunc)(void *self, long offset,
	 Lib3dsIoSeek origin);
	 typedef long (*Lib3dsIoTellFunc)(void *self);
	 typedef size_t (*Lib3dsIoReadFunc)(void *self, void *buffer, size_t size);
	 typedef size_t (*Lib3dsIoWriteFunc)(void *self, const void *buffer,
	 size_t size);
	 */

	io = lib3ds_io_new(stream.rdbuf(), Parser3ds::_IoErrorFunc, _IoSeekFunc,
			_IoTellFunc, _IoReadFunc, _IoWriteFunc);

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

}

Lib3dsBool Parser3ds::_IoErrorFunc(void *self) {
	Logger::getInstance()->error("Error func not implemented");
	return 0 == 0;
}

long Parser3ds::_IoSeekFunc(void *self, long offset, Lib3dsIoSeek origin) {
	Logger::getInstance()->error("Seek func not implemented");
	return 0;
}

long Parser3ds::_IoTellFunc(void *self) {
	Logger::getInstance()->error("Tell func not implemented");
	return 0;
}

size_t Parser3ds::_IoReadFunc(void *self, void *buffer, size_t size) {
	Logger::getInstance()->error("Read func not implemented");
	return 0;
}

size_t Parser3ds::_IoWriteFunc(void *self, const void *buffer, size_t size) {
	Logger::getInstance()->error("Write func not implemented");
	return 0;
}

Parser3ds::~Parser3ds() {
}

