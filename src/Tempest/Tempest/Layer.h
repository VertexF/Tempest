#ifndef LAYER_HDR
#define LAYER_HDR

#include "PreComp.h"

namespace Tempest 
{
    class Layer 
    {
    public:
        Layer(const std::string &layerName = "Layer");

        inline std::string getLayer() const { return _debugName; }
    private:
        std::string _debugName;
    };
}


#endif //LAYER_HDR