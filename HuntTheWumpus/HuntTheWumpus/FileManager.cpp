#include "FileManager.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <iostream>

std::string const FileManager::readFile(const char* filename) {
	const int bitLimit = 100;
	char* buffered = new char[bitLimit];
	std::string serialized = "";
	FILE* fres = nullptr;

#ifdef linux
	fres = fopen(filename, "r");
#endif

#ifdef _WIN32	
	fopen_s(&fres, filename, "r");
#endif

	if (fres == NULL || fres == nullptr) {
		throw FileManager::FILE_NOT_FOUND;
	}

	while (fgets(buffered, bitLimit, fres) != NULL) {
		serialized.append(buffered);
	}

	delete[] buffered;
	fclose(fres);
	return serialized;
}

bool FileManager::writeFile(const char* filename, const std::string message) {
	FILE* fres = nullptr;

#ifdef linux
	fres = fopen(filename, "w+");
#endif

#ifdef _WIN32	
	fopen_s(&fres, filename, "w+");
#endif

	if (fres == NULL || fres == nullptr) {
		throw FileManager::FILE_NOT_FOUND;
	}
	fputs(message.c_str(), fres);
	if (ferror(fres)) {
		throw FileManager::FAILD_TO_WRITE_TO_FILE;
	}
	fclose(fres);
	return true;
}
