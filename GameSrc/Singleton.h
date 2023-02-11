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

        static T& getInstance() 
        {
            if (_instance == nullptr) 
            {
                createInstance();
            }
            return *_instance;
        }

        //Destroys the old instance and creates the one passed in as a argument.
        static void setInstance(T* newInstance) 
        {
            if (_instance)
            {
                destroyInstance();
            }
            _instance = newInstance;
        }
    private:
        Singleton() {}
        ~Singleton() {}

        static void createInstance()
        {
            _instance = new T();
        }

        static void destroyInstance()
        {
            delete _instance;
            _instance = nullptr;
        }


        static T* _instance;
    };

    template <class T>
    T* Singleton<T>::_instance = nullptr;
}

#endif // !SINGLETON_HDR
