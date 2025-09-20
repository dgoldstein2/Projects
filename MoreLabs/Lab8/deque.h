// FILE: deque.h
// PROVIDES: A class for deque (double ended queue)
// Belongs to namespace coen79_lab8
//
//  COEN 79
//  Behnam Dezfouli, COEN, SCU
//
// TEMPLATE PARAMETER, TYPEDEFS and MEMBER CONSTANTS for the deque<Item> class:
//   The template parameter, Item, is the data type of the items in the deque,
//   also defined as deque<Item>::value_type. It may be any of the C++ built-in
//   types (int, char, etc.), or a class with a default constructor, a copy
//   constructor, and an assignment operator. The definition
//   deque<Item>::size_type is the data type of any variable that keeps track of
//   how many items are in a deque.
//
//   static const size_t BLOCK_SIZE = ____
//     deque::BLOCK_SIZE is the number of enteries in each data block
//
//   static const size_t BLOCKPOINTER_ARRAY_SIZE = ____
//     deque::BLOCKPOINTER_ARRAY_SIZE is the number of enteries in the array of block pointers
//
//   typedef ____ Item
//     sequence::Item is the data type of the items in the deque. It may be any of
//     the C++ built-in types (int, char, etc.), or a class with a default
//     constructor, an assignment operator, and a copy constructor.
//
//
// CONSTRUCTOR for the deque<Item> class:
//   deque(szie_type init_bp_array_size = BLOCKPOINTER_ARRAY_SIZE,
//         size_type initi_block_size = BLOCK_SIZE);
//     Postcondition: The deque contains an array of block pointers with BLOCKPOINTER_ARRAY_SIZE entries
//     NOTE: The default value for the init_bp_array_size is BLOCKPOINTER_ARRAY_SIZE.
//     The default value for the initi_block_size is BLOCK_SIZE.
//
//
//
// CONST MEMBER FUNCTIONS for the deque<Item> class:
//
//   bool isEmpty()
//     Postcondition: Returns false if the deque is empty.
//     Otherwise returns true.
//
//   value_type front()
//    Precondition: isItem() must return true.
//    Postcondition: Returns a copy of the front item.
//
//   value_type back()
//    Precondition: isItem() must return true.
//    Postcondition: Returns a copy of the back item.
//
//
// MEMBER FUNCTIONS for the deque<Item> class:
//   void clear()
//     Postcondition: All the entries of the deque are deleted.
//
//   void print()
//     Postcondition: Prints all the entries of the deque.
//
//   void reserve()
//    Postcondition: Increases the capacity of the deque by 20 x BLOCK_SIZE
//
//   void push_front(const value_type& entry)
//    Postcondition: Adds entry to the front of the deque
//
//   void push_back(const value_type& entry)
//    Postcondition: Adds entry to the back of the deque
//
//   void pop_front()
//    Precondition: isItem() must return true
//    Postcondition: Removes the front item of the deque
//
//   void pop_back()
//    Precondition: isItem() must return true
//    Postcondition: Removes the back item of the deque
//
//
// VALUE SEMANTICS for the deque<Item> class:
//    Assignments and the copy constructor may be used with deque objects.
//
//
// STANDARD ITERATOR MEMBER FUNCTIONS (provide a forward iterator):
//   iterator begin( )
//   iterator end( )


/*
 * Dakota Goldstein
 * dagoldstein@scu.edu
 * Lab 8
 * Description: Builds the deque data structure
 * 
*/
#ifndef COEN79_DEQUE
#define COEN79_DEQUE

#define USEDEBUG

#ifdef USEDEBUG
//#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <cassert>

#include "deque_iterator.h" // The iterator class for deque (refer to file deque_iterator.h)


namespace coen79_lab8
{
    template <class Item>
    class deque {
    public:
        
        // TYPEDEF
        static const size_t BLOCK_SIZE = 5; // Number of data items per data block
        static const size_t BLOCKPOINTER_ARRAY_SIZE = 5; // Number of entries in the array of block pointers (The minimum acceptable value is 2)
        
        typedef std::size_t size_type;
        typedef Item value_type; // The type of items stored in the deque
        
        typedef deque_iterator<Item> iterator; // A typedef to simplify the use of iterator class
        
        // CONSTRUCTOR and DESTRUCTOR
        deque(size_type init_bp_array_size = BLOCKPOINTER_ARRAY_SIZE, size_type initi_block_size = BLOCK_SIZE);
        deque(const deque& source);
        ~deque();
        
        // CONST MEMBER FUNCTIONS
        bool isEmpty();
        value_type front();
        value_type back();
        
        // ITERATOR MEMBER FUNCTIONS
        iterator begin();
        iterator end();
        
        // MODIFICATION MEMBER FUNCTIONS
        void operator=(const deque& source);
        void clear();
        void reserve();
        void push_front(const value_type& entry);
        void push_back(const value_type& entry);
        void pop_back();
        void pop_front();
        
        
    private:
        
        value_type** block_pointers;      // A pointer to the array of block pointers
        value_type**  block_pointers_end; // A pointer to the final entry in the array of block pointers
        
        value_type**  first_bp;  // A pointer to the entry of the array of block pointers which points to the first data block
        value_type**  last_bp;   // A pointer to the entry of the array of block pointers which points to the last data block
        
        value_type* front_ptr;   // A pointer to the front element of the deque
        value_type* back_ptr;    // A pointer to the back element of the deque
        
        size_type bp_array_size; // Number of entries in the array of block pointers
        size_type block_size;    // Number of entries in each data block
    };
    
    
    
    
    // ------------------------------------------------------------------------------
    // IMPLEMENTATION
    // ------------------------------------------------------------------------------

    
    //CONSTRUCTOR
    template <class Item>
    deque<Item>::deque (size_type init_bp_array_size, size_type init_block_size) {
        
        bp_array_size = init_bp_array_size;
        block_size = init_block_size;
        
        // Create an an array of block pointers and assign its address to "block_pointers"
        try{
            block_pointers = new value_type* [bp_array_size];
        }catch (const std::bad_alloc& e) {
                std::cout << "Allocation failed: " << e.what() << '\n';
        }
        // Assign NULL to all the entries of the array of block pointers
        for (size_type index = 0; index < bp_array_size; ++index)
        {
            block_pointers[index] = NULL;
        }
        
        // Set block_pointers_end to point to the end of the array
        block_pointers_end = block_pointers + (bp_array_size - 1);
        
        first_bp = last_bp = NULL;
        front_ptr = back_ptr = NULL;
    }
    
    
    //COPY CONSTRUCTOR
    template <class Item>
    deque<Item>::deque (const deque<Item>& source) {
        
        first_bp = last_bp = NULL;
        front_ptr = back_ptr = NULL;
        block_pointers = block_pointers_end = NULL;
        bp_array_size = 0;
        block_size = 0;
        
        // Use the assignment operator
        // (must have been already implemented, you cannot rely on the compiler)
        *this = source;
    }
    
    
    // ASSIGNMENT OPERATOR
   template <class Item>
    void deque<Item>::operator=(const deque<Item>& source) {
        // Self-assignment check
        if (this == &source)
            return;
    
        // Clear existing data
        clear();
    
        // Delete existing block pointers array
        delete[] block_pointers;
    
        // Copy basic parameters
        bp_array_size = source.bp_array_size;
        block_size = source.block_size;
    
        // Allocate new block pointers array
        try {
            block_pointers = new value_type*[bp_array_size];
        } catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            bp_array_size = 0;
            block_size = 0;
            block_pointers = NULL;
            block_pointers_end = NULL;
            first_bp = NULL;
            last_bp = NULL;
            front_ptr = NULL;
            back_ptr = NULL;
            return;
        }
    
        // Initialize block pointers array to NULL
        for (size_type i = 0; i < bp_array_size; ++i) {
            block_pointers[i] = NULL;
        }
    
        // Set block_pointers_end
        block_pointers_end = block_pointers + (bp_array_size - 1);
    
        // Track offset if source has non-NULL blocks
        if (source.first_bp != NULL) {
            // Calculate offset of first and last block pointers
            size_type first_bp_offset = source.first_bp - source.block_pointers;
            size_type last_bp_offset = source.last_bp - source.block_pointers;
        
            // Copy and allocate blocks
            for (size_type bp_index = 0; bp_index <= last_bp_offset - first_bp_offset; ++bp_index) {
                if (source.block_pointers[first_bp_offset + bp_index] != NULL) {
                    try {
                        // Allocate new block
                        block_pointers[first_bp_offset + bp_index] = new value_type[block_size];
                    
                        // Copy items in the block
                        for (size_type item_index = 0; item_index < block_size; ++item_index) {
                            block_pointers[first_bp_offset + bp_index][item_index] = source.block_pointers[first_bp_offset + bp_index][item_index];
                        }
                    
                        // Set first_bp and last_bp if this is the first or last block
                        if (bp_index == 0) {
                            first_bp = block_pointers + first_bp_offset;
                        }
                        if (bp_index == last_bp_offset - first_bp_offset) {
                            last_bp = block_pointers + first_bp_offset + bp_index;
                        }
                    
                        // Track front and back pointers
                        if (source.front_ptr >= source.block_pointers[first_bp_offset + bp_index] &&
                            source.front_ptr < source.block_pointers[first_bp_offset + bp_index] + block_size) {
                            front_ptr = block_pointers[first_bp_offset + bp_index] + (source.front_ptr - source.block_pointers[first_bp_offset + bp_index]);
                        }
                    
                        if (source.back_ptr >= source.block_pointers[first_bp_offset + bp_index] &&
                            source.back_ptr < source.block_pointers[first_bp_offset + bp_index] + block_size) {
                            back_ptr = block_pointers[first_bp_offset + bp_index] + (source.back_ptr - source.block_pointers[first_bp_offset + bp_index]);
                        }
                    
                    } catch (const std::bad_alloc& e) {
                        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                        // Cleanup
                        clear();
                        delete[] block_pointers;
                        block_pointers = NULL;
                        return;
                    }
                }
            }
        }
    }

    
    
    //DESTRUCTOR
    template <class Item>
    deque<Item>::~deque () {
        for (size_type i=0; i<bp_array_size; ++i) {
            delete [] block_pointers[i];
            block_pointers[i] = NULL;
        }
        delete [] block_pointers;
        first_bp = last_bp = block_pointers_end = block_pointers = NULL;
        front_ptr = back_ptr = NULL; 
    }
    
    
    template <class Item>
    void deque<Item>::clear () {
        
        // Clear the data blocks
        
        for (size_type i=0; i<bp_array_size; ++i) {
            delete [] block_pointers[i];
            block_pointers[i] = NULL;
        }
        
        first_bp = last_bp = NULL;
        front_ptr = back_ptr = NULL;
        
        // Note: The array of block pointers should not be deleted;
        //       However, all of its entries are NULL because all the
        //       data blocks have been deleted.
    }
    
    
    
    template <class Item>
    void deque<Item>::reserve()
    {
        // The new array of block pointers includes 20 more entries
        // This results in increasing the size by 20 x BLOCK_SIZE
        size_type newSize = bp_array_size + 20;
        value_type** new_block_pointers;
        // Create a new array of block pointers
        try{
            new_block_pointers = new value_type* [newSize];
        }catch (const std::bad_alloc& e) {
            std::cout << "Allocation failed: " << e.what() << '\n';
        }
        // Assign NULL to all the entries of the array of block pointers
        for (size_type index = 0; index < newSize; ++index)
        {
            new_block_pointers[index] = NULL;
        }
        
        // Find the location of "first_bp" in the new array of block pointers
        // The offset enables us to copy the not-NULL elements of the existing
        // array to the middle of the new array
        size_type offsett_first_bp = first_bp - block_pointers;
        size_type offsett_last_bp = last_bp - block_pointers;
        
        
        // Copy the not-NULL elements of the array of block pointers to the new array,
        // starting at the computer offset
        std::copy(first_bp, last_bp + 1, new_block_pointers + 10 + offsett_first_bp);
        
        
        // Delete the existing array of block pointers
        delete [] block_pointers;
        
        // Set the pointers
        block_pointers = new_block_pointers;
        bp_array_size = newSize;
        block_pointers_end = block_pointers + bp_array_size - 1;
        first_bp = block_pointers + offsett_first_bp + 10;
        last_bp = block_pointers + offsett_last_bp + 10;
    }
   template <class Item>
    void deque<Item>::push_front(const value_type& entry)
    {
        // Only the array of block pointers exists (and no data block exists)
        if (first_bp == NULL)
        {
            assert(bp_array_size > 1);
            size_t bp_mid = floor(bp_array_size/2); // Get the mid point of the array of block pointers
        
            // Both last_bp and first_bp point to the same location of the array of block pointers
            last_bp = first_bp = block_pointers + bp_mid - 1;
        
            try {
                // Allocate a new block
                *first_bp = new value_type[block_size];
            
                // Set front and back pointers to the first element of the new block
                front_ptr = back_ptr = *first_bp;
            
                // Add the entry
                *front_ptr = entry;
            } catch (const std::bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                first_bp = last_bp = NULL;
                front_ptr = back_ptr = NULL;
                return;
            }
        }
    
        // There is at least one empty slot before the entry that front_ptr points to 
        // (in the same data block)
        else if (front_ptr != *first_bp)
        {
            --front_ptr;
            *front_ptr = entry;
        }
    
        // Data block has no room left before front_ptr; however,
        // the array of block pointers has at least one available
        // slot before first_bp to allocate a new data block
        else if ((*first_bp == front_ptr) && (first_bp != block_pointers))
        {
            --first_bp;
        
            try {
                *first_bp = new value_type[block_size];
                front_ptr = *first_bp + (block_size - 1);
                *front_ptr = entry;
            } catch (const std::bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                // Restore first_bp
                ++first_bp;
                return;
            }
        }
    
        // Data block has no room left before front_ptr;
        // and the array of block pointers has no available slot before first_bp
        else if ((*first_bp == front_ptr) && (first_bp == block_pointers))
        {
            // First, expand the block pointer array
            reserve();
            
            try {
                // Now allocate a new block at the beginning of the expanded array
                *first_bp = new value_type[block_size];
                front_ptr = *first_bp + (block_size - 1);
                *front_ptr = entry;
            } catch (const std::bad_alloc& e) {
                std::cerr << "Memory allocation failed: " << e.what() << std::endl;
                return;
            }
        }
    }
    
    template <class Item>
    void deque<Item>::push_back(const value_type& entry)
    {
        
        // Only the array of block pointers exists (and no data block exists)
        if (last_bp == NULL)
        {
            assert(bp_array_size > 1);
            size_t bp_mid = floor(bp_array_size/2); // Get the mid point of the array of block pointers
            
            last_bp = first_bp = block_pointers + bp_mid  - 1;
            try{
                *(last_bp) = new value_type[block_size];
            }catch (const std::bad_alloc& e) {
                std::cout << "Allocation failed: " << e.what() << '\n';
            }
            back_ptr = front_ptr = *last_bp;
            
            *back_ptr = entry;
        }
        
        // There is at least one empty slot after the entry
        // that back_ptr points to (in the same data block)
        else if (back_ptr != ((*last_bp) + (block_size - 1)))
        {
            ++back_ptr;
            *back_ptr = entry;
        }
        
        // Data block has no room left after back_ptr;
        // however, the array of block pointers has at least one available slot
        // below last_bp to allocate a new data block
        else if ((back_ptr == ((*last_bp) + (block_size - 1))) && (last_bp != block_pointers_end))
        {
            ++last_bp;
            try{
                *(last_bp) = new value_type[block_size];
            }catch (const std::bad_alloc& e) {
                std::cout << "Allocation failed: " << e.what() << '\n';
            }
            
            
            back_ptr = *last_bp;
            *back_ptr = entry;
            

        }
        
        // Data block has no room left after back_ptr;
        // and the array of block pointers has no available slot after last_bp
        else if ((back_ptr == ((*last_bp) + (block_size - 1))) && (last_bp == block_pointers_end))
        {
            
            reserve();
            
            ++last_bp;
            
            try{
                *last_bp = new value_type[block_size];
            }catch (const std::bad_alloc& e) {
                std::cout << "Allocation failed: " << e.what() << '\n';
            }
            back_ptr = *last_bp;
            *back_ptr = entry;
        }
    }
    
    
    template <class Item>
    void deque<Item>::pop_front()
    {
        assert(!isEmpty());
        
        // This is the only entry in the deque; remove it and delete the data block
        if (back_ptr == front_ptr)
        {
           
            clear();

        }
        // This is the last entry of the data block; move to the next block
        else if (front_ptr == ((*first_bp) + block_size - 1))
        {
           
            delete[] *first_bp;
            *first_bp = NULL;
            ++first_bp;
            front_ptr = *first_bp;

        }
        // Simply move the pointer
        else
        {
            
            ++front_ptr;

        }
    }
    
    
    template <class Item>
    void deque<Item>::pop_back()
    {
        assert(!isEmpty());
        
        if (back_ptr == front_ptr)
        {
            clear( );
        }
        else if (back_ptr == *last_bp)
        {
            delete [] *last_bp;
            *last_bp = NULL;
            --last_bp;
            back_ptr = (*last_bp) + (BLOCK_SIZE -1);

        }
        else
        {
            --back_ptr;
        }
    }
    
    template <class Item>
    bool deque<Item>::isEmpty()
    {
        if (front_ptr == NULL)
            return true;
        
        return false;
    }
    
    template <class Item>
    typename deque<Item>::value_type deque<Item>::back()
    {
        assert(!isEmpty());
        return *back_ptr;
    }
    
    template <class Item>
    typename deque<Item>::value_type deque<Item>::front()
    {
        assert(!isEmpty());
        return *front_ptr;
    }
    
    
    // Constructs an itertor which points to the
    // first element of the deque
    template <class Item>
    typename deque<Item>::iterator deque<Item>::begin()
    {
        
        value_type* tmp_cursor = NULL;
        value_type* tmp_current_boundary = NULL;
        value_type** tmp_current_block_pointer = NULL;
        
        if (front_ptr != NULL)
        {
            tmp_cursor = front_ptr;
            tmp_current_block_pointer = first_bp;
            tmp_current_boundary = (*first_bp) + (block_size - 1);
        }
        
        return iterator(block_pointers, block_pointers_end, first_bp, last_bp,
                        front_ptr, back_ptr,
                        bp_array_size, block_size,
                        tmp_cursor, tmp_current_boundary, tmp_current_block_pointer);
    }
    
    
    // Constructs an itertor which points to the past the
    // last element of the deque
    template <class Item>
    typename deque<Item>::iterator deque<Item>::end()
    {
        value_type* tmp_cursor = NULL;
        value_type* tmp_current_boundary = NULL;
        value_type** tmp_current_block_pointer = NULL;
        
        return iterator(block_pointers, block_pointers_end, first_bp, last_bp,
                        front_ptr, back_ptr,
                        bp_array_size, block_size,
                        tmp_cursor, tmp_current_boundary, tmp_current_block_pointer);
    }
    
}

#endif /* deque_hpp */
