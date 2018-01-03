
#ifndef _Singleton_H_
# define _Singleton_H_

namespace b2ge
{
  template <typename TSingleton>
  class Singleton
  {
   protected:
    Singleton() = default;

   public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    virtual ~Singleton() = default;

    static TSingleton &getInstance()
    {
      static TSingleton instance;

      return instance;
    }
  };
}

#endif /* !_Singleton_H_ */