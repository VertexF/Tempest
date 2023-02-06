#include "Layer.h"
#include "PreComp.h"

namespace Tempest
{
    Layer::Layer(const std::string& layerName, float zoomLevel) : _debugName(layerName), zoomLevel(zoomLevel)
    {
    }

    Layer::~Layer() 
    {
    }

    void Layer::onAttach() 
    {
    
    }

    void Layer::onDetach()
    {
    
    }

    void Layer::onUpdate(TimeStep timeStep)
    {
    
    }

    void Layer::onEvent(Event& e) 
    {
    
    }

    void Layer::onImGuiRender() 
    {
    }

    float Layer::getZoomLevel() const 
    {
        return zoomLevel;
    }
}