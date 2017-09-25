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
#include <nanogui/slider.h>
#include <nanogui/textbox.h>
#include "object/Function.h"

using namespace nanogui;

namespace any_fw {

class NanoGUIWindow : public NanoGUIWidget {
public:
	NanoGUIWindow(nanogui::Widget* parent, const any::AnyItem& params) : NanoGUIWidget("Window", parent, params) {
		properties["posx"] = (double)properties["posx"].asType<int>(15);
		properties["posy"] = (double)properties["posy"].asType<int>(15);

		window = new Window(getParent());
		window->setLayout(new GroupLayout());
		setWidget(window);
		update();
	}
	void update() {
		window->setTitle(properties["title"].val<std::string>());
		window->setPosition(Vector2i(properties["posx"].asType<int>(), properties["posy"].asType<int>()));
	}

private:
	Window* window;
};

class NanoGUIButton : public NanoGUIWidget {
public:
	NanoGUIButton(nanogui::Widget* parent, const any::AnyItem& params) : NanoGUIWidget("Button", parent, params) {
		b = new Button(parent, properties["title"].val<std::string>());
		//b->setTooltip("short tooltip");
		setWidget(b);
		update();
	}
	void update() {
	}
	void setCallback(Function* callback) {
		if (callback != NULL) {
			b->setCallback([callback] { (*callback)(); });
		}
	}

private:
	Button* b;
};

class NanoGUIPanel : public NanoGUIWidget {
public:
	NanoGUIPanel(nanogui::Widget* parent, const any::AnyItem& params) : NanoGUIWidget("Panel", parent, params) {
		panel = new Widget(parent);
		panel->setLayout(new BoxLayout(Orientation::Horizontal, Alignment::Middle, 0, 20));
		setWidget(panel);
		update();
	}
	void update() {
	}

private:
	Widget* panel;
};

class NanoGUISlider : public NanoGUIWidget {
public:
	NanoGUISlider(nanogui::Widget* parent, const any::AnyItem& params) : NanoGUIWidget("Slider", parent, params) {
		slider = new Slider(parent);
		setWidget(slider);
		update();
	}
	void update() {
		slider->setValue(0.5f);
		slider->setFixedWidth(80);
	}
	void setCallback(Function* callback) {
		if (callback != NULL) {
			slider->setCallback([callback](float value) {
				(*callback)(any::ValueItem<float>(value));
			});
		}
	}

private:
	Slider* slider;
};

class NanoGUITextBox : public NanoGUIWidget {
public:
	NanoGUITextBox(nanogui::Widget* parent, const any::AnyItem& params) : NanoGUIWidget("TextBox", parent, params) {
		textbox = new TextBox(parent);
		setWidget(textbox);
		update();
	}
	void update() {
		textbox->setFixedSize(Vector2i(60, 25));
		textbox->setValue("50");
		textbox->setUnits("%");
	}

private:
	TextBox* textbox;
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
		else if (type == "Panel") {
			widget = new NanoGUIPanel(parent, params);
		}
		else if (type == "Slider") {
			widget = new NanoGUISlider(parent, params);
		}
		else if (type == "TextBox") {
			widget = new NanoGUITextBox(parent, params);
		}

		return widget;
	}
};

} /* namespace any_fw */

#endif /* NANOGUIWIDGETS_H_ */
