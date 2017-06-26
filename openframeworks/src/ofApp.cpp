#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	vector<float> x, y;

	for (int i = 0; i < 100; i++) {
		x.push_back(i);
		y.push_back(ofRandom(100));
	}

	if (GetPlotImage(x, y, plotImg)) {
		ofLog() << "Show plot !!";
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	plotImg.draw(0,0,ofGetWidth(),ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	vector<float> x, y;

	for (int i = 0; i < 100; i++) {
		x.push_back(i);
		y.push_back(ofRandom(100));
	}

	if (GetPlotImage(x, y, plotImg)) {
		ofLog() << "Show plot !!";
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
