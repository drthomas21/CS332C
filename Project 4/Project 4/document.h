#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <set>
#include <string>
#include <iostream>

class Document {
	private:
		std::set<std::string> characters;
	public:
		Document();
		Document(const Document&);
		Document operator=(const Document&);
		const std::set<std::string> getSet();
		void addToSet(const std::string);
		double similarity(const std::set<std::string>&);
		friend std::istream& operator>>(std::istream&, Document&);
};
#endif