// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)
/*
 * Dakota Goldstein
 * dagoldstein@scu.edu
 * file: company.cpp
 * Description: this file builds the company methods and objects
 */

#include <cassert>
#include "company.h"
#include "node.h"
//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    //default constructor for the company class
    company::company() {
        this->company_name = "";
        this->head_ptr = nullptr;
        this->tail_ptr = nullptr;
    }
    //constructor for the company class
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);
        this->head_ptr = nullptr;
        this->tail_ptr = nullptr;
        this->company_name = company_name;
    }
    //Company src cannot be NULL and must exist
    //Post: copy constructor for the company class
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);
        this->company_name = src.get_name();
        this->head_ptr = nullptr;
        this->tail_ptr = nullptr;
        list_copy(src.get_head(), head_ptr,tail_ptr);
    }

    //Post: overloading the = operator to allow you to create a copy of an object onto a new object
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);
        list_clear(head_ptr);
        head_ptr = nullptr;
        tail_ptr = nullptr;
        list_copy(src.get_head(),head_ptr,tail_ptr);
        this->company_name = src.get_name();
        return *this;
    }
    
    //Destructor for the company class
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    //Post: Inserts an item into the company with name product_name and price price
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == nullptr) {
            list_init(head_ptr, tail_ptr, product_name, price);
        }
        else {
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }

    //Post: removes an item with name product_name from the list returns if it was removed
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);
        node *target_ptr;
        target_ptr = list_search(head_ptr, product_name);
        if(target_ptr == nullptr){
            return false;
        }
        target_ptr->setName(head_ptr->getName());
        target_ptr->setPrice(head_ptr->getPrice());
        list_head_remove(head_ptr);
        return true;

    }
    
    
}
