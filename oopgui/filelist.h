#ifndef FILELIST_H
#define FILELIST_H

#include <oopgui/scrollarea.h>
#include <loaders/dirreader.h>
#include <oopgui/button.h>

class FileList : public ScrollArea, public sf::Drawable
{
    std::vector <Button> files;
    sf::Font & font;
    sf::RenderWindow & win;
public:
    FileList(sf::Font & font, sf::RenderWindow & win);
    void init(sf::Vector2f pos, sf::Vector2f dim, sf::FloatRect ratio, std::string dir);
    int update(sf::Event ev);
    std::string get_button_text(int num);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif // FILELIST_H
