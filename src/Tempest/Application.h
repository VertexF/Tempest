#ifndef APPLICATION_HDR
#define APPLICATION_HDR

#include <tempest_export.h>

namespace Tempest
{
    //TEMPEST_EXPORT void test();
    class TEMPEST_EXPORT Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
    };

    //To be defined in the client.
    Application* createApplication();
}

#endif // TEST_HDR
