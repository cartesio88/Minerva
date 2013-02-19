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

	/* Load textures */
	// TODO
	/* Load Geometry */
	for (Lib3dsMesh* m = file3ds->meshes; m != NULL; m = m->next) {
		/* It is necessary to calculate the normals */
		Lib3dsVector normals[m->faces * 3];
		lib3ds_mesh_calculate_normals(m, normals);

		/* Vertex list */
		cout << "Number of vertex: " << m->points << endl;
		for (unsigned int i = 0; i < m->points; i++) {
			Lib3dsPoint v = m->pointL[i];

			MAOVector3 mv(v.pos[0], v.pos[1], v.pos[2]);
			model._vertex.push_back(mv);
		}

		/* UV list */
		cout << "Number of uvs: " << m->texels << endl;
		for (unsigned int i = 0; i < m->texels; i++) {
			float u = m->texelL[2 * i][0];
			float v = m->texelL[2 * i][1];

			MAOVector2 uv(u, v);
			model._uv.push_back(uv);
		}

		/* Normals */
		cout << "Number of normals: " << (m->faces * 3) << endl;
		for (unsigned int i = 0; i < m->faces; i++) {
			float nx = normals[3 * i][0];
			float ny = normals[3 * i][1];
			float nz = normals[3 * i][2];

			MAOVector3 n(nx, ny, nz);
			model._normals.push_back(n);
		}

		/* Faces list */
		cout << "Number of faces: " << m->faces << endl;
		for (unsigned int i = 0; i < m->faces; i++) {
			Lib3dsFace f = m->faceL[i];

			MAOFace mf;

			for (int j = 0; j < 3; j++) {
				mf.vertex[j].x = model._vertex.at(f.points[j]).x;
				mf.vertex[j].y = model._vertex.at(f.points[j]).y;
				mf.vertex[j].z = model._vertex.at(f.points[j]).z;

				mf.uv[j].x = model._uv.at(f.points[j]).x;
				mf.uv[j].y = model._uv.at(f.points[j]).y;

				mf.normal[j].x = normals[i*3 + j][0];
				mf.normal[j].y = normals[i*3 + j][1];
				mf.normal[j].z = normals[i*3 + j][2];
			}

			model._faces.push_back(mf);
		}

	}

	/* Load animation */

	// Dont forget to free it
	lib3ds_file_free(file3ds);

	_generateCallList(model);
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

