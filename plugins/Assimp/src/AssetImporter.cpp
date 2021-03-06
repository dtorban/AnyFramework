/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <AssetImporter.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "utilities/FileHelpers.h"
#include "AssimpScene.h"

namespace any_fw {

class AssimpImportMethod : public Object::Method {
public:
	AssimpImportMethod(Object& obj) : Method(obj, "import") {
		parameters["Path"] = std::string("");
		parameters["GenerateSmoothNormals"] = (bool)1;
	}
	any::AnyItem operator()(const any::AnyItem& parameters) {
		std::string path = parameters["Path"].asType<std::string>();

		if (fileExists(path)) {
			Assimp::Importer importer;
			unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs;
			if (parameters["GenerateSmoothNormals"].val<bool>()) {
				flags = flags | aiProcess_GenSmoothNormals;
			}
			else {
				flags = flags | aiProcess_GenNormals;
			}
			const aiScene *scene = importer.ReadFile(path, flags);

			if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
				return any::AnyItem::blank();
			}

			return any::ValueItem<AssimpScene*>(new AssimpScene(scene));
		}
		else {
			std::cout << "ERROR::ASSIMP::Path not found: " << path << std::endl;
		}

		return any::AnyItem::blank();
	}
};

AssetImporter::AssetImporter(const any::AnyItem& item) : Object("AssetImporter") {
	addMethod(new AssimpImportMethod(*this));
}

AssetImporter::~AssetImporter() {
	// TODO Auto-generated destructor stub
}

} /* namespace any_fw */
