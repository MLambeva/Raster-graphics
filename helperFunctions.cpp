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

bool helperFunctions::isOneDigit(int x)
{
    return x >= 0 && x <= 9;
}

bool helperFunctions::isTwoDigit(int x)
{
    return x >= 10 && x <= 99;
}

bool helperFunctions::isThreeDigit(int x)
{
    return x >= 100 && x <= 255;
}

bool helperFunctions::isCommand(std::string command)
{
    return command == "load" || command == "close" || command == "save" || command == "saveas" || command == "help" || command == "exit"
        || command == "grayscale" || command == "monochrome" || command == "negative" || command == "rotate"
        || command == "undo" || command == "add" || command == "session" || command == "info" || command == "switch"
        || command == "collage";
}

void helperFunctions::help()
{
    std::cout << "load <image> create session with unique ID.\n"
        << "close -->closes currently opened file.\n"
        << "save -->saves the currentrly load file.\n"
        << "saveas <file> -->saves the currently load file in <file>.\n"
        << "help -->prints this information.\n"
        << "exit -->exist the program.\n"
        << "grayscale --> change the image to grayscale.\n"
        << "monochrome --> change the image to monochrome.\n"
        << "negative --> change the image to negative.\n"
        << "rotate <direction> --> rotate image right ot left.\n"
        << "undo --> return command back.\n"
        << "add <image> --> add image to session.\n"
        << "session info --> display information about session.\n"
        << "switch <session> --> switch session to another with ID <session>.\n"
        << "collage <direction> <image1> <image2> <outimage> "
        << "--> create collage with horizontal ot vertical <direction> and save them in new image <outimage>.\n";
}