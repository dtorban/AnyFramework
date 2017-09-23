/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <NanoGUIInterface.h>
#include "NanoGUIScreen.h"
#include <nanogui/nanogui.h>

namespace any_fw {

class NanoGUICreateScreenMethod : public Object::Method {
public:
	NanoGUICreateScreenMethod(Object& obj) : Method(obj, "createScreen") {
		parameters["width"] = (double)500;
		parameters["height"] = (double)500;
		parameters["title"] = std::string("");
	}
	virtual ~NanoGUICreateScreenMethod() {}

	any::AnyItem operator()(const any::AnyItem& parameters) {
		return any::ValueItem<NanoGUIScreen*>(new NanoGUIScreen(parameters));
	}
};

class NanoGUIInitMethod : public Object::Method {
public:
	NanoGUIInitMethod(Object& obj) : Method(obj, "init") {
	}

	any::AnyItem operator()(const any::AnyItem& parameters) {
		nanogui::init();
		return any::AnyItem::blank();
	}
};

class NanoGUIMainLoopMethod : public Object::Method {
public:
	NanoGUIMainLoopMethod(Object& obj) : Method(obj, "mainloop") {
	}

	any::AnyItem operator()(const any::AnyItem& parameters) {
		nanogui::mainloop();
		return any::AnyItem::blank();
	}
};

NanoGUIInterface::NanoGUIInterface(const any::AnyItem& anyItem) : Object("NanoGUIInterface") {
	addMethod(new NanoGUICreateScreenMethod(*this));
	addMethod(new NanoGUIInitMethod(*this));
	addMethod(new NanoGUIMainLoopMethod(*this));
}

NanoGUIInterface::~NanoGUIInterface() {
}

} /* namespace any_fw */
