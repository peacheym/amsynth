#include "LibmapperController.h"
#include <iostream>

void LibmapperController::init()
{

    // graph.set_iface("wlp0s20f3");

    while (dev.poll())
        if (dev.ready())
            break;

    for (int i = kAmsynthParameter_AmpEnvAttack; i != kAmsynthParameterCount; i++)
    {
        float min = presetController->getCurrentPreset().getParameter(i).getMin();
        float max = presetController->getCurrentPreset().getParameter(i).getMax();
        std::string name = presetController->getCurrentPreset().getParameter(i).getName();
        mapper::Signal sig = dev.add_signal(mapper::Direction::INCOMING, name, 1, mapper::Type::FLOAT, 0, &min, &max);

        // Get default value for this parameter.
        float init_val = presetController->getCurrentPreset().getParameter(i).getDefault();
        sig.set_value(init_val);
        prev_vals[name] = init_val;
        
        // Add this signal to list of signals.
        signals.push_back(sig);
    }


}

void LibmapperController::process()
{
    dev.poll();

    for (const auto &signal : signals)
    {
        float *value = (float *)signal.value();
        if (value != 0)
        {
            std::string name = signal[mapper::Property::NAME];
            float prev = prev_vals[name];
            if(*value != prev){
                presetController->getCurrentPreset().getParameter(name).setValue(*value);
                prev_vals[name] = *value;
            }
        }
    }
}
