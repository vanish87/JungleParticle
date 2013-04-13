#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxParticleEmitter.h"
#include "WindParticle.h"

class testApp : public ofBaseApp
{
	
public:
	testApp();
	~testApp();

	void	setup();
	void	update();
	void	draw();
	void	exit();
	
	void	keyPressed( int key );
	void	keyReleased( int key );
	void	mouseMoved( int x, int y );
	void	mouseDragged( int x, int y, int button );
	void	mousePressed( int x, int y, int button );
	void	mouseReleased( int x, int y, int button );
	void	windowResized( int w, int h );
	
protected:

	ofVec3f sphere_pos_;
	int next_index_;
	ofVec3f sphere_acc_;
	ofVec3f sphere_vol_;

	ofVec3f org_pos_;
	ofVec3f pre_pos_;
	ofVec3f f_dir_;
	float mass_;
	float x0_;
	float k_;
	float frac_para_;

	
	ofxParticleEmitter		m_emitter;
	float angle_;

	vector<WindParticle> wind_;
    
    
    
    ofVec3f hand_pos_;
    ofVec3f hand_vel_;
    float hand_radius_;
    float hand_mass_;
    
    ofVec3f butterfly_pos_;
    ofVec3f butterfly_vel;
    float butterfly_radius_;
    float butterfly_mass_;
    
    
    
};

#endif
	
