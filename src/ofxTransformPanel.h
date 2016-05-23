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
#pragma once

#include "ofxGuiExtended.h"
#include "ofxTransformer.h"

/// \class TransformPanel
/// \brief ofxGui panel for transform control
///
/// note: requires including ofxGui in your project
class ofxTransformPanel {

	public:

		ofxTransformPanel() : transformer(NULL) {}

		ofxGui gui;

		ofxGuiPanel *panel; //< gui panel

		ofParameter<ofPoint> position; //< 3d transform origin
		ofParameter<bool> translate;     //< translate the origin?
		ofParameter<bool> mirrorX;       //< mirror horizontally?
		ofParameter<bool> mirrorY;       //< mirror vertically?
		ofParameter<bool> aspect;        //< keep aspect ratio?
		ofParameter<bool> centering;     //< center in middle of the screen?
		ofParameter<bool> warp;          //< enable the quad warper?
		ofParameter<void> editWarp;      //< edit quad warper
		ofParameter<void> saveWarp;      //< save quad warper
		ofParameter<void> reset;         //< reset everything

		/// set the transformer to control, set optional panel name and settings file name,
		/// loads settings file if found
		void setup(ofxTransformer *transformer, const string &name="Transform", const string &xmlFile="transformSettings.xml");

		/// update the transformer with the current panel settings
		void update();

		/// draw the panel
		void draw();

		/// load and save the control panel settings
		void loadSettings(const string &xmlFile="transformSettings.xml");
		void saveSettings(const string &xmlFile="transformSettings.xml");

		/// button callbacks
		void editWarpPressed();
		void saveWarpPressed();
		void resetPressed();

	protected:

		ofxTransformer *transformer; //< current transformer to control
};
