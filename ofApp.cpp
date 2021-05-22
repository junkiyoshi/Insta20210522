#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofNoFill();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	ofColor color;
	for (int hue = 0; hue < 256; hue += 16) {

		color.setHsb(hue, 255, 180);
		this->base_color_list.push_back(color);
	}

	for (int base_x = -250; base_x <= 250; base_x += 500) {

		for (int base_y = -250; base_y <= 250; base_y += 500) {

			for (int x = -200; x <= 200; x += 1) {

				for (int y = -200; y <= 200; y += 1) {

					this->base_location_list.push_back(glm::vec3(base_x + x, base_y + y, 0));
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	int radius = 3;
	while (this->log_list.size() < 3000) {

		int font_location_index = ofRandom(this->base_location_list.size());
		vector<glm::vec3> log;
		log.push_back(this->base_location_list[font_location_index]);
		this->log_list.push_back(log);
		this->color_list.push_back(this->base_color_list[(int)ofRandom(this->base_color_list.size())]);
		this->life_list.push_back(ofRandom(80, 150));
	}

	for (int i = this->log_list.size() - 1; i >= 0; i--) {

		this->life_list[i] -= 1;
		if (this->life_list[i] < 0) {

			this->log_list.erase(this->log_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);

			continue;
		}

		auto deg = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.0015, ofGetFrameNum() * 0.001)), 0, 1, -360, 360);
		this->log_list[i].push_back(this->log_list[i].back() + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
		/*
		while (this->log_list[i].size() > 100) {

			this->log_list[i].erase(this->log_list[i].begin());
		}
		*/
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int i = 0; i < this->log_list.size(); i++) {

		ofSetColor(this->color_list[i]);

		if (this->life_list[i] > 30) {

			ofSetLineWidth(2);
		}
		else {

			ofSetLineWidth(ofMap(this->life_list[i], 0, 30, 0, 2));
		}

		ofSetColor(this->color_list[i]);

		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}

	ofSetColor(255);
	ofSetLineWidth(2);


	for (int base_x = -250; base_x <= 250; base_x += 500) {

		for (int base_y = -250; base_y <= 250; base_y += 500) {

			ofDrawRectangle(glm::vec3(base_x, base_y, 0), 400, 400);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}