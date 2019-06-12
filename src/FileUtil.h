#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <fstream>
#include <string>

namespace FileUtil
{
	static std::string readFile(std::string fileName)
	{
		std::ifstream stream;
		std::string line;
		std::string buffer;
		stream.open(fileName);

		while (std::getline(stream, line))
		{
			buffer.append(line.append("\n"));
		}
		stream.close();

		return buffer;
	}
}

#endif