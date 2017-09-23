/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef NANOGUIINTERFACE_H_
#define NANOGUIINTERFACE_H_

#include "object/Object.h"

namespace any_fw {

class NanoGUIInterface : public Object {
public:
	NanoGUIInterface(const any::AnyItem& anyItem);
	virtual ~NanoGUIInterface();
};

} /* namespace any_fw */

#endif /* NANOGUIINTERFACE_H_ */
