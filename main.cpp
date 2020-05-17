#include"PPM.h"
#include"PGM.h"
#include"PBM.h"
#include"Session.h"
#include"helperFunctions.h"
//#include<string>

std::string command;
std::vector<Session> session = { };

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
        || command == "grayscale" || command == "monochrome" || command == "negative" || command == "rotate" 
        || command == "undo" || command == "add" || command == "session" || command == "info" || command == "switch"
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
    std::string paths = {};
    std::vector<std::string> path = {};
    std::string direction;
    std::string image1;
    std::string image2;
    std::string outimage;
    std::cin.ignore();
    std::getline(std::cin, paths);
    path = helperFunctions::findPath(paths);
    
    int counter = 0;
    for (size_t i = 0; i < path.size(); i++)
    {
        if (helperFunctions::isCorrectFileFormat(path[i]) && helperFunctions::read(path[i]))
        {
            counter++;
        }
    }

    if (counter != 0)//ima pone enda snimka
    {
        Session helper;


        for (size_t i = 0; i < path.size(); i++)
        {
            if (helperFunctions::isCorrectFileFormat(path[i]) && helperFunctions::read(path[i]))
            {
                helper.getFormats().push_back(loadAccordingToFormat(path[i]));
                helper.getFormats().back()->open(path[i]);
                helper.getActions() = {};

                std::cout << "Session with ID: " << helper.getId() << " started!\n";
                std::cout << "Image " << path[i] << " added!\n";
            }
            else
            {
                std::cout << "Image " << path[i] << " is not added!\n";
            }
        }
        session.push_back(helper);
   
     
    
        do
        {
            do
            {
                std::cout << ">";
                
                std::cin >> command;
                if (command == "session")
                {
                    std::cin >> command;
                    if (command == "info") break;
                }
                                

            } while (!isCommand(command));

            if (command == "saveas")
            {
                std::cin.ignore();
                std::getline(std::cin, paths);
                
                session[Session::getId() - 1].getFormats()[0]->saveas(paths);
                std::cout << "Successfully saved another " << session[Session::getId() - 1].getFormats()[0]->getPath() << '\n';
                
            }
            else if (command == "save")
            {
                for (size_t i = 0; i < session[(Session::getId()) - 1].getFormats().size(); i++)
                {
                    session[Session::getId() - 1].getFormats()[i]->saveas(session[Session::getId() - 1].getFormats()[i]->getPath());
                    std::cout << "Successfully saved " << session[Session::getId() - 1].getFormats()[i]->getPath() << '\n';
                }
            }
            else if (command == "help")
            {
                help();
            }
            else if (command == "add")
            {
                //paths.clear();
                std::cin.ignore();
                std::cin >> paths;

                if (helperFunctions::isCorrectFileFormat(paths) && helperFunctions::read(paths))
                {
                    session[(Session::getId()) - 1].getFormats().push_back(loadAccordingToFormat(paths));
                    session[(Session::getId()) - 1].getFormats().back()->open(paths);
                    session[(Session::getId()) - 1].addActions("add");
                    std::cout << "Successfully added!: " << session[(Session::getId()) - 1].getFormats().back()->getPath() << '\n';
                }


            }
            else if (command == "grayscale")
            {
                for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                {
                    session[Session::getId() - 1].getFormats()[i]->grayscale();
                }
                session[Session::getId() - 1].getActions().push_back("grayscale");
            }
            else if (command == "monochrome")
            {
                for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                {
                    session[Session::getId() - 1].getFormats()[i]->monochrome();
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
            else if (command == "rotate")
            {
                std::cin.ignore();
                std::cin >> direction;
                for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                {
                    session[Session::getId() - 1].getFormats()[i]->rotation(direction);
                }
                std::string helper = command + " " + direction;
                session[Session::getId() - 1].addActions(helper);
            }
            else if (command == "switch")
            {
                int id;
                std::cin.ignore();
                std::cin >> id;
                if (id >= 1 && id <= session.size())
                {
                    std::cout << "You switch to session with ID: " << id << "!\n";
                    std::cout << "Name of images in the session ";
                    for (size_t i = 0; i < session[id - 1].getFormats().size(); i++)
                    {
                        std::cout << session[id - 1].getFormats()[i]->getPath() << " ";
                    }

                    std::cout << "\nPending transformations: ";
                    for (size_t i = 0; i < session[id - 1].getActions().size(); i++)
                    {
                        std::cout << session[id - 1].getActions()[i] << ", ";
                    }
                    std::cout << '\n';
                }
                else
                {
                    std::cout << "Incorrect session with id " << id << '\n';
                }
            }
            else if (command == "undo")
            {
                if (session[Session::getId() - 1].getActions().size() != 0)
                {
                    std::string helper = session[Session::getId() - 1].getActions().back();

                    if (helper == "grayscale")
                    {
                        for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                        {
                            session[Session::getId() - 1].getFormats()[i]->undoGrayscale();
                        }
                    }
                    else if (helper == "monochrome")
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
                    }
                    else if (helper == "rotate left")
                    {
                        for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                        {
                            session[Session::getId() - 1].getFormats()[i]->rotation("right");
                        }
                    }
                    else if (helper == "add")
                    {
                        session[Session::getId() - 1].getFormats().pop_back();
                    }
                    session[Session::getId() - 1].getActions().pop_back();

                }
                else std::cout << "Cannot undo!\n";
            }
            else if (command == "info")
            {
                std::cout << session[Session::getId() - 1] << "\n";
            }
            else if (command == "collage")
            {
                std::cin.ignore();
                std::cin >> direction;
                std::cin.ignore();
                std::cin >> image1;
                std::cin.ignore();
                std::cin >> image2;
                std::cin.ignore();
                std::cin >> outimage;
                bool flag1 = false;
                bool flag2 = false;
               
                for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                {
                    if (session[Session::getId() - 1].getFormats()[i]->getPath() == image1)
                    {
                        flag1 = true; break;
                    }
                }
                for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                {
                    if (session[Session::getId() - 1].getFormats()[i]->getPath() == image2)
                    {
                        flag2 = true; break;
                    }
                }
                if (flag1 == true && flag2 == true)
                {
                    session[(Session::getId()) - 1].getFormats().push_back(loadAccordingToFormat(outimage));
                   
                    session[(Session::getId()) - 1].getFormats().back()->collage(direction, image1, image2, outimage);
                   
                    session[(Session::getId()) - 1].addActions("collage");
                    
                }
                else
                {
                    std::cout << "unable to make collage!\n";
                }          
            }
        
        } while (command != "close" && command != "exit");
        if (command == "close")
        {
            std::cout << "Successfully closed!\n";
        }
    }
    else
    {
    std::cout << "Cannot create session without correct images!\n";
    }

}





int main()
{
    do
    {
        do
        {
            std::cout << ">";
           // if (!command.empty())
            //{
           //     std::cin.ignore();
           // }          
            std::cin >> command;
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
    std::cout << "Exiting the program...\n";
   // PPM ppm;
   // ppm.open("img.ppm");
   // 
   // ppm.grayscale();
   // ppm.save("D:/2 семестър/img5.ppm"); 
               
    

  
//delete[] form;
  return 0;
}