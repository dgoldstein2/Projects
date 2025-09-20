
#ifndef ITEM_CPP
#define ITEM_CPP

#include "node.h"

namespace coen79_lab7
{
    node::node(const std::string &itemName, const float &newPrice, node *nextNode) {
        name = itemName;
        price = newPrice;
        link = nextNode;
    }
    
    void node::setName(const std::string &newName) {
        name = newName;
    }
    
    void node::setPrice(const float &newPrice) {
        price = newPrice;
    }
    
    void node::setLink(node *new_next) {
        link = new_next;
    }
    
    node* node::getLink() {
        return link;
    }
    
    const node* node::getLink() const {
        return link;
    }
    
    std::string node::getName() const{
        return name;
    }
    
    float node::getPrice() const {
        return price;
    }
    
    
    void list_init(node*& head, node*& tail, const std::string& newName, const float& newPrice) {
        head = new node(newName, newPrice, NULL);
        tail = head;
    }
    
    //Pre: newname exists and has a length greater than 0
    //Post: inserts a new node into the list at the tail side
    void list_tail_insert(node*& tail, const std::string &newName, const float &newPrice) {
        node *temp;
        
        try{
            temp = new node(newName, newPrice, nullptr);
        }catch (const std::bad_alloc& e){
            std::cerr << "Error" << e.what() <<std::endl;
        }
        
        tail->setLink(temp);
        tail = temp;
        tail->setLink(nullptr); 
    }
    
    //Pre: head exists 
    //Post: clears whole list
    void list_clear(node*& head) {
        node *cur = head;
        while(cur != nullptr){
            node *temp = cur;
            cur = cur->getLink();
            delete temp;

        }
    }
    
    void list_copy(const node *old_head, node* &new_head, node* &new_tail) {
        new_head = nullptr;
        new_tail = new_head;
        
        const node *cur = old_head;
        while (cur != nullptr) {
            if (new_head == nullptr) {
                new_head = new node(cur->getName(), cur->getPrice());
                new_tail = new_head;
            }
            else {
                new_tail->setLink(new node(cur->getName(), cur->getPrice()));
                new_tail = new_tail->getLink();
            }
            cur=cur->getLink();
        }
    }
    
    //Pre: head exists
    //Post: removes the head node and makes the next node the new head node
    void list_head_remove(node*& head) {
        node* temp = head;
        head = temp->getLink();
        delete temp;
        
    }
    
    
    void list_print(node *head) {
        node *cur = head;
        while (cur != NULL) {
            std::cout << "- " << cur->getName() << ", where the price is $" << cur->getPrice() << std::endl;
            cur = cur->getLink();
        }
    }
    
    
    bool list_contains_item(node *head_ptr, const std::string& newName) {
        return (list_search(head_ptr, newName) != NULL);
    }
    
    
    node* list_search(node* head_ptr, const std::string& target)
    {
        node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
    
    const node* list_search(const node* head_ptr, const std::string & target)
    {
        const node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->getLink( ))
            if (target == cursor->getName( ))
                return cursor;
        return NULL;
    }
    
}

#endif
