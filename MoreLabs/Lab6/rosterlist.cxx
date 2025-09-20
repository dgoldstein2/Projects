#include <string>
#include <iostream>
#include <stdexcept>
#include <exception>
#include "roster.h"
#include "rosterlist.h"
namespace csen79{
    
    bool RosterList::insert(T &rec){
        
        try{
            if(isEmpty){
                size = 0;
            }
            Node *ptr = new Node(rec);
            Node *temp = head;
            Node *cur = head;
            std::cout<< "allocated"<<std::endl;
            if(head == nullptr) {
                head = ptr;
                isEmpty = false;
            }                
            else{
                std::cout<<"Check"<<std::endl;
                while(temp!=nullptr){
                    if(temp->data.getID() == rec.getID()){
                        std::cout<< "Already Added"<< std::endl;
                        return false; 
                    }
                    else{
                        temp = temp->next;
                    }
                }

                
                while (cur->next != nullptr){
                    
                    cur = cur->next;
                }
                cur-> next = ptr;
                
            }

        } catch (const std::bad_alloc &e){
            return false;
        }
        std::cout<<rec.getID()<<" added"<< std::endl;
        
        return true;
    }
    void RosterList::erase(Student::ID_t id){
      
        Node *prev = nullptr;
        Node *cur = head;
        
        while (cur != nullptr && cur->data.getID() != id){
            prev = cur;
            cur = cur->next;
        }
        if(cur == nullptr){
            std::cout<< "Id not found" << std::endl;
            return;
        }
        if (prev == nullptr) head = cur->next;
        else prev->next = cur->next;
        cur->next = nullptr;
        delete cur;
    }
}