/*
 * Copyright Regents of the University of Minnesota, 2016.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Seth Johnson (joh08230)
 */

#include <vector>
#include <string> 
#include <fstream>

#ifndef FILE_HELPERS_H_
#define FILE_HELPERS_H_
namespace any_fw {
	inline bool fileExists(const std::string& fileName)
	{
		std::ifstream infile(fileName.c_str());
		return infile.good();
	}

	std::vector<std::string> listDirectory(
		const std::string& path, bool directories, std::string extension = "");

	void makeDirectory(const std::string& path);
}

#endif

