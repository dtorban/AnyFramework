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
#include <map>

namespace any_fw {

class AnyItemFactory {
public:
	AnyItemFactory(const std::string& typeName) : typeName(typeName) {}
	virtual ~AnyItemFactory() {}
	const std::string& getTypeName() const { return typeName; }
	const any::AnyItem& getDefaultParameters() const { return parameters; }
	virtual any::AnyItem create(const any::AnyItem& params) const = 0;

	friend std::ostream& operator<<(std::ostream& out, const AnyItemFactory& factory);

protected:
	virtual void write(std::ostream& out) const {
		out << "create(" << getDefaultParameters() << ") : " << typeName;
	}
	any::AnyItem parameters;
private:
	std::string typeName;
};

inline std::ostream& operator<<(std::ostream& out, const AnyItemFactory& factory) {
	factory.write(out);
	return out;
}

class CompositeAnyItemFactory : public AnyItemFactory {
public:
	CompositeAnyItemFactory() : AnyItemFactory("") {}
	virtual ~CompositeAnyItemFactory() {
		for (int f = 0; f < factories.size(); f++) {
			delete factories[f];
		}
	}

	virtual void addFactory(AnyItemFactory* factory) {
		factories.push_back(factory);
	}

	any::AnyItem create(const any::AnyItem& params) const {
		for (int f = 0; f < factories.size(); f++) {
			any::AnyItem obj = factories[f]->create(params);
			if (!obj.isBlank()) {
				return obj;
			}
		}

		return any::AnyItem::blank();
	}

	void write(std::ostream& out) const {
		for (int f = 0; f < factories.size(); f++) {
			out << *factories[f] << std::endl;
		}
	}

private:
	std::vector<AnyItemFactory*> factories;
};

class GroupedAnyItemFactory : public AnyItemFactory {
public:
	GroupedAnyItemFactory() : AnyItemFactory("") {}
	virtual ~GroupedAnyItemFactory() {
		for (std::map<std::string, CompositeAnyItemFactory*>::iterator it = factories.begin(); it != factories.end(); it++) {
			delete it->second;
		}
	}

	void addFactory(const std::string& key, AnyItemFactory* factory) {
		std::map<std::string, CompositeAnyItemFactory*>::iterator it = factories.find(key);
		CompositeAnyItemFactory* cfactory = NULL;
		if (it != factories.end()) {
			cfactory = it->second;
		}
		else {
			cfactory = new CompositeAnyItemFactory();
			factories[key] = cfactory;
		}

		cfactory->addFactory(factory);
	}

	AnyItemFactory* getFactory(const std::string& key) const {
		return factories.find(key)->second;
	}

	virtual std::string getKey(const any::AnyItem& params) const = 0;

	any::AnyItem create(const any::AnyItem& params) const {
		std::string key = getKey(params);
		if (factories.find(key) != factories.end()) {
			return getFactory(key)->create(params);
		}

		return any::AnyItem::blank();
	}

	void write(std::ostream& out) const {
		for (std::map<std::string, CompositeAnyItemFactory*>::const_iterator it = factories.begin(); it != factories.end(); it++) {
			out << *it->second;
		}
	}

private:
	std::map<std::string, CompositeAnyItemFactory*> factories;
};

class GroupedAnyItemTypeFactory : public GroupedAnyItemFactory {
public:
	GroupedAnyItemTypeFactory(const std::string& typeKey = "Type") : typeKey(typeKey) {}
	std::string getKey(const any::AnyItem& params) const {
		return params[typeKey].asType<std::string>();
	}

private:
	std::string typeKey;
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
