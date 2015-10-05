#ifndef GLOBAL_SETTING_H
#define GLOBAL_SETTING_H

#include "singleton.h"

struct GlobalSetting
{
    // --
    GlobalSetting(void);

    // --
    int fps;
};


#define GLOBAL_SETTING Singleton<GlobalSetting>::instance()

inline GlobalSetting::GlobalSetting(void) :
    fps(30)
{}







#endif
