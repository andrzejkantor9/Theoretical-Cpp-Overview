// "\" in comments serves to extend commenting into next line as well
#include "stdafx.h"
#include <iostream>		//i/o
#include <string>
#include <vector>
#include <memory>		
#include <mutex>
#include <stdexcept>		//standard exceptions
#include <typeinfo>			//bad_cast
#include <conio.h>			//_getch();
#include "theheader.h"

using std::endl;		// std - contains standard library declarations
#define ROUND

//macros
#if __STDCPP_THREADS__ == 1
#define NUMBER 20
#define SOUP std::cout<< "soup" << endl;

#define SPOON std::cout<< "spoon" << endl;\
	for(int i=0; i<5; ++i){ \
	std::cout << i << " ";} \
	std::cout << "spoon" << endl;
#define ADD(n1, n2) 	int nequal = n1 + n2;\
 	std::cout << "Equation result is: " << nequal << endl;
#define MAXIMUM(a, b) (a > b ? a : b)

#ifndef SOUP
	#define SOUP std::cout<< "soup" << endl;
#elif NUMBER > 100
	#define LAMB std::cout << "lamb" << endl;
#else
	#define PORK std::cout << "pork" << endl;
#endif
#define CASE break; case

int macroFunctionAddition(int a
#ifdef SOUP
	, int b) 
{
	return a + b;
#endif
	return a;
}
#endif

//inline
namespace Iline
{
	namespace old_version
	{
		std::string function() { return std::string("This is old version"); }
	}

	inline namespace new_version
	{
		std::string function() { return std::string("This is new version."); }
	}
}

//macros "if __STDCPP_THREADS__ == 1", are here only for my convinience, so i could hide lines during more intense work in this project
//pointers and references
#if __STDCPP_THREADS__ == 1
void writeIntArray(int na1[], int length)
{
	for (int i = 0; i != length; ++i)
	{
		std::cout << na1[i] << ", ";
	}
	std::cout << endl;
}

void writeExtendedIntArray(int *na1, int rows, int cols)	//quite complicated construct - pointer transfer
{
	for (int i = 0; i != rows; ++i)
	{
		for (int j = 0; j != cols; ++j)
		{
			std::cout << na1[i*cols + j] << ", ";		//counting absolute place in memory of array - relative to beginning
		}
		std::cout << endl;
	}
	std::cout << endl;
}

void changeIntReference(int &n1)		// both functions change argument implicitly, it's better not to do that, and if you do - you need to make it very clear
{
	n1 = 25;
}

void changeIntPointer(int *n1)
{
	*n1 = 25;
}

void optimizedSwap(int &n1, int &n2)
{
	int tmp { static_cast<int&&>(n1) };			//using rvalue references - so you don't have to copy objects needlesly
	n1 = static_cast<int&&>(n2);
	n2 = std::move(tmp);						//move is shorter form of static_cast<int&&>(tmp)
}	
#endif

//printf
#if __STDCPP_THREADS__ == 1
#include <stdio.h>
#include <windows.h>		//SetConsoleCP
extern int var;			//informs program, that there exists variable var in other file and that you can use it in entire project range if it's defined
#include <cstdint>	
#include <limits>		//tools concerning data size in the very memory implementation
#include <cstdint>		//int declarations and their exact length
#endif

// enumerations, basic concepts of memory management
#if __STDCPP_THREADS__ == 1
class Vector {
public:
	//class INVARIANT - elem points array of sz times numbers of type double; this invariant is beeing executed in constructor
	//the very purpose of invariants is to cleary state what given code does
	//Vector(int s) :elem{new double[s] }, sz{s} {}
	Vector(int s)
	{
		if (s < 0) throw std::length_error{0};		
		elem = new double[s];
		sz = s;
	}
	//constructor is ALWAYS used when class is created
	int size() { return sz; }
	double &operator[](int i);		// interface (skeletal class)

	//RAII - Resource Aquisition is Initialization
	~Vector() { delete[] elem; }							// memory is released after last line of code in block object is in

private:
	double *elem;
	int sz;
};

double &Vector::operator[](int i)		//defining operation outside of class body
{
	if (i < 0 || size() <= i) throw std::out_of_range("Vector::operator[]");			//operator overload, throwing out_of_range exception
	return elem[i];
}

/*								
class Locked_file_handle {						//code that is supposed to guarantee to call the destructor if all variables will not be initialized in the constructor
private:
	File_ptr p;
	unique_lock<mutex> lck;
public:
	X(const char* file, mutex &m)
		: p{ file, "rw" },
		lck{ m }
	{}
};
*/

enum class Color : char { red = 'a' , green = 'e', blue = 'h' };		//enum reprezentuje wartości całkowito-liczbowe, nazwy są symboliczne, : - zmiana z domyślnego int na char (1 bajt, zamiast 4)
//red, green i blue are called enumerators, when enumerators are declared without defition - you need to name it's type
Color& operator++(Color &c)					//defining operator ++color for this enumeration
{
	switch (c) {
	case Color::red: return c = Color::green;
	case Color::green: return c = Color::blue;
	case Color::blue: return c = Color::red;
	}
}
enum class Life {bad = 1, medicore = 2, excellent = 4};
constexpr Life operator|(Life a, Life b)
{
	return static_cast<Life>(static_cast<int>(a) | static_cast<int>(b));
}
constexpr Life operator&(Life a, Life b)
{
	return static_cast<Life>(static_cast<int>(a) & static_cast<int>(b));
}
enum class Printer_flags {
	acknowledge = 1, 
	paper_empty = 2, 
	busy = 4, 
	out_of_black = 8,
	out_of_color = 16
};
constexpr Printer_flags operator|(Printer_flags a, Printer_flags b)		//defined as constexpr because for "switch" you need to know value at compilation time
{
	return static_cast<Printer_flags>(static_cast<int>(a) | static_cast<int>(b));
}
constexpr Printer_flags operator&(Printer_flags a, Printer_flags b)
{
	return static_cast<Printer_flags>(static_cast<int>(a)&static_cast<int>(b));
}

