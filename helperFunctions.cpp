#include"helperFunctions.h"

std::string helperFunctions::findFormat(std::string path)
{
    std::string helper;
    for (int i = path.size() - 1; i >= 0; i--)
    {
        if (path[i] == '.')break;
        helper = path[i] + helper;
    }
    return helper;
}

std::vector<std::string> helperFunctions::findPath(std::string paths)
{
    std::vector<std::string> saver;
    std::string helper;
    int k = 0;
    for (size_t i = 0; i < paths.size(); i++)
    {
        if ((int)paths[i] != 32)
        {
            helper.push_back(paths[i]);
        }
        else
        {
            saver.push_back(helper);
            helper.clear();
        }
    }
    saver.push_back(helper);
    return saver;
}

bool helperFunctions::isCorrectFileFormat(std::string path)
{
    return findFormat(path) == "ppm" || findFormat(path) == "pgm" || findFormat(path) == "pbm";
}

bool helperFunctions::read(std::string path)
{
    std::ifstream input(path.c_str());
    return input.good();
}