/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef NANOGUIWIDGETS_H_
#define NANOGUIWIDGETS_H_

#include "NanoGUIWidget.h"

#include <nanogui/window.h>
#include <nanogui/layout.h>

using namespace nanogui;

namespace any_fw {

class NanoGUIWindow : public NanoGUIWidget {
public:
	NanoGUIWindow(nanogui::Widget* parent, const any::AnyItem& params) : NanoGUIWidget("Window", parent, params) {
		properties["posx"] = (double)properties["posx"].asType<int>(15);
		properties["posy"] = (double)properties["posy"].asType<int>(15);

		Window *window = new Window(getParent(), properties["title"].val<std::string>());
		window->setPosition(Vector2i(properties["posx"].asType<int>(), properties["posy"].asType<int>()));
		window->setLayout(new GroupLayout());
		setWidget(window);
	}
	void update() {
	}
};

class NanoGUIButton : public NanoGUIWidget {
public:
	NanoGUIButton(nanogui::Widget* parent, const any::AnyItem& params) : NanoGUIWidget("Button", parent, params) {
		Button *b = new Button(parent, properties["title"].val<std::string>());
		b->setCallback([] { std::cout << "pushed!" << std::endl; });
		b->setTooltip("short tooltip");
		setWidget(b);
	}
	void update() {
	}
};

class NanoGUIWidgetFactory {
public:
	NanoGUIWidget* create(const std::string& type, nanogui::Widget* parent, const any::AnyItem& params) {
		NanoGUIWidget* widget = NULL;
		if (type == "Window") {
			widget = new NanoGUIWindow(parent, params);
		}
		else if (type == "Button") {
			widget = new NanoGUIButton(parent, params);
		}

		return widget;
	}
};

} /* namespace any_fw */

#endif /* NANOGUIWIDGETS_H_ */
