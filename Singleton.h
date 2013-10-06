#ifndef SINGLETON_H_
#define SINGLETON_H_
#include <stdlib.h>

template <class T>
class Singleton
{
protected:
	static T* INSTANCE;
public:
	static T* getInstance();
};

template <class T>
T* Singleton<T>::INSTANCE = NULL;

template <class T>
T* Singleton<T>::getInstance()
{
	if ( INSTANCE == NULL )
		INSTANCE = new T();
	return INSTANCE;
}

#endif /* SINGLETON_H_ */
