/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef NANOGUISCREEN_H_
#define NANOGUISCREEN_H_

#include "object/Object.h"

#include <nanogui/nanogui.h>
#include <nanogui/screen.h>

namespace any_fw {

class NanoGUIScreen : public Object {
public:
	NanoGUIScreen(const any::AnyItem& parameters);
	virtual ~NanoGUIScreen();

private:
	nanogui::Screen* screen;
};

} /* namespace any_fw */

#endif /* NANOGUISCREEN_H_ */
