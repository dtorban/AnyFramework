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

#include "NanoGUIWidget.h"

namespace any_fw {

class NanoGUIScreen : public NanoGUIWidget {
public:
	NanoGUIScreen(const any::AnyItem& parameters);
	virtual ~NanoGUIScreen();

	void update();
	void setCallback(Function* callback) {
		this->callback = callback;
	}

private:
	class ScreenWidget : public nanogui::Screen {
	public:
		ScreenWidget(NanoGUIScreen& screenWidget, int width, int height, const std::string& title) : nanogui::Screen(Eigen::Vector2i(width, height), title), screenWidget(screenWidget) {}
		void drawContents() {
			if (screenWidget.callback != NULL) {
				(*screenWidget.callback)();
			}
		}
	private:
		NanoGUIScreen& screenWidget;
	};

	nanogui::Screen* screen;
	Function* callback;
};

} /* namespace any_fw */

#endif /* NANOGUISCREEN_H_ */
