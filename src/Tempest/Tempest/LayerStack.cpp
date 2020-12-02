#include "LayerStack.h"
#include "Layer.h"

namespace Tempest 
{
    LayerStack::LayerStack() 
    {
    }

    //Layers are only raw pointer because we want to be able to remove them 
    //without losing them from memory.
    LayerStack::~LayerStack() 
    {
        for (Layer *layer : _layers)
        {
            delete layer;
        }
    }

    //We want the normal layers pushed the back of the layers in the list,
    //but still be a head of the overlay layers. So, we are keeping track
    //of the last time we added a normal layer to the stack with an 
    //iterator. 
    void LayerStack::pushLayer(Layer* layer) 
    {
        _layers.emplace(_layers.begin() + _layerIteratorIndex, layer);
        _layerIteratorIndex++;
    }

    //We want overlay layers to be added to the back of the vector always.
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
            _layerIteratorIndex--;
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