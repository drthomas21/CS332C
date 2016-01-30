#include <string>

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

class FileManager {
public:
	enum ERROR {FILE_NOT_FOUND,FAILED_TO_ACCESS_FILE,FAILD_TO_WRITE_TO_FILE};
	static std::string const readFile(const char* );
	static bool writeFile(const char*, const std::string);
};
#endif // FILEMANAGER_H
