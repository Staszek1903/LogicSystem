#include "componentsloader.h"

ComponentsLoader::ComponentsLoader(entityx::EntityManager &es, ContainersContainer & container)
    : container(container), es(es)
{}

void ComponentsLoader::load()
{
    ConfigParser parser;
    DirReader dirread;
    ListCreator listcreator;
    std::vector<std::string> categories;

    categories = dirread("./LS-resources/components");

    auto zeroanc = es.create();
    auto list0 = listcreator(es,sf::Vector2f(30,0),sf::Vector2f(100,20),"Components",zeroanc, false);

    for(auto s: categories)
    {
        auto list = listcreator.addList(es,list0,s);
        std::string dir = std::string("./LS-resources/components/") + s + std::string("/");
        std::cout<<"DIR: "<<dir<<std::endl;
        std::vector<std::string> files = dirread(dir);
        for(auto file : files)
        {
            std::string filedir = dir+file;
            std::cout<<"            "<<filedir<<std::endl;
            if(!parser.load(filedir))
                continue;
            if(!create_button(list,parser))
                continue;
            load_vertex_array(parser);
            load_config_type(parser);
            load_additional(parser);
            PortNames names = load_ports(parser);
            container.port_names.add_ports_info(names);
            load_memory(parser, names);
            load_algorithm(parser, names);
        }
    }
}

bool ComponentsLoader::create_button(entityx::Entity list, ConfigParser &parser)
{
    ListCreator listcreator;
    if(!parser.setSection(std::string("name")))
        return false;

    std::string name = parser.getString();
    listcreator.addButton(es,list,name);
    container.names.new_name(name);
    return true;
}

void ComponentsLoader::load_vertex_array(ConfigParser &parser)
{
    std::vector<sf::Vector2f> vertexes;
    if(!parser.setSection(std::string("vertex")))
        return;
    while(!parser.EndOfSection())
    {
        //std::cout<<"next fertex"<<std::endl;
        float x,y;
        x = parser.getFloat();
        y = parser.getFloat();
        vertexes.push_back(sf::Vector2f(x,y));
    }

    sf::VertexArray array(sf::TriangleFan, vertexes.size());

    //std::cout<<"ŁADUJE:"<<std::endl;
    for(unsigned int i=0; i<vertexes.size(); ++i)
    {
        array[i].position = vertexes[i];
        array[i].color = sf::Color(50,50,70);
    }

    /*std::cout<<"Ilość: " <<*/container.draw.add_gate(array);//<<std::endl;
}

PortNames ComponentsLoader::load_ports(ConfigParser &parser)
{
    std::vector <PortInf> ports;
    PortNames port_names;
    //std::vector <sf::Vector2f> positions;
    if(!parser.setSection(std::string("ports")))
    {
        return port_names;
    }

    while (!parser.EndOfSection())
    {
        std::string direction = parser.getString();
        std::string name = parser.getString();
        int size = parser.getFloat();
        int x = parser.getFloat();
        int y = parser.getFloat();
        bool out;
        if(direction == "in")
        {
            out = false;
            int last_size = port_names.in.size();
            port_names.in[name] = last_size;
        }
        else
        {
            out = true;
            int last_size = port_names.out.size();
            port_names.out[name] = last_size;
        }

        PortInf pI(size,sf::Vector2f(x,y),out);
        ports.push_back(pI);
        //positions.push_back(sf::Vector2f(x,y));

        std::cout<<name<<"["<<size<<"] : "<<direction<<"  {"<<x<<","<<y<<"}"<<std::endl;
    }

    sf::VertexArray array(sf::Points,ports.size());
    for(unsigned int i=0; i<ports.size(); ++i)
    {
        array[i].position = ports[i].pos;
        array[i].color = (ports[i].out)? sf::Color::Green : sf::Color::Red;
    }

    container.ports.add(ports);
    container.draw.add_port(array);
    return port_names;
}

bool ComponentsLoader::load_config_type(ConfigParser &parser)
{
    if(!parser.setSection("configwindow"))
    {
        container.win_create.creates.push_back(createNoneWindow);
        return false;
    }
    std::string s = parser.getString();
    if(s == std::string("button"))
        container.win_create.creates.push_back(createBindButtonWindow);
    if(s == std::string("constant"))
        container.win_create.creates.push_back(createConstWindow);
    if(s == std::string("memory"))
        container.win_create.creates.push_back(create_memory_window);

    return true;
}

void ComponentsLoader::load_additional(ConfigParser &parser)
{
    std::vector <int> additionals;

    if(!parser.setSection("additional"))
    {
        container.additional.additional.push_back(additionals);
        return;
    }

    while(!parser.EndOfSection())
    {
        std::string s = parser.getString();
        std::cout<<"znaleziono additional: "<<s<<std::endl;

        if( s == "button")
            additionals.push_back(AdditionalContainer::BUTTON);
        else if(s == "led")
            additionals.push_back(AdditionalContainer::LED);
        else if(s == "algorithm")
        {
            additionals.push_back(AdditionalContainer::ALGORITHM);
            std::cout<<"dodaje algorithm do additional"<<std::endl;
        }
        else if(s == "latch")
        {
            additionals.push_back(AdditionalContainer::LATCH);
            std::cout<<"dodaje latch do additional"<<std::endl;
        }
        else if(s == "probe")
        {
            additionals.push_back(AdditionalContainer::PROBE);
            std::cout<<"dodaje probe do additional"<<std::endl;
        }
        else if (s == "label")
        {
            additionals.push_back(AdditionalContainer::LABEL);
        }
        else if(s == "pin")
        {
            additionals.push_back(AdditionalContainer::PIN);
        }
        else if(s == "7segdisp")
        {
            additionals.push_back(AdditionalContainer::DISP_7_SEG);
        }
        else if(s == "startpoint")
        {
            additionals.push_back(AdditionalContainer::START_POINT);
            std::cout<<"DODAJE STARTPOINT"<<std::endl;
        }
    }

   container.additional.additional.push_back(additionals);
}

void ComponentsLoader::load_algorithm(ConfigParser &parser, PortNames &names)
{
    GatesAssembler assembler(names);
    std::vector<uint8_t> machine_vec;

    if(!parser.setSection("algorithm"))
    {
        container.instruction.inst.push_back(machine_vec);
        return;
    }

    std::cout<<"znaleziono algorithm: "<<std::endl;
    //assembler(machine_vec, parser.getData());
    assembler(machine_vec, parser.getData());
    container.instruction.inst.push_back(machine_vec);
}

void ComponentsLoader::load_memory(ConfigParser &parser, PortNames &names)
{
    int mems =0;
    if(!parser.setSection("memory"))
    {
        container.memory.add(mems);
        return;
    }

    std::cout<<"znaleziono sekcje memory"<<std::endl;
    while(!parser.EndOfSection())
    {
        std::string init = parser.getString();
        std::string identifier = init;

        int mem_size = 1;
        size_t open_b = init.find('[', 0);
        size_t close_b =  init.find(']',0);
        if(open_b != std::string::npos && close_b != std::string::npos)
        {
            identifier = init.substr(0,open_b);
            std::stringstream ss(init.substr(open_b+1, close_b - open_b-1));
            ss>>mem_size;

            std::cout<< "WYKRYTO TABLICE nazwa: "<<identifier<<" size: "<<mem_size<<std::endl;
        }

        names.mem[identifier] = mems;
        std::cout<<"nazwa: "<<identifier<<" adres: "<<mems<<std::endl;
        mems+= mem_size;
    }

    container.memory.add(mems);
}
