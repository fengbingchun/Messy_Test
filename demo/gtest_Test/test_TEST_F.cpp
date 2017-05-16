#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <gtest/gtest.h>
#include "funset.hpp"

// reference: googletest/samples

/////////////////////////////////////////////////////////////
// To use a test fixture, derive a class from testing::Test.
class QueueTest : public testing::Test {
protected:  // You should make the members protected s.t. they can be
	// accessed from sub-classes.

	// virtual void SetUp() will be called before each test is run.  You
	// should define it if you need to initialize the varaibles.
	// Otherwise, this can be skipped.
	virtual void SetUp() override {
		q1_.Enqueue(1);
		q2_.Enqueue(2);
		q2_.Enqueue(3);
	}

	// virtual void TearDown() will be called after each test is run.
	// You should define it if there is cleanup work to do.  Otherwise,
	// you don't have to provide it.
	//
	// virtual void TearDown() {
	// }

	// A helper function that some test uses.
	static int Double(int n) {
		return 2 * n;
	}

	// A helper function for testing Queue::Map().
	void MapTester(const Queue<int> * q) {
		// Creates a new queue, where each element is twice as big as the
		// corresponding one in q.
		const Queue<int> * const new_q = q->Map(Double);

		// Verifies that the new queue has the same size as q.
		ASSERT_EQ(q->Size(), new_q->Size());

		// Verifies the relationship between the elements of the two queues.
		for (const QueueNode<int> * n1 = q->Head(), *n2 = new_q->Head();
			n1 != NULL; n1 = n1->next(), n2 = n2->next()) {
			EXPECT_EQ(2 * n1->element(), n2->element());
		}

		delete new_q;
	}

	// Declares the variables your tests want to use.
	Queue<int> q0_;
	Queue<int> q1_;
	Queue<int> q2_;
};

// When you have a test fixture, you define a test using TEST_F instead of TEST.

// Tests the default c'tor.
TEST_F(QueueTest, DefaultConstructor) {
	// You can access data in the test fixture here.
	EXPECT_EQ(0u, q0_.Size());
}

// Tests Dequeue().
TEST_F(QueueTest, Dequeue) {
	int * n = q0_.Dequeue();
	EXPECT_TRUE(n == NULL);

	n = q1_.Dequeue();
	ASSERT_TRUE(n != NULL);
	EXPECT_EQ(1, *n);
	EXPECT_EQ(0u, q1_.Size());
	delete n;

	n = q2_.Dequeue();
	ASSERT_TRUE(n != NULL);
	EXPECT_EQ(2, *n);
	EXPECT_EQ(1u, q2_.Size());
	delete n;
}

// Tests the Queue::Map() function.
TEST_F(QueueTest, Map) {
	MapTester(&q0_);
	MapTester(&q1_);
	MapTester(&q2_);
}

/////////////////////////////////////////////////////////////////////////////
// teaches how to reuse a test fixture in multiple test cases by deriving sub-fixtures from it
class QuickTest : public testing::Test {
protected:
	// Remember that SetUp() is run immediately before a test starts.
	// This is a good place to record the start time.
	virtual void SetUp() override {
		start_time_ = time(NULL);
	}

	// TearDown() is invoked immediately after a test finishes.  Here we
	// check if the test was too slow.
	virtual void TearDown() override {
		// Gets the time when the test finishes
		const time_t end_time = time(NULL);

		// Asserts that the test took no more than ~5 seconds.  Did you
		// know that you can use assertions in SetUp() and TearDown() as
		// well?
		EXPECT_TRUE(end_time - start_time_ <= 5) << "The test took too long.";
	}

	// The UTC time (in seconds) when the test starts
	time_t start_time_;
};

// We derive a fixture named IntegerFunctionTest from the QuickTest
// fixture.  All tests using this fixture will be automatically
// required to be quick.
class IntegerFunctionTest : public QuickTest {
	// We don't need any more logic than already in the QuickTest fixture.
	// Therefore the body is empty.
};

// Now we can write tests in the IntegerFunctionTest test case.
// Tests Factorial()
TEST_F(IntegerFunctionTest, Factorial) {
	// Tests factorial of negative numbers.
	EXPECT_EQ(1, Factorial(-5));
	EXPECT_EQ(1, Factorial(-1));
	EXPECT_GT(Factorial(-10), 0);

	// Tests factorial of 0.
	EXPECT_EQ(1, Factorial(0));

	// Tests factorial of positive numbers.
	EXPECT_EQ(1, Factorial(1));
	EXPECT_EQ(2, Factorial(2));
	EXPECT_EQ(6, Factorial(3));
	EXPECT_EQ(40320, Factorial(8));
}

// Tests IsPrime()
TEST_F(IntegerFunctionTest, IsPrime) {
	// Tests negative input.
	EXPECT_FALSE(IsPrime(-1));
	EXPECT_FALSE(IsPrime(-2));
	EXPECT_FALSE(IsPrime(INT_MIN));

	// Tests some trivial cases.
	EXPECT_FALSE(IsPrime(0));
	EXPECT_FALSE(IsPrime(1));
	EXPECT_TRUE(IsPrime(2));
	EXPECT_TRUE(IsPrime(3));

	// Tests positive input.
	EXPECT_FALSE(IsPrime(4));
	EXPECT_TRUE(IsPrime(5));
	EXPECT_FALSE(IsPrime(6));
	EXPECT_TRUE(IsPrime(23));
}

//////////////////////////////////////////////////////////////
// teaches how to reuse a test fixture in multiple test cases by deriving sub-fixtures from it
class QueueTest_2 : public QuickTest {
protected:
	virtual void SetUp() override {
		// First, we need to set up the super fixture (QuickTest).
		QuickTest::SetUp();

		// Second, some additional setup for this fixture.
		q1_.Enqueue(1);
		q2_.Enqueue(2);
		q2_.Enqueue(3);
	}

	// By default, TearDown() inherits the behavior of
	// QuickTest::TearDown().  As we have no additional cleaning work
	// for QueueTest, we omit it here.
	//
	// virtual void TearDown() override {
	//   QuickTest::TearDown();
	// }

	Queue<int> q0_;
	Queue<int> q1_;
	Queue<int> q2_;
};

// Tests the default constructor.
TEST_F(QueueTest_2, DefaultConstructor) {
	EXPECT_EQ(0u, q0_.Size());
}

// Tests Dequeue().
TEST_F(QueueTest_2, Dequeue) {
	int* n = q0_.Dequeue();
	EXPECT_TRUE(n == NULL);

	n = q1_.Dequeue();
	EXPECT_TRUE(n != NULL);
	EXPECT_EQ(1, *n);
	EXPECT_EQ(0u, q1_.Size());
	delete n;

	n = q2_.Dequeue();
	EXPECT_TRUE(n != NULL);
	EXPECT_EQ(2, *n);
	EXPECT_EQ(1u, q2_.Size());
	delete n;
}
