#include"PPM.h"
#include"PGM.h"
#include"PBM.h"
#include"Session.h"
#include"helperFunctions.h"

//Глобални променливи
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
    else return nullptr;
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

        std::cout << "Session with ID: " << helper.getId() << " started!\n";
        for (int i = path.size() - 1; i >= 0; i--)
        {
            if (helperFunctions::isCorrectFileFormat(path[i]) && helperFunctions::read(path[i]))
            {
                helper.getFormats().push_back(loadAccordingToFormat(path[i]));
                helper.getFormats().back()->load(path[i]);
                helper.getTransformations() = {};
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

            } while (!helperFunctions::isCommand(command));

            if (command == "saveas")
            {
                std::cin.ignore();
                std::getline(std::cin, paths);
                if (helperFunctions::findFormat(paths) == helperFunctions::findFormat(session[Session::getId() - 1].getFormats()[0]->getPath()))
                {
                    session[Session::getId() - 1].getFormats()[0]->saveas(paths);
                    std::cout << "Successfully saved another " << session[Session::getId() - 1].getFormats()[0]->getPath() << '\n';
                }
                else std::cout << "Incorrect file format!\n";
                
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
                helperFunctions::help();
            }
            else if (command == "add")
            {
                std::cin.ignore();
                std::getline(std::cin, paths);
                if (helperFunctions::isCorrectFileFormat(paths) && helperFunctions::read(paths))
                {
                    session[(Session::getId()) - 1].getFormats().push_back(loadAccordingToFormat(paths));
                    session[(Session::getId()) - 1].getFormats().back()->load(paths);
                    session[(Session::getId()) - 1].addTransformations("add");
                    std::cout << "Successfully added!: " << session[(Session::getId()) - 1].getFormats().back()->getPath() << '\n';
                }
                else
                {
                    std::cout << "Unsuccessfully added!: " << paths << '\n';
                }
            }
            else if (command == "grayscale")
            {
                for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                {
                    session[Session::getId() - 1].getFormats()[i]->grayscale();
                }
                session[Session::getId() - 1].getTransformations().push_back("grayscale");
            }
            else if (command == "monochrome")
            {
                for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                {
                    session[Session::getId() - 1].getFormats()[i]->monochrome();
                }
                session[Session::getId() - 1].getTransformations().push_back("monochrome");
            }
            else if (command == "negative")
            {
                for (size_t i = 0; i < session[Session::getId() - 1].getFormats().size(); i++)
                {
                    session[Session::getId() - 1].getFormats()[i]->negative();
                }
                session[Session::getId() - 1].getTransformations().push_back("negative");
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
                session[Session::getId() - 1].addTransformations(helper);
            }
            else if (command == "switch")
            {
                size_t id;
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
                    for (size_t i = 0; i < session[id - 1].getTransformations().size(); i++)
                    {
                        std::cout << session[id - 1].getTransformations()[i] << ", ";
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
                if (session[Session::getId() - 1].getTransformations().size() != 0)
                {
                    std::string helper = session[Session::getId() - 1].getTransformations().back();

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
                    session[Session::getId() - 1].getTransformations().pop_back();

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
                   
                    session[(Session::getId()) - 1].addTransformations("collage");
                    
                }
                else
                {
                    std::cout << "Unable to make collage!\n";
                }          
            }
        
        } while (command != "close" && command != "exit");
        if (command == "close")
        {
            std::cout << "Successfully closed!\n";
        }
        for (size_t i = 0; i < helper.getFormats().size(); i++)
        {
            delete helper.getFormats()[i];
        }
    }
    else
    {
    std::cout << "Cannot create session without correct images!\n";
    }


}



////////////////////destryktyr i monochrome!!!

int main()
{
    do
    {
        do
        {
            std::cout << ">";         
            std::cin >> command;
        } while (!helperFunctions::isCommand(command));
    
        if (command == "load")
        {
            load();
        }
        else if (command == "help")
        {
            helperFunctions::help();
        }
    
    } while (command != "exit");
    std::cout << "Exiting the program...\n";

   
    
  

  return 0;
}