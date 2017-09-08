/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef FACTORYAPI_H_
#define FACTORYAPI_H_

#include "factory/AnyItemFactory.h"

namespace any_fw {

class FactoryAPI {
public:
	virtual ~FactoryAPI() {}

	virtual void addFactory(AnyItemFactory* factory) = 0;
};

} /* namespace any_fw */

#endif /* FACTORYAPI_H_ */
