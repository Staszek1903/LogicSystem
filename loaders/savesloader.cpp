#include "savesloader.h"

SavesLoader::SavesLoader(entityx::EntityX &ex, ContainersContainer &container)
    :ex(ex), container(container), current_project("Unnamed"), ctrl_pushed(false)
{
    ex.events.subscribe<ButtonPushEvent>(*this);
    ex.events.subscribe<NewDirEvent>(*this);
    ex.events.subscribe<NameChangeEvent>(*this);
    ex.events.subscribe<KeyPushEvent>(*this);
    ex.events.subscribe<KeyReleasedEvent>(*this);
}

void SavesLoader::load()
{
    ListCreator listcreator;
    DirReader dirreader;

    auto zeroanc = ex.entities.create();
    list0 = listcreator(ex.entities,sf::Vector2f(160,0),sf::Vector2f(100,20),"Projects",zeroanc, false);
    projList = listcreator.addList(ex.entities,list0, "LOAD");

    std::vector <std::string> saves = dirreader("./LS-resources/projects");

    std::cout<<"SAVES: "<<saves.size()<<std::endl;

    for( auto & s : saves)
    {
        int id = listcreator.addButton(ex.entities, projList, s);
        proj_dirs.dirs[id] =  s;
    }

    newButtonId = listcreator.addButton(ex.entities, list0, "NEW");
    saveButtonId = listcreator.addButton(ex.entities, list0, "SAVE");
    std::cout<<"new: "<<newButtonId<<std::endl;
    std::cout<<"save: "<<saveButtonId<<std::endl;
}

void SavesLoader::receive(const ButtonPushEvent &ev)
{
    if(ev.id == newButtonId)
    {
        std::cout<<"NEW"<<std::endl;
        auto en = ex.entities.create();
        std::string m("Unsaved data will be deleted. Proceed?");
        en.assign<YesNoWindow>(m, deleter);
        ex.events.emit<ConfigWindowCreateEvent>(en, YNWindowCreate);
    }

    else if( ev.id == saveButtonId)
    {
        std::cout<<"SAVE"<<std::endl;
        if(current_project == "Unnamed")
        {
            auto en = ex.entities.create();
            en.assign<SaveData>(saver, projList);
            ex.events.emit<ConfigWindowCreateEvent>(en, saveWindowCreate);
        }
        else
        {
            std::cout<<"INSTANT ZAPIS "<<current_project.size()<<std::endl;
            saver(current_project, ex.entities, container);
        }
    }
    else if(proj_dirs.dirs.find(ev.id) != proj_dirs.dirs.end())
    {
        std::cout<<"LOAD"<<std::endl;
        auto en = ex.entities.create();
        en.assign<LoadData>(deleter, loader, proj_dirs.dirs[ev.id]);
        ex.events.emit<ConfigWindowCreateEvent>(en, loadWindowCreate);
    }
}

void SavesLoader::receive(const NewDirEvent &ev)
{
    proj_dirs.dirs[ev.id] = ev.dir;
    ex.events.emit<NameChangeEvent>(ev.dir);
}

void SavesLoader::receive(const NameChangeEvent &ev)
{
    current_project = ev.name;
    std::cout<<"New name: "<<current_project<<std::endl;
}

void SavesLoader::receive(const KeyPushEvent &ev)
{
    if(ev.key == sf::Keyboard::LControl)
        ctrl_pushed = true;
    else if(ctrl_pushed && ev.key == sf::Keyboard::S)
    {
        std::cout<<"SAVE"<<std::endl;
        if(current_project == "Unnamed")
        {
            auto en = ex.entities.create();
            en.assign<SaveData>(saver, projList);
            ex.events.emit<ConfigWindowCreateEvent>(en, saveWindowCreate);
        }
        else
        {
            std::cout<<"INSTANT ZAPIS "<<current_project.size()<<std::endl;
            saver(current_project, ex.entities, container);
        }
    }
}

void SavesLoader::receive(const KeyReleasedEvent &ev)
{
    if(ev.key == sf::Keyboard::LControl)
        ctrl_pushed = false;
}