//enumeration interval exists in range <0;2^k-1> ( for negative <-2^k;2^k-1> ), where k is power in which entire number of enumerators fits
enum light { soft, ambient, rough };		//enumerations of type 98
enum skills { hard, sideways, /*soft*/};			//you cannot use soft 2 times - there will be names conflict

enum {easy, impossible};	//annonymous enumeration - set of constant integers wihtout a name
#endif

#if __STDCPP_THREADS__ == 1
//OOP
//this is a concrete class - just  a class with all functions defined, oposite is abstract class - with at least one undefined function\
concrete types are not polymorphic, concrete types are not derivative nor base classes
//good practice is to place functions, which do not require class data outside of class body so interface is more transparent\
you can place them in the same header file for one class or in namespace with multiple classes\
constructors construct from base -> components -> derivatives\
you should name invariants for constructors before writing them - condition, which has to be met, when any class function is called\
for example write next to constructor in comments "ELEM indicates SZ numbers of type DOUBLE"\
destructor can be only one for class and usually is called implicitly, it is important co release all resources initialized with keyword "new"\
"new" operator when it cannot occupy resources with reason beeing lack of memory returns std::bad_alloc exception\
you can initiate classes like: OOPClass oopc1; - usually it sets to zero all elements, but sometimes (when we deal with component class they can become undefines\
that's why it's better to initialize object with OOPClass oopc1{};, example without brackets does not work when any constructors are defined\
initialization with using () is equal to using constructor with given argument list, while {} is equal to using elements list, usually it's better to use {}, with exeption when you need to make clear that you are using version with constructor\

class OOPClass {				//class can be declared first, then used and after that defined if you wish so
public:
	//explicit - forbids implicits conversions - for example "=" operator when explicit keyword is used
	explicit OOPClass(int n1, int n2) : x{ n1 }, n1{ n2 } { }		//:<something> - initializer list
	explicit OOPClass() : x{ 1 }, n1{ 2 } {  }						//constructor overload
	explicit OOPClass(float f1 = 987., float f2 = 234.) : x{ static_cast<int>(f1) }, n1{ static_cast<int>(f2) } {}		//you can use static_cast in non-implicit initialization
	explicit OOPClass(char c1, char c2, char c3);
	explicit OOPClass(double d1) : x{ 1 }, n1{ 2 } { change_float(static_cast<double>(d1)); }
					//if you won't pass all values, then missing ones will be replace by given attributions
											
	friend class FriendClass;		// declaration of friend class, private / public / protected modifiers have no effect on friend classes, now funtions with friend class have accessto every element of given class
	friend void friend_function();	// you can declare any functions and friend function as well
									//when you don't need to use friend classes, don't do it
									//friend class must be defined in surrounding namespace or in the same header, with exception beeing when function has input arguments\
										that way the language finds it by argument types
		
	void writeFields() const		//const guarantees that no data will be changed in that function, it's called physical constancy
		//if you want to change some part of object, while not beeing seen from outside - you can use another function inside, this time without const at the end - it's called logical constancy\
		you can use mutable variables or const_cast, but it's better to divide into two classes and there change variables as normal ones
	{
		int n1{ 0 };
		std::cout << "x: " << x << ", n1: " << this->n1 << "\n";			//this is a pointer, it gives access "outside" of block of code in this case
	}
	void saveValues(int, int);			// you do not need to declare variables names in function declaration
	static void showUniversalNumber();	//static function cannot refer to non-static class elements, they are used when none of non-static are used
											//they cannot use "this" pointer, in c++ there is nothing like static constructor
											
	OOPClass add(int n1) { x += n1; return *this; }
	OOPClass dec_x() { --x; return *this; }

	class NestedClass {				//nested class, you can refer to it by OOPClass::NestedClass, parent class has no privileges over her, it does not see nested class elements
	public:
		NestedClass() : n1{ 0 } {}

		static void operator delete(void* ptr, std::size_t sz)		//delete operator overload - it is always static, but you don't need to use this keyword
		{															//for global operator overload, you only need to give void *ptr 
			std::cout << "custom delete for size " << sz << '\n';
			::operator delete(ptr);
		}
	private:
		int n1;
	};

private:				//private is default field type, but typing in increases clearance
	int x, n1;
	static int ns1;					//static variable, there is only one for all class instances, in multi-threaded applications static variables can create issues when\
									many threads try to change them, static variables can be used to count how many object of given class have been created
	static const int ns2 = 2;		//statc const can be defined inside class, unlike normal static variable
	std::string s1 = "Ala has a cat.";		//inside-class constructor - initialization without using constructor
	mutable float f1;		//mutable allows to change variable inside constant function
	void change_float(float f1) { f2 =f1; }
	float f2{ 0.999f };

	enum class Color : char {red, green, blue};
	//using value_type = T;
};
OOPClass operator+(OOPClass o1, int n1) { return o1.add(n1); }	//add and decrement operators overloads - they returns objects, not numbers
OOPClass &operator--(OOPClass &o1) { return o1.dec_x();  }		
OOPClass::OOPClass(char c1, char c2, char c3) {		//repeating explicit keyword here would be a compilation error
	x = c2;
	x = c3;
	x =  static_cast<int>(c1) ;
	n1= 30 ;
}
void OOPClass::showUniversalNumber()		//you shouldn't repeat keyword static here
{
	ns1 = 777;
	std::cout << "static ns1: " << ns1 << "\n";
}
//void OOPClass::writeFields() const		//you need to use const keyword here as well
void OOPClass::saveValues(int n1, int n2)			//function definition outside class body
{
	x = n1;
	this->n1 = n2;			//this returns pointer to object used at this very moment, it can be used on its own to pass object itself
}
int OOPClass::ns1;		//there is a compilation error if i did not declare static variable outside of class

class ConcreteClass {			//it is used to represent types: small, performance critical and often used

};

class {};

//polymorphism - interfaces derivation (strictly in C++ - it's a class that has at least one virtual function)
//real time polymorphism  - interface derivation
//private - one class and friend classes, protected - only given classes / friend classes / derivative classes and derivatives friends, if you can declare something a private - do it\
public - visible everywhere, public derivation - it can be cast to base class, all public and protected data become private\
classes can derivate from structures and probably it can happen the vice versa\
encapsulation - rule telling that you should not allow free access to data when it's not necessary and recommends to use interfaces
class Human {			//actually - not very usefull class
public:
	void great() const { std::cout << "I am great and awesome and stuff.\n"; }
};
class Employee {
public:
	enum Empl_type { man, emp } ;
	Empl_type type;

	Employee() {}
	virtual void print() const;				//virtual function (method) - can be used as an interface in derivative classes and have other implementation, they have to have the same inputs\
											and usually the same output\
											array of virtual functions - array of pointers to virtual functions - index to pointer is changed from functions name
	virtual int give_number() { return 66; }

	void f(int) {}
	virtual Employee *write() = 0;
	void see_if_private_function_was_defined() { show_text(); }

	std::string full_name() const { return first_name + ' ' + middle_initial + ' ' + family_name; }
protected:
	float f1{ 0.987f };
private:
	std::string first_name, family_name;
	char middle_initial;
	void show_text() const;
};
class Manager : public Employee, public Human{		//in goal of having common features of worker and manager, you can only derive from defined classes\
													most commonly used is public derivation, though default type is private\
													private derivation - derivating class takes derivates only public and private elements,	you can, but don't have to define them in derivative classes\
													protected - public and protected elements - only for derivative and friend classes
public:
	Manager() {	type = man; }
	void print() const;																
	int give_number() override final{		//override is not required, but it is a good programming practice - it informs that is is a virtual function override and compiler will detect if it is otherwise
		return 20;							//however override cannot be used outside of function body, override is almost always a last keyword after functions (more "finite" is final keyword
	}										//final - forbids further overrides, it also improves performance (it is connected to array of virtual functions), but to use it in such way would be\
											bad programming habbit and would dramatically decrease code readability, also - it cannot be used outside of class body
											
											

	using Employee::f;					//it moves all funtions f() from Employee class to namepsace of Manager - thanks to that, when Manager::f(int) is called f(double) won't be used\
										with implicit conversion, if it's not in range available with derivation - moved names are not available			
	using Employee::Employee;			//constructor derivation - it's better to use only in simple classes
	void f(double) {}
	Manager *write() override { return nullptr; }			//you can change return type of virtual method to a pointer / reference of derived class
private:
	int level;
};
class Director final : public Manager {};		//class hierarchy - at least 3 classes in relations of derivation
												//final po nazwie klasy - wszystkie funkcje wewnątrz niej są finalne i klasa ta nie może mieć klas pochodnych
class Maid : private Employee {
public:
	using Employee::f1;							//with usage of "using" keyword you can publicly share outside otherwise private-only data 
	using Employee::type;						

	Maid *write() override { return nullptr;  }
};
void Employee::print() const		// you do not need to repeat "virtual" word
{
	std::cout << family_name << '\n';
}
void Employee::show_text() const { std::cout << "This is a private function defined outside of the class. \n"; }
void Manager::print() const
{
	Employee::print();					// you can override it in derivate class using Employee::print() notation
	std::cout << "\poziom " << level << '\n';
}

class Shape {							//abstract class- with at least one purely virtual class, you cannot create objects of this class, in derivate classes you can only create\
										objects after denining ALL functions\
										interface derivation - programming style based on abstract classes
public:
	virtual void rotate(int) = 0;			//=0 - indicates that function MUST overridden in other class than this one
	virtual void draw() const = 0;
	virtual bool is_closed() const = 0;

	virtual ~Shape() {}						//virtual destructor - it is necessary in polymorphic classes 
};

class Std_interfate {
public:
	virtual void suspend() = 0;
	static void schelude() {}

	virtual ~Std_interfate() {}
};
class Text : public Std_interfate {
public:
	void start() {}
	void suspend() { }

	virtual void print() {}
};
class CPointer {
public:
	const char *val;

	void print(int x) const { std::cout << val << x << '\n'; }
	CPointer(const char *v) { val = v; }
};

class CastClass0 {
public:
	virtual void f() {}

	virtual ~CastClass0() {}
};
class CastClass0Derived : public CastClass0 {
	CastClass0Derived(CastClass0 *cc0) { dynamic_cast<CastClass0Derived*>(cc0); }		//downcast
};
class CastClass1 {
public:
	virtual void write_value() const{ std::cout << "Value of 2+2 is: 4. \n"; }

	int x;

	virtual ~CastClass1() {}
};
class CastClass2 : public CastClass1{
public:
	virtual ~CastClass2() {}
};

class AnonymousClass{
public:
	class {								//anonymous class as a nested class, it serves only as a way to collect data in bigger set
	public:
		int ac1, ac2;
	}; 
} anonymous_c;							//anonymous_c is class instance - it's a reason why after every class declaration there is a semicolon

void friend_function()
{
	OOPClass em1{ 0.343 };
	std::cout << "This function friend variable is equal to: " << em1.f2 << '\n';
}
class FriendClass {						//przyjaciel klasy ma dostęp do składowych klasy i jej pochodnych
public:
	FriendClass() {}

	void show_friend_value() const { std::cout << " Friend value is equal to: " << oopc1.f2 << '\n'; }

private:
	OOPClass oopc1{0.345 };
};
//SOLID - rules of writing object oriented applications\
	S - Single responsibility class should have single responsibility\
	O - open / closed elements of class should be open to extensions and closed to modifications\
	L - liskov distribution objects you should be able to substitute object by instances of their subobjects, without affecting correctness of application(?)\
	I - inteface segregation many specialized interfaces instead of one general\
	D - dependency inversion class shoudl be dependant of abstraction, not of corrections (writing class "inside" outside of class body)
#endif

//struktury, unie
#if __STDCPP_THREADS__ == 1
struct AnotherStruct;					//structure declaration - so you can use it before its definition, however you cannot use its elements or data about its size
struct SimpleStruct {										
	SimpleStruct() : n1{ 10 } {}		//you can still use constructors in structures
	void writeVariables();

	AnotherStruct *as1;
	int n2;
private:								//you can still use private modifier in structures
	int n1;
};
void SimpleStruct::writeVariables()
{
	std::cout << "n1: " << n1 << ", n2: " << n2 << "\n";
}

struct AnotherStruct {
	AnotherStruct(int n1, char *c1) : n1{ n1 }, c1{ c1 } {}
	void write_variables();

	int n1;
	char *c1;
};
void AnotherStruct::write_variables()
{
	std::cout << "n1: " << n1 << ", c1: " << c1 << "\n";
}

struct SizeStruct1 {		//its size is 12B - arrangement in memory: 1B, 4B, 1B (3x4B)
	char c1;
	int n1;
	char c2;
};
struct SizeStruct2 {		//its size is 8B - arrangement in memory 4B and 1B + 1B (2x4B), it's called memory alignment (236 page)
	int n1;					//if you want to optimalize container size, usually you should declare first: biggest data and last smallest data
	char c1;
	char c2;
};

struct struc1 { int a; };		//this two structures are not equal and cannot be implicitly converted
struct struc2 { int a; };

void simpleStructInit(SimpleStruct &s1, int n1)
{
	s1.n2 = n1;
}

struct BitStructCopy {				//you cannot initialize bit fields, and they are available to use only in structures, objects and unions
	// three-bit unsigned field,
	// allowed values are 0...7
	unsigned int b : 3;
};
struct BitStruct {
		bool b1 : 1;			//": 1" - so called "bit field" - declaration of how many BITS in memory given variable can use
		int n2 : 3;						// bit fields use less memory space, but access to them is slower - it may be tricky to optimalize with them
		int : 3;						//anonymous fields - it serves not as variable, but as proper bit alignment in memory
};

#include <type_traits>			//is_pod
template<typename T>			//POD example
void mycope(T *to, const T *from, int count)
{
	if (is_pod<T>::value)
		memcpy(to, from, count * sizeof(T));
	else
		for (int i = 0; i != count; ++i)
			to[i] = from[i];
}

//Union - structure in which only one variable is stored at one moment, it has the size of biggest variable in itself\
	it is used if you need information only about one variable at a time, but it does not have any tools to track which variable is stored
union Fudge {
	int n1, n2;
	int *p;
	char c1{ 'c' };		//inisde union you can only define one variable
};
#endif

//multi-dimmensional arrays, reccursion
int rek(int n1) 
{
	std::cout << n1;
	if (n1 < 10) 
	{
		return rek(n1 + 2);
	}
	return n1;
}

//stack, heap
//on stack you allocate data which size is know at compilation time

//basics - theory
#ifdef ROUND
constexpr double square(const double x) { return x*x; }			//if you want function to be constexpr it needs to have only return instruction, if you want output to be constant, input must be constant as well\
																you can use constexpr as well to optimize code
namespace Space {
	int main();
}	//no semicolon - you cannot instantiate here
int Space::main()
{
	std::cout << "And there are some namespaces at its best! \n";
	return 0;
}
#endif

int main()
{
	//macros
	{
		std::cout << "Macros: \n" << endl;

		SOUP
			SPOON
			ADD(1, 2);
		std::cout << macroFunctionAddition(2, 3) << endl;		//they work the same way
#undef SOUP
		std::cout << "Bigger number is: " << MAXIMUM(1, 100) << endl;
		//LAMB
		std::cout << macroFunctionAddition(2, 3) << endl;		//they work the same way
		PORK

			switch (2)
			{
			case 1: std::cout << "1" << endl;
				CASE 2: std::cout << "2" << endl;
				CASE 3: std::cout << "3" << endl;
				CASE 4: std::cout << "4" << endl;
			}

		std::cout << "C++ version: " << __cplusplus << endl;
		std::cout << "Date: " << __DATE__ << endl;
		std::cout << "Exact time: " << __TIME__ << endl;
		std::cout << "Current source file: " << __FILE__ << endl;
		std::cout << "Current row number: " << __LINE__ << endl;
		std::cout << "Is the implemetation hosted: " << __STDC_HOSTED__ << endl;
		std::cout << "Can the program have more than one thread: " << __STDCPP_THREADS__ << endl;

		std::cout << "------------------------------------------------------" << endl;
	}

	//inline
	{
		std::cout << "Inline namespace:\n" << endl;

		std::string s1 = Iline::function();
		std::cout << s1 << endl;

		using namespace Iline;

		s1 = function();
		std::cout << s1 << endl;
		s1 = old_version::function();
		std::cout << s1 << endl;

		std::cout << "------------------------------------------------------" << endl;
	}

	//pointers and references
	{
		std::cout << "Pointers:\n" << endl;

		int n1 = 10;
		int *np1;
		int &n3 = n1;		//reference cannot be initialized with a number
		np1 = &n1;
		std::cout << "n1 variable value: " << n1 << ", n1 variable adress: " << &n1 << endl;
		std::cout << "np pointer adress: " << np1 << ", np pointer value: " << *np1 << endl;
		std::cout << "n3: " << n3 << ", &n3: " << &n3 << endl;		//n3 - value, &n3 - address

		char **cpp; //pointer to pointer of char
		int *ap[15]; //array of 15 pointer of int
		int(*fp)(char *); //it takes char*, returns int, it is a pointer to functions
		int *f(char *); //it takes char*, returns int*, it is a standard function

		void *vp;	//pointer to void, it is used when you don't know type of passed data
		vp = np1;
		int *np2 = static_cast<int*>(vp);
		std::cout << "int writen as void: " << vp << ", void cast to int adress: " << np2 << ", void cast to int value: " << *np2 << endl;

		int *np3 = nullptr;		//nullptr - empty pointer, it can be assigned to any pointer, but not to normal variable
		double *dp1 = nullptr;
		std::cout << "int null pointer: " << np3 << ", double null pointer: " << dp1 << endl;

		//int na1[n1];		//it won't work, array size has to be constant
		const int n2 = 10; int na1[n2];
		std::vector<int> v1(n1);	//vector with variable number of elements
		int na2[] = { 0, 1, 2, 3 };	// automatic array size calculation
		int na3[5] = { 0 };			//array is automaticly filled with zeroes
		int length = sizeof(na2) / sizeof(*na2);	//C style array size calculation, you cannot calculate size of array inside function
		writeIntArray(na2, length);
		length = sizeof(na3) / sizeof(*na3);
		writeIntArray(na3, length);

		std::cout << "Playing a sound \\ \"right now! \a" << endl;;		//\a - system alert, \ - before \ i " serves to display
		std::cout << u8"\u00E6" << endl;	// text representation in utf-8 - but it does not work here

		int na4[] = { 0, 1, 2, 3 };
		int *np4 = na4;			// reference to first array address (implicit conversion)
		int *np5 = &na4[0];		// reference to first array address (public conversion)
		int *np6 = na4 + 4;		//pointer to place in memory after the last element
		std::cout << "na4: " << &na4 << ", np4: " << np4 << ", np5: " << np5 << ", np6: " << np6 << endl;
		std::cout << "na4[2]: " << na4[2] << ", 2[na4]: " << 2[na4] << endl;		//na4[2] = 2[na4]

		int na5[3][5] = { {0, 0} };		//auto-initialization with zeroes
		for (int i = 0; i != sizeof(na5) / sizeof(*na5); ++i)
		{
			for (int j = 0; j != sizeof(*na5) / sizeof(int); ++j)
				na5[i][j] = 10 * i*j;
		}
		writeExtendedIntArray(&na5[0][0], sizeof(na5) / sizeof(*na5), sizeof(*na5) / sizeof(int));		//lines, rows

		//constexpr - it's used to calculate constant value at compilation time
		const int n5{ 20 };		// constant int
		const int *n6{ &n5 };	// pointer to constant int
		int *n7{ na4 };
		int *const n8{ n7 };	// constant pointer to non-constant int
		const int *const n9{ n7 };		//constant pointer to constant

		//if any pointer occupies memory using new operator it is a good practice to collect it in unique_ptr collection, to make it clear - that's because you cannot verify if pointer used new operator
		//pointers are used to pass objects while beeing light on resources (address instead of entire object=, zou need to use -> instead of .\
		you need to pay attention so a pointer show right object and isn't empty
		//references are similiar construct - they also are light on resource, but syntax is like objects not pointers (. instead of ->) and there is no "null" reference
		int n10 = 20;
		int &nr1{ n10 };		//reference usage - it refers to n10 address, but has easier syntax, reference HAS TO be initialized
		int n11 = nr1;
		nr1 = 9;
		int *np7 = &nr1;		//to assign address you need to use reference
		++nr1;					//incrementation of n10 VALUE, after initialization you cannot change reference address
		std::cout << "Pointer to reference: " << *np7 << ", reference: " << nr1 << '\n';

		//lvalue - object that exists after given line beeing executed, rvalue - object that exists only while given line is executed
		const int &n12{ 11 };		// usually reference has to refer to lvalue, constant one can refer to rvalue - purpose beeing to not to be able to modify it
		int* n13 = &n10, n14 = n10;		//int* - * works only for first variable, that's why i prefer int *n instead of int* n
		changeIntReference(n10);			//both constructs work the same way, but references have easier syntax
		std::cout << "n10: " << n10 << '\n';
		changeIntPointer(&n10);
		std::cout << "n10: " << n10 << '\n';

		//rvalue reference - it refers to temporary object, that can by modyfied by reference user and that will never again be used - it helps with optimalization
		int &&n15{ 20 };			//rvalue reference is used ONLY for rvalue values, const int &&n14 {10} won't work - because && reference is used only for temporary objects
		int n16 = 90;			
		optimizedSwap(n10, n16);		//swap in "modern style" with rvalue references usage
		std::cout << "After swapping with optimizedSwap n10: " << n10 << ", n16: " << n16 << '\n';
		using rr_i = int&&;			// creating various templates of data types - something similiar to macros
		using lr_i = int&;
		using rr_rr_i = rr_i&&;		// = int &&
		using lr_rr_i = rr_i&;		// = int &, everything with at least one lvalue reference is lvalue reference, int& &&n1 - i; is a syntax error
		using rr_lr_i = lr_i&&;		
		using lr_lr_i = lr_i&;

		//pointers are better: to change object value, when there is no value at given address (nullptr)
		// references are better: for constant assignments, with overloaded operators

		std::cout << "------------------------------------------------------" << endl;
	}

	//printf, ASCII, data types
	{
			std::cout << "Printf (variable types):\n" << endl;

			int n1 = 9;
			printf("Specifiers: int(d): %hd, float(f): %f, shorter float(g): %g, char(c): %c, string(s): %s, octal(o): %o, unsingned hex int(x): %x, pointer: %p\n", // h oznacza short (int)
				10, .10, .10, 'c', "marta", 01232, 0x2EF, &n1);

			SetConsoleCP(437); //819
			SetConsoleOutputCP(437);
			std::cout << "not written ascii character, cause they take too much place." << endl;
			for (int i = 0; i < 256; ++i)
			{
				//std::cout << "ASCII value: " << i << ", character: " << static_cast<char>(i) << endl;		//0-31 special characters, 31 - "non alphabetic characters" 48 - digits, 65 - capital letters, 97 - regular letters
			}																								// 128+ - extended set of characters

			bool b1{ 10 == 9 };			//bool takes 1 BYTE of memory because you cannot address CPU in bites and every data in c++ must be addressable
			//bool b2{ 8 };				//error - brackets are more "modern" type on initialization - it forbids implicit conversion
			bool b2{ static_cast<bool>(8) };
			std::cout << "b1: " << b1 << ", b2: " << b1 << endl;

			char c1{ 67 };		//char - 1 BYTE, singed - with a sign (dependant on char implementation architecture it is equal or not to char), unsigned - without a sign (it matters for char initialization with a number)
								//char16_t, char32_t - 16 and 32 byte set of characters (like utf-32), wchar_t - size dependant on implementation, bigger sets of characters (like unicode)
			wchar_t c2[]{ L"Ala has a cat, and i enjoy my own PC" };		//wchar_t i wstring, you should use wcout instead of cout
			std::wstring s1{ L"Ala has a cat, and i enjoy my own PC" };
			std::wcout << "widechar: " << c2;
			std::wcout << ", widestring: " << s1 << endl;
			std::cout << "\nchar \'c\' + 2: " << static_cast<char>('c' + 2) << endl;
			//singed char c {'kl'}; char *c1 = &c;		//error - you cannot assign pointer to char variations

			long n2 = 890;		//short, normal, long, long long, int - 4 bytes
			volatile static const unsigned long long int n3 = 10;		//header <cstdint>: uint_fast16_t - 1 byte unsigned int, int64 - 8 byte int, volatile - it guarantees
																		//that code WILL NOT be optimize at compile time
			uint_fast16_t n4 = 10;		//10U - 10 unsigned, 10L - 10 long, 10LU - 10 long unsigned

			void *vp;		//void is used only as pointer to unknown type and function that doesn't return anything

			double d1 = 1.2e-3;				//float, double, long double
			float f1 = 10.232f;
			long double ld2 = 9.23l;		// ll - long long
											// short int -2 bytes, long int  i long long int  - 8 bytes, int* - 8 bytes, double - 8 bytes, long double - 16 bytes, sizeof(x) - size of x
											//however size depends on memory implementation
#undef max		//windows.h macro that conflicts with code below
			std::cout << "biggest float: " << std::numeric_limits<float>::max() << endl;
			std::cout << "char with a sign: " << std::numeric_limits<char>::is_signed << endl;

			int16_t n5 = 0xaabb;		//always 2 bytes
			int_least16_t n6;			//at least 2 bytes
			int_fast32_t n7;			//fastest implementation of at least 4 bytes
			std::cout << "int16_t size: " << sizeof(n5) << ", int_least16_t size: " << sizeof(n6) << ", int_fast32_t: " << sizeof(n7) << '\n';

			auto a1 = alignof(int);			//shows how many bytes is alligned by current memory implementation 
			std::cout << "Int allign: " << a1 << '\n';

			std::cout << "------------------------------------------------------" << endl;
		}

	//enumerations, basics of memory management
	{
		std::cout << "Enumerations and basics of memory management:\n" << endl;

		Vector v(6);
		for (int i = 0; i != v.size(); ++i)
		{
			v[i] = (i * 3) ;
			std::cout << "Element v[" << i << "]: " << v[i] << ", ";
		}
		std::cout << "\n";

		Color col = Color::red, col1;
		Life lif = static_cast<Life>(2);		//explicit conversion of int to life
		std::cout << "color: " << static_cast<char>(col);		//conversion to int (for enum class you have to use explicit conversion)
		++col;
		std::cout << ", color after ++col: " << static_cast<std::underlying_type<Color>::type>(col) << "\n";		//universal way to find enum type
		std::cout << "Operator | between medicore and excellent: " << static_cast<int>(Life::medicore | Life::excellent) << "\n";
		std::cout << "Operator & between medicore and excellent: " << static_cast<int>(Life::medicore & Life::excellent) << "\n";
		std::cout << "Operator |& between bad medicore and excellent: " << static_cast<int>(Life::bad | (Life::medicore & Life::excellent)) << "\n";

		light l1 = ambient;
		light l2 = light::soft;
		light l3 = static_cast<light>(7);
		light l4 = static_cast<light>(ambient|rough);
		skills s1 = hard;			//when names happen to be the same you cannot use one without stating namespace of given enumeration
		//normal enumerations make type conflicts easier to occur, they allow implicit conversions
		skills s2 = skills::sideways;
		skills s3 = static_cast<skills>(static_cast<int>(l2));
		std::cout << "cast from light::soft:" << l2 << ", into skills::soft: " << s3 << "\n";		//implicit conversion from light to int
		std::cout << "cast from non-existing 7 into light: " << l3 << ", and a bit flag (|) of ambient (1) and rough (2): " << l4 <<"\n";		//implicit conversion of bit flag \
														when using enumeration classes - it is not allowed
		std::cout << endl;

		std::unique_ptr<int> un{ new int };		//object type, passed to unique_ptr - it guarantees proper resources release that were occupied with "new" operator
		std::shared_ptr<int> sn{ new int };		//pointers shared_ptr are copied, not moved
		//resources need to be released from last occupied to first

		try {
			v[v.size()] = 7;
		}
		catch (std::out_of_range) {
			std::cout << "7 is out of range of Vector[6]. \n";
		}
		try {
			Vector v1(-27);
		}
		catch (std::length_error) {
			std::cout << "-27 is negative value of number of elemets: not allowed. \n";
		}
		catch (std::bad_alloc) {
			std::cout << "failed to allocate memory for \"Vector\" \n";
		}

		static_assert(4 <= sizeof(int), "the type you entered here is too small");		//static assertion, verifies condition at compilation time - throws compilation error if not met
		constexpr double maxSpeed = 299792.458 ;
		constexpr double speed = 8677.967 ;
		static_assert(speed < maxSpeed, "You cannot go so fast.");		//they have to be constant

		std::cout << "------------------------------------------------------" << endl;
	}

	//OOP, casting
	{
		std::cout << "Object Oriented Programing principles and casting:\n" << endl;

		//class - on default its elements are private, structure - on default its elements are public\
		OOP rules:	restricted access to data structure\
					separation between implementation details and application functionality\
					only class function can modify class data (however you can cheat is using addresses manipulation (7.4.1) and type casting (11.5)\
					constructor default for int* - value is equal to nullptr, for other data type it can be 0, 0.0, 0.f, ""
		OOPClass o1{ 3, 5 };
		OOPClass *o2 = new OOPClass(20, 30);
		OOPClass o3{ o1 };		//initialization via copy
		int n1;
		OOPClass o4{ (n1 = "abc" ? 777 : 666), 111 };		//unfortunately it works, but it's very impractical and "bad", assignment inside a condition - "if abc exists, then condition is true"
		OOPClass o5{ 10, 20 };						
		int n2(OOPClass);		//"hidden" constructor of "class" "int"
		//int n3 = n2(OOPClass{10, 20});			//is it allowed?
		//std::cout << n3 << endl;
		--o1;					//operator overload
		o1.writeFields();		//access as an instancce
		o2->writeFields();		//access as a pointer
		o3.writeFields();
		o4.writeFields();
		o5.writeFields();

		OOPClass::NestedClass on1{};
		OOPClass::NestedClass *on2{ new OOPClass::NestedClass() };
		delete on2;						//you need to use delete for every new operator used

		std::cout << endl;
		OOPClass::showUniversalNumber();		//in static function you refer to function in class not in object

		Manager mn1 = {};
		Employee *em1 = &mn1;				//implicit conversion from inherited class to base, it doesn't work other way around
		em1->see_if_private_function_was_defined();
		Maid md1 = {};
		std::cout << "employee protected and private field: " << md1.f1 << ", " << static_cast<int>(md1.type) << '\n';

		//there exists something like pointer to element like "md1->*x" / "md1.*x", they are very technical constructs (page 627),	i don't get it too clearly
		void(*p)() = &Std_interfate::schelude;		//assigment to pointer of type void static variable using pointer to function
		using Pmfi = void (CPointer::*)(int);
		using Pm = const char *CPointer::*;
		char c1{ 'a' }, c2{ 'b' };
		CPointer z1 = { &c1 }; CPointer z2 = { &c2 };
		CPointer *p1 = &z2;
		Pm pm = &CPointer::val;
		z1.*pm = "nv1";
		z2.print(3);
		//void (Text::*pmt)() = &Std_interface::start; - it should work...

		friend_function();
		FriendClass fc1 = {};
		fc1.show_friend_value();

		//(int)f1 - cast in C style, int(f1) - cast in function style - both aren't safe and in now way verifiable neither clear\
		they replace any cast that "fits" other than dynamic_cast\
		staic_cast can cast from *n1 to n1 and from n1 to *n1\
		but it doesn't verify if cast was successful
		const int &n4{ 20 };
		const int n5{ 30 };
		int n6{ 22 };
		//const_cast - allows to change value of constant or volatile variable
		OOPClass o6{ const_cast<int&>(n4), *(const_cast<int*>(&n5)) };		
		OOPClass o7{ n4, n5 };
		o6.writeFields();
		o7.writeFields();
		const_cast<int&>(n4) = 30;
		*(const_cast<int*>(&n5)) = 40;
		//reinterpret_cast can convert from *n1 to *f1, but it does not verify if it was successful
		int *n7 = &n6;
		float *f1;
		f1 = reinterpret_cast<float*>(n7);
		std::cout << "*f1 from int* cast: *n7: " << n7 << ", *f1: " << f1 << "\n";
		//widgets - objects passed between system and applications\
		dynamic_cast - casting between classes, downcast - from base class to inherited one, upcast - from inherited to base, crosscast - from base to sister class\
		verifies if cast was successful, returns nullptr if not, it is used if you cannot verify it by compiler\
		it used less resources than static_Cast (?), but it works only on references and pointers\
		dynamic_cast needs to cast to polymorphic class so it has informations about class hierarchy that polymorphic classes contain (strictly speaing virtual operator)\
		static_Cast cannot cast from polymorphic base class
		CastClass2 CC;
		CastClass1* CC1 = &CC;
		CastClass1 *CC2{new CastClass1()};
		if (auto b1 = dynamic_cast<CastClass2*>(CC1))  //auto - automaticly returns variable type depending on initializer, in this case it is castclass2
		{
			CastClass2 *obj2 = dynamic_cast<CastClass2*>(CC1);
			std::cout << "object from class 1 was cast successfully to class 2. \n";
			obj2->write_value();
		}
		else
			std::cout << "Failed to cast from class 1 to class 2. \n";
		CastClass1 &CC3 = CC;
		try {
			CastClass2 &obj2 = dynamic_cast<CastClass2&>(CC3);
		}
		catch (std::bad_cast &e) {
			std::cout << "Failed to cast from reference of object 1 to reference of object 2.\n";
		}
		try {
			CastClass1 CC4;			
			CastClass2 &CC5 = dynamic_cast<CastClass2&>(CC4);		//exception occurs here becayse CC4 is empty
		}
		catch (std::bad_cast &e) {
			std::cout<< "Failed to cast from reference of object 1 to reference of object 2.\n";
		}
		CC1->x = 20;
		void *vp1 = dynamic_cast<void*>(CC1);		//it is used when you want to know beggining of object address 
		CastClass1 *CC4 = static_cast<CastClass1*>(vp1);		//dynamic_cast can be used when you know types on both side of casting, so to cast void* you need to use static_Cast
		CC4 = dynamic_cast<CastClass1*>(CC4);					//and then you can use dynamic_cast to verify if cast was successful
		std::cout << "dynamic cast to void* and then static and dynamic cast to class*: " << CC4->x << '\n';
		//when you try to cast to class which has the same name with any other (it is possible via multiple inheritance) casting returns 0 (page 665)
		delete CC2; 

		anonymous_c.ac1;
		
		std::cout << "------------------------------------------------------" << endl;
	}

	//structures, unions, rounding
	{}
	{
		std::cout << "Structures, Unions and rounding: \n" << endl;

		SimpleStruct s1{};
		simpleStructInit(s1, 29);
		s1.writeVariables();
		AnotherStruct s2 = { 10, "lambda" };	//you can intialize structure in this implicit way if all elements are public
		AnotherStruct *s3 = new AnotherStruct(96, "It\'s a pointer!");
		s2.write_variables();
		(*s3).write_variables();			//"(*s3)." - the other way of writing "s3->" 
		struc1 s4[3]{ {1}, {2}, {3} };

		std::cout << "3 times struc1: ";
		for (int i = 0; i != 3; ++i)
		{
			std::cout << s4[i].a << ", ";
		}
		std::cout << "\n";

		std::cout << "Size of 2 structs with different variable places s1: " << sizeof(SizeStruct1) << "B, s2: " << sizeof(SizeStruct2) << "B \n";
		//std::memcpy(dest, source, sizeof(dest)); - is optimized to data copying
		//POD concept - plain old data - object in which there is no custom memory manipulation syntax nor data scheme (242 page), "only data" inside\
			it has to have simple default constructor  - that does not do any actions\
			POD is used if you want to have optimized operations of object on memory					

		Fudge fu1;
		fu1.n1 = 30;
		fu1.n2 = 40;
		std::cout << "fu1.n1(30) in union: " << fu1.n1 << ", fu1.n2(40): " << fu1.n2 << ", fu1.p(pointer) when fu1.n2 in union is assigned:" << fu1.p << "\n";
		//fu1.p - cast from int to int*, fu1.n1 - shows the only know variable
		//anonymous union - union withot a name: union { ... };, it is an object - its elements can be used without using object name (247 page)

		//ceil - up, floor - down, round - closest value, trund - to zero
		float f1{ 37.65f };
		float f2{ 23.32f };
		int n1 = ceil(f1);
		std::cout << n1 << ", " << floor(f2) << ", " << round(f1) << endl;		//why they are not in cmath nor std?

		std::cout << "------------------------------------------------------" << endl;
	}

	//multi-dimmensional arrays, recursion
	{
		std::cout << "multi-dimmension arrays, input / output, reccursion:\n" << endl;

		int na1[10][10];
		int **na2;
		na2 = new int*[10];

		std::cout << "traditional 2d array: \n";
		for (int i = 0; i != 10; ++i)
		{
			std::cout << i + 1 << ": ";
			for (int j = 0; j != 10; ++j)
			{
				na1[i][j] = i*10 + j;
				std::cout << na1[i][j] << ", ";
			}
			std::cout << "\n";
		}

		std::cout << "pointer 2d array: \n";
		for(int i=0; i != 10; ++i)
			na2[i] = new int[10];
		for (int i = 0; i != 10; ++i)
		{
			std::cout << i + 1 << ": ";
			for (int j = 0; j != 10; ++j)
			{
				na2[i][j] = i * 10 + j;
				std::cout << na2[i][j] << ", ";
			}
			std::cout << "\n";
		}
		for (int i = 0; i != 10; ++i)
			delete[]na2[i];
		delete[]na2;
		
		//4 dimmensional pointers
		{
			int ****na3;
			na3 = new int***[5];
			for (int i = 0; i != 5; ++i)
			{
				na3[i] = new int**[5];
				for (int j = 0; j != 5; ++j)
				{
					na3[i][j] = new int*[5];
					for (int k = 0; k != 5; ++k)
						na3[i][j][k] = new int[5];
				}
			}
			for (int i = 0; i != 5; ++i)
			{
				for (int j = 0; j != 5; ++j)
					delete[]na3[i][j];
				delete[]na3[i];
			}
			delete[]na3;
		}

		rek(2);

		std::cout << "------------------------------------------------------" << endl;
	}

	//stos, sterta

	//basics - theory
	{/*
		scheme of c++ as compiled type language:
		source files -> compilation -> object files -> consolidation -> executive file
		portability of C++ is about beeing able to carry source code into multiple platforms - because executive application is created for more concrete hardware configuration
		c++ has static control of data types - types are verified at compilation time, so it can state what kind of operations may be used on given data
		int main() - it is commonly accepted that value of 0 is returned if there were no errors and value other than 0 if there was an error, but even then not all systems use that
		for example at this aspect Linux is better than Windows
		 */
		//		"///" - are comments with a single XML link (?)
		std::cout << "basics of C++ and theory:\n" << endl;

		const double d1 = square(25.786);
		std::cout << "constexpr function: " << d1 << '\n';
		auto *oopc1{ new OOPClass{10, 20} };			//auto is used when you want to make writing faster for example: compiled classes

		int n1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int *pn1 = n1;
		std::cout << "simple for statement: \n";
		for (auto x : n1)
			std::cout << x << " ,";
		std::cout << '\n';
		//for (auto x : { 10, 21, 32, 43, 54, 65 })		- automaticly will pass through all elements in given collection, auto - detects iterative data type, then set of values\
														by which this variable iterates, but it is (probably) not the best optimized, this version of for is more susceptible to errors
		Header hh1{};							//simple header - just to have one
		hh1.show_some_text();					//good programming habbits - header files are an interface, source files are an implementation,	you only need to include a header\
												headers need to be splitted by application logic, using modules makes compilation faster
		Space::main();							//namespaces - make code organisation easier in bigger libraries, make name collisions less likely
		
		//exceptions
		//invariants - invariant (:o) initial function rules, which should be verified when you pass input, derivative classes should verify if invariant is respected
		//static assertion - try to be using it, it only refers to compilation time constants

		//bool operator !=(object o1, object o2) {return !(o1==o2); }
		//container - object that stores set of elements
		//abstract classes unlike concrete claases don't need to be compiled again when inherited classes are changed
		//copying - two separate objects (lvalue reference), moving - one object (rvalue reference)\
		to move you can also use stl function std::move();\
		code unrolling in a line - does not affect performance for small functions, for large functions - you should avoid it

		//templates, aliases

		//concatenation - adding, for example strings\
		container - class which main purpose is to store data\
		predicate - element that meets given condition in general algorithm\
		algorithm - finished set of rules, specifying sequence of actions, allowing to solve specific set of issues and having five important features:\
		finiteness, definiteness, input, output, efficiency\
		in context of STL: function template working on sequences of elements\
		there is something like extended std if i will need it

		//unique_ptr, shared_ptr\
		tasks - equations, that can be done parallel with others\
		thread - taks representation at system level, threads in applications use common adress space\
		mutex, synchronous programming is less efficient than copying for small amount of data and more efficient for big amount of data\
		<chrono> - tools concerning time

		std::cout << "------------------------------------------------------" << endl;
	}

	_getch();
	return 0;
}