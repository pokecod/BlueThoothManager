#ifndef DEFINES_H
#define DEFINES_H


#include <QDebug>

/*
#ifdef QT_DEBUG

     qDebug() << "Running a debug build";

#endif
*/

typedef quint16 uuid;

//
// Property macros
//

#define PROPERTY_RW(Type, name)									\
        private:												\
        Type _##name;											\
        public:													\
        Type get_##name() const { return _##name; }				\
        void set_##name(const Type& name) { _##name = name; }	\
        __declspec(property(									\
        get = get_##name,										\
        put = set_##name))										\
        Type name;

#define PROPERTY_RO(Type, name)									\
        private:												\
        Type _##name;											\
        void set_##name(const Type& name) { _##name = name; }	\
        public:													\
        Type get_##name() const { return _##name; }				\
        __declspec(property(									\
        get = get_##name,										\
        put = set_##name))										\
        Type name;

#define PROPERTY_PROTECT(Type, name)									\
        protected:												\
        Type _##name;											\
        void set_##name(const Type& name) { _##name = name; }	\
        public:													\
        Type get_##name() const { return _##name; }				\
        __declspec(property(									\
        get = get_##name,										\
        put = set_##name))										\
        Type name;



#endif // DEFINES_H
