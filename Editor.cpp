#include"Editor.h"

std::vector<Session> Editor::session;
std::string Editor::command;

Formats* Editor::loadAccordingToFormat(std::string path)
{//����� ����� ��� �������, ����� ����������� �� ��������� �����.
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
    else return nullptr;
}

bool Editor::isCommand(std::string command)//��������� �� ���������� �� ��������� ���.
{
    return command == "load" || command == "close" || command == "save" || command == "saveas" || command == "help" || command == "exit"
        || command == "grayscale" || command == "monochrome" || command == "negative" || command == "rotate"
        || command == "undo" || command == "add" || command == "session" || command == "info" || command == "switch"
        || command == "collage";
}

void Editor::help()//������� ������ ���������� �� ������������ �� ���������� �������.
{
    std::cout << "load <image> create session with unique ID.\n"
        << "close --> closes currently opened file.\n"
        << "save --> saves the currentrly load file.\n"
        << "saveas <file> --> saves the currently load file in <file>.\n"
        << "help --> prints this information.\n"
        << "exit --> exist the program.\n"
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

std::string Editor::findFormat(std::string path)//����� ������������ �� �����.
{
    std::string helper;//������� ����������, � ����� ��������� ������������.
    for (int i = path.size() - 1; i >= 0; i--)
    {
        if (path[i] == '.')break;//����� ����� ������, ������ ������ �� �����.
        helper = path[i] + helper;
    }
    return helper;
}

bool Editor::isCorrectFileExtension(std::string extension)//��������� ���� ���������� ���������� �� �������� �� ����������.
{
    return extension == "ppm" || extension == "pgm" || extension == "pbm";
}

std::vector<std::string> Editor::findPath(std::string paths)//��� � ���� ������ ��� ������� ������, �.�. ������� ������, �� ���� ������� �� ������.
{
    std::vector<std::string> saver;//����������, � ����� ��������� ����� ������� ����� � � ������� ���� ��������.
    std::string helper;//����������, � ����� ��������� ��������� �����.
    std::string help;//����������, � ����� ��������� ����������, �� �� ���������� �� ����������.
    for (int i = paths.size() - 1; i >= 0; i--)//��������� ����� ������.
    {
        if (paths[i] != ' ')//������ �� ������� �� ��������, �������� ����� ����� � ������������ "helper".
        {
            helper = paths[i] + helper;
        }
        else if (paths[i] == ' ')/*��� ������� �� ��������, ����������� ���� ���������� �����, ����� ���������, 
         ��������� �������� ���������� � ��� ���������, �� ����� ������ �� ���� ������� ��� ����� � ������ � ������������ 
         "helper" ����� ������� ���� �����, ����� �������� ��� ������������ "saver" � ���������� "helper",
         �� �� ���� ������ �� � ��������, ��� �� - �� ����� ������ � ������ ��� ������ ����� � ������������ �� �� ����������.*/
        {
            help.clear();
            for (int j = i - 1; j >= i - 3 && j >= 0; j--)
            {
                help = paths[j] + help;
            }
            if (isCorrectFileExtension(help))
            {
                saver.push_back(helper);
                helper.clear();
            }
            else
            {
                helper = paths[i] + helper;
            }
        }
    }
    saver.push_back(helper);
    return saver;
}

bool Editor::isCorrectFileFormat(std::string path)//��������� �� ����� ����� ���� � �������� ������������.
{
    return findFormat(path) == "ppm" || findFormat(path) == "pgm" || findFormat(path) == "pbm";
}

void Editor::addEffectToPPM(Session& other, std::string effect)//������� ������� �� �������� �� ������������� � ������ �����.
{//�������� �� ���� ��� ".ppm" ������, ������ ����������� ��������� "grayscale" � "monochrome", ������ �� �� ������� ���� �� ���� ������.
    for (size_t i = 0; i < other.Formats().size(); i++)
    {
        if (findFormat(other.Formats()[i]->getPath()) == "ppm")
        {
            other.Transformations().push_back(effect);
            break;
        }
    }
}

bool Editor::read(std::string path)//��������� ���� ����������� �� ������ � �����.
{
    std::ifstream input(path.c_str());
    return input.good();
}

int Editor::countExistedImage(std::vector<std::string> path)
{
    //�����, ���� ����� ����������� ���� ��� ��������� �� �������������, ��� ������ � ������� �����, ������ ��� ����, �� ����� ��� ������ � �����������.
    int counter = 0;
    for (size_t i = 0; i < path.size(); i++)
    {
        if (isCorrectFileFormat(path[i]) && read(path[i]))
        {
            counter++;
        }
    }
    return counter;
}

void Editor::commandGrayscale(Session& other)
{
    for (size_t i = 0; i < other.Formats().size(); i++)
    {
        other.Formats()[i]->grayscale();
    }
    addEffectToPPM(other, "grayscale");//������, �� � ��������� ������������� ���� ��� ��� ���� ���� ����������� �� ".ppm" ������.  
}

void Editor::commandMonochrome(Session& other)
{
    for (size_t i = 0; i < other.Formats().size(); i++)
    {
        other.Formats()[i]->monochrome();
    }
    addEffectToPPM(other, "monochrome"); //������, �� � ��������� ������������� ���� ��� ��� ���� ���� ����������� �� ".ppm" ������.  
}

void Editor::commandNegative(Session& other)
{
    for (size_t i = 0; i < other.Formats().size(); i++)
    {
        other.Formats()[i]->negative();
    }
    other.Transformations().push_back("negative");
}

void Editor::commandSaveas(Session& other, std::string paths)
{
    std::cin.ignore();
    std::getline(std::cin, paths);//��������� ���� � � ����� ��� ������ �� ������� ������� �������� ����������� � �������.
    if (findFormat(paths) == findFormat(other.Formats()[0]->getPath()))
    {//��� ��� ���������� �� ������������ �� ������������� � ���������� ����������, �� ������ �� ���������.
        other.Formats()[0]->saveas(paths);
        std::cout << "Successfully saved another " << other.Formats()[0]->getPath() << '\n';
        other.Transformations().clear();
    }    
    else std::cout << "Incorrect file format!\n";   
}

void Editor::commandSave(Session& other)
{
    for (size_t i = 0; i < other.Formats().size(); i++)
    {
        other.Formats()[i]->saveas(other.Formats()[i]->getPath());
        std::cout << "Successfully saved " << other.Formats()[i]->getPath() << '\n';
    }
    other.Transformations().clear();
}

void Editor::commandAdd(Session& other, std::string paths)
{
    if (isCorrectFileFormat(paths) && read(paths))
    {
        other.Formats().push_back(loadAccordingToFormat(paths));
        other.Formats().back()->load(paths);
        other.addTransformations("add");
        std::cout << "Successfully added: " << other.Formats().back()->getPath() << '\n';
    }
    else
    {
        std::cout << "Unsuccessfully added!: " << paths << '\n';
    }
}

void Editor::commandRotation(Session& other)
{
    std::string direction;
    std::cin.ignore();
    std::cin >> direction;
    for (size_t i = 0; i < other.Formats().size(); i++)
    {
        other.Formats()[i]->rotation(direction);
    }
    std::string helper = command + " " + direction;
    other.addTransformations(helper);
}

void Editor::commandSwitchSession()
{
    size_t id;
    std::cin.ignore();
    std::cin >> id;
    if (id >= 1 && id <= session.size())
    {
        std::cout << "You switch to session with ID: " << id << "!\n";
        std::cout << "Name of images in the session ";
        for (size_t i = 0; i < session[id - 1].Formats().size(); i++)
        {
            std::cout << session[id - 1].Formats()[i]->getPath() << " ";
        }
        
        std::cout << "\nPending transformations: ";
        for (size_t i = 0; i < session[id - 1].Transformations().size(); i++)
        {
            std::cout << session[id - 1].Transformations()[i] << ", ";
        }
        std::cout << '\n';
    }
    else
    {
        std::cout << "Incorrect session with id " << id << '\n';
    }
}

void Editor::commandUndo(Session& other)
{
    if (other.Transformations().size() != 0)//��� ��� ���� ���� �������:
    {
        std::string helper = other.Transformations().back();//���������� � �� ������� � �������������.
        //� ���������� �� ����������� �������������, �������� ���������.
        if (helper == "grayscale")
        {
            for (size_t i = 0; i < other.Formats().size(); i++)
            {
                other.Formats()[i]->undoGrayscale();
            }
        }
        else if (helper == "monochrome")
        {
            for (size_t i = 0; i < other.Formats().size(); i++)
            {
                other.Formats()[i]->undoMonochrome();
            }
        }
        else if (helper == "negative")
        {
            for (size_t i = 0; i < other.Formats().size(); i++)
            {
                other.Formats()[i]->negative();
            }
        }
        else if (helper == "rotate right")
        {
            for (size_t i = 0; i < other.Formats().size(); i++)
            {
                other.Formats()[i]->rotation("left");
            }
        }
        else if (helper == "rotate left")
        {
            for (size_t i = 0; i < other.Formats().size(); i++)
            {
                other.Formats()[i]->rotation("right");
            }
        }
        else if (helper == "add")
        {
            other.Formats().pop_back();
        }
        other.Transformations().pop_back();

    }
    else std::cout << "Cannot undo!\n";//��� ���� ������������.
}

void Editor::commandCollage(Session& other)
{       
    std::string direction;//����������, ����� ����������, ������ ��������� ������ �� ��������� �� �����. 
    std::string path;//����������, � ����� � �������� �� ����� 3 ������.
    std::vector<std::string> paths;
    std::cin.ignore();
    std::cin >> direction;//������������ ��� ����������.
    std::cin.ignore();
    std::getline(std::cin, path);//������ �� 3-�� �����������.
   
    //������ ����������, ���� ����� ����������� ���� ����������� ����� �������� ����������� � �������� �����.
    bool flag1 = false;
    bool flag2 = false;

    paths = findPath(path);//�������� 3-�� ������.
   
    std::string image1 = paths[2];
    std::string image2 = paths[1];
    std::string outimage = paths[0];
    for (size_t i = 0; i < other.Formats().size(); i++)
    {
        if (other.Formats()[i]->getPath() == image1)
        {
            flag1 = true;
        }
        if (other.Formats()[i]->getPath() == image2)
        {
            flag2 = true;
        }
    }
    //��� ���������� ����������� �� ��������, ��������� �����.
    if (flag1 == true && flag2 == true && countExistedImage(paths) == 2 &&  //�������������� ����������� �� ���, ������ ������� �� ���������.
       (findFormat(image1) == findFormat(outimage)) && (findFormat(image2) == findFormat(outimage)))
    {      
        /*������� ����� �� ��� ����������� <image1> � <image2> (� ���� � ��� ������ � ���� � ���� ����������),
           ������� � �������� �����. ���������� �� ������� � ���� ����������� <outimage>, ����� �� ������ � �������� �����.*/
        other.Formats().push_back(loadAccordingToFormat(outimage));
        other.Formats().back()->collage(direction, image1, image2, outimage);
        other.addTransformations("collage");        
        std::cout << "New collage \"" << outimage << "\" created!\n";
    }
    else std::cout << "Unable to make collage!\n";
}

void Editor::load()//�������� �������, ��������� ����� � ���������� ��������� �������� �� �������������.
{    
    std::string paths = {};//����������, ���� ����� ��������� �����/� �� �����������/�.
      
    std::cin.ignore();
    std::getline(std::cin, paths);//��������� �����/� �� �����������/�.
    std::vector<std::string> path = Editor::findPath(paths);//�������� ���������� �������, �� �� �� ����� ���� �� ����.

    if (countExistedImage(path) != 0)//��� ��� ���� ���� ������, �� ��������� ����� � �������� ���������������� �����.
    {
        session.push_back(Session());
        std::cout << "Session with ID: " << session.back().getId() << " started!\n";
        for (int i = path.size() - 1; i >= 0; i--)
        {
            if (isCorrectFileFormat(path[i]) && read(path[i]))
            {           
                session.back().Formats().push_back(loadAccordingToFormat(path[i]));//�������� ������������� ������ ���� ��.           
                session.back().Formats().back()->load(path[i]);//������� ���������� �� ����.
                session.back().Transformations() = {};//���� ������� ������������� ��� ���.
                std::cout << "Image " << path[i] << " added!\n";
            }
            else
            {
                std::cout << "Image " << path[i] << " is not added!\n";
            }
        }
        do
        {
            do//��������� �������, ����� ������ �� � �������.
            {                
                std::cout << ">";

                std::cin >> command;
                if (command == "session")
                {
                    std::cin >> command;
                    if (command == "info") break;
                }

            } while (!isCommand(command));

            if (command == "saveas")//������� ����������� ������� ��� ����, ���� ��������� �� ����������� �� ����� ������� ���.
            {
                commandSaveas(session[Session::getId() - 1], paths);
            }
            else if (command == "save")//������� ����������� ������� ������� � ����� ����, �� ����� �� ���� ��������� �������.
            {
                commandSave(session[Session::getId() - 1]);
            }
            else if (command == "help")//������� ������ ���������� �� ������������ �� ���������� �������.
            {
                help();
            }
            else if (command == "add")//������ ����������� ��� �������� �����. 
            {
                std::cin.ignore();
                std::getline(std::cin, paths);
                commandAdd(session[Session::getId() - 1], paths);
            }
            else if (command == "grayscale")//������� ��������� �� �� � ��� �����. ������� ���� ����� ������ ����������� �� ".ppm" ������.
            {
                commandGrayscale(session[Session::getId() - 1]);
            }
            else if (command == "monochrome")//������� ��������� �� �� ����� ��� ����. ������� ���� ����� ������ ����������� �� ".ppm" ������.
            {
                commandMonochrome(session[Session::getId() - 1]); 
            }
            else if (command == "negative")//������� ��������. ������� ����� ������ ������� � ������ ����������� � �������.
            {
                commandNegative(session[Session::getId() - 1]);
            }
            else if (command == "rotate")//��������� �� ������������� � ������� �� 90� � ���������� �� ���������� ������.
            {
                commandRotation(session[Session::getId() - 1]);
            }
            else if (command == "switch")//���������� ��� ����� � ���������������� ����� <session>.
            {
                commandSwitchSession();                
            }
            else if (command == "undo")//�������� �������� ����������� ������������� � �������� �����.
            {
                 commandUndo(session[Session::getId() - 1]);
            }
            else if (command == "info")//������� ���������� �� �������.
            {
                std::cout << session[Session::getId() - 1] << "\n";
            }
            else if (command == "collage")
            {
                commandCollage(session[Session::getId() - 1]);
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

void Editor::start()
{
    do
    {
        do
        {
            std::cout << ">";
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

    //���������� ���������� �����.
    for (size_t i = 0; i < session.size(); i++)
    {
        for (size_t j = 0; j < session[i].Formats().size(); j++)
        {
            delete session[i].Formats()[j];
        }
    }

}