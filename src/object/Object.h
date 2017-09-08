/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "AnyItem/AnyItem.h"
#include <vector>
#include <string>
#include <typeinfo>
#include <map>
#include <set>

namespace any_fw {

class Object {
	friend class Method;
public:
	class Method {
	public:
		virtual ~Method() {}
		const std::string& getName() const { return name; }
		virtual const any::AnyItem& getParameters() const { return parameters; }
		any::AnyItem operator()() { return (*this)(parameters); }
		virtual any::AnyItem operator()(const any::AnyItem& parameters) = 0;
		friend std::ostream& operator<<(std::ostream& stream, const Method& item);
	protected:
		Method(Object& obj, const std::string& name) : name(name), obj(obj) {}
		std::string name;
		any::AnyItem parameters;
		Object& obj;
	};

	class MethodSet {
	public:
	public:
		MethodSet(std::map<std::string, Method*>& methods) : methods(methods) {}
		Method& operator[](const std::string& name) { return *methods[name]; }
	private:
		std::map<std::string, Method*>& methods;
	};

	Object(const std::string& name) : name(name), Methods(methods) {}
	virtual ~Object();
	const std::string& getName() const { return name; }
	const any::AnyItem& getProperties() const { return properties; }
	const std::map<std::string, Method*>& getMethods() const { return methods; }
	const std::set<const std::type_info*>& getTypes() const { return types; }
	friend std::ostream& operator<<(std::ostream& stream, const Object& item);

	MethodSet Methods;

private:
	std::string name;
	std::set<const std::type_info*> types;

protected:
	any::AnyItem properties;
	std::map<std::string, Method*> methods;
	template <typename T>
	void addType() {
		types.insert(&typeid(T));
	}
};

inline Object::~Object() {
	for (std::map<std::string, Object::Method*>::iterator it = methods.begin(); it != methods.end(); it++) {
			delete it->second;
	}
}

inline std::ostream& operator<<(std::ostream& out, const Object& obj) {
	out << "" << obj.getName();
	const std::set<const std::type_info*>& types = obj.getTypes();
	if (types.size() > 0) {
		out << " :\n\t// Types";
	}
	int count = 0;
	for (std::set<const std::type_info*>::const_iterator it = types.begin(); it != types.end(); it++) {
		if (count > 0) {
			out << ",";
		}
		out << std::endl;
		out << "\t"<< (*(*it)).name();
		count++;
	}
	for (int f = 0; f < types.size(); f++) {
	}
	out << std::endl << "{" << std::endl;
	out << "\t// Properties\n\t" << obj.getProperties() << std::endl;
	const std::map<std::string, Object::Method*>& methods = obj.getMethods();
	out << "\n\t// Methods\n";
	for (std::map<std::string, Object::Method*>::const_iterator it = methods.begin(); it != methods.end(); it++) {
		out << "\t" << *it->second << std::endl;
	}
	out << "};";
	return out;
}

inline std::ostream& operator<<(std::ostream& out, const Object::Method& method) {
	out << method.getName() << "(";
	if (method.getParameters().isValue()) { out << "\""; }
	out << method.getParameters();
	if (method.getParameters().isValue()) { out << "\""; }
	out << ");";
	return out;
}

} /* namespace any_fw */

#endif /* OBJECT_H_ */
