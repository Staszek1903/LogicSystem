#include "frequencycontrol.h"

FrequencyControl::FrequencyControl()
    :time_step(0.01f), run(true), max(false)
{
}

void FrequencyControl::init(entityx::EntityX &enX)
{
    enX.events.subscribe<ButtonPushEvent>(*this);

    entityx::Entity zeroanc = enX.entities.create();
    ButtonCreator b_creator;
    sr_button = b_creator(enX.entities, sf::Vector2f(400,0), sf::Vector2f(100,20), "    STOP", zeroanc, -1);
    ListCreator l_creator;
    frq_list = l_creator(enX.entities,sf::Vector2f(530,0), sf::Vector2f(100,20), "Frq: 100Hz",zeroanc, false);
    frq_table[l_creator.addButton(enX.entities,frq_list, "          1Hz")] = {1.0f,   "1Hz"};
    frq_table[l_creator.addButton(enX.entities,frq_list, "          2Hz")] = {0.5f,   "2Hz"};
    frq_table[l_creator.addButton(enX.entities,frq_list, "          4Hz")] = {0.25f,  "4Hz"};
    frq_table[l_creator.addButton(enX.entities,frq_list, "          8Hz")] = {0.125f, "8Hz"};
    frq_table[l_creator.addButton(enX.entities,frq_list, "        100Hz")] = {0.01f,"100Hz"};
    frq_table[l_creator.addButton(enX.entities,frq_list, "       1000Hz")] = {0.001f,"1000Hz"};
    frq_table[l_creator.addButton(enX.entities,frq_list, "       2000Hz")] = {0.0005f,"2000Hz"};
    frq_table[l_creator.addButton(enX.entities,frq_list, "       4000Hz")] = {0.00025f,"4000Hz"};
    max_button = l_creator.addButton(enX.entities,frq_list, "      MAX Hz");
}

float FrequencyControl::getTimeStep()
{
    return time_step;
}

bool FrequencyControl::isRunning()
{
    return run;
}

bool FrequencyControl::isMax()
{
    return max;
}

void FrequencyControl::setDisplayedFrq(int frq)
{
    std::stringstream ss;
    ss<<frq;
    Text::Handle frq_text = frq_list.component<Text>();
    frq_text->text = "Frq: " + ss.str() + "Hz";
}

void FrequencyControl::receive(const ButtonPushEvent &ev)
{
    if(ev.id == -1)
    {
        Text::Handle sr_text_c = sr_button.component<Text>();
        run = !run;
        sr_text_c->text = (run) ? "    STOP" : "    RUN";
    }
    else if(frq_table.find(ev.id) != frq_table.end())
    {
        Text::Handle frq_text = frq_list.component<Text>();
        frq_text->text = "Frq: " + frq_table[ev.id].second;
        time_step = frq_table[ev.id].first;
        max = false;
    }
    else if(max_button == ev.id)
    {
        max = true;
        Text::Handle frq_text = frq_list.component<Text>();
        frq_text->text = "Frq: MAX Hz";
    }
}
