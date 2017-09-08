/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <factory/TypeGroupFactory.h>

namespace any_fw {

TypeGroupFactory::TypeGroupFactory() {
	groupedFactory = new GroupedAnyItemTypeFactory();
	otherFactory = new CompositeAnyItemFactory();

	CompositeAnyItemFactory::addFactory(groupedFactory);
	CompositeAnyItemFactory::addFactory(otherFactory);
}

TypeGroupFactory::~TypeGroupFactory() {
	// TODO Auto-generated destructor stub
}

void TypeGroupFactory::addFactory(AnyItemFactory* factory) {
	const any::AnyItem& params = factory->getDefaultParameters();
	std::string key = groupedFactory->getKey(params);
	if (key.size() > 0) {
		groupedFactory->addFactory(key, factory);
	}
	else {
		otherFactory->addFactory(factory);
	}
}

any::AnyItem TypeGroupFactory::createType(const std::string& typeName,
		const any::AnyItem& params) const {
	any::AnyItem newParams;
	if (!params.isBlank()) {
		newParams.set(params);
	}

	newParams["Type"] = std::string(typeName);
	return CompositeAnyItemFactory::create(newParams);
}

} /* namespace any_fw */
