/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <NanoGUIScreen.h>

using namespace nanogui;

namespace any_fw {

NanoGUIScreen::NanoGUIScreen(const any::AnyItem& parameters) : Object("NanoGUIScreen") {
	screen = new Screen(Eigen::Vector2i(parameters["width"].asType<int>(), parameters["height"].asType<int>()), parameters["title"].asType<std::string>());
	screen->performLayout();
	screen->setVisible(true);
}

NanoGUIScreen::~NanoGUIScreen() {
	delete screen;
}

} /* namespace any_fw */
