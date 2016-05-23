/*
 * Copyright (c) 2015 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxAppUtils for documentation
 *
 */
#include "ofxTransformPanel.h"

//--------------------------------------------------------------
void ofxTransformPanel::setup(ofxTransformer *transformer, const string &name, const string &xmlFile) {

	this->transformer = transformer;

	// setup callbacks
	editWarp.addListener(this, &ofxTransformPanel::editWarpPressed);
	saveWarp.addListener(this, &ofxTransformPanel::saveWarpPressed);
	reset.addListener(this, &ofxTransformPanel::resetPressed);

	// setup values from transformer
	position.set("position",
	   transformer->getPosition(),                                                      // val
	   ofPoint(-transformer->getRenderWidth(), -transformer->getRenderHeight(), -200),  // min
	   ofPoint(transformer->getRenderWidth(), transformer->getRenderHeight(), 1000));   // max
	translate.set("translate", transformer->getTranslate());
	mirrorX.set("mirrorX", transformer->getMirrorX());
	mirrorY.set("mirrorY", transformer->getMirrorY());
	centering.set("centering", transformer->getCentering());
	aspect.set("aspect", transformer->getAspect());
	warp.set("warp", transformer->getWarp());
	editWarp.set("edit warp");
	saveWarp.set("save warp");
	reset.set("reset everything");

	// add widgets to panel
	panel = gui.addPanel(name, ofToDataPath(xmlFile));
	panel->add(position);
	panel->add(translate);
	panel->add(mirrorX);
	panel->add(mirrorY);
	panel->add(centering);
	panel->add(aspect);
	panel->add(warp);
	panel->add(editWarp);
	panel->add(saveWarp);
	panel->add(reset);

	// load settings if they exist
	if(ofFile::doesFileExist(ofToDataPath(xmlFile))) {
		loadSettings(xmlFile);
	}
	transformer->loadWarpSettings();
	update();
}

//--------------------------------------------------------------
void ofxTransformPanel::update() {
	if(!transformer) {
		return;
	}
	transformer->setPosition(position->x, position->y, position->z);
	transformer->setTranslate(translate);
	transformer->setMirrorX(mirrorX);
	transformer->setMirrorY(mirrorY);
	transformer->setCentering(centering);
	transformer->setAspect(aspect);
	transformer->setWarp(warp);
}

//--------------------------------------------------------------
void ofxTransformPanel::draw() {
	if(!transformer || transformer->getEditWarp()) {
		return;
	}
}

//--------------------------------------------------------------
void ofxTransformPanel::loadSettings(const string &xmlFile) {
	panel->loadFromFile(ofToDataPath(xmlFile));
}

//--------------------------------------------------------------
void ofxTransformPanel::saveSettings(const string &xmlFile) {
	panel->saveToFile(ofToDataPath(xmlFile));
}

//--------------------------------------------------------------
void ofxTransformPanel::editWarpPressed() {
	if(!transformer) {
		return;
	}
	transformer->setEditWarp(true);
}

//--------------------------------------------------------------
void ofxTransformPanel::saveWarpPressed() {
	if(!transformer) {
		return;
	}
	transformer->saveWarpSettings();
}

//--------------------------------------------------------------
void ofxTransformPanel::resetPressed() {
	position = ofPoint(0, 0, 0);
	translate = false;
	mirrorX = false;
	mirrorY = false;
	centering = false;
	aspect = false;
	warp = false;
}
