#ifndef MEMORYWINDOW_H
#define MEMORYWINDOW_H

#include <oopgui/configwindow.h>
#include <sstream>
#include <oopgui/button.h>
#include <oopgui/memorycontentgui.h>
#include <oopgui/bytegui.h>
#include <loaders/configparser.h>
#include <creators/configcreator.h>
#include <memory>

#include <oopgui/fileselectwindow.h>

class MemoryWindow : public ConfigWindowBase
{
    sf::Font font;
    sf::Text size_text, size_num;
    std::vector <uint8_t> * memory;

    MemoryContentGUI scroll_area;

    ByteGUI current_cell;

    Button load_button, save_button;
    bool load, save;

    std::unique_ptr <FileSelectWindow> file_select;

public:
    MemoryWindow();

    bool update();
    Configs get_configs();
    void load_config(Configs &conf);

private:
    void render();

    void save_content(std::string dir);
    void load_content(std::string dir);
};

ConfigWindowBase * create_memory_window();

#endif // MEMORYWINDOW_H
