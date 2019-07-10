#include "portscontainer.h"

PortsContainer::PortsContainer()
{

}

void PortsContainer::add(std::vector<PortInf> v)
{
    meta_data.push_back(v);
    std::cout<<"dodaje wektor portów, liczba w sumie: "<<meta_data.size()<<std::endl;
}

int PortsContainer::create(int index, entityx::Entity en)
{
    std::vector <PortInf> temp_inf = meta_data[index];
    std::vector <PortIN> temp_in;
    std::vector <PortOUT> temp_out;

    for(PortInf inf : temp_inf)
    {
        if(inf.out)
        {
            PortOUT out;
            out.pos = inf.pos;
            out.size = inf.size;
            uint8_t mask = 0;
            for(int i=0; i<inf.size; ++i)   {mask<<1; mask += 1;}
            out.mask = mask;
            out.data = 0;
            temp_out.push_back(out);
        }
        else
        {
            PortIN in;
            in.pos = inf.pos;
            in.size = inf.size;
            in.joined = false;
            in.source = NULL;
            temp_in.push_back(in);
        }
    }
//    std::cout<<"index tworzenia: "<<index<<std::endl;
//    std::cout<<"tworze porty o nowym indexie: "<<ports_in.size()<<std::endl;
//    std::cout<<"portów wejsciowych: "<<temp_in.size()<<std::endl;
//    std::cout<<"portów wyjsciowych: "<<temp_out.size()<<std::endl;
    ports_in.push_back(std::make_pair(en, temp_in));
    ports_out.push_back(std::make_pair(en, temp_out));

    return (ports_in.size()-1);
}

void PortsContainer::destroy(int index)
{
    std::vector<std::pair<entityx::Entity, std::vector<PortIN> > >::iterator iter_in = ports_in.begin();
    std::vector<std::pair<entityx::Entity, std::vector<PortOUT> > >::iterator iter_out = ports_out.begin();
    ports_in.erase(iter_in + index);
    ports_out.erase(iter_out + index);

    int size_in = ports_in.size(),
        size_out = ports_out.size();

    Ports::Handle pH;

    for(int i=0; i<size_in; ++i)
    {
        pH = ports_in[i].first.component<Ports>();
        pH->index = i;
    }

    for(int i=0; i<size_out; ++i)
    {
        pH = ports_out[i].first.component<Ports>();
        pH->index = i;
    }
}

std::vector<PortIN> &PortsContainer::get_ports_in(int index)
{
    //std::cout<<"portów w tym wektorze: "<<ports_in[index].second.size()<<std::endl;
    return ports_in[index].second;
}

std::vector<PortOUT> &PortsContainer::get_ports_out(int index)
{
    return ports_out[index].second;
}

