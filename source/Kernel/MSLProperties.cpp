/*
 * MSLProperties.cpp
 *
 *  Created on: 23/03/2011
 *      Author: cesar
 */

#include "MSLProperties.h"

MSLProperties::MSLProperties() {
	init();
}

MSLProperties::MSLProperties(const MSLProperties& o){
	init();
	fill(o);
}

void MSLProperties::fill(const MSLProperties& o){
	if(o.string1 != 0) *string1 = *o.string1;
	if(o.string2 != 0) *string2 = *o.string2;
	if(o.string3 != 0) *string3 = *o.string3;
	if(o.string4 != 0) *string4 = *o.string4;

	if(o.float1 != 0.) float1 = o.float1;
	if(o.float2 != 0.) float2 = o.float2;
	if(o.float3 != 0.) float3 = o.float3;

	if(o.int1 != 0) int1 = o.int1;
	if(o.int2 != 0) int2 = o.int2;
	if(o.int3 != 0) int3 = o.int3;
	if(o.int4 != 0) int4 = o.int4;

	if(o.bool1 != false) bool1 = o.bool1;

	if(o.btvector1 != 0) *btvector1= *o.btvector1;
	if(o.btvector2 != 0) *btvector2= *o.btvector2;

	if(o.pose1 != 0) pose1 = new cv::Mat(*o.pose1);
	if(o.pose2 != 0) pose2= new cv::Mat(*o.pose2);

	if(o.maovalue1 != 0) *maovalue1= *o.maovalue1;
	if(o.maovalue2 != 0) *maovalue2= *o.maovalue2;

	//Dont copy!
	if(o.maoproperty1 == 0) maoproperty1 = o.maoproperty1;
	if(o.maoproperty2 == 0) maoproperty2 = o.maoproperty2;

}

void MSLProperties::init(){
	string1 = 0;
	string2 = 0;
	string3 = 0;
	string4 = 0;
	float1 = 0.;
	float2 = 0.;
	float3 = 0.;
	int1 = 0;
	int2 = 0;
	int3 = 0;
	int4 = 0;
	bool1 = false;
	btvector1 = 0;
	btvector2 = 0;
	pose1 = 0;
	pose2 = 0;
	maovalue1 = 0;
	maovalue2 = 0;
	maoproperty1 = 0;
	maoproperty2 = 0;
}

MSLProperties::~MSLProperties() {
	if(string1!=0) delete string1;
	if(string2!=0) delete string2;
	if(string3!=0) delete string3;
	if(string4!=0) delete string4;
	if(btvector1!=0) delete btvector1;
	if(btvector2!=0) delete btvector2;
	if(pose1!=0) delete pose1;
	if(pose2!=0) delete pose2;
	if(maovalue1!=0) delete maovalue1;
	if(maovalue2!=0) delete maovalue2;
}
