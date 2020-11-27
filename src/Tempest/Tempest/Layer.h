#ifndef LAYER_HDR
#define LAYER_HDR

#include "PreComp.h"
#include "Events/Event.h"

namespace Tempest 
{
    class TEMPEST_EXPORT Layer 
    {
    public:
        Layer(const std::string &layerName = "Layer");
        virtual ~Layer();

        virtual void onAttach();
        virtual void onDeattach();
        virtual void onUpdate();
        virtual void onEvent(Event& e);

        inline std::string getLayer() const { return _debugName; }
    private:
        std::string _debugName;
    };
}


#endif //LAYER_HDR