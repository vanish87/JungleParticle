#include "WindParticle.h"


WindParticle::WindParticle(void)
{
	moving_ = false;

	pos_.set(300, 300, 0);
	acc_.set(0, 0, 0);
	vol_.set(0, 0, 0);

	x0_ = 60 * ofRandom(0.5,1);
	k_ = 0.3* ofRandom(0.3,1);;
	mass_ = 5* ofRandom(0.6,1);;
	frac_para_ = 50* ofRandom(0.5,1);;
}

WindParticle::WindParticle( ofVec3f pos )
{
	moving_ = false;

	pos_ = pos;
	acc_.set(0, 0, 0);
	vol_.set(ofRandomf(), ofRandomf(), 0);

	x0_ = 100 * ofRandom(0.5,1);
	k_ = 0.001* ofRandom(0.3,1);;
	mass_ = 10* ofRandom(0.6,1);;
	frac_para_ = 1* ofRandom(0.5,1);; 
}


WindParticle::~WindParticle(void)
{
}

void WindParticle::Simulate( float delta_time )
{


	float d = force_.length();
	float f = ofClamp(k_ * (d - x0_),0, 1000);
	ofVec3f force = f * (force_.normalize());
	ofVec3f v_dir = vol_;
	v_dir.normalize();
	ofVec3f frac = -frac_para_ * v_dir;
	if(moving_)
	{
		force = force + frac;
		//cout<<"force +frac"<<endl;
	}
	else
	{
		force = frac;
		//cout<<"frac"<<endl;
	}
	if(pos_.distance(ofVec3f(300,300,0))< 60)
	{
		ofVec3f dir = pos_ - ofVec3f(300,300,0);
		dir.normalize();

		pos_ = dir*50 + ofVec3f(300,300,0);
		force += dir*200;
		//cout<<pos_.x<<" "<<pos_.y<<" "<<pos_.z<<endl;
	}

	acc_ = force / mass_;
	vol_ += acc_;
	pos_ += vol_;

	pos_.x = ofClamp(pos_.x, 50, 1024-50);
	pos_.y = ofClamp(pos_.y, 50, 768-50);


	ofSetColor( 0, 74, 255 );
//    (0+i*5, 74+i*5, 255-i*5);
    
	ofPushMatrix();
	ofTranslate(pos_.x, pos_.y, 0.0f);
	ofCircle(0, 0, 3); //size of particles
	ofPopMatrix();
}

void WindParticle::SetOrg( ofVec3f org_pos )
{
	if(org_pos.x == pre_pos_.x && org_pos.y == pre_pos_.y)
		moving_ = false;
	else
		moving_ = true;
	force_ = org_pos - pos_;
	pre_pos_ = org_pos;
}
