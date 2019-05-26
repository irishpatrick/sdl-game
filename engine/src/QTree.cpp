#include "QTree.hpp"
#include <cstdlib>

namespace engine
{
    template <class T>
    void allocate(struct QLeaf<T>* leaf)
    {
        leaf = (struct QLeaf<T>*)malloc(sizeof(struct QLeaf<T>));
        leaf->q1 = nullptr;
        leaf->q2 = nullptr;
        leaf->q3 = nullptr;
        leaf->q4 = nullptr;
    }
    
    template <class E>
    void r_insert(struct QLeaf<E>* leaf, E& data, Point& p)
    {
        bool above;
        bool right;
        if (p.x < 0.0f)
        {
            above = false;
        }
        else if (p.x > 0.0f)
        {
            above = true;
        }

        if (p.y < 0.0f)
        {
            right = false;
        }
        else if (p.y > 0.0f)
        {
            right = true;
        }

        if (above && right)
        {
            if (leaf->q1 == nullptr)
            {
                allocate<E>(leaf->q1);
                leaf->q1->data = data;
                return;
            }
            else
            {
                r_insert<E>(leaf->q1, data, p);
                return;
            }
        }

        else if (above && !right)
        {
            if (leaf->q2 == nullptr)
            {
                //leaf->q2 = (struct QLeaf<E>*)malloc(sizeof(struct QLeaf<E>));
                allocate<E>(leaf->q2);
                leaf->q2->data = data;
                return;
            }
            else
            {
                r_insert<E>(leaf->q2, data, p);
                return;
            }
        }

        else if (!above && !right)
        {
            if (leaf->q3 == nullptr)
            {
                //leaf->q3 = (struct QLeaf<E>*)malloc(sizeof(struct QLeaf<E>));
                allocate<E>(leaf->q3);
                leaf->q3->data = data;
                return;
            }
            else
            {
                r_insert<E>(leaf->q3, data, p);
                return;
            }
        }

        else if (!above && right)
        {
            if (leaf->q4 == nullptr)
            {
                //leaf->q4 = (struct QLeaf<E>*)malloc(sizeof(struct QLeaf<E>));
                allocate<E>(leaf->q4);
                leaf->q4->data = data;
                return;
            }
            else
            {
                r_insert<E>(leaf->q4, data, p);
                return;
            }
        }
    }

    template <class T>
    QTree<T>::QTree()
    {

    }

    template <class T>
    QTree<T>::~QTree()
    {
        
    }

    template <class T>
    void QTree<T>::insert(T& data, Point& p)
    {
        r_insert<T>(&root, data, p);
    }
}
