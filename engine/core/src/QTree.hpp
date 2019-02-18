#pragma once

#include "Point.hpp"

namespace engine
{
    template <class T>
    struct QLeaf
    {
        T data;

        struct QLeaf* q1;
        struct QLeaf* q2;
        struct QLeaf* q3;
        struct QLeaf* q4;
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
