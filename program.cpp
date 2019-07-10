#include "program.h"

Program::Program()
    : sl(ex,container), cl(ex.entities,container), mouse(window_main,v)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window_main.create(sf::VideoMode(800,600),"LogicSystem - Unnamed",sf::Style::Default, settings);
    window_main.setVerticalSyncEnabled(true);
    window_main.setFramerateLimit(30);
    setSystems();

    SliderCreator slidercreator;

    slidercreator(ex.entities,sf::Vector2f(20,580),780,true, true);
    slidercreator(ex.entities,sf::Vector2f(0,0),500,false, false);

    cl.load();
    sl.load();
    frequency.init(ex);


    //TEST

   // auto en = ex.entities.create();
    //en.assign<Label>("SIEMANO MORDY", sf::Vector2f(0,0));
    //en.assign<Position>(sf::Vector2f(100,100));
}

void Program::run()
{
    sf::Time dt =sf::Time::Zero,
            second_t = sf::Time::Zero,
            max_t = sf::Time::Zero;

    sf::Clock clock;
    sf::Clock max_clock;

    int fps_count = 0;

    while(window_main.isOpen())
    {

        //static size_t bebug =0;

        //bebug++;

        input();
        sf::Time temp_t = clock.restart();
        dt += temp_t;
        second_t += temp_t;

        if( !frequency.isRunning() )
            dt = sf::Time::Zero;

        bool isMax = frequency.isMax();
        bool isRunning = frequency.isRunning();
        float timeStep=  frequency.getTimeStep();
        bool run_permit = (isMax)? isRunning : (dt.asSeconds() > timeStep && isRunning);

        max_clock.restart();
        while(run_permit)
        {
            dt = (isMax)? sf::Time::Zero : (dt - sf::seconds(frequency.getTimeStep()));
            max_t += max_clock.restart();

            update();

            run_permit = (isMax)? ((max_t.asSeconds() < (1.0f/30.0f)) && isRunning) : ((dt.asSeconds() > timeStep) && isRunning);
            ++fps_count;
        }

        max_t = sf::Time::Zero;

        if(second_t.asSeconds() > 1.0f)
        {
            frequency.setDisplayedFrq(fps_count);
            fps_count = 0;
            second_t = sf::Time::Zero;
        }

        render();
    }

}

void Program::input()
{
    sf::Event event;
    while(window_main.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window_main.close();
            break;

        case sf::Event::MouseMoved:
            mouse.pos.x = event.mouseMove.x;
            mouse.pos.y = event.mouseMove.y;
            ex.systems.update<GuiSystem>(0);
            ex.systems.update<GatesGuiSystem>(0);
            break;

        case sf::Event::MouseButtonPressed:
            if(event.mouseButton.button == sf::Mouse::Left)
                mouse.Lbutton = true;
            if(event.mouseButton.button == sf::Mouse::Right)
                mouse.Rbutton = true;
            ex.systems.update<GuiSystem>(0);
            ex.systems.update<GatesGuiSystem>(0);
            break;

        case sf::Event::MouseButtonReleased:
            if(event.mouseButton.button == sf::Mouse::Left)
                mouse.Lbutton = false;
            if(event.mouseButton.button == sf::Mouse::Right)
                mouse.Rbutton = false;
            ex.systems.update<GuiSystem>(0);
            ex.systems.update<GatesGuiSystem>(0);
            break;

        case sf::Event::Resized:
            ex.events.emit<ResizeEvent>(
            event.size.width,
            event.size.height);
            ex.systems.update<GuiSystem>(0);
            break;

        case sf::Event::KeyPressed:
            ex.events.emit<KeyPushEvent>(event.key.code);
            break;

        case sf::Event::KeyReleased:
            ex.events.emit<KeyReleasedEvent>(event.key.code);
            break;

        case sf::Event::MouseWheelScrolled:
            ex.events.emit<MouseScrollEvent>(event.mouseWheelScroll.delta, event.mouseWheelScroll.wheel);
            break;
        default:
            break;
        }
    }
}

void Program::update()
{
    ex.systems.update<GatesProcessingSystem>(0);
}

void Program::render()
{
    ex.systems.update<ConfigWindowSystem>(0);
    ex.systems.update<RenderSystem>(0);
}

void Program::setSystems()
{
    ex.systems.add<RenderSystem>(window_main, ex.events,v, view_range, view_origin, container);
    ex.systems.add<GuiSystem>(mouse, ex);
    ex.systems.add<GatesGuiSystem>(ex, mouse, container);
    ex.systems.add<ConfigWindowSystem>(ex, container);
    ex.systems.add<GatesProcessingSystem>(ex,container);
    ex.systems.configure();
}
