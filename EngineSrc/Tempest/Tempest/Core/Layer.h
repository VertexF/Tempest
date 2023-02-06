#ifndef LAYER_HDR
#define LAYER_HDR

#include "PreComp.h"
#include "Tempest/Events/Event.h"

#include "TimeStep.h"

namespace Tempest 
{
    //Every thing in the engine is layered. 
    //Each layer contains away to detach and attach itself.
    //TODO: Add the functionality for layering to be useful.
    class Layer 
    {
    public:
        Layer(const std::string &layerName = "Layer", float zoomLevel = 1.f);
        virtual ~Layer();

        virtual void onAttach();
        virtual void onDetach();
        virtual void onUpdate(TimeStep timeStep);
        virtual void onEvent(Event& e);
        virtual void onImGuiRender();
        virtual bool isFinished() const = 0;
        virtual float getZoomLevel() const;

        //Only really used for debugging and shouldn't be used in release.
        inline std::string getLayer() const { return _debugName; }
    protected:
        float zoomLevel;
    private:
        std::string _debugName;
    };
}


#endif //LAYER_HDR