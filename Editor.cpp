#include"Editor.h"

std::vector<Session> Editor::session;
std::string Editor::command;

Formats* Editor::loadAccordingToFormat(std::string path)
{//Връща обект към формата, който съответства на зададения адрес.
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

bool Editor::isCommand(std::string command)//Проверява за коректност на командния ред.
{
    return command == "load" || command == "close" || command == "save" || command == "saveas" || command == "help" || command == "exit"
        || command == "grayscale" || command == "monochrome" || command == "negative" || command == "rotate"
        || command == "undo" || command == "add" || command == "session" || command == "info" || command == "switch"
        || command == "collage";
}

void Editor::help()//Извежда кратка информация за поддържаните от програмата команди.
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

std::string Editor::findFormat(std::string path)//Връща разширението на файла.
{
    std::string helper;//Помощна променлива, в която запазваме разширението.
    for (int i = path.size() - 1; i >= 0; i--)
    {
        if (path[i] == '.')break;//Цикли отзад напред, докато стигне до точка.
        helper = path[i] + helper;
    }
    return helper;
}

bool Editor::isCorrectFileExtension(std::string extension)//Проверява дали подаденото разширение се поддържа от програмата.
{
    return extension == "ppm" || extension == "pgm" || extension == "pbm";
}

std::vector<std::string> Editor::findPath(std::string paths)//Ако в един стринг има няколка адреса, т.е. няколко снимки, то тази функция ги отделя.
{
    std::vector<std::string> saver;//Променлива, в която запазваме всеки отделен адрес и я връщаме като резултат.
    std::string helper;//Променлива, в която запазваме единичния адрес.
    std::string help;//Променлива, в която запазваме разширение, за да сравняваме за коректност.
    for (int i = paths.size() - 1; i >= 0; i--)//Обхождаме отзад напред.
    {
        if (paths[i] != ' ')//Докато не стигнем до интервал, добавяме всяка буква в променливата "helper".
        {
            helper = paths[i] + helper;
        }
        else if (paths[i] == ' ')/*Ако стигнем до интервал, проверяваме дали следващите букви, които предстоят, 
         образуват коректно разширение и ако образуват, то значи следва да бъде изчетен нов адрес и затова в променливата 
         "helper" имаме отделен един адрес, който добавяме към променливата "saver" и изчистваме "helper",
         за да може отново да я ползваме, ако не - то значи просто в адреса има празно място и продължаваме да го образуваме.*/
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

bool Editor::isCorrectFileFormat(std::string path)//Проверява по даден адрес дали е коректно разширението.
{
    return findFormat(path) == "ppm" || findFormat(path) == "pgm" || findFormat(path) == "pbm";
}

void Editor::addEffectToPPM(Session& other, std::string effect)//Помощна функция за добавяне на трансформация в дадена сесия.
{//Използва се само при ".ppm" формат, когато изпълняваме функциите "grayscale" и "monochrome", защото те се отнасят само за този формат.
    for (size_t i = 0; i < other.Formats().size(); i++)
    {
        if (findFormat(other.Formats()[i]->getPath()) == "ppm")
        {
            other.Transformations().push_back(effect);
            break;
        }
    }
}

bool Editor::read(std::string path)//Проверява дали състоянието на потока е добро.
{
    std::ifstream input(path.c_str());
    return input.good();
}

int Editor::countExistedImage(std::vector<std::string> path)
{
    //Брояч, чрез който проверяваме дали при въвеждане на изображенията, има такова с валиден адрес, защото ако няма, то сесия без снимки е безсмислено.
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
    addEffectToPPM(other, "grayscale");//Добавя, че е извършена трансформация само ако има поне едно изображение от ".ppm" формат.  
}

void Editor::commandMonochrome(Session& other)
{
    for (size_t i = 0; i < other.Formats().size(); i++)
    {
        other.Formats()[i]->monochrome();
    }
    addEffectToPPM(other, "monochrome"); //Добавя, че е извършена трансформация само ако има поне едно изображение от ".ppm" формат.  
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
    std::getline(std::cin, paths);//Въвеждаме къде и с какво име искаме да запазим първото заредено изображение в сесията.
    if (findFormat(paths) == findFormat(other.Formats()[0]->getPath()))
    {//Ако има съвпадение на разширението на изображението и въведеното разширение, то тогава го записваме.
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
    if (other.Transformations().size() != 0)//Ако има поне една промяна:
    {
        std::string helper = other.Transformations().back();//Премахваме я от списъка с трансформации.
        //В зависимост от направената трансформация, премахва промените.
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
    else std::cout << "Cannot undo!\n";//Ако няма транформации.
}

void Editor::commandCollage(Session& other)
{       
    std::string direction;//Променлива, която използваме, когато въвеждаме посока на създаване на колаж. 
    std::string path;//Променлива, в която в началото ще имаме 3 адреса.
    std::vector<std::string> paths;
    std::cin.ignore();
    std::cin >> direction;//Хоризонтален или вертикален.
    std::cin.ignore();
    std::getline(std::cin, path);//Адреси на 3-те изображения.
   
    //Булеви променливи, чрез които проверяваме дали съществуват двете въведени изображения в текущата сесия.
    bool flag1 = false;
    bool flag2 = false;

    paths = findPath(path);//Отделяме 3-те адреса.
   
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
    //Ако въведените изображения са коректни, създаваме колаж.
    if (flag1 == true && flag2 == true && countExistedImage(paths) == 2 &&  //Съществуващите изображения са две, защото третото го създаваме.
       (findFormat(image1) == findFormat(outimage)) && (findFormat(image2) == findFormat(outimage)))
    {      
        /*Създава колаж от две изображения <image1> и <image2> (в един и същ формат и една и съща размерност),
           налични в текущата сесия. Резултатът се записва в ново изображение <outimage>, което се добавя в текущата сесия.*/
        other.Formats().push_back(loadAccordingToFormat(outimage));
        other.Formats().back()->collage(direction, image1, image2, outimage);
        other.addTransformations("collage");        
        std::cout << "New collage \"" << outimage << "\" created!\n";
    }
    else std::cout << "Unable to make collage!\n";
}

void Editor::load()//Командна функция, създаваща сесия и извършваща основните редакции по изображенията.
{    
    std::string paths = {};//Променлива, чрез която въвеждаме адрес/и на изображение/я.
      
    std::cin.ignore();
    std::getline(std::cin, paths);//Въвеждаме адрес/и на изображение/я.
    std::vector<std::string> path = Editor::findPath(paths);//Отделяме коректните формати, за да ги имаме един по един.

    if (countExistedImage(path) != 0)//Ако има поне една снимка, то създаваме сесия с уникален идентификационен номер.
    {
        session.push_back(Session());
        std::cout << "Session with ID: " << session.back().getId() << " started!\n";
        for (int i = path.size() - 1; i >= 0; i--)
        {
            if (isCorrectFileFormat(path[i]) && read(path[i]))
            {           
                session.back().Formats().push_back(loadAccordingToFormat(path[i]));//Добавяме изображението според вида му.           
                session.back().Formats().back()->load(path[i]);//Зарежда информация за него.
                session.back().Transformations() = {};//Няма никакви трансформации все още.
                std::cout << "Image " << path[i] << " added!\n";
            }
            else
            {
                std::cout << "Image " << path[i] << " is not added!\n";
            }
        }
        do
        {
            do//Въвеждаме команда, която трябва да е валидна.
            {                
                std::cout << ">";

                std::cin >> command;
                if (command == "session")
                {
                    std::cin >> command;
                    if (command == "info") break;
                }

            } while (!isCommand(command));

            if (command == "saveas")//Записва направените промени във файл, като позволява на потребителя да укаже неговия път.
            {
                commandSaveas(session[Session::getId() - 1], paths);
            }
            else if (command == "save")//Записва направените промени обратно в същия файл, от който са били прочетени данните.
            {
                commandSave(session[Session::getId() - 1]);
            }
            else if (command == "help")//Извежда кратка информация за поддържаните от програмата команди.
            {
                help();
            }
            else if (command == "add")//Добавя изображение към текущата сесия. 
            {
                std::cin.ignore();
                std::getline(std::cin, paths);
                commandAdd(session[Session::getId() - 1], paths);
            }
            else if (command == "grayscale")//Променя пикселите да са в сив нюанс. Действа само върху цветни изображения от ".ppm" формат.
            {
                commandGrayscale(session[Session::getId() - 1]);
            }
            else if (command == "monochrome")//Променя пикселите да са черни или бели. Действа само върху цветни изображения от ".ppm" формат.
            {
                commandMonochrome(session[Session::getId() - 1]); 
            }
            else if (command == "negative")//Цветово обръщане. Действа върху всички формати и всички изображения в сесията.
            {
                commandNegative(session[Session::getId() - 1]);
            }
            else if (command == "rotate")//Завъртане на изображенията в сесията на 90° в зависимост от зададената посока.
            {
                commandRotation(session[Session::getId() - 1]);
            }
            else if (command == "switch")//Превключва към сесия с идентификационен номер <session>.
            {
                commandSwitchSession();                
            }
            else if (command == "undo")//Премахва последно направената трансформация в текущата сесия.
            {
                 commandUndo(session[Session::getId() - 1]);
            }
            else if (command == "info")//Извежда информация за сесията.
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

    //Изчистваме заделената памет.
    for (size_t i = 0; i < session.size(); i++)
    {
        for (size_t j = 0; j < session[i].Formats().size(); j++)
        {
            delete session[i].Formats()[j];
        }
    }

}