/*
 * MLBActuatorAnimOrej.cpp
 *
 *  Created on: 02/04/2011
 *      Author: cesar
 */

#include "MLBActuatorAnimOrej.h"

MLBActuatorAnimOrej::MLBActuatorAnimOrej(const std::string& name, MAORenderable3DOrj& parent, int animChoice, int animType): MLBActuator(name, parent) {
	_animType = animType;
	_animChoice = animChoice;
	_mlbType = T_MLBACTUATORANIMOREJ;
}

void MLBActuatorAnimOrej::specificActuate(){
	switch(_animChoice){
	case PLAY:
		((MAORenderable3DOrj&)getParent()).playAnim(_animType);
		break;
	case PAUSE:
		((MAORenderable3DOrj&)getParent()).pauseAnim();
		break;
	case STOP:
		((MAORenderable3DOrj&)getParent()).stopAnim();
		break;
	default:
		Logger::getInstance()->error("Invalid animation type for MLB Actuator Anim Orej: "+getName());
		break;
	}
}

/* Python functions! */
int MLBActuatorAnimOrej::mPyGetAnimType(){
	return _animType;
}
void MLBActuatorAnimOrej::mPySetAnimType(int animType){
	_animType = animType;
}
int MLBActuatorAnimOrej::mPyGetAnimChoice(){
	return _animChoice;
}
void MLBActuatorAnimOrej::mPySetAnimChoice(int animChoice){
	_animChoice = animChoice;
}

MLBActuatorAnimOrej::~MLBActuatorAnimOrej() {
}
