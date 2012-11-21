/*
 * MLBActuatorAnimOrej.h
 *
 *  Created on: 02/04/2011
 *      Author: cesar
 */

#ifndef MLBACTUATORANIMOREJ_H_
#define MLBACTUATORANIMOREJ_H_

#include <MLB/Actuator/MLBActuator.h>
#include <MAO/MAORenderable3DOrj.h>

#define PLAY 0
#define PAUSE 1
#define STOP 2

class MLBActuatorAnimOrej: public MLBActuator {
public:
	MLBActuatorAnimOrej(const std::string& name, MAORenderable3DOrj& parent, int animChoice, int animType = 0);
	virtual ~MLBActuatorAnimOrej();

	/* Python funcions! */
	int mPyGetAnimType();
	void mPySetAnimType(int animType);
	int mPyGetAnimChoice();
	void mPySetAnimChoice(int animChoice);

private:
	void specificActuate();
	int _animType; /* Refers to the animation type: LOOP; SIMPLE, PING-PONG */
	int _animChoice; /* Refers to the command: PLAY, PAUSE or STOP */
};

#endif /* MLBACTUATORANIMOREJ_H_ */
