
#ifndef _LIBMAPPERONTROLLER_H
#define _LIBMAPPERONTROLLER_H

#include <mapper/mapper_cpp.h>

#include <map>
#include "PresetController.h"
#include "Parameter.h"
// #include "controls.h"

class LibmapperController
{
public:
    LibmapperController() : dev("amsynth"), graph(){};

    void init();

    void setPresetController(PresetController &pc) { presetController = &pc; }

    void process();

private:
    PresetController *presetController = nullptr;
    mapper::Device dev;
    mapper::Graph graph;
    std::list<mapper::Signal> signals;
    std::map<std::string, float> prev_vals;
    mapper::Signal exportSig;
    int prevID = -1;

};

#endif
