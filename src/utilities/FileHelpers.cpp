#include "FileHelpers.h"

#if defined(WIN32)
//#include <winsock2.h>
#include <Windows.h>
//#include <winsock2.h>
#else
#include <dirent.h> 
#endif

#include <iostream>
#include <fstream>

#include <string>
#include <sys/types.h>
#include <sys/stat.h>

#include <vector>
namespace IVGFX {

	std::vector<std::string> listDirectory(
		const std::string& path, bool directories, std::string extension) {
		std::vector<std::string> files;

		std::string searchString = std::string("*") + extension;

#if defined(WIN32)
		char search_path[300];
		if (path[path.size() - 1] == '/') {
			sprintf(search_path, "%s%s", path.c_str(), searchString.c_str());
		}
		else {
			sprintf(search_path, "%s/%s", path.c_str(), searchString.c_str());
		}
		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile(search_path, &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				if (directories && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					files.push_back(fd.cFileName);
				}
				else if (((fd.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) || (fd.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)))
				{
					files.push_back(fd.cFileName);
				}
			} while (::FindNextFile(hFind, &fd));
			::FindClose(hFind);
		}
		else {
			/* could not open directory */
			//perror ("");
		}
#else
		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir(path.c_str())) != NULL) {
			/* print all the files and directories within directory */
			while ((ent = readdir(dir)) != NULL) {
				if (directories && ent->d_type == DT_DIR)
				{
					files.push_back(ent->d_name);
				}
				else if (ent->d_type == DT_REG)
				{
					std::string fileName = ent->d_name;
					if (searchString == "*" || fileName.find(extension) != std::string::npos) {
						files.push_back(ent->d_name);
					}
				}
			}
			closedir(dir);
		}
		else {
			/* could not open directory */
			//perror ("");
		}
#endif

		return files;
	}

	void makeDirectory(const std::string& path) {
		/*mode_t nMode = 733;
		int nError = 0;
#if defined(WIN32)
		nError = _mkdir(path.c_str());
#else
		nError = mkdir(path.c_str(), nMode);
#endif
		if (nError != 0) {
			std::cout << "There was an error in creating directory: " << path << std::endl;
		}*/
	}
}
