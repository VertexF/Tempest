#ifndef LAYER_STACK_HDR
#define LAYER_STACK_HDR

#include "PreComp.h"

namespace Tempest 
{
    class Layer;

    //This is a wrapper around a vector. This will handle navigation of
    // the layers.
    class TEMPEST_EXPORT LayerStack 
    {
    public:
        LayerStack();
        ~LayerStack();

        void pushLayer(Layer *layer);
        void pushOverlay(Layer* overlay);
        void popLayer(Layer* layer);
        void popOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return _layers.begin(); }
        std::vector<Layer*>::iterator end() { return _layers.end(); }
    private:
        std::vector<Layer*> _layers;
        std::vector<Layer*>::iterator _layerIterator;
    };
}

#endif // !LAYER_STACK_HDR
