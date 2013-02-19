/*
 * ResourceFile.cpp
 *
 *  Created on: 12/02/2013
 *      Author: cesar
 */

#include <Kernel/Resources/ResourceFile.h>

using namespace std;

ResourceFile::ResourceFile(const boost::filesystem::path& uri) :
		Resource(uri) {
	load();
}

void ResourceFile::load() {
	if (isOpened()) {
		Logger::getInstance()->warning(
				"[ResourceFile] The resource " + _uri.generic_string() + " is already opened.");
		return;
	}

	Logger::getInstance()->out(
			"[ResourceFile] Looking for the resource " + _uri.generic_string());

	ifstream file;

	//Logger::getInstance()->out("[ResourceFile] Opening resource " + _uri);

	file.open(_uri.generic_string().c_str(), ios::binary);

	if (!file.is_open()) {
		//Logger::getInstance()->error("[ResourceFile] Error opening the file " + _uri.generic_string());
		_opened = false;
		return;
	}

	// get length of file
	file.seekg(0, ios::end);
	_size = file.tellg();
	file.seekg(0, ios::beg);

	_data = new char[_size];

	_opened = true;

	file.read(_data, _size);
	file.close();
}

ResourceFile::~ResourceFile() {
}

