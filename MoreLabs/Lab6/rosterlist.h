/*
 * Dakota Goldstein
 * dagoldstein@scu.edu
 * file: node.h
 * 
 * 
*/
#ifndef ROSTERLIST_H
#define ROSTERLIST_H
#include "roster.h"
namespace csen79{
    class RosterList : public Roster {
        public:
            struct Node{
                T data;
                Node *next;
                Node(T &t): data(t){}
                ~Node() {if(this->next != nullptr) delete this-> next;}

            };
            class iterator{
                public: 
                    iterator(Node *t) {ptr = t;}
                    bool operator !=(const iterator &rhs){return this->ptr != rhs.ptr;}
                    T &operator *() {return ptr->data;}
                    iterator &operator ++() {this->ptr = this->ptr->next; return *this;}
                private:
                    Node *ptr;
            };
            RosterList(): head(nullptr){}
            ~RosterList() {delete head;}
            bool insert(T &);
            void erase(Student::ID_t);
            friend iterator;
            iterator begin(){return iterator(head);}
            iterator end(){ return iterator(nullptr);}
            
        private:
            Node *head;
            unsigned int size;
            bool isEmpty = true;

    };
}
#endif // ROSTERLIST_H
