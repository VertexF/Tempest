#ifndef LAYER_HDR
#define LAYER_HDR

#include "PreComp.h"
#include "Events/Event.h"

namespace Tempest 
{
    //Every thing in the engine is layered. 
    //Each layer contains away to detach and attach itself.
    //TODO: Add the functionality for layering to be useful.
    class TEMPEST_EXPORT Layer 
    {
    public:
        Layer(const std::string &layerName = "Layer");
        virtual ~Layer();

        virtual void onAttach();
        virtual void onDetach();
        virtual void onUpdate();
        virtual void onEvent(Event& e);
        virtual void onImGuiRender() {}

        //Only really used for debugging and shouldn't be used in release.
        inline std::string getLayer() const { return _debugName; }
    private:
        std::string _debugName;
    };
}


#endif //LAYER_HDR