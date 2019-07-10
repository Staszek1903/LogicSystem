#include "filelist.h"

FileList::FileList(sf::Font &font, sf::RenderWindow &win)
    :font(font), win(win)
{
}

void FileList::init(sf::Vector2f pos, sf::Vector2f dim, sf::FloatRect ratio, std::string dir)
{
    DirReader reader;

    auto dirs = reader(dir);

    ScrollArea::init(pos,dim,ratio, 2*dim.y);

    files.resize(dirs.size());
    for(unsigned int i =0; i<dirs.size(); ++i)
    {
        files[i].init(sf::Vector2f(10, 5 + i*25), sf::Vector2f(245, 20), dirs[i], font);
        files[i].setCamera(&camera, &win);
    }
}

int FileList::update(sf::Event ev)
{
    ScrollArea::update(ev);

    for(unsigned int i=0; i<files.size(); ++i)
        if(files[i].update(ev))
            return i;

    return -1;
}

std::string FileList::get_button_text(int num)
{
    return files[num].get_text();
}

void FileList::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    ScrollArea::draw(target);

    setCamera(target);

    for(auto & button : files)
        target.draw(button);

    unsetCamera(target);
}
