#include "cFolder.h"
#include <vector>
#include <fstream>
#include <io.h>
static const std::string cDLC = "资料片DLC";
static const int cDeep = 8;

static bool isVers(std::ifstream& ifile, std::string& path) {
	if (!::_access((path + cDLC + "/dlc.exe").c_str(), 0)) {
		path += cDLC;
		return true;
	}
	return !::_access((path + "dlc.exe").c_str(), 0);
}

static void enumDir(const std::string& path, std::string& path_found, int deep) {
	if (deep > cDeep * 2) {
		return;
	}
	std::ifstream ifile;
	path_found = path;
	if (isVers(ifile, path_found)) {
		return;
	} else {
		path_found.clear();
	}
	_finddata_t file_data;
	auto str_temp = path + "*";
	auto handle = _findfirst(str_temp.c_str(), &file_data);
	if (handle == -1L) {
		return;
	}
	do {
		if (file_data.attrib & _A_SUBDIR) {
			if ((strcmp(file_data.name, ".") != 0) && (strcmp(file_data.name, "..") != 0)) {
				str_temp = path + file_data.name + "/";
				enumDir(str_temp, path_found, deep + 1);
				if (!path_found.empty()) {
					return;
				}
			}
		}
	} while (_findnext(handle, &file_data) == 0);
	_findclose(handle);
}


std::string getDLC(std::string client) {
	for (auto& c : client) {
		if (c == '\\') {
			c = '/';
		}
	}
	bool rewrite = true;
	std::string path_found;
	if (::_access(client.c_str(), 0)) {
	} else {
		std::ifstream ifile;
		ifile.open(client);
		if (ifile.is_open()) {
			//  不要 >> 小心路径空格
			getline(ifile, path_found);
			ifile.close();
			if (isVers(ifile, path_found)) {
				rewrite = false;
			}
		}
	}
	if (!rewrite) {
		return path_found;
	}
	path_found.clear();
	std::string path;
	std::ifstream ifile;

	char arr[1024];
	memset(arr, 0, sizeof(arr));
	memcpy(arr, __argv[0], strlen(__argv[0]));
	int length = -1;
	while (arr[++length] != 0) {
		if (arr[length] == '\\') {
			arr[length] = '/';
		}
	}
	int deep = 1;
	while (length > 0) {
		if (arr[--length] != '/') {
			continue;
		}
		arr[length + 1] = 0;
		if (--deep < -cDeep) {
			break;
		}
		path = arr;
		if (isVers(ifile, path)) {
			path_found = path;
			break;
		}
	}
	deep = 0;
	if (length == 0) {
		std::vector<char> chars;
		for (char c = 'D'; c <= 'N'; ++c) {
			chars.push_back(c);
		}
		chars.push_back('C');
		for (const auto& c : chars) {
			path = c;
			path = path + ":/";
			path_found.clear();
			enumDir(path, path_found, deep);
			if (path_found.size()) {
				break;
			}
		}
	}
	deep = 0;
	path = arr;
	enumDir(path, path_found, deep);

	if (path_found.size()) {
		if (path_found.back() != '/') {
			path_found.push_back('/');
		}
		std::ofstream ofile(client);
		if (ofile.is_open()) {
			ofile << path_found;
			ofile.close();
		}
	}

	return path_found;
}