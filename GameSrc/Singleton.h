#ifndef SINGLETON_HDR
#define SINGLETON_HDR

namespace game 
{
    //A global instance template for classes.
    template<typename T>
    class Singleton 
    {
    public:
        Singleton(const Singleton&) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton& operator=(Singleton&&) = delete;

        static void createInstance() 
        {
            instance = new T();
        }

        static void destroyInstance() 
        {
            delete instance;
            instance = nullptr;
        }

        static T& getInstance() 
        {
            if (instance == nullptr) 
            {
                createInstance();
            }
            return *instance;
        }

        //Destroys the old instance and creates the one passed in as a argument.
        static void setInstance(T* newInstance) 
        {
            if (instance) 
            {
                destroyInstance();
            }
            instance = newInstance;
        }

    private:
        static T* instance;

        Singleton() {}
        ~Singleton() {}
    };

    template <class T>
    T* Singleton<T>::instance = nullptr;
}

#endif // !SINGLETON_HDR
