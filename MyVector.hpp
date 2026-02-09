
/**
 *Name:Emmanuel De Guzman 
 *CWID:884886995
 *Email:edeguzmanjr05@csu.fullerton.edu
 */


/// Your welcome
#include <assert.h>
#include <iostream>
#include <string>

namespace CPSC131::MyVector
{

	//
	template <typename T>
	class MyVector
	{
		public:
			
			/*******************
			 * Static constants
			 ******************/
			
			/// Default capacity
			static constexpr size_t DEFAULT_CAPACITY = 64;
			
			/// Minimum capacity
			static constexpr size_t MINIMUM_CAPACITY = 8;
			
			/*****************************
			 * Constructors / Destructors
			 ****************************/
			
			/// Normal constructor
			MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY)
			: size_(0), capacity_(capacity)
			{
				if (capacity < MINIMUM_CAPACITY) { 
					capacity_ = MINIMUM_CAPACITY;
				}
				elements_ = new T[capacity_];
			}
			// Size has to be set to 0 since we have no items in it
			// Capacity instantiates to itself without _ because it is bound to change, and we're given the default cap
			// Elements instantiates to new T[capacity] because elements will change based off the capacity
			
			/// Copy constructor
			MyVector(const MyVector& other) :
			size_(other.size()), capacity_(other.capacity()), elements_(new T[other.capacity_])
			{
				size_t i = 0;
				while (i < size_) { 
				elements_[i] = other[i];
				i++;
				}
			}
			// Size and capacity will for the most part not change, and will copy over
			// Elements will not change from the normal CTOR because you shouldn't copy the elements over 
			// The while loop holds true, as the copy constructor copies over to the other capac
			
			/**
			 * Destructor
			 * Cleanup here.
			 */
			 
			 //I FOUND MY NEW 13TH REASON
			 //STG I'M GONNA CRASH OUT HARDER THAN MY OWN PROGRAM
			 //I AM SO F***KING CLOSE DAMMIT
			~MyVector()
			{
				if (elements_ != nullptr) {
					delete[] elements_;
					elements_ = nullptr;
					}
				
			}
			//Deletes the data inside the elements ptr then sets element to nullptr
			
			/************
			 * Operators
			 ************/
			
			///	Assignment operator
			MyVector& operator=(const MyVector& rhs)
			{
				if (this != &rhs){
					duplicate(rhs);
				}
				return *this;
				
				
			}
			
			/// Operator overload to at()
			T& operator[](size_t index) const
			{
				indexValidity(index);
				return elements_[index];
			}
			
			
			/************
			 * Accessors
			 ************/
			
			/// Return the number of valid elements in our data
			size_t size() const
			{
				return size_;
			}
			
			/// Return the capacity of our internal array
			size_t capacity() const
			{
				return capacity_;
			}
			
			/**
			 * Check whether our vector is empty
			 * Return true if we have zero elements in our array (regardless of capacity)
			 * Otherwise, return false
			 */
			bool empty() const
			{
				if (size_ == 0) {
					return true;
				} else {
					return false;
				}
			}
			/// Return a reference to the element at an index
			T& at(size_t index) const
			{
				indexValidity(index);
				return elements_[index];
				
			}
			
			/***********
			 * Mutators
			 ***********/
			
			/**
			 * Reserve capacity in advance, if our capacity isn't currently large enough.
			 * Useful if we know we're about to add a large number of elements,
			 *   and we'd like to avoid the overhead of many internal changes to capacity.
			 */
			void reserve(size_t capacity)
			{
				if (capacity > capacity_)
					changeCapacity(capacity);
				
			}
			
			/**
			 * Set an element at an index.
			 * Throws range error if outside the size boundary.
			 * Returns a reference to the newly set element (not the original)
			 */
			T& set(size_t index, const T& element)
			{
				indexValidity(index);
				
				
				elements_[index].~T();
				elements_[index] = element;
				return elements_[index];
				
				
			}
			
			/**
			 * Add an element onto the end of our vector.
			 * Returns a reference to the newly inserted element.
			 */
			T& push_back(const T& element)
			{
				if (size_ == capacity_) {
					changeCapacity(capacity_* 2);
				}
				
				elements_[size_] = element;
				size_++;
				return elements_[size_ - 1];
				
				
			}
			
			/**
			 * Remove the last element in our vector.
			 * Should throw std::range_error if the vector is already empty.
			 * Returns a copy of the element removed.
			 */
			T pop_back()
			{
				T deleted_element;
				
				if (size_ == 0) {
					throw std::range_error("Vector is already empty!");
				}
				
				deleted_element = elements_[size_ - 1];
				elements_[size_].~T();
				
				size_--;
				reduceCap();
				
				return deleted_element;
				
				
			}
			
			/**
			 * Insert an element at some index in our vector
			 * 
			 * Example:
			 * 	 Insert a 9 at index 2
			 *   Contents before: [6, 2, 7, 4, 3]
			 *   Contents after:  [6, 2, 9, 7, 4, 3]
			 * 
			 * Returns a reference to the newly added element (not the original).
			 */
			T& insert(size_t index, const T& element)
			{
				if (index > size_)
					throw std::range_error("Index cannot be greater than size");
				if (size_ == capacity_) {
					changeCapacity(capacity_* 2);
				}
					size_t i = size_;
						while (i > index) {
						
						elements_[i] = elements_[i - 1];
						
						--i;	
						}
						
				elements_[index].~T();
				size_++;
				elements_[index] = element;				
				
				return elements_[index];
			}
			
			/**
			 * Erase one element in our vector at the specified index
			 * 
			 * Throws std::range_error if the index is out of bounds.
			 * 
			 * Example:
			 *   Erase index 2
			 *   Contents before: [8, 4, 3, 9, 1]
			 *   Contents after:  [8, 4, 9, 1]
			 * 
			 * Returns a copy of the erased element.
			 * Hint: call DTOR on original after making the copy.
			 */
			 
			 //If this doesn't solve my unit test, I'm jumping off McCarthy Hall
			 //This is aboutta be my 13th reason why
			 //It's joever, note to self, make sure to get some sleep before doing this
			 //HOW DO I NOT FIX THE IF STATEMENT IN THE WHILE LOOP FOR REDUCECAP UGHHHHHH
			
			T erase(size_t index)
			{
				if (index >= size_ || index < 0) {
				throw std::range_error("Range is out of bounds.");
				}
				
				T deletedElement = elements_[index];
				elements_[index].~T();
				
				for (size_t i = index; i < size_ - 1; i++) {
					elements_[i] = elements_[i + 1];	
				}
				
				
				size_--;
				reduceCap();
				
				
				
				
				return deletedElement;
			}
			
			/**
			 * Removes all elements (i.e., size=0 and DTORs called)
			 * 
			 * Should also reset capacity, if needed
			*/
			
			//I THOUGHT ERASE WAS MY 13TH REASON WHY, NAH IT'S THIS CLEAR FUNCTION
			//IF I DON'T PASS THIS DAMN TEST CASE, I AM GOING TO CRY, AND JUMP OFF MH
			//I HAVE TRIED this->~MyVECTOR(); AND SAME RESULT
			//I WAS EVEN MOVING AROUND THE CODE HOWWWWWW???????
			void clear() 
			{
												
				size_t i = 0;
				while (i < size_) {
				elements_[i].~T();
				i++;
				}
				
				size_ = 0;
				
				if (capacity_ != DEFAULT_CAPACITY){
				changeCapacity(DEFAULT_CAPACITY);
				}
				
				//elements_ = new T[capacity_];
			}
		
		
		//ALL THAT CRYING! ALL THAT WHINING! I DID IT!!!! YAYYYY!!!
		
		
		/**
		 * Begin private members and methods.
		 * You may add your own private helpers here, if you wish.
		*/
		private:
			
			/// Number of valid elements currently in our vector
			size_t size_ = 0;
			
			/// Capacity of our vector; The actual size of our internal array
			size_t capacity_ = 0;
			
			/**
			 * Our internal array of elements of type T.
			 * Starts off as a null pointer.
			 */
			T* elements_ = nullptr;
			
			/**
			 * Helper function that is called whenever we need to change the capacity of our vector.
			 * Should throw std::range_error when asked to change to a capacity that cannot hold our existing elements.
			 */
			void changeCapacity(size_t c)
			{
				if (c < size_) {
				throw std::range_error("ERRR! Capacity can't be less than size Silly wabbit!");
				}
			//Change capacity has to check if our new size is less than our old size, and for that, we have to throw
			//a range error when unable to change the size
				
				
				T* newMem = new T[c];
				for (size_t i = 0; i < size_; i++) {
					newMem[i] = elements_[i];
				}
				delete[] elements_;
				elements_ = newMem;
				capacity_ = c; //From TheCherno, a youtuber who helps with C++, specifically his vector
				//From what I see, we have to initialize a new pointer to c (new capacity)
				//Then create a for loop to copy the elements over (technically move over the elements)
			}
			
			
			void indexValidity (size_t index) const { //This checks the validity of the index
				if (index >= size_) {
					throw std::range_error("Index is out of range");
			
				}
			}
			
			
			void duplicate (const MyVector &other){ //This duplicates the vector when needed to
				if (elements_ != nullptr) {
					delete[] elements_;
					
					size_ = other.size();
					capacity_ = other.capacity();
					elements_ = new T[other.capacity_];
					
					for (size_t i = 0; i < size_; i++) {
					elements_[i] = other[i];
					}
				
				}
			
			
			}
			
			void reduceCap () { //This reduces the capacity down using the rule with a while loop
				while (size_ < (capacity_ / 3) ) {
					changeCapacity(capacity_ / 2);
						}
				if (capacity_ < MINIMUM_CAPACITY){
					capacity_ = MINIMUM_CAPACITY;
					}
				} //This if statement reduces the capacity down to the Minimum
			
			
	};

}

