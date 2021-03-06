/*
 * MLBActuatorAddDynamicObject.cpp
 *
 *  Created on: 14/03/2011
 *      Author: cesar
 */

#include <MLB/Actuator/MLBActuatorAddDynamicObject.h>

MLBActuatorAddDynamicObject::MLBActuatorAddDynamicObject(
		const std::string& name, MAOPositionator3D& parent,
		MAORenderable3D& mao, int timeToExpire, cv::Mat* offset,
		btVector3* impulse) :
	MLBActuator(name, parent) {
	if (mao.getMass() == 0) {
		throw "MLB Actuator Add Dynamic Object only applicable to Dynamic MAO's (Non-Zero mass): "
				+ name;
	}

	_mao = &mao;
	_timeToExpire = timeToExpire;

	if (offset == 0) { //Load an identity matrix
		_offset = cv::Mat(4, 4, CV_32F, cv::Scalar(0.f));
		_offset.at<float> (0, 0) = 1;
		_offset.at<float> (1, 1) = 1;
		_offset.at<float> (2, 2) = 1;
		_offset.at<float> (3, 3) = 1;
	} else {
		_offset = *offset;
	}

	if (impulse == 0) {
		_impulse = btVector3(0, 0, 0);
	} else {
		_impulse = *impulse;
	}
	_mlbType = T_MLBACTUATORADDDYNAMICOBJECT;
}

void MLBActuatorAddDynamicObject::specificActuate() {
	MAORenderable3D* m;

	if (!((MAOPositionator3D&) getParent()).isPositioned()) {
		Logger::getInstance()->out(
				"Can not add an object if it is NOT positioned!: " + getName());
		return;
	}

	switch (_mao->getType()) {
	case T_MAORENDERABLE3DMODEL:
		/*m = new MAORenderable3DOrj("", _mao->getSize(),
		 ((MAORenderable3DOrj*) _mao)->getPathOrj(),
		 ((MAORenderable3DOrj*) _mao)->getPathTex());*/
		m = new MAORenderable3DModel(*(MAORenderable3DModel*) _mao);
		break;
	default:
	  Logger::getInstance()->warning("MAO Type Not supported for Add Dynamic Object.. Yet! ;): "
					 + getName());
	  return;
		break;
	}

	MAOFactory::getInstance()->addInstMAORenderable3D(*m, _timeToExpire);
	PhysicsController::getInstance()->addDynamicRigidBody(*m,
			(MAOPositionator3D&) getParent(), _mao->getMass(), &_offset,
			&_impulse);

}

int MLBActuatorAddDynamicObject::mPyGetTimeToExpire() {
	return _timeToExpire;
}
void MLBActuatorAddDynamicObject::mPySetTimeToExpire(int timeToExpire) {
	_timeToExpire = timeToExpire;
}

VectorFloat MLBActuatorAddDynamicObject::mPyGetImpulse() {
	VectorFloat v;
	 v.push_back(_impulse.x());
	 v.push_back(_impulse.y());
	 v.push_back(_impulse.z());

	 return v;
}

void MLBActuatorAddDynamicObject::mPySetImpulse(VectorFloat impulse) {
	if (impulse.size() != 3) {
		Logger::getInstance()->error(
				"Impulse vector size should be 3 for MLB Actuator Add Dynamic Object: "
						+ getName());
		throw "Impulse vector size should be 3 for MLB Actuator Add Dynamic Object: "
				+ getName();
	} else {
		_impulse.setX(impulse.at(0));
		_impulse.setY(impulse.at(1));
		_impulse.setZ(impulse.at(2));
	}
}

VectorFloat MLBActuatorAddDynamicObject::mPyGetOffset(){
  VectorFloat v;
  for(unsigned int i = 0; i<4; i++){
    for(unsigned int j = 0; j<4; j++){
      v.push_back(_offset.at<float>(i,j));
    }
  }
  return v;
}

void MLBActuatorAddDynamicObject::mPySetOffset(VectorFloat offset){
  if(offset.size()!=16){
    Logger::getInstance()->error("Offset vector size of MLBActuatorAddDynamicObject should be 16: "+getName());
    throw "Offset vector size of MLBActuatorAddDynamicObject should be 16: "+getName();
  }

  for(unsigned int i=0;i<4;i++){
    for(unsigned j=0;j<4;j++){
      _offset.at<float>(i,j) = offset.at(i*4+j);
    }
  }
}


MLBActuatorAddDynamicObject::~MLBActuatorAddDynamicObject() {
}
