#ifndef GATESGUISYSTEM_H
#define GATESGUISYSTEM_H

#include <entityx/entityx.h>

#include <events/buttonpushevent.h>
#include <events/configwindowcreateevent.h>
#include <events/keypushevent.h>
#include <events/keyreleasedevent.h>

#include <containers/containerscontainer.h>

#include <creators/circutcreator.h>
#include <creators/wirecreator.h>

#include <components/configwindow.h>
#include <components/circuitbutton.h>
#include <components/line.h>
#include <components/wire.h>
#include <components/selectarea.h>
#include <components/circuittypeindex.h>

#include <oopgui/configwindow.h>

#include <mousehandler.h>

class GatesGuiSystem : public entityx::System<GatesGuiSystem>, public entityx::Receiver<GatesGuiSystem>
{
    struct WireSaveData
    {
        int en_in, en_out, port_in, port_out;
    };

    struct CircSaveData
    {
        entityx::Entity en;
        int index;
        sf::Vector2f pos;
    };

    MouseHandler & mouse;
    entityx::Entity mouse_latch;
    entityx::Entity select_area;
    sf::Vector2f s_area_origin;
    sf::Vector2f s_area_catch_pos;

    ContainersContainer & container;
    entityx::EntityX& entX;
    bool latch, block,is_selecting_area, is_selected_area, select_area_catch, ctrl_pushed;

    WireCreator wire_create;
    entityx::Entity wire_origin;

    std::vector<entityx::Entity> s_a_catched;
    std::vector<CircSaveData > saved_circ;
    std::vector<WireSaveData> saved_wires;
    sf::Vector2f selected_save_size;

    int to_create;


public:
    GatesGuiSystem(entityx::EntityX& entX, MouseHandler & mouse, ContainersContainer & container);
    void update(entityx::EntityManager &entities, entityx::EventManager &events, double dt);
    void receive(const ButtonPushEvent& ev);
    void receive(const KeyPushEvent& ev);
    void receive(const KeyReleasedEvent& ev);

private:
    bool has_mouse(sf::FloatRect rect);
    void set_circ_pos(entityx::Entity en, sf::Vector2f pos);
};

#endif // GATESGUISYSTEM_H
