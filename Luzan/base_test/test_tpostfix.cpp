#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, correct_expression_is_correct) {
	TPostfix postfix("(a + b) * (c /d) - e");
	ASSERT_NO_THROW(postfix.ToPostfix(););
}

TEST(TPostfix, two_operators_one_by_one_error) {
	TPostfix postfix("(a + b) */ (c /d) - e");
	ASSERT_ANY_THROW(postfix.ToPostfix(););
}

TEST(TPostfix, operation_after_opening_bracket_is_an_error) {
	TPostfix postfix("(a + b) * (/ c * d) - e");
	ASSERT_ANY_THROW(postfix.ToPostfix(););
}

TEST(TPostfix, operand_after_closing_bracket_is_an_error) {
	TPostfix postfix("(a + b)c * ( c * d) - e");
	ASSERT_ANY_THROW(postfix.ToPostfix(););
}

TEST(TPostfix, double_openning_bracket_is_an_error) {
	TPostfix postfix("(a + b) * ((c /d) - e");
	ASSERT_ANY_THROW(postfix.ToPostfix(););
}

TEST(TPostfix, double_closing_bracket_is_an_error) {
	TPostfix postfix("(a + b)) * (c /d) - e");
	ASSERT_ANY_THROW(postfix.ToPostfix(););
}

TEST(TPostfix, opening_bracket_after_operand_is_an_error) {
	TPostfix postfix("(a + b( * (c /d) - e");
	ASSERT_ANY_THROW(postfix.ToPostfix(););
}

TEST(TPostfix, incorrect_expression_is_an_error) {
	TPostfix postfix("(mess#$%");
	ASSERT_ANY_THROW(postfix.ToPostfix(););
}

TEST(TPostfix, calculation_check) {
	TPostfix postfix("(a + b) * (c /d) - e");
	postfix.ToPostfix();
	map<char, double> oper = { {'a', 100}, {'b', 58.58}, { 'c', 42.42}, {'d', 1}, {'e', 2.0} };
	double res = postfix.Calculate(oper);
	double ans = 6724.9636;
	ASSERT_TRUE(fabs(res - ans) <= 0.1);
}

TEST(TPostfix, get_infix_works_properly) {
	TPostfix postfix("(a + b) * (c /d) - e");
	ASSERT_TRUE("(a+b)*(c/d)-e" == postfix.GetInfix());
}

TEST(TPostfix, get_postfix_works_properly) {
	TPostfix postfix("(a + b) * (c /d) - e");
	postfix.ToPostfix();
	ASSERT_TRUE("ab+cd/*e-" == postfix.GetPostfix());
}
