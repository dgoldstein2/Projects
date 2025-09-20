// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];

    }
    
    
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...
        used_slots = src.used_slots;
        aloc_slots = src.aloc_slots;
        company_array = new company[aloc_slots];
        for(unsigned int i = 0; i < src.used_slots; ++i){
            company_array[i] = src.company_array[i];
        }


    }
    
    
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...
        if (&rhs == this){
        return *this;
        }
        this->used_slots = rhs.used_slots;
        this->aloc_slots = rhs.aloc_slots;
        reserve(rhs.aloc_slots);
        for(size_t i = 0; i< rhs.used_slots; ++i){
            company_array[i] = rhs.company_array[i];
        }
        return *this;
    }


    
    
    database::~database() {
        // COMPLETE THE IMPLEMENTATION...
        delete [] company_array;
        aloc_slots = 0;
        used_slots = 0;
    }
    
    
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);
        company* newComp;
        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        
        // COMPLETE THE IMPLEMENTATION...
        try{
            newComp = new company[new_capacity];
        }catch (const std::bad_alloc& e){
            std::cerr << "Error" << e.what() <<std::endl;
        }
        std::copy(company_array, company_array + used_slots, newComp);
        delete [] company_array;
        company_array = newComp;
        
        aloc_slots = new_capacity;
    }
    
    //Pre: entry exists and has a length greater than 0
    //Post: inserts a new company with name entry into the array of companies
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." <<  entry << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }
        if(used_slots == aloc_slots){
            reserve(aloc_slots + 1);
        }
        company temp(entry);
        company_array[used_slots++] = temp;
        return true;
        

    }
    
    //Pre: company, product name and price all exist
    //Post: Inserts an item into the compamy called with name product name and price: price
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);
        size_t pos = search_company(company);
        if(pos == COMPANY_NOT_FOUND){
            return false;
        }
        return company_array[pos].insert(product_name, price);
    }
    
    //Pre: company exists in the array
    //Post: erases a company from the array
    bool database::erase_company(const std::string &company) {
        
        size_type index = search_company(company);
        
       
        if(index == COMPANY_NOT_FOUND){
            return false;
        }
        for(size_t i = index; i < used_slots-1; i++){
            company_array[i] = company_array[i+1];
        }
        used_slots--;
        return true;
    }
    
    //Pre:cName and pName exist and have lengths greater than 0
    //Post: erases an item from the list

    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);
        size_t index = search_company(cName);
        if(index == COMPANY_NOT_FOUND){
            return false;
        }
        return company_array[index].erase(pName);
    }
    
    
    //Post: searches for the company in 
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);

        
        for(size_t i = 0; i< used_slots; i++){
            if(company_array[i].get_name() == company){
                return i;
            }
        }
        return COMPANY_NOT_FOUND;
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        std::cout<<used_slots<<std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
