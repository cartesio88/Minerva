/*
 * MAORenderable3DOrj.h
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#ifndef MAORENDERABLE3DORJ_H_
#define MAORENDERABLE3DORJ_H_

#include <MAO/MAORenderable3D.h>
#include <Kernel/Orej.h>

class MAORenderable3DOrj: public MAORenderable3D {
public:
	MAORenderable3DOrj(const std::string& name, float scale, const std::string& pathOrj, const std::string& pathTex);
	MAORenderable3DOrj(const MAORenderable3DOrj& o);
	virtual ~MAORenderable3DOrj();
	void drawGeometryWithTexture();
	void drawGeometryWithoutTexture();

	std::string& getPathOrj();
	std::string& getPathTex();

	void generateCollisionShape(int type);

	void playAnim(int animType);
	void pauseAnim();
	void stopAnim();

private:
	float _scale;
	Orej* _orj;
	std::string _pathOrj;
	std::string _pathTex;
};

#endif /* MAORENDERABLE3DORJ_H_ */
