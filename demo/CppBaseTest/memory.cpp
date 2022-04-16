#include "memory.hpp"
#include <memory>
#include <iostream>
#include <string>

namespace memory_ {

// Blog: https://blog.csdn.net/fengbingchun/article/details/124222059
namespace {
struct C : std::enable_shared_from_this<C> {};

struct Best : std::enable_shared_from_this<Best> { // note: public inheritance
    std::shared_ptr<Best> getptr() { return shared_from_this(); }

    // No public constructor, only a factory function, so there's no way to have getptr return nullptr.
#ifdef _MSC_VER
	static std::shared_ptr<Best> create() //  nodiscard need compiler flags: "/std:c++17"
#else
    [[nodiscard]] static std::shared_ptr<Best> create()
#endif
    {
        // Not using std::make_shared<Best> because the c'tor is private.
        return std::shared_ptr<Best>(new Best());
    }

private:
    Best() = default;
};

class Y: public std::enable_shared_from_this<Y> {
public:
    std::shared_ptr<Y> f()
    {
        return shared_from_this(); // returns a valid shared_ptr, even though it had no member instance
        //return std::shared_ptr<Y>(this); // error
    }
};

class Foo : public std::enable_shared_from_this<Foo> {
public:
    Foo() = default;
    ~Foo() {}

    void set_name(std::string name) { name_ = name; }
    void set_age(int age) { age_ = age; }
    const std::string& get_name() const { return name_; }
    int get_age() const { return age_; }

private:
    std::string name_;
    int age_;
};

void modify_foo(std::shared_ptr<Foo> foo)
{
    foo->set_name("Tom");
    foo->set_age(10);
    fprintf(stdout, "modify_foo use count: %d\n", foo.use_count()); // 2
}

} // namespace

int test_enable_shared_from_this_1()
{
    // reference: http://www.cplusplus.com/reference/memory/enable_shared_from_this/
    std::shared_ptr<C> foo, bar;
    foo = std::make_shared<C>();
    bar = foo->shared_from_this();
    if (!foo.owner_before(bar) && !bar.owner_before(foo))
        fprintf(stdout, "foo and bar share ownership\n");

    return 0;
}

int test_enable_shared_from_this_2()
{
    // reference: https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
    // Best: Same but can't stack-allocate it:
    std::shared_ptr<Best> best0 = Best::create();
    std::shared_ptr<Best> best1 = best0->getptr();
    fprintf(stdout, "best0.use_count: %d, best1.use_count: %d\n", best0.use_count(), best1.use_count()); // 2, 2

    //Best stackBest; // <- Will not compile because Best::Best() is private.
    return 0;
}

int test_enable_shared_from_this_3()
{
    // reference: https://stackoverflow.com/questions/712279/what-is-the-usefulness-of-enable-shared-from-this
    // It enables you to get a valid shared_ptr instance to this, when all you have is this. 
    // Without it, you would have no way of getting a shared_ptr to this, unless you already had one as a member.
    std::shared_ptr<Y> p(new Y);
    std::shared_ptr<Y> q = p->f();
    if (!(p == q)) {
        fprintf(stderr, "p should be equal to q\n");
        return -1;
    }

    if (p < q || q < p) { // p and q must share ownership
        fprintf(stderr, "p and q must share ownership\n");
        return -1;
    }

    return 0;
}

int test_enable_shared_from_this_4()
{
    std::shared_ptr<Foo> foo = std::make_shared<Foo>();
    foo->set_name("Take");
    foo->set_age(20);
    fprintf(stdout, "foo use count: %d, name: %s, age: %d\n", foo.use_count(), foo->get_name().c_str(), foo->get_age()); // 1, Take, 20

    modify_foo(foo->shared_from_this());
    fprintf(stdout, "foo use count: %d, name: %s, age: %d\n", foo.use_count(), foo->get_name().c_str(), foo->get_age()); // 1, Tom, 10

    return 0;
}

} // namespace memory_
