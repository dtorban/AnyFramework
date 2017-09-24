/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef NANOGUIWIDGET_H_
#define NANOGUIWIDGET_H_

#include "object/Object.h"

#include <nanogui/nanogui.h>

namespace any_fw {

class NanoGUIWidget : public Object {
public:
	NanoGUIWidget(const std::string& name, nanogui::Widget* parent, const any::AnyItem& parameters);
	virtual ~NanoGUIWidget();

	virtual void update() {}
	NanoGUIWidget* createWidget(const std::string& type, const any::AnyItem& parameters);
	void setWidget(nanogui::Widget* widget) { this->widget = widget; }
	nanogui::Widget* getWidget() { return widget; }
	nanogui::Widget* getParent() { return parent; }

private:
	nanogui::Widget* parent;
	nanogui::Widget* widget;
	std::vector<NanoGUIWidget*> widgets;
};

} /* namespace any_fw */

#endif /* NANOGUIWIDGET_H_ */
