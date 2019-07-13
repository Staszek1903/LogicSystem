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
    std::map < int, uint8_t > inner_states;
    std::map <std::string, std::vector<std::string> > memory_sections;
    std::map <std::string, std::string> text_sections;
    std::map < int, std::string > inner_sections;

    Position::Handle pos;
    CircuitTypeIndex::Handle type;
    Wire::Handle wire;
    Line::Handle line;


    //ODCZYT BRAMEK
    int id = 0;
    for(auto en : manager.entities_with_components(type,pos))
    {
        id++;

        circuits_data.push_back({id, en, cont.names.get_name(type->index), pos->pos});
        if(en.has_component<CircuitButton>())
        {
            CircuitButton::Handle c_b = en.component<CircuitButton>();
            button_keys[id] = c_b->key;
            //std::cout<<"zapisuje: "<<static_cast<char>(c_b->key + 65)<<" dla id: "<<id<<std::endl;
        }

        if(en.has_component<Constant>())
        {
            auto ports = en.component<Ports>();
            auto & out_ports = cont.ports.get_ports_out(ports->index);
            if(out_ports.size() == 0)
            {
                std::cout <<"cant find outports in constant"<<std::endl;
                continue;
            }
            uint8_t state = out_ports.at(0).data;
            inner_states[id] = state;
            //tODO
        }

        /*if(en.has_component<Latch>())
        {
            auto mem = en.component<Memory>();
            auto & memory = cont.memory.get_mem(mem->index);
            if(memory.size() == 0)
            {
                std::cout <<"cant find memory in latch"<<std::endl;
                continue;
            }
            uint8_t state = memory.at(0);
            inner_states[id] = state;
        }*/

        // ZAPIS PAMIECI ( Jak zidentyfikować pamieć?? (na pewno nie komponent Memory))
        // UPDATE: zapisywać wszytkie komponenty z memory, zpisywać odnosnik do sekcji
        //  kontent memory w sekcji

        if(en.has_component<Memory>())
        {
            auto mem = en.component<Memory>();
            auto & memory = cont.memory.get_mem(mem->index);
            if(memory.size() == 0) goto Label; // XD ale archaizm // continue;

            std::stringstream ss;
            ss << id;
            std::string section_name = "memory"+ ss.str();
            inner_sections[id] = section_name;

            std::vector <std::string> memory_content;
            for(uint8_t d : memory)
            {
                int temp = d;
                std::stringstream ss2;
                ss2<<temp;
                memory_content.push_back(ss2.str());
            }
            memory_sections[section_name] = memory_content;
        }

        Label:
        if(en.has_component<Label>())
        {
            auto l = en.component<Label>();
            if(l->text.find("TEXT:") == std::string::npos) continue;

            std::stringstream ss;
            ss << id;
            std::string section_name = "text"+ ss.str();
            inner_sections[id] = section_name;

            text_sections[section_name] = l->text;
        }
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

        if(inner_states.find(p.id) != inner_states.end())
        {
            std::stringstream ss;
            int  temp = inner_states.at((p.id));
            ss<< temp;
            line.push_back(ss.str());
        }

        if(inner_sections.find(p.id) != inner_sections.end())
        {
            line.push_back(inner_sections.at(p.id));
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

    //MEMORY_SECTIONS

    for(auto & section : memory_sections)
    {
        std::vector <std::string> & content = section.second;
        std::vector < std::vector <std::string> > temp;
        temp.push_back(content);
        cc.addSection(section.first, temp); // KONCERSJA UINT NA STRING I JESZCZE ODCZYT
    }

    //TEXT_SECTIONS
    for(auto & section : text_sections)
    {
        std::vector <std::string> content;
        content.push_back(section.second);
        std::vector < std::vector <std::string> > temp;
        temp.push_back(content);
        cc.addSection(section.first,temp);
    }

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

    std::map <int, std::string > additional_sections;

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
                auto ports = entities[id].component<Ports>();
                auto & out_ports = cont.ports.get_ports_out(ports->index);
                if(out_ports.size() == 0)
                {
                    std::cout <<"cant find outports in constant"<<std::endl;
                    continue;
                }
                std::stringstream ss(s);
                int temp;
                ss >> temp;
                out_ports.at(0).data = static_cast<uint8_t> (temp);
            }

            /*if(entities[id].has_component<Latch>())
            {
                auto mem = entities[id].component<Memory>();
                auto & memory = cont.memory.get_mem(mem->index);
                if(memory.size() == 0)
                {
                    std::cout <<"cant find memory in latch"<<std::endl;
                    continue;
                }

                std::stringstream ss(s);
                ss >> memory.at(0);
            }*/

            additional_sections[id] = s;

        }
    }

    // MEMORY_CONTENTS
    for(auto & p : additional_sections)
    {
        if(!parser.setSection(p.second)) continue;
        int id = p.first;

        // Kazdy entit ma Memory ( zebys sie nie zdziwił XD)
        auto mem = entities[id].component<Memory>();
        auto & memory = cont.memory.get_mem(mem->index);

        if(memory.size() != 0)
        {
            size_t iter = 0;
            while(!parser.EndOfSection() && iter < memory.size())
            {
                memory.at(iter) = static_cast <uint8_t> (parser.getFloat());
                iter++;
            }
        }
        else if(entities[id].has_component<Label>())
        {
            auto l = entities[id].component<Label>();
            if(l->text.find("TEXT:") == std::string::npos) continue;
            l->text = parser.getString();
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
