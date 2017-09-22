/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef CALLBACK_H_
#define CALLBACK_H_

#include "Function.h"

namespace any_fw {

class Callback : public Function {
public:
	Callback() : Function("callback") {}
	virtual ~Callback() {}

	any::AnyItem operator()(const any::AnyItem& parameters) {
		exec(parameters);
		return any::AnyItem::blank();
	}
	void exec(const any::AnyItem& parameters) = 0;
};

} /* namespace any_fw */

#endif /* CALLBACK_H_ */
