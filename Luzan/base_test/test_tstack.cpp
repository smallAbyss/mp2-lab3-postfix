#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, get_size_works_correct)
{
	TStack<int> st(2);
	st.Push(42);
	ASSERT_EQ(1, st.getsize());
}

TEST(TStack, cannot_push_in_full_stack)
{
	TStack<int> st(3);
	for (int i = 0; i < 3; i++) {
		st.Push(42);
	}
	ASSERT_ANY_THROW(st.Push(0));
}

TEST(TStack, cannot_pop_from_empty_stack)
{
	TStack<int> st(5);
	st.Push(42);
	st.Pop();
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, IsEmpty_works_correct)
{
	TStack<int> st(2);
	bool q0 = st.IsEmpty();
	st.Push(42);
	bool q1 = st.IsEmpty();
	st.Pop();
	bool q2 = st.IsEmpty();
	ASSERT_TRUE((q0 == 1) && (q1 == 0) && (q2 == 1));
}

TEST(TStack, Full_works_correct)
{
	TStack<int> st(2);
	bool q0 = st.Full();
	st.Push(42);
	bool q1 = st.Full();
	st.Push(42);
	bool q2 = st.Full();
	ASSERT_TRUE((q0 == 0) && (q1 == 0) && (q2 == 1));
}

TEST(TStack, TStack_can_work_with_user_types)
{
	class MyClass {
		int a;
		char b;
	public:
		MyClass(int a_ = 0, char b_ = ' ') : a(a_), b(b_) { }

		bool operator==(const MyClass& rh) {
			return ((a == rh.a) && (b == rh.b));
		}

		bool operator!=(const MyClass& rh) {
			return !(this->operator==(rh));
		}
	};
	TStack<MyClass> st(2);
	MyClass obj1(5, 'o'), obj2(15, 'm');
	st.Push(obj1);
	st.Push(obj1);

	ASSERT_TRUE( (st.Pop() == obj1) && (st.Pop() != obj2));
}

