/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef TYPEGROUPFACTORY_H_
#define TYPEGROUPFACTORY_H_

#include "AnyItemFactory.h"

namespace any_fw {

class TypeGroupFactory : public CompositeAnyItemFactory {
public:
	TypeGroupFactory();
	virtual ~TypeGroupFactory();

	void addFactory(AnyItemFactory* factory);
	any::AnyItem createType(const std::string& typeName, const any::AnyItem& params = any::AnyItem::blank()) const;

private:
	GroupedAnyItemTypeFactory* groupedFactory;
	CompositeAnyItemFactory* otherFactory;
};

} /* namespace any_fw */

#endif /* TYPEGROUPFACTORY_H_ */
