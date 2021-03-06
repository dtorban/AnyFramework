/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <AssimpScene.h>

namespace any_fw {

AssimpScene::AssimpScene(const aiScene* scene) : Object("AssimpScene") {
	properties["NumMeshes"] = scene->mNumMeshes;
	properties["NumMaterials"] = scene->mNumMaterials;
	properties["NumTextures"] = scene->mNumTextures;
	properties["NumAnimations"] = scene->mNumAnimations;

	properties["Meshes"].toArray();

	for (int f = 0; f < scene->mNumMeshes; f++) {
		any::AnyItem mesh;
		properties["Meshes"][f]["NumVertices"] = scene->mMeshes[f]->mNumVertices;
		properties["Meshes"][f]["NumNormals"] = scene->mMeshes[f]->HasNormals() ? scene->mMeshes[f]->mNumVertices : 0;
		properties["Meshes"][f]["NumIndices"] = scene->mMeshes[f]->HasFaces() ? scene->mMeshes[f]->mNumFaces*3 : 0;
		properties["Meshes"][f]["MaterialIndex"] = scene->mMeshes[f]->mMaterialIndex;

		properties["Meshes"][f]["Vertices"] = std::vector<float>();
		std::vector<float>& vertices = properties["Meshes"][f]["Vertices"].val<std::vector<float> >();
		for (int i = 0; i < scene->mMeshes[f]->mNumVertices; i++) {
			vertices.push_back(scene->mMeshes[f]->mVertices[i].x);
			vertices.push_back(scene->mMeshes[f]->mVertices[i].y);
			vertices.push_back(scene->mMeshes[f]->mVertices[i].z);
		}

		if (scene->mMeshes[f]->HasNormals()) {
			properties["Meshes"][f]["Normals"] = std::vector<float>();
			std::vector<float>& normals = properties["Meshes"][f]["Normals"].val<std::vector<float> >();
			for (int i = 0; i < scene->mMeshes[f]->mNumVertices; i++) {
				normals.push_back(scene->mMeshes[f]->mNormals[i].x);
				normals.push_back(scene->mMeshes[f]->mNormals[i].y);
				normals.push_back(scene->mMeshes[f]->mNormals[i].z);
			}
		}

		if (scene->mMeshes[f]->HasFaces()) {
			properties["Meshes"][f]["Indices"] = std::vector<unsigned int>();
			std::vector<unsigned int>& indices = properties["Meshes"][f]["Indices"].val<std::vector<unsigned int> >();
			for (int i = 0; i < scene->mMeshes[f]->mNumFaces; i++) {
				indices.push_back(scene->mMeshes[f]->mFaces[i].mIndices[0]);
				indices.push_back(scene->mMeshes[f]->mFaces[i].mIndices[1]);
				indices.push_back(scene->mMeshes[f]->mFaces[i].mIndices[2]);
			}
		}
	}
}

AssimpScene::~AssimpScene() {
}

} /* namespace any_fw */
