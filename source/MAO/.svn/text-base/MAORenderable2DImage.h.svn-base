/*
 * MAORenderable2DImage.h
 *
 *  Created on: 23/02/2011
 *      Author: cesar
 */

#ifndef MAORENDERABLE2DIMAGE_H_
#define MAORENDERABLE2DIMAGE_H_

#include <SDL/SDL.h>
#include <MAO/MAORenderable2D.h>

class MAORenderable2DImage: public MAORenderable2D {
public:
	MAORenderable2DImage(const std::string& name, const std::string& filePath, const int& x, const int& y, const int& width, const int& height);
	virtual ~MAORenderable2DImage();
	void generateTexFromSDLSurface();


	std::string& getFilePath();

private:

	std::string _filePath;
};

#endif /* MAORENDERABLE2DIMAGE_H_ */
