/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef ASSIMPSCENE_H_
#define ASSIMPSCENE_H_

#include "object/Object.h"
#include "assimp/scene.h"

namespace any_fw {

class AssimpScene : public Object {
public:
	AssimpScene(const aiScene* scene);
	virtual ~AssimpScene();

private:
	const aiScene* scene;
};

} /* namespace any_fw */

#endif /* ASSIMPSCENE_H_ */
