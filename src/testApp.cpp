#include "testApp.h"

static int NUM_PARTICLE = 250;
static const int MAX_PARTICLE = 300;
static const int MIN_PARTICLE = 200;
testApp::testApp()
{

}

testApp::~testApp()
{

}

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetWindowTitle( "particle example" );
	ofBackground( 0, 0, 0 ); //why doesn't it work with a white background?
	ofSetFrameRate( 60 );
	
	if ( !m_emitter.loadFromXml( "circles.pex" ) )
	{
		ofLog( OF_LOG_ERROR, "testApp::setup() - failed to load emitter config" );
	}

	sphere_pos_.set(300, 300, 0);
	sphere_acc_.set(0, 0, 0);
	sphere_vol_.set(0, 0, 0);
	next_index_ = 0;

	x0_ = 0;
	k_ = 0;
	mass_ = 0;
	frac_para_ = 0;

	for (int i = 0; i < NUM_PARTICLE; ++i)
	{
		WindParticle particle;
		wind_.push_back(particle);
	}
}

//--------------------------------------------------------------
void testApp::exit()
{
	// TODO
}

//--------------------------------------------------------------
void testApp::update()
{		
	org_pos_= ofVec3f(ofGetMouseX(),ofGetMouseY(),0);
	float ep = 0.1;
	if(-ep <= sphere_acc_.x && sphere_acc_.x <= ep)
		sphere_acc_.x = 0;
	if(-ep <= sphere_acc_.y && sphere_acc_.y <= ep)
		sphere_acc_.y = 0;
	if(sphere_acc_.x > 0)
		sphere_acc_.x -= ep;
	else
	{
		if(sphere_acc_.x < 0)
			sphere_acc_.x += ep;
	}
	if(sphere_acc_.y > 0)
		sphere_acc_.y -= ep;
	else
	{
		if(sphere_acc_.y < 0)
			sphere_acc_.y += ep;
	}
/*	m_emitter.update();
	sphere_vol_ += sphere_acc_;
	sphere_pos_+= sphere_vol_;

	
	if(wind_path_.size() > 1)
	{
		ofVec3f dir;
		if(next_index_ > 1)
			dir = (wind_path_[next_index_] - wind_path_[next_index_- 1]).normalize();
		else
			dir = (wind_path_[1] - wind_path_[0]).normalize();
		float scale = next_index_ * 1.0f/ wind_path_.size();
		sphere_pos_ = wind_path_[next_index_];
		cout<<next_index_<<" "<<wind_path_.size()<<"\r";
		if(next_index_ < wind_path_.size() - 1 && sphere_pos_.distance(wind_path_[next_index_]) > 200 ) next_index_++;
		sphere_acc_ = (wind_path_[next_index_] - sphere_pos_).normalize() * 0.3;
		wind_path_.erase(wind_path_.begin());
		if(next_index_ == wind_path_.size())
			next_index_ = wind_path_.size() - 1;
	}*/

	f_dir_  = org_pos_ - sphere_pos_;

	float d = f_dir_.length();
	float f = ofClamp(k_ * (d - x0_),0, 1000);
	ofVec3f force = f * (f_dir_.normalize());
	ofVec3f v_dir = sphere_vol_;
	v_dir.normalize();
	ofVec3f frac = -frac_para_ * v_dir;
	if( (org_pos_.x != ofGetPreviousMouseX() && org_pos_.y != ofGetPreviousMouseY()))
	{
		force = force + frac;
		//cout<<"force +frac"<<endl;
	}
	else
	{
		force = frac;
		//cout<<"frac"<<endl;
	}
	sphere_acc_ = force / mass_;
	sphere_vol_ += sphere_acc_;
	sphere_pos_ += sphere_vol_;

	ofVec3f delta =  org_pos_- pre_pos_;

	//cout<<delta.x<<" "<<delta.y<<" "<<delta.z<<endl;
	if(delta.x == 0 && delta.y == 0 && NUM_PARTICLE < MAX_PARTICLE)
	{
		NUM_PARTICLE++;
		WindParticle particle(org_pos_);
		wind_.push_back(particle);
	}
	else
	{
		if(NUM_PARTICLE > MIN_PARTICLE && ofRandomf()*10 > 3)
		{
			NUM_PARTICLE --;
			wind_.pop_back();
		}
	}

	for(int i = 0; i < NUM_PARTICLE; ++i)
		wind_[i].SetOrg(org_pos_);


 	sphere_pos_.x = ofClamp(sphere_pos_.x, -100+ org_pos_.x, 100 + org_pos_.x);
 	sphere_pos_.y = ofClamp(sphere_pos_.y, -100+ org_pos_.y, 100 + org_pos_.y);

	sphere_pos_.x = ofClamp(sphere_pos_.x, 50, ofGetWindowWidth()-50);
	sphere_pos_.y = ofClamp(sphere_pos_.y, 50, ofGetWindowHeight()-50);

	
	pre_pos_ = org_pos_;
}

//--------------------------------------------------------------
void testApp::draw()
{
	m_emitter.draw( 0, 0 );
	
	ofSetColor( 0, 0, 0 ); // 255 255 255
	ofDrawBitmapString( "fps: " + ofToString( ofGetFrameRate(), 2 ), 20, 20 );
	
	ofDrawBitmapString("acc "+ ofToString(sphere_acc_.x) + " " + ofToString(sphere_acc_.y), 20, 40);
	ofDrawBitmapString("vol "+ ofToString(sphere_vol_.x) + " " + ofToString(sphere_vol_.y), 20, 60);
	ofDrawBitmapString("particle num "+ ofToString(NUM_PARTICLE), 20, 80);

	ofPushMatrix();
	ofSetColor( 255, 0, 0 ); //color object
	ofTranslate(300,300,0); //location object
	ofSphere(50); //size object
	ofPopMatrix();

	ofPushMatrix();
	for(int i = 0; i < NUM_PARTICLE; ++i)
	{
//		ofSetColor(2.55*i,2.55*i,2.55*i,1);
		wind_[i].Simulate(0);
	}
// 	ofTranslate(sphere_pos_.x, sphere_pos_.y, sphere_pos_.z);
// 	ofSphere(20);
	ofPopMatrix();
    ofEnableAlphaBlending(); //neu
//
	ofSetColor(255, 226, 141, 20); //color particles //added alpha
    
    ofDisableAlphaBlending(); //neu
    
//    (255-j*5, 226+j*5, 141+j*5);

}


//--------------------------------------------------------------
void testApp::keyPressed  (int key)
{
	// nothing
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key)
{
	// nothing
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{
	//cout<<x<<" "<<y<<"\r";
	// nothing	

	//cout<<f_dir_.x<<" "<<f_dir_.y<<"\r";
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
/*
	m_emitter.sourcePosition.x = x;
	m_emitter.sourcePosition.y = y;

	ofVec3f dir = ofVec3f(x, y, 0)- ofVec3f(ofGetPreviousMouseX(), ofGetPreviousMouseY(), 0);
	dir.normalize();	
	angle_ = dir.angle(ofVec3f(1,0,0));
	if(dir.y >=  0) angle_+=180;
	m_emitter.angle = angle_;

	if(ofVec3f(x, y, 0).distance(sphere_pos_) < 50)
		sphere_acc_+= dir;*/
	f_dir_ = ofVec3f(x,y,0.0f) - ofVec3f(ofGetPreviousMouseX(),ofGetPreviousMouseY(),0);

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
	// nothing
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
	f_dir_ = ofVec3f(0,0,0);
	// nothing
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
	// nothing
}
