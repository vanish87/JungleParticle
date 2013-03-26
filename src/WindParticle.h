#pragma once

#include "ofVec3f.h"
#include "ofGraphics.h"
class WindParticle
{
public:
	WindParticle(void);
	~WindParticle(void);


	WindParticle(ofVec3f pos);
	void Simulate(float delta_time);
	void SetOrg(ofVec3f org_pos);

	ofVec3f pos_;
	ofVec3f pre_pos_;
	bool moving_;
	ofVec3f acc_;
	ofVec3f vol_;
	ofVec3f force_;
	float mass_;

	//spring para
	float x0_;
	float k_;
	float frac_para_;
};

