#ifndef FREQUENCYCONTROL_H
#define FREQUENCYCONTROL_H

#include <entityx/entityx.h>

#include <creators/listcreator.h>
#include <creators/buttoncreator.h>

#include <events/buttonpushevent.h>

#include <components/text.h>

#include <map>
#include <sstream>

class FrequencyControl : public entityx::Receiver<FrequencyControl>
{
    std::map <int, std::pair<float, std::string> > frq_table;
    entityx::Entity sr_button;
    entityx::Entity frq_list;
    float time_step;
    int max_button;
    bool run, max;
public:
    FrequencyControl();
    void init(entityx::EntityX & enX);
    float getTimeStep();
    bool isRunning();
    bool isMax();
    void setDisplayedFrq(int frq);

    void receive( const ButtonPushEvent& ev);
};

#endif // FREQUENCYCONTROL_H
