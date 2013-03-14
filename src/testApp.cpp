#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup()
{
	ofSetWindowTitle( "particle example" );
	ofBackground( 0, 0, 0 );
	ofSetFrameRate( 60 );
	
	if ( !m_emitter.loadFromXml( "circles.pex" ) )
	{
		ofLog( OF_LOG_ERROR, "testApp::setup() - failed to load emitter config" );
	}

	sphere_pos_.set(300, 300, 0);
	sphere_acc_.set(0, 0, 0);
	sphere_vol_.set(0, 0, 0);
}

//--------------------------------------------------------------
void testApp::exit()
{
	// TODO
}

//--------------------------------------------------------------
void testApp::update()
{
	if(sphere_acc_.x > 0)
		sphere_acc_.x -= 0.1;
	else
	{
		if(sphere_acc_.x < 0)
			sphere_acc_.x += 0.1;
	}
	if(sphere_acc_.y > 0)
		sphere_acc_.y -= 0.1;
	else
	{
		if(sphere_acc_.y < 0)
			sphere_acc_.y += 0.1;
	}
	sphere_pos_.x = ofClamp(sphere_pos_.x, 50, ofGetWindowWidth()-50);
	sphere_pos_.y = ofClamp(sphere_pos_.y, 50, ofGetWindowHeight()-50);
	m_emitter.update();
	sphere_vol_ += sphere_acc_;
	sphere_pos_+= sphere_acc_;
}

//--------------------------------------------------------------
void testApp::draw()
{
	m_emitter.draw( 0, 0 );
	
	ofSetColor( 255, 255, 255 );
	ofDrawBitmapString( "fps: " + ofToString( ofGetFrameRate(), 2 ), 20, 20 );
	
	ofDrawBitmapString(ofToString(angle_), 20, 40);

	ofPushMatrix();
	ofTranslate(sphere_pos_.x, sphere_pos_.y, sphere_pos_.z);
	ofSphere(20);

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
	// nothing
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
	m_emitter.sourcePosition.x = x;
	m_emitter.sourcePosition.y = y;

	ofVec3f dir = ofVec3f(x, y, 0)- ofVec3f(ofGetPreviousMouseX(), ofGetPreviousMouseY(), 0);
	dir.normalize();	
	angle_ = dir.angle(ofVec3f(1,0,0));
	if(dir.y >=  0) angle_+=180;
	m_emitter.angle = angle_;

	if(ofVec3f(x, y, 0).distance(sphere_pos_) < 50)
		sphere_acc_+= dir;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
	// nothing
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
	// nothing
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
	// nothing
}
