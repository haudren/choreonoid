/*!
  @file
  @author Shin'ichiro Nakaoka
*/

#ifndef CNOID_GRXUI_PLUGIN_H_INCLUDED
#define CNOID_GRXUI_PLUGIN_H_INCLUDED

#include <cnoid/Plugin>
#include "exportdecl.h"

namespace cnoid {

class CNOID_EXPORT GrxUIPlugin : public Plugin
{
public:
    static bool isActive();
    GrxUIPlugin();
    virtual bool initialize();
    void onImportGrxUICheckToggled(bool on, bool doWriteConfig);
    virtual bool finalize();
};
}

#endif
