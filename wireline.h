#ifndef WIRELINE_H
#define WIRELINE_H

#include "line.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

namespace stuff {
    class WireLine : public sf::Drawable
    {
        enum{
            STR_ANG_HOR, // straght angle horizontal
            STR_ANG_VER, // strrait angle vertical
            DIRECT, // direct line;
        };

        int type;
        size_t lines_count;
        std::unique_ptr < Liner[] > lines;
        sf::Vector2f begining, end;
        float break_place; // gdzie przegiąć linie 0-1
        float thickness;
        sf::Color color;

    public:
        WireLine(const sf::Vector2f & begining,const sf::Vector2f& end);
        WireLine(const WireLine & other);
        WireLine(WireLine && other) = delete;
        WireLine & operator= (const WireLine & other) = delete;
        WireLine & operator= (WireLine && other) = delete;

        void setBegining(const sf::Vector2f & v);
        void setEnd(const sf::Vector2f & v);
        void setType(int type);
        int getType();
        void nextType();
        void setColor(const sf::Color & c);
        sf::Color getColor();
        void setThickness(float t);
        float getThickness();
        void setBreakPoint(float bp);
        float getBreakPoint();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        void update_shape();

        void gen_angle(bool up);
        void gen_dir();
    };
}


#endif // WIRELINE_H
