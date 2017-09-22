/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

namespace any_fw {

class Function {
public:
	virtual ~Function() {}
	const std::string& getName() const { return name; }
	virtual const any::AnyItem& getParameters() const { return parameters; }
	any::AnyItem operator()() { return (*this)(parameters); }
	virtual any::AnyItem operator()(const any::AnyItem& parameters) = 0;
	friend std::ostream& operator<<(std::ostream& stream, const Function& item);
protected:
	Function(const std::string& name) : name(name) {}
	std::string name;
	any::AnyItem parameters;
};

inline std::ostream& operator<<(std::ostream& out, const Function& method) {
	out << method.getName() << "(";
	if (method.getParameters().isValue()) { out << "\""; }
	out << method.getParameters();
	if (method.getParameters().isValue()) { out << "\""; }
	out << ");";
	return out;
}

} /* namespace any_fw */


#endif /* FUNCTION_H_ */
