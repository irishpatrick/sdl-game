#pragma once 

#include "Point.hpp"

namespace engine
{
    template <class E>
    struct QLeaf
    {
        E data;

        struct QLeaf<E>* q1;
        struct QLeaf<E>* q2;
        struct QLeaf<E>* q3;
        struct QLeaf<E>* q4;
    };

    template <class E>
    class QTree
    {
    public:
        QTree<E>();
        ~QTree<E>();

        void insert(E&, Point&);
        void clear();
        void trim();

        struct QLeaf<E> root;
    private:

    };
}
