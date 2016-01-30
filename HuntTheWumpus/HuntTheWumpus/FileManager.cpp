#include "FileManager.h"

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
	fres = fopen(filename, "r");
#endif

#ifdef _WIN32	
	fopen_s(&fres, filename, "r");
#endif

	if (fres == NULL || fres == nullptr) {
		throw FileManager::FAILED_TO_ACCESS_FILE;
	}
	fputs(message.c_str(), fres);
	fclose(fres);
	return true;
}
