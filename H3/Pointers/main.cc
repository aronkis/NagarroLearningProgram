#include "include/UniquePointer.h"
#include "include/SharedPointer.h"
#include <iostream>

struct Foo {
  Foo() { std::cout << "Foo created\n"; }
  ~Foo() { std::cout << "Foo destroyed\n"; }
};

struct Vec3
{
    int x, y, z;
 
    // following constructor is no longer needed since C++20
    Vec3(int x = 0, int y = 0, int z = 0) noexcept : x(x), y(y), z(z) { }
 
    friend std::ostream& operator<<(std::ostream& os, const Vec3& v)
    {
        return os << "{ x=" << v.x << ", y=" << v.y << ", z=" << v.z << " }";
    }
};

void test1()
{  
  // Test 1: Construct UniquePointer and verify the object is created
  {
    UniquePointer<Foo> p1(new Foo); // Foo created
  } // Foo destroyed

  // Test 2: Reset UniquePointer and verify the original object is destroyed
  {
    UniquePointer<Foo> p1(new Foo); // Foo created
    p1.reset(nullptr); // Foo destroyed
  }

  // Test 3: Move UniquePointer and verify the moved-from instance has a nullptr
  {
    UniquePointer<Foo> p1(new Foo); // Foo created
    UniquePointer<Foo> p2 = std::move(p1);
    std::cout << "p1 is null: " << (p1 ? "false" : "true") << '\n'; // outputs true
  } // Foo destroyed

  // Test 4: Make Unique
  {
    UniquePointer<Vec3> p1 = make_unique<Vec3>();
    std::cout << "make_unique<Vec3>():      " << *p1 << '\n';
    int array[3] = {1, 2, 3};
    UniquePointer<int> p2 = make_unique<int>(array, 3);
    for (int i = 0; i < 3; i++)
    {
      std::cout << p2[i] << " ";
    }
    std::cout << "\n";
  }

  //Test 5: ArrayTest
  {
    int size = 10;
    UniquePointer<int> p(10);
    for (int i = 0; i < 10; i++){
      p[i] = i;
    }
    for (int i = 0; i < 10; i++){
      std::cout << p[i] << " ";
    }
    std::cout << "\n";
  }
}

void test2()
{
  // Test 1: Construct SharedPointer and verify the object is created
  {
    SharedPointer<Foo> p1(new Foo); // Foo created 
    std::cout << "Use count: " << p1.use_count() << '\n'; // outputs 1
  } // Foo destroyed
  std::cout << std::endl;

  // Test 2: Copy construct SharedPointer and verify use count is updated
  {
    SharedPointer<Foo> p1(new Foo); // Foo created
    SharedPointer<Foo> p2(p1); 
    std::cout << "Use count: " << p1.use_count() << '\n'; // outputs 2
  } // Foo destroyed
  std::cout << std::endl;

  // Test 3: Copy assignment SharedPointer and verify use count is updated
  {
    SharedPointer<Foo> p1(new Foo); // Foo created 
    SharedPointer<Foo> p2(new Foo); // Foo created
    p1 = p2;  // Foo destroyed
    std::cout << "Use count: " << p1.use_count() << '\n'; // outputs 2
    std::cout << "Use count: " << p2.use_count() << '\n'; // outputs 2
  } // Foo destroyed
  std::cout << std::endl;

  // Test 4: Reset SharedPointer and verify the original object is destroyed
  {
    SharedPointer<Foo> p1(new Foo); // Foo created 
    p1.reset(nullptr); // Foo destroyed 
  } 
  std::cout << std::endl;

  // Test 5: Move SharedPointer and verify the moved-from instance has a nullptr
  {
    SharedPointer<Foo> p1(new Foo); // Foo created 
    SharedPointer<Foo> p2 = std::move(p1);
    std::cout << "Use count: " << p2.use_count() << '\n'; // outputs 1
    std::cout << "p1 is null: " << (p1 ? "false" : "true") << '\n'; // outputs true
  } // Foo destroyed 
  std::cout << std::endl;

  // Test 6: Move assignment and verify the moved-from instance has a nullptr
  {
    SharedPointer<Foo> p1(new Foo); // Foo created 
    SharedPointer<Foo> p2;
    p2 = std::move(p1);
    std::cout << "Use count: " << p2.use_count() << '\n'; // outputs 1
    std::cout << "p1 is null: " << (p1 ? "false" : "true") << '\n'; // outputs true
  } // Foo destroyed 
  std::cout << std::endl;

  // Test 7: Generalized copy constructor with related types 
  {
    SharedPointer<Foo> p1(new Foo);  // Foo created 
    SharedPointer<Foo> p2(p1); 
    SharedPointer<const Foo> p3(p2);
    std::cout << "Use count: " << p3.use_count() << '\n'; // outputs 3
  } // Foo destroyed 
  std::cout << std::endl;
}

int main()
{
  test1();
  std::cout << std::endl;
  test2();
}