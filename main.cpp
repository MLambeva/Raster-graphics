#include"PPM.h"
#include"PGM.h"
#include"PBM.h"
#include"Session.h"
#include"helperFunctions.h"
//#include<string>

std::string command;

Formats* loadAccordingToFormat(std::string path)
{
    if (helperFunctions::findFormat(path) == "ppm")
     {
        return new PPM;
     }
     else if (helperFunctions::findFormat(path) == "pgm")
     {
        return new PGM;
     }
     else if (helperFunctions::findFormat(path) == "pbm")
     {
        return new PBM;
     }
}

bool isCommand(std::string command)
{
    return command == "load" || command == "close" || command == "save" || command == "saveas" || command == "help" || command == "exit"
        || command == "grayscale" || command == "monochrome" || command == "negative" || command == "rotate right" || command == "rotate left"
        || command == "undo" || command == "add" || command == "session info" || command == "switch"
        || command == "collage";
}

void help()
{
    std::cout << "load <image> create session with unique ID.\n"
        << "close -->closes currently opened file.\n"
        << "save -->saves the currentrly open file.\n"
        << "saveas <file> -->saves the currently open file in <file>.\n"
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

void load()
{
    std::string paths;
    std::vector<std::string> path;
    Formats* form;
    std::vector<Session> session = { };
    Session helper;

    //std::cin.ignore();
    std::getline(std::cin, paths);
    path = helperFunctions::findPath(paths);
    
    for (size_t i = 0; i < path.size(); i++)
    {
        if (helperFunctions::isCorrectFileFormat(path[i]) && helperFunctions::read(path[i]))
        {
            helper.getFormats().push_back(loadAccordingToFormat(path[i]));
            helper.getFormats().back()->open(path[i]);

            std::cout << "Session with ID: " << helper.getId() << " started!\n";
            std::cout << "Image " << path[i] << " added!\n";
            session.push_back(helper);
        }
        else
        {
            std::cout << "Image " << path[i] << " is not added!\n";
        }
    }
        do
        {
            do
            {
                std::cout << ">";
               //std::cin.ignore();
                std::getline(std::cin, command);
            } while (!isCommand(command));

            if (command == "save")
            {
                //std::cout << session[Session::getId() - 1].getFormats()[0]->getPath() << '\n';
                for (size_t i = 0; i < session[(Session::getId()) - 1].getFormats().size(); i++)
                {       
                    std::cout << "CHECK\n";
                    form = loadAccordingToFormat(session[Session::getId() - 1].getFormats()[i]->getPath());
                    //std::cout << form << '\n';
                    form->save(session[Session::getId() - 1].getFormats()[i]->getPath());
                    
                    
                }
            }
            else if (command == "saveas")
            {
                std::cout << "saveas\n";
            }
            else if (command == "help")
            {
                help();
            }
            else if (command == "add")
            {
                paths.clear();
                std::cin.ignore();
                std::cin >> paths;

                if (helperFunctions::isCorrectFileFormat(paths) && helperFunctions::read(paths))
                {
                    helper.getFormats().push_back(loadAccordingToFormat(paths));
                    helper.getFormats().back()->open(paths);
                    session.push_back(helper);
                }
                std::cout << "Successfully added!: " << session[(Session::getId()) - 1].getFormats().back()->getPath() << '\n';
            }
            else if (command == "grayscale")
            {
                for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                {                    
                     session[Session::getId() - 1].getFormats()[i]->grayscale(); 
                     std::cout << "CHECK\n";
                }
                session[Session::getId() - 1].getActions().push_back("grayscale");
            }
            else if (command == "monochrome")
            {
                for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                {
                    if (session[Session::getId() - 1].getFormats()[i]->getASCIInum() == "P3")
                    {
                        session[Session::getId() - 1].getFormats()[i]->monochrome();
                    }
                }
                session[Session::getId() - 1].getActions().push_back("monochrome");
            }
            else if (command == "negative")
            {
                for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                {                    
                     session[Session::getId() - 1].getFormats()[i]->negative();                    
                }
                session[Session::getId() - 1].getActions().push_back("negative");
            }
            else if (command == "rotate right")
            {
                for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                {
                    session[Session::getId() - 1].getFormats()[i]->rotation("right");
                }
                session[Session::getId() - 1].getActions().push_back("rotate right");
            }
            else if (command == "rotate left")
            {
                for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                {
                    session[Session::getId() - 1].getFormats()[i]->rotation("left");
                }
                session[Session::getId() - 1].getActions().push_back("rotate left");
            }
            else if (command == "undo")
            {
                std::string helper = session[Session::getId() - 1].getActions().back();
                if (helper == "grayscale")
                {
                    for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                    {
                        session[Session::getId() - 1].getFormats()[i]->undoGrayscale();
                    }
                }
                else if(helper == "monochrome")
                {
                    for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                    {
                        session[Session::getId() - 1].getFormats()[i]->undoMonochrome();
                    }
                }
                else if (helper == "negative")
                {
                    for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                    {
                        session[Session::getId() - 1].getFormats()[i]->negative();
                    }
                }
                else if (helper == "rotate right")
                {
                    for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                    {
                        session[Session::getId() - 1].getFormats()[i]->rotation("left");
                    }
                    session[Session::getId() - 1].getActions().push_back("rotate left");
                }                
                else if (helper == "rotate left")
                {
                    for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                    {
                        session[Session::getId() - 1].getFormats()[i]->rotation("right");
                    }
                    session[Session::getId() - 1].getActions().push_back("rotate right");
                }
                session[Session::getId() - 1].getActions().pop_back();
            }
            else if (command == "session info")
            {
                std::cout << session[Session::getId() - 1];
            }



        } while (command != "close" && command != "exit");
    
}





int main()
{
  
    do
    {
        do
        {
            std::cout << ">";
            std::getline(std::cin, command);
        } while (!isCommand(command));
   
        if (command == "load")
        {
            load();
        }
        else if (command == "help")
        {
            help();
        }
   
    } while (command != "exit");
    //PPM ppm;
    //ppm.open("img.ppm");
    //ppm.grayscale();
    //ppm.save("img.ppm");

  
 
               
    // else if (command == "close")
    // {
    //     for (size_t i = 0; i < session.size(); i++)
    //     {
    //         std::cout << "Successfully closed " << session[i] << '\n';
    //         break;
    //     }
    // }
    // else if (command == "exit")
    // {
    //     std::cout << "Exiting the program...";
    //     break;
    // }



  
//delete[] form;
  return 0;
}