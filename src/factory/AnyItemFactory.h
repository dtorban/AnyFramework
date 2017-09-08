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

namespace any_fw {

class AnyItemFactory {
public:
	AnyItemFactory(const std::string& typeName) : typeName(typeName) {}
	virtual ~AnyItemFactory() {}
	const std::string& getTypeName() const { return typeName; }
	const any::AnyItem& getDefaultParameters() const { return parameters; }
	virtual any::AnyItem create(const any::AnyItem& params) const = 0;
protected:
	any::AnyItem parameters;
private:
	std::string typeName;
};

class CompositeAnyItemFactory : public AnyItemFactory {
public:
	CompositeAnyItemFactory(std::vector<AnyItemFactory*>& factories) : AnyItemFactory(""), factories(factories) {}
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

class AnyItemTypeFactory : public AnyItemFactory {
public:
	AnyItemTypeFactory(const std::string& typeName) : AnyItemFactory(typeName) {
		parameters["Type"] = getTypeName();
	}

	any::AnyItem create(const any::AnyItem& query) const {
		if (query["Type"].asType<std::string>() == getTypeName()) {
			return createItem(query);
		}

		return any::AnyItem::blank();
	}

protected:
	virtual any::AnyItem createItem(const any::AnyItem& query) const = 0;
};

template <typename T>
class SimpleItemFactory : public AnyItemFactory {
public:
	template <typename S>
	struct item_create { static S create(const any::AnyItem& query) { return S(query); } };
	template <typename S>
	struct item_create<S*> { static S* create(const any::AnyItem& query) { return new S(query); } };

	SimpleItemFactory(const std::string& typeName) : AnyItemFactory(typeName) {
		parameters["Type"] = typeName;
	}
	any::AnyItem create(const any::AnyItem& query) const {
		if (query["Type"].asType<std::string>() == getTypeName()) {
			return any::ValueItem<T>(item_create<T>::create(query));
		}

		return any::AnyItem::blank();
	}
};

} /* namespace any_fw */

#endif /* ANYITEMFACTORY_H_ */
