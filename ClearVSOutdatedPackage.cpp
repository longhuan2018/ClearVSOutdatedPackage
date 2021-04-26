// ClearVSOutdatedPackage.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

typedef std::vector<std::string> StringList;
void split(const std::string& src, StringList& list, char separator = ' ')
{
	std::string::size_type start = src.find_first_not_of(separator);
	while (start != std::string::npos)
	{
		std::string::size_type end = src.find_first_of(separator, start);
		if (end != std::string::npos)
		{
			list.push_back(std::string(src, start, end - start));
			start = src.find_first_not_of(separator, end);
		}
		else
		{
			list.push_back(std::string(src, start, src.size() - start));
			start = end;
		}
	}
}

class VersionCompare
{
public:
	bool operator()(const std::string& lhs, const std::string& rhs)const
	{
		StringList lVals;
		split(lhs, lVals, '.');

		StringList rVals;
		split(rhs, rVals, '.');
		std::size_t count = std::min(lVals.size(), rVals.size());
		for (std::size_t i = 0U; i < count; ++i)
		{
			int l = atoi(lVals[i].c_str());
			int r = atoi(rVals[i].c_str());
			if (l != r)
				return l > r;
		}

		return lVals.size() > rVals.size();
	}
};

typedef std::map<std::string, StringList, VersionCompare > VersionFileMap;
typedef std::unordered_map<std::string, VersionFileMap> FileValueMap;

int main(int argc, char *argv[])
{
	if (argc < 2)
		return -1;

	char folderPath[MAX_PATH] = { 0 };
	strcpy_s(folderPath, MAX_PATH, argv[1]);
	if (strlen(argv[1]) == 1)
		strcat_s(folderPath, MAX_PATH, ":");
	strcat_s(folderPath, MAX_PATH, "\\*.*");

	WIN32_FIND_DATAA FindFileData = { 0 };
	HANDLE hFind = FindFirstFileA(folderPath, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
		return -1;

	FileValueMap fileValueMap;
	do
	{
		if (strcmp(FindFileData.cFileName, ".") == 0 || strcmp(FindFileData.cFileName, "..") == 0)
			continue;

		if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			std::string fileName;
			std::string chip;
			std::string language;
			std::string version;
			StringList vals;
			split(FindFileData.cFileName, vals, ',');
			for (StringList::iterator it = vals.begin(); it != vals.end(); ++it)
			{
				StringList v;
				split(*it, v, '=');
				if (v.size() == 2)
				{
					if (_stricmp(v[0].c_str(), "version") == 0)
						version = v[1];
					else if (_stricmp(v[0].c_str(), "chip") == 0)
						chip = v[1];
					else if (_stricmp(v[0].c_str(), "language") == 0)
						language = v[1];
				}
				else
					fileName = *it;
			}

			if (!fileName.empty() && !version.empty() )
			{
				std::string key = fileName + "_" + chip + "_" + language;
				std::transform(key.begin(), key.end(), key.begin(), std::tolower);
				fileValueMap[key][version].push_back(FindFileData.cFileName);
			}
		}
	}while (FindNextFileA(hFind, &FindFileData));
	FindClose(hFind);

	for (FileValueMap::iterator itf = fileValueMap.begin(); itf != fileValueMap.end(); ++itf)
	{
		if (itf->second.size() <= 1)
			continue;

		bool first = true;
		for (VersionFileMap::iterator itv = itf->second.begin(); itv != itf->second.end(); ++itv)
		{
			for (StringList::iterator it = itv->second.begin(); it != itv->second.end(); ++it)
			{
				std::cout << *it << std::endl;
				if (!first)
				{
					char folderPath[MAX_PATH] = { 0 };
					strcpy_s(folderPath, MAX_PATH, argv[1]);
					if (strlen(argv[1]) == 1)
						strcat_s(folderPath, MAX_PATH, ":");
					strcat_s(folderPath, MAX_PATH, "\\");
					strcat_s(folderPath, MAX_PATH, it->c_str());

					SHFILEOPSTRUCTA FileOp = { 0 };
					FileOp.fFlags = FOF_NOCONFIRMATION;
					FileOp.pFrom = folderPath;
					FileOp.pTo = NULL;
					FileOp.wFunc = FO_DELETE;
					SHFileOperationA(&FileOp);
				}
			}

			if (first)
			{
				std::cout << "---" << std::endl;
				first = false;
			}
		}
		std::cout << "********************" << std::endl;
	}

	return (0);
}