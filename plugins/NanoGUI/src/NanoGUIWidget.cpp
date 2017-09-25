/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <NanoGUIWidget.h>
#include "impl/NanoGUIWidgets.hpp"
#include "object/Callback.h"

namespace any_fw {

class NanoGUIWidgetUpdate : public Object::Method {
public:
	NanoGUIWidgetUpdate(NanoGUIWidget& widgetObj) : Method(obj, "update"), widgetObj(widgetObj) {}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		widgetObj.update();
		return any::AnyItem::blank();
	}

private:
	NanoGUIWidget& widgetObj;
};

class NanoGUIWidgetCreate : public Object::Method {
public:
	NanoGUIWidgetCreate(NanoGUIWidget& widgetObj) : Method(obj, "createWidget"), widgetObj(widgetObj) {
		parameters["type"] = std::string("");
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		NanoGUIWidget* widget = widgetObj.createWidget(parameters["type"].val<std::string>(), parameters);
		return any::ValueItem<NanoGUIWidget*>(widget);
	}

private:
	NanoGUIWidget& widgetObj;
};

class NanoGUIWidgetSetCallback : public Object::Method {
public:
	NanoGUIWidgetSetCallback(NanoGUIWidget& widgetObj) : Method(obj, "setCallback"), widgetObj(widgetObj) {
		parameters.set(any::ValueItem<Function*>(NULL));
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		widgetObj.setCallback(parameters.ptr<Function*>());
		this->parameters.set(any::ValueItem<Function*>(parameters.ptr<Function*>()));
		return any::AnyItem::blank();
	}

private:
	NanoGUIWidget& widgetObj;
};

NanoGUIWidget::NanoGUIWidget(const std::string& name, nanogui::Widget* parent, const any::AnyItem& parameters) : Object(name), widget(NULL), parent(parent) {
	this->properties.set(parameters);
	std::string title = properties["title"].asType<std::string>();
	if (title == "null") {
		title = name;
	}
	properties["title"].set(any::ValueItem<std::string>(title));

	addMethod(new NanoGUIWidgetUpdate(*this));
	addMethod(new NanoGUIWidgetCreate(*this));
	addMethod(new NanoGUIWidgetSetCallback(*this));
}

NanoGUIWidget* NanoGUIWidget::createWidget(const std::string& type, const any::AnyItem& parameters) {
	static NanoGUIWidgetFactory factory;

	NanoGUIWidget* widget = factory.create(type, getWidget(), parameters);

	if (widget != NULL) {
		widgets.push_back(widget);
	}

	return widget;
}

NanoGUIWidget::~NanoGUIWidget() {
	for (int f = 0; f < widgets.size(); f++) {
		delete widgets[f];
	}
}

} /* namespace any_fw */
