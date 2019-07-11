#include "project_funcs.h"

void deleter(entityx::EntityX &enX, ContainersContainer &cont)
{
    VertexArray::Handle vert;
    CircutCreator cc(enX, cont);
    for(auto en: enX.entities.entities_with_components(vert))
        cc.destroy(en);
}

void saver(std::string filename, entityx::EntityManager &manager, ContainersContainer &cont)
{
    ConfigCreator cc;
    std::vector <std::vector <std::string> > circuits_section;
    std::vector <std::vector <std::string> > wires_section;
    std::vector <DATA> circuits_data;
    std::map <int, sf::Keyboard::Key> button_keys;

    Position::Handle pos;
    CircuitTypeIndex::Handle type;
    Wire::Handle wire;
    Line::Handle line;


    //ODCZYT BRAMEK
    int id = 0;
    for(auto en : manager.entities_with_components(type,pos))
    {
        circuits_data.push_back({id, en, cont.names.get_name(type->index), pos->pos});
        if(en.has_component<CircuitButton>())
        {
            CircuitButton::Handle c_b = en.component<CircuitButton>();
            button_keys[id] = c_b->key;
            //std::cout<<"zapisuje: "<<static_cast<char>(c_b->key + 65)<<" dla id: "<<id<<std::endl;
        }

        if(en.has_component<Constant>())
        {
            // zapis stanu
        }

        if(en.has_component<Latch>())
        {
            //zapis stanu
        }

        if(en.has_component<Memory>())
        {
            //najpierw zapisz plik z kontentem i wpisz odnoscik do tego pliku
        }

        ++id;
    }

    //ZAPIS BRAMKI
    for(auto p: circuits_data)
    {
        std::stringstream s_id, s_x, s_y;
        s_id<<p.id;
        s_x<<p.pos.x;
        s_y<<p.pos.y;

        std::vector <std::string> line = {s_id.str(), p.name, s_x.str(), s_y.str()};

        if(button_keys.find(p.id) != button_keys.end())
        {
            std::string ks;
            int k = button_keys[p.id];
            //std::cout<<"jest key: "<<static_cast<char>(k+65)<<" dla id: "<<p.id<<std::endl;
            std::stringstream ss;
            ss<<k;
            ks = ss.str();
            line.push_back(ks);
        }

        circuits_section.push_back(line);            
    }

    //WIRES
    for(auto en : manager.entities_with_components(wire, line))
    {
        std::stringstream id_out, id_in, port_out, port_in, wire_type, break_point;
        id_out << findId(wire->entity_out, circuits_data);
        port_out << wire->out_index;
        id_in << findId(wire->entity_in, circuits_data);
        port_in << wire->in_index;
        wire_type <<line->line.getType();
        break_point << line->line.getBreakPoint();
        std::vector <std::string> line = {id_out.str(), port_out.str(),
                                          id_in.str(), port_in.str(),
                                         wire_type.str(), break_point.str()};
        wires_section.push_back(line);
    }

    cc.addSection("circuits", circuits_section);
    cc.addSection("wires", wires_section);
    cc.setDir("./LS-resources/projects/"+ filename);
    cc.create();
}

void loader(entityx::EntityX &enX, ContainersContainer &cont, std::string &dir)
{
    std::map <int, sf::Keyboard::Key> int_to_sf_key = {{0,sf::Keyboard::A},{1,sf::Keyboard::B},{2,sf::Keyboard::C},{3,sf::Keyboard::D},
                                                       {4,sf::Keyboard::E},{5,sf::Keyboard::F},{6,sf::Keyboard::G},{7,sf::Keyboard::H},
                                                       {8,sf::Keyboard::I},{9,sf::Keyboard::J},{10,sf::Keyboard::K},{11,sf::Keyboard::L},
                                                       {12,sf::Keyboard::M},{13,sf::Keyboard::N},{14,sf::Keyboard::O},{15,sf::Keyboard::P},
                                                       {16,sf::Keyboard::Q},{17,sf::Keyboard::R},{18,sf::Keyboard::S},{19,sf::Keyboard::T},
                                                       {20,sf::Keyboard::U},{21,sf::Keyboard::V},{22,sf::Keyboard::W},{23,sf::Keyboard::X},
                                                       {24,sf::Keyboard::Y},{25,sf::Keyboard::Z}};

    std::cout<<"sf::W: "<<sf::Keyboard::W<<std::endl;
    std::string full_dir = "./LS-resources/projects/"+dir;
    std::cout<<"LOADER : "<<dir<<std::endl;
    ConfigParser parser;
    parser.load(full_dir);

    if(!parser.setSection("circuits"))
    {
        std::cout<<"load failed: no circuits section"<<std::endl;
        return;
    }

    CircutCreator create(enX,cont);
    WireCreator w_create(enX, cont);

    std::map < int, entityx::Entity > entities;

    while(!parser.EndOfSection())
    {
        int id = parser.getFloat();
        std::string name = parser.getString();
        int x = parser.getFloat();
        int y = parser.getFloat();

        entities[id] = create(enX.entities, cont.names.get_index(name), sf::Vector2f(x,y));
        if(!parser.EndOfLine()) // jesli nie koniec linni pobiera dodatkowe info
        {
            std::string s = parser.getString(); //Dodatakowy kontent
            //std::cout<<"wykryto ogon: ["<<s<<"]"<<std::endl;
            if(entities[id].has_component<CircuitButton>())
            {
                std::stringstream ss(s);
                int k;
                ss>>k;
                CircuitButton::Handle c_b = entities[id].component<CircuitButton>();
                c_b->key = int_to_sf_key[k];
            }

            if(entities[id].has_component<Constant>())
            {
                // odczyt stanu
            }

            if(entities[id].has_component<Latch>())
            {
                // odczyt stanu
            }

            if(entities[id].has_component<Memory>())
            {
                //wczytanie pliku z kontentem do memory ( jak to nie wiem )
            }

        }
    }

    //WIRES
    if(!parser.setSection("wires"))
        return;

    while(!parser.EndOfSection())
    {
        int id1 = parser.getFloat();
        int p1 = parser.getFloat();
        int id2 = parser.getFloat();
        int p2 = parser.getFloat();
        int type = parser.getFloat();
        float break_point = parser.getFloat();

        auto en1 = entities[id1];
        auto en2 = entities[id2];

        Position::Handle pos1 = en1.component<Position>();
        Ports::Handle port1 = en1.component<Ports>();

        Ports::Handle port2 = en2.component<Ports>();

        w_create.start(en1, port1->index, p1, pos1->pos);
        w_create.setType(type, break_point);
        w_create.end(en2, port2, p2);
    }
}

int findId(entityx::Entity en, std::vector<DATA> &data)
{
    for( DATA & d : data)
    {
        if(d.en == en)
            return d.id;
    }

    return -1;
}
