/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <AssimpScene.h>

namespace any_fw {

AssimpScene::AssimpScene(const aiScene* scene) : Object("AssimpScene"), scene(scene) {
	properties["NumMeshes"] = scene->mNumMeshes;
	properties["NumMaterials"] = scene->mNumMaterials;
	properties["NumTextures"] = scene->mNumTextures;
	properties["NumAnimations"] = scene->mNumAnimations;

	properties["Meshes"].toArray();

	for (int f = 0; f < scene->mNumMeshes; f++) {
		any::AnyItem mesh;
		properties["Meshes"][f]["NumVertices"] = scene->mMeshes[f]->mNumVertices;
	}
}

AssimpScene::~AssimpScene() {
	delete scene;
}

} /* namespace any_fw */
