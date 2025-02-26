# Classes

### Classes 

> Why and What?

##### Why?

* C has no objects
* No way of encapsulating data and the functions that operate on that data
* No ability to have object-oriented programming (OOP) design patterns

##### object-oriented-programming

* Object-oriented-programming is centered around objects 
* Focuses on design and implementation of classes! 
* Classes are the user-defined types that can be declared as an object!

##### struct & class

struct is a class without **access restriction** & member functions

##### public, protected, private

* public: accessible everywhere
* protect: accessible in the class itself and its sub-class
* private: only accessible in the class itself

##### Header File (.h) and Source Files (.cpp)

|          | Header File (.h)                                             | Source File (.cpp)                         |
| -------- | ------------------------------------------------------------ | ------------------------------------------ |
| Purpose  | Defines the **interface**                                    | Implements class functions                 |
| Contains | Function prototypes, class declarations, type definitions, macros, constants | Function implementations, executable code  |
| Access   | This is shared across source files                           | Is compiled into an object file            |
| Example  | `void someFunction();`                                       | `void someFunction() {implementation...};` |

##### class design

* A constructor 
  * The constructor initializes the state of newly created objects
* Private member functions/variables 
* Public member functions (interface for a user) 
* Destructor

```.h file
class StanfordID {
private:
    // An example of type aliasing
	using String = std::string;
	String name;
	String sunet;
	int idNumber;
public:
	// constructor for our StudentID, here The syntax for the constructor is just the name of the class
	StanfordID(std::string name, std::string sunet, int idNumber);
	// method to get name, sunet, and idNumber, respectively
	std::string getName();
	std::string getSunet();
	int getID();
}
```

```.cpp file
#include “StanfordID.h”
#include <string>

// default constructor
StanfordID::StanfordID() {
	name = “John Appleseed”;
	sunet = “jappleseed”;
	idNumber = 00000001;
}
// parameterized constructor
StanfordID::StanfordID(std::string name, std::string sunet, int idNumber) {
	this->name = name;
	this->sunet = sunet;
	this->idNumber = idNumber;
}

// list initialization constructor
// StanfordID::StanfordID(std::string name, std::string sunet, int idNumber): name{name}, sunet{sunet}, idNumber{idNumber} {};

StanfordID::~StanfordID() {
	// free/deallocate any data here
    // delete [] my_array; /// for illustration
}

std::string StanfordID::getName() {
    return this->name;
}

std::string StanfordID::getSunet() {
    return this->sunet;
}

int stanfordID::getID() {
    return this->idNumber;
}
```

* Remember namespaces, like `std::` In our `.cpp` file 
* Use this `this` keyword to disambiguate which `name` you’re referring to.
* We need to use our class as our **namespace** when defining our member functions

> Another code practice can be seen at code: lec07_IntVector.cpp.

### Inheritance

##### Aim:

* Dynamic Polymorphism: Different types of objects may need the same interface
* Extensibility: Inheritance allows you to **extend a class** by creating a subclass with specific properties

##### Example: Shape

```.h file
class Shape {
public:
	virtual double area() const = 0;
	// here are two key points:
    // 1. const: 含义：表示成员函数 area() 是一个 常量成员函数。
	// 行为：
	// 	在该函数内部，不能修改类的任何非静态成员变量（除非变量被 mutable 修饰）。
	// 	常量对象（如 const Shape* 或 const Shape&）只能调用 const 成员函数。
	// 用途：
	// 	这里的 area() 是计算面积的函数，逻辑上不应修改对象的状态。用 const 可以确保这一点，同时允许常量对象调用该方法。
    // 2. =0
    // 这表示该函数为一个 **纯虚函数**, 包含纯虚函数的类称为 抽象类（abstract class），不能直接实例化。
	// 必须重写（override）所有纯虚函数，否则派生类也会成为抽象类。
    // 作用:
    // 	强制派生类实现特定接口。
	// 	实现多态：通过基类指针或引用调用不同派生类的方法。
};

class Circle : public Shape {
public:
	// constructor
	Circle(double radius): _radius{radius} {};
	double area() const { // 保持函数签名一致
		return 3.14 * _radius * _radius;
	}
private:
	double _radius;
};
```

##### Types of Inheritance

| Inheritance Type  | public                          | protected                       | private                         |
| ----------------- | ------------------------------- | ------------------------------- | ------------------------------- |
| Example           | `class B: public A {...}`       | `class B: protected A {...}`    | `class B: private A {...}`      |
| Public Members    | Are public in the derived class | Protected in the derived class  | Private in the derived class    |
| Protected Members | Protected in the derived class  | Protected in the derived class  | Private in the derived class    |
| Private Members   | Not accessible in derived class | Not accessible in derived class | Not accessible in derived class |

##### Diamond Inheritance Problem

The way to fix this is to make Employee and Student inherit from Person in a virtual way. 

Virtual inheritance means that a derived class, in this case SectionLeader, should only have a **single instance** of base classes, in this case Person.

```.h file
class Employee : public virtual Person {
protected:
	double salary;
public:
	Employee(const std::string& name);
	virtual std::string getRole() const = 0;
	virtual double getSalary() const = 0;
	virtual void setSalary() const = 0;
	virtual ~Employee() = default;
};
```

