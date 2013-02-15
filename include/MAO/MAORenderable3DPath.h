/*
 * MAORenderable3DPath.h
 *
 *  Created on: 28/02/2011
 *      Author: cesar
 */

#ifndef MAORENDERABLE3DPATH_H_
#define MAORENDERABLE3DPATH_H_

#include <MAO/MAORenderable3D.h>
#include <Kernel/PathPoint.h>

class MAORenderable3DPath: public MAORenderable3D {
public:
	MAORenderable3DPath(const std::string& name, float size, int r, int g, int b);
	virtual ~MAORenderable3DPath();
	void drawGeometryWithTexture();
	void drawGeometryWithoutTexture();
	void addPoint();
	void removePoints();
	int getR();
	int getG();
	int getB();
	bool getVisiblePoint();

	void generateCollisionShape(int type);

private:
	std::vector<PathPoint> _vectorPathPoint;
	PathPoint* refPoint; //Just nothing!

	bool hasChanged(PathPoint& p);
};

#endif /* MAORENDERABLE3DPATH_H_ */
