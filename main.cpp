#include"PPM.h"
#include"PGM.h"
#include"PBM.h"
#include"Session.h"
//#include<string>

std::string findFormat(std::string path)
{
	std::string helper;
	for (int i = path.size() - 1; i >= 0; i--)
	{
		if (path[i] == '.')break;
		helper = path[i] + helper;
	}
	return helper;
}

std::vector<std::string> findPath(std::string paths)
{
    std::vector<std::string> saver;
    std::string helper;
    int k = 0;
    for (int i = 0; i < paths.size(); i++)
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

bool isCorrectFileFormat(std::string path)
{
    return findFormat(path) == "ppm" || findFormat(path) == "pgm" || findFormat(path) == "pbm";
}

bool read(std::string path)
{
    std::ifstream input(path.c_str());
    return input.good();
}

Formats* loadAccordingToFormat(std::string path)
{
    if (findFormat(path) == "ppm")
     {
        return new PPM;
     }
     else if (findFormat(path) == "pgm")
     {
        return new PGM;
     }
     else if (findFormat(path) == "pbm")
     {
        return new PBM;
     }
}

int main()
{
  std::string command;
  std::string action;
  std::string paths;//////

  Formats* form;///////
 
  std::vector<std::string> path;/////
  
  
  std::vector<Session> session;
  int currentSession;
 
  do
  {
     
  	do
    {
        std::cout << ">";
        std::cin >> command;
        
        if (command == "load")
        {
            std::cin.ignore();
            std::getline(std::cin, paths);

            path = findPath(paths);


            for (int i = 0; i < path.size(); i++)
            {
                if (isCorrectFileFormat(path[i]) && read(path[i]))
                {
                    form = loadAccordingToFormat(path[i]);
                    form->load(path[i]);
                    Session helper;
                    helper.getFormats().push_back(form);
                   // helper.getPath().push_back(path[i]);
                    helper.addPath(path[i]);
                    
                    currentSession = helper.getId();
                    std::cout << "Session with ID: " << helper.getId() << " started!\n";
                    std::cout << "Image " << path[i] << " added!\n";
                    session.push_back(helper);
                    
                }
                else
                {
                    std::cout << "Image " << path[i] << " is not added!\n";
                }
            }
        }
        else if (command == "close")
        {
            for (size_t i = 0; i < session.size(); i++)
            {
                std::cout << "Successfully closed " << session[i] <<'\n';
            }
        }
        else if (command == "add")
        {
            std::cin.ignore();
            std::cin >> paths;
            
            if (isCorrectFileFormat(paths) && read(paths))
            {
                loadAccordingToFormat(paths);
                session[currentSession-1].addPath(paths);
              // session[currentSession-1].getPath().push_back(paths);
                session[currentSession-1].getFormats().push_back(form);
                
            }
            std::cout << "Successfully added!: " << session[currentSession-1] << '\n';
        
        }
      
  
  
  
  	} while (command == "close");
  } while (command != "exit");
  if (command == "exit")
  {
      std::cout << "Exiting the program...";
  }
//  delete[] form;
  return 0;
}