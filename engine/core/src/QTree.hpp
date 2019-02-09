#pragma once

#include "Point.hpp"

namespace engine
{
    template <class T>
    struct QLeaf
    {
        T data;

        struct _QLeaf* q1;
        struct _QLeaf* q2;
        struct _QLeaf* q3;
        struct _QLeaf* q4;
    };

    template <class T>
    class QTree
    {
    public:
        QTree<T>();
        ~QTree<T>();

        void insert(T&, Point&);
        void clear();
        void trim();

        struct QLeaf<T> root;
    private:

    };
}