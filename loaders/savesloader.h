#ifndef SAVESLOADER_H
#define SAVESLOADER_H

#include <creators/listcreator.h>

#include <loaders/dirreader.h>

#include <events/buttonpushevent.h>
#include <events/configwindowcreateevent.h>
#include <events/newdirevent.h>
#include <events/namechangeevent.h>
#include <events/keypushevent.h>
#include <events/keyreleasedevent.h>

#include <components/yesnowindow.h>
#include <components/savedata.h>
#include <components/loaddata.h>

#include <oopgui/ynwindow.h>
#include <oopgui/savewindow.h>
#include <oopgui/loadwindow.h>

#include <containers/projectdicontainer.h>

#include <project_funcs.h>

class SavesLoader : public entityx::Receiver<SavesLoader>
{

    entityx::EntityX & ex;
    ContainersContainer &container;
    int newButtonId, saveButtonId;
    entityx::Entity projList, list0;
    ProjectDirContainer proj_dirs;

    std::string current_project;
    bool ctrl_pushed;

public:
    SavesLoader(entityx::EntityX & ex, ContainersContainer &container);
    void load();
    void receive ( const ButtonPushEvent & ev);
    void receive ( const NewDirEvent & ev);
    void receive ( const NameChangeEvent & ev);
    void receive ( const KeyPushEvent & ev);
    void receive ( const KeyReleasedEvent & ev);
};

#endif // SAVESLOADER_H
