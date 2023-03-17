#include <filesystem>
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include <pwutils/pwmath.hpp>

TEST(MATH_TESTS, IS_INTEGER) {
	EXPECT_TRUE(pw::isInteger("1"));
	EXPECT_TRUE(pw::isInteger("42323"));
	EXPECT_FALSE(pw::isInteger("a"));
	EXPECT_FALSE(pw::isInteger("3.234"));
	EXPECT_FALSE(pw::isInteger("false"));
}

TEST(MATH_TESTS, VECTOR_OF_INTEGERS){
	EXPECT_TRUE(pw::isIntegers(std::vector<std::string>{"843"}));
	EXPECT_TRUE(pw::isIntegers(std::vector<std::string>{"1", "2", "3"}));
	EXPECT_FALSE(pw::isIntegers(std::vector<std::string>{"1", "2.3", "3"}));
	EXPECT_FALSE(pw::isIntegers(std::vector<std::string>{}));
	EXPECT_FALSE(pw::isIntegers(std::vector<std::string>{"c"}));
}

TEST(MATH_TESTS, STRING_OF_INTEGERS) {
	EXPECT_TRUE(pw::isIntegers("843"));
	EXPECT_TRUE(pw::isIntegers("1 2 3"));
	EXPECT_FALSE(pw::isIntegers("1 2.3 3"));
	EXPECT_FALSE(pw::isIntegers(""));
	EXPECT_FALSE(pw::isIntegers("c"));
}

TEST(MATH_TESTS, IS_DOUBLE) {
	EXPECT_TRUE(pw::isDouble("1.8"));
	EXPECT_TRUE(pw::isDouble("13.24"));
	EXPECT_FALSE(pw::isDouble("a"));
	EXPECT_FALSE(pw::isDouble("9.x5"));
	EXPECT_FALSE(pw::isDouble("false"));
}

TEST(MATH_TESTS, VECTOR_OF_DOUBLES){
	EXPECT_TRUE(pw::isDoubles(std::vector<std::string>{"1.8"}));
	EXPECT_TRUE(pw::isDoubles(std::vector<std::string>{"1.8", "2.8", "3.8"}));
	EXPECT_FALSE(pw::isDoubles(std::vector<std::string>{"1.8", "2.XX", "3.8"}));
	EXPECT_FALSE(pw::isDoubles(std::vector<std::string>{}));
	EXPECT_FALSE(pw::isDoubles(std::vector<std::string>{"c"}));
}

TEST(MATH_TESTS, STRING_OF_DOUBLES) {
	EXPECT_TRUE(pw::isDoubles("1.8"));
	EXPECT_TRUE(pw::isDoubles("1.8 2.8 3.8"));
	EXPECT_FALSE(pw::isDoubles("1.8 2.XX 3.8"));
	EXPECT_FALSE(pw::isDoubles(""));
	EXPECT_FALSE(pw::isDoubles("c"));
}
