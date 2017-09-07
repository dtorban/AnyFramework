/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef ANYITEMFACTORY_H_
#define ANYITEMFACTORY_H_

#include "AnyItem/AnyItem.h"

namespace IVGFX {

class AnyItemFactory {
public:
	virtual ~AnyItemFactory() {}
	virtual any::AnyItem create(const any::AnyItem& params) const = 0;
};

class CompositeAnyItemFactory : public AnyItemFactory {
public:
	CompositeAnyItemFactory(std::vector<AnyItemFactory*>& factories) : factories(factories) {}
	virtual ~CompositeAnyItemFactory() {}

	any::AnyItem create(const any::AnyItem& params) const {
		for (int f = 0; f < factories.size(); f++) {
			any::AnyItem obj = factories[f]->create(params);
			if (!obj.isBlank()) {
				return obj;
			}
		}

		return any::AnyItem::blank();
	}

private:
	std::vector<AnyItemFactory*>& factories;
};


template <typename T>
class SimpleItemFactory : public AnyItemFactory {
public:

	template <typename S>
	struct item_create { static S create(const any::AnyItem& query) { return S(query); } };
	template <typename S>
	struct item_create<S*> { static S* create(const any::AnyItem& query) { return new S(query); } };

	SimpleItemFactory(const std::string& type) : type(type) {}
	any::AnyItem create(const any::AnyItem& query) const {
		if (query["Type"].asType<std::string>() == type) {
			return any::ValueItem<T>(item_create<T>::create(query));
		}

		return any::AnyItem::blank();
	}

private:
	std::string type;
};

} /* namespace IVGFX */

#endif /* ANYITEMFACTORY_H_ */
