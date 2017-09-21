/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef ASSETIMPORTER_H_
#define ASSETIMPORTER_H_

#include "object/Object.h"

namespace any_fw {

class AssetImporter : public Object {
public:
	AssetImporter(const any::AnyItem& item);
	virtual ~AssetImporter();
};

} /* namespace any_fw */

#endif /* ASSETIMPORTER_H_ */
