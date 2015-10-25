#ifndef GLOBAL_SETTING_H
#define GLOBAL_SETTING_H

#include "singleton.h"


#define GLOBAL_SETTING Singleton<GlobalSetting>::instance()


struct GlobalSetting
{
    // --
    GlobalSetting(void);

    // --
    int fps;
};


// --
inline GlobalSetting::GlobalSetting(void) :
    fps(60)
{}




#endif
