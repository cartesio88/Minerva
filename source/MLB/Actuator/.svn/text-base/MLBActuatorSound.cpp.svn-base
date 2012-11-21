/*
 * MBLActuatorSound.cpp
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#include "MLBActuatorSound.h"

MLBActuatorSound::MLBActuatorSound(const std::string& name, MAO& parent,
		const std::string& path) :
	MLBActuator(name, parent) {
	_path = path;
	_chunk = NULL;

	_chunk = Mix_LoadWAV(path.c_str());

	if (_chunk == NULL) {
		Logger::getInstance()->error(
				"Error creating MLB Actuator Sound with SDL_Mixer: " + name);
		throw "Error creating MLB Actuator Sound: " + name;
	}

	Mix_VolumeChunk(_chunk, MIX_MAX_VOLUME);
	_mlbType = T_MLBACTUATORSOUND;
}

void MLBActuatorSound::specificActuate() {
	Mix_PlayChannel(-1,_chunk,0);
}

MLBActuatorSound::~MLBActuatorSound() {
	Mix_FreeChunk(_chunk);
}
