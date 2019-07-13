#include "configwindowsystem.h"

ConfigWindowSystem::ConfigWindowSystem(entityx::EntityX &enX, ContainersContainer &container)
    :enX(enX), container(container)
{
    enX.events.subscribe<ConfigWindowCreateEvent>(*this);
}

ConfigWindowSystem::~ConfigWindowSystem()
{
    for(auto & p : windows)
    {
        delete p.second;
        std::cout<<"deleted window"<<std::endl;
    }
}

void ConfigWindowSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, double dt)
{
    int i =0;
    for(auto & w : windows)
    {

        Configs conf = w.second->get_configs();
        //std::cout<< static_cast<char> (conf.key+65) <<std::endl;
        if(w.first.has_component<CircuitButton>())
        {
            CircuitButton::Handle cb= w.first.component<CircuitButton>();
            cb->key = conf.key;
            //std::cout<<"config window  BUTTON"<<std::endl;
        }
        else if(w.first.has_component<Constant>())
        {
            //std::cout<<"new value: "<<conf.universal<<std::endl;
            Ports::Handle ports = w.first.component<Ports>();
            container.ports.get_ports_out(ports->index)[0].data = conf.universal;
        }
        else if(w.first.has_component<Label>())
        {
            auto l = w.first.component<Label>();
            if(conf.text.find("TEXT:") != std::string::npos)
                l->text = conf.text;
        }

        if(!w.second->update())
        {
            std::cout<<"config window DELETE"<<std::endl;
            if(w.first.has_component<YesNoWindow>())
            {
                YesNoWindow::Handle ynw= w.first.component<YesNoWindow>();
                conf = w.second->get_configs();
                if(conf.result)
                {
                    ynw->result_func(enX, container);
                    events.emit<NameChangeEvent>("Unnamed");
                }
                w.first.destroy();
            }
            else if(w.first.has_component<SaveData>())
            {
                std::cout<<"zamykam okno sejwu"<<std::endl;
                SaveData::Handle sd = w.first.component<SaveData>();
                ListCreator create;

                conf = w.second->get_configs();
                int new_id;
                if(conf.result)
                {
                    new_id = create.addButton(entities,sd->projList, conf.text);
                    sd->func(conf.text, entities, container);
                    events.emit<NewDirEvent>(new_id, conf.text);
                }

                w.first.destroy();
            }
            else if(w.first.has_component<LoadData>())
            {
                LoadData::Handle ld = w.first.component<LoadData>();
                conf = w.second->get_configs();
                if(conf.result)
                {
                    ld->delete_func(enX, container);
                    ld->load_func(enX, container, ld->dir);
                    events.emit<NameChangeEvent>(ld->dir);
                }
                w.first.destroy();
            }

            delete w.second;
            windows.erase(windows.begin()+i);
        }

        ++i;
    }
}

void ConfigWindowSystem::receive(const ConfigWindowCreateEvent &event)
{
    for(auto & w :windows)
    {
        if(w.first == event.en)
            return;
    }
    ConfigWindowBase * base = event.win();

    if(base == NULL)
        return;

    entityx::Entity en = event.en;

    Configs conf;

    if(event.en.has_component<CircuitButton>())
    {
        CircuitButton::Handle cb = en.component<CircuitButton>();
        conf.key = cb->key;
    }
    else if(event.en.has_component<Constant>())
    {
        Ports::Handle ports = en.component<Ports>();
        conf.universal = container.ports.get_ports_out(ports->index)[0].data;
    }
    else if(event.en.has_component<YesNoWindow>())
    {
        YesNoWindow::Handle ynw= en.component<YesNoWindow>();
        conf.text = ynw->message;
    }
    else if(event.en.has_component<Memory>())
    {
        Memory::Handle mem = en.component<Memory>();
        conf.memory = &(container.memory.get_mem(mem->index));
    }

    if (event.en.has_component<Label>())
    {
        auto l = en.component<Label>();
        if(l->text.find("TEXT:") != std::string::npos)
            conf.text = l->text.substr(5);
    }

    base->load_config(conf);
    windows.push_back(std::pair<entityx::Entity, ConfigWindowBase *>(en, base));
    std::cout<<"win update size: "<<windows.size()<<std::endl;
}