```.h file
class Student : public virtual Person {
protected:
	std::string idNumber;
	std::string major;
	std::string advisor;
	uint16_t year;
public:
	Student(const std::string& name, …);
	std::string getIdNumber() const;
	std::string getMajor() const;
	uint16_t getYear() const;
	void setYear(uint16_t year);
	void setMajor(const std::string& major);
	std::string getAdvisor() const;
	void setAdvisor(const std::string& advisor);
};
```

* This requires the **derived class** to initialize the base class!

### Recap

* Classes allow you to **encapsulate** *functionality* and *data* with **access protections** 
* Inheritance allows us to design powerful and versatile abstractions that can help us model complex relationships in code.
* These concepts are tricky – this lecture really highlights the power of C++

### More about *Virtual* C++ 类继承中虚函数、纯虚函数、抽象类与虚基类总结(from deepseek)

##### **1. 虚函数（Virtual Function）**

- **定义**
  在基类中用 `virtual` 关键字声明的成员函数，允许派生类通过重写（override）实现多态行为。

- **语法**

  ```
  class Base {
  public:
      virtual void func() { /* 默认实现 */ }
  };
  ```

- **核心特性**

  - **动态绑定（运行时多态）**Dynamic Binding：通过基类指针或引用调用函数时，实际调用的是对象类型对应的函数。
  - **派生类可选择性重写**：派生类可以选择是否重写虚函数。若不重写，则使用基类实现。

- **示例**

  ```
  class Derived : public Base {
  public:
      void func() override { /* 重写实现 */ }
  };
  ```

##### **2. 纯虚函数（Pure Virtual Function）**

- **定义**
  在基类中声明但没有实现的虚函数，使用 `= 0` 标记，强制派生类必须重写。

- **语法**

  ```
  class AbstractBase {
  public:
      virtual void pureFunc() const = 0; // 纯虚函数
  };
  ```

- **核心特性**

  - 包含纯虚函数的类称为 **抽象类（Abstract Class）**，**不可实例化**。
  - 派生类必须实现所有纯虚函数，否则派生类也会成为抽象类。

- **示例**

  ```
  class ConcreteClass : public AbstractBase {
  public:
      void pureFunc() const override { /* 必须实现 */ }
  };
  ```

##### **3. 抽象类（Abstract Class）**

- **定义**
  包含至少一个纯虚函数的类，用于定义接口规范。

- **特性**

  - 不能直接创建对象（`AbstractBase obj;` ❌）。
  - 可以定义非虚成员函数和成员变量（提供部分公共实现）。
  - 可通过指针或引用实现多态。

- **示例**

  ```
  AbstractBase* ptr = new ConcreteClass();
  ptr->pureFunc(); // 调用派生类实现
  ```

##### **4. 虚基类（Virtual Base Class）**

- **定义**
  用于解决多重继承中的“菱形继承”问题，确保最终派生类中只保留一份基类子对象。

- **语法**
  在继承时使用 `virtual` 关键字：

  ```
  class Base { /* ... */ };
  
  class Derived1 : virtual public Base { /* ... */ };
  class Derived2 : virtual public Base { /* ... */ };
  
  class Final : public Derived1, public Derived2 { /* ... */ };
  ```

- **核心特性**

  - 避免多重继承时基类成员的重复存储。
  - 最终派生类（如 `Final`）负责直接初始化虚基类。

- **初始化规则**

  ```
  class Final : public Derived1, public Derived2 {
  public:
      Final() : Base(), Derived1(), Derived2() { /* 直接初始化虚基类 */ }
  };
  ```

##### **5. 关键对比**

| 特性                   | 虚函数                 | 纯虚函数                   | 虚基类                    |
| :--------------------- | :--------------------- | :------------------------- | :------------------------ |
| **语法**               | `virtual void func();` | `virtual void func() = 0;` | `class A : virtual Base;` |
| **是否强制派生类实现** | 否                     | 是                         | 不适用                    |
| **基类是否可实例化**   | 是                     | 否（抽象类）               | 是                        |
| **用途**               | 实现多态               | 定义接口规范               | 解决菱形继承问题          |

##### **6. 常见问题**

1. **虚函数 vs 普通函数重写**

   - 虚函数通过基类指针调用时触发动态绑定，普通函数重写是静态绑定。

2. **纯虚函数能否有默认实现？**

   - 可以！纯虚函数可以有默认实现，但派生类仍需显式重写：

     ```
     class AbstractBase {
     public:
         virtual void func() const = 0;
     };
     void AbstractBase::func() const { /* 默认实现 */ }
     ```

3. **虚基类的构造函数调用顺序**

   - 虚基类的构造函数优先于所有直接基类的构造函数执行。

##### **7. 总结**

- **虚函数**：实现多态的核心机制。
- **纯虚函数**：定义接口，强制派生类实现。
- **抽象类**：不可实例化的接口规范。
- **虚基类**：解决多重继承中的冗余问题。

掌握这些概念是深入理解 C++ 面向对象编程的关键！ 🚀
