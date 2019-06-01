<<<<<<< HEAD
#ifndef SINGLETONE_H
#define SINGLETONE_H

template < typename T >
class Singleton {

public:

    static T& GetInstance() {
      static MemGuard g; // clean up on program end
      if (!m_instance) {
        m_instance = new T();
      }
      return *m_instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;

protected:

    Singleton() { }
    virtual ~Singleton() { }

private:

    static T * m_instance;


    class MemGuard
    {
      public:

        ~MemGuard() {
            delete m_instance;
            m_instance = nullptr;
        }
    };
};

#endif // SINGLETONE_H
=======
#ifndef SINGLETONE_H
#define SINGLETONE_H

template < typename T >
class Singleton {

public:

    static T& GetInstance() {
      static MemGuard g; // clean up on program end
      if (!m_instance) {
        m_instance = new T();
      }
      return *m_instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;

protected:

    Singleton() { }
    virtual ~Singleton() { }

private:

    static T * m_instance;


    class MemGuard
    {
      public:

        ~MemGuard() {
            delete m_instance;
            m_instance = nullptr;
        }
    };
};

#endif // SINGLETONE_H
>>>>>>> 70376e58ffc9b3f7820f5e9b2bcc0cad92d33f44
