#include "LayerStack.h"
#include "Layer.h"

namespace Tempest 
{
    LayerStack::LayerStack() 
    {
        _layerIterator = _layers.begin();
    }

    LayerStack::~LayerStack() 
    {
        for (Layer *layer : _layers)
        {
            delete layer;
        }
    }

    void LayerStack::pushLayer(Layer* layer) 
    {
        _layerIterator = _layers.emplace(_layerIterator, layer);
    }

    void LayerStack::pushOverlay(Layer* overlay)
    {
        _layers.emplace_back(overlay);
    }

    //Layer will not be deleted if you pop it from the layer stack
    void LayerStack::popLayer(Layer* layer) 
    {
        auto it = std::find(_layers.begin(), _layers.end(), layer);
        if (it != _layers.end()) 
        {
            _layers.erase(it);
            _layerIterator--;
        }
    }

    void LayerStack::popOverlay(Layer* overlay) 
    {
        auto it = std::find(_layers.begin(), _layers.end(), overlay);
        if (it != _layers.end())
        {
            _layers.erase(it);
        }
    }
}