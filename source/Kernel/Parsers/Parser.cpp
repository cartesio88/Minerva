/*
 * Parser.cpp
 *
 *  Created on: 04/02/2013
 *      Author: cesar
 */

#include <Kernel/Parsers/Parser.h>

Parser::Parser() {
}

bool Parser::_loadResourceToTexture(const std::string& file, GLuint& texId,
		int& texHeight) {
	SDL_Surface* img = NULL;
	SDL_RWops *rw = NULL;
	GLenum textureFormat;

	try {
		Resource& r = ResourcesManager::getInstance()->getResource(file);

		rw = SDL_RWFromMem((void*) r.getData(), r.getSize());
		img = IMG_Load_RW(rw, 1);
	} catch (std::string& e) {
		if (img != NULL)
			SDL_FreeSurface(img);
		return false;
	}

	if (img == NULL) {
		Logger::getInstance()->error("Error Loading the texture: " + file);
		Logger::getInstance()->error(IMG_GetError());
		return false;
	}

	ResourcesManager::getInstance()->addResource(file);

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

	// Create the texture id
	glGenTextures(1, &texId);
	texHeight = img->h;

	if (texId == GL_INVALID_OPERATION) {
		Logger::getInstance()->error("Error processing an OreJ texture");
		throw "Error processing an OreJ texture";
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, img->format->BytesPerPixel, img->w, img->h,
			0, textureFormat, GL_UNSIGNED_BYTE, img->pixels);

	SDL_FreeSurface(img);
	return true;
}

Parser::~Parser() {
}

