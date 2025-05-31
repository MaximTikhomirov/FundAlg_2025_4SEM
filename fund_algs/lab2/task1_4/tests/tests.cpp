#include <gtest/gtest.h>
#include "../include/big_int.hpp"
class BigIntTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(BigIntTest, DefaultConstructor) {
    BigInt num;
    EXPECT_EQ(num.size(), 1);
    EXPECT_EQ(num[0], 0);
    EXPECT_FALSE(num.is_negative());
}

TEST_F(BigIntTest, StringConstructorPositive) {
    BigInt num("12345678901234567890");
    EXPECT_FALSE(num.is_negative());
    EXPECT_GT(num.size(), 0);
}

TEST_F(BigIntTest, StringConstructorNegative) {
    BigInt num("-12345678901234567890");
    EXPECT_TRUE(num.is_negative());
    EXPECT_GT(num.size(), 0);
}

TEST_F(BigIntTest, StringConstructorInvalid) {
    EXPECT_THROW(BigInt("abc123"), std::invalid_argument);
    EXPECT_THROW(BigInt("123a456"), std::invalid_argument);
}

TEST_F(BigIntTest, IntegerConstructor) {
    BigInt num(12345);
    EXPECT_FALSE(num.is_negative());
    EXPECT_EQ(num.size(), 1);
    EXPECT_EQ(num[0], 12345);
}

TEST_F(BigIntTest, NegativeIntegerConstructor) {
    BigInt num(-12345);
    EXPECT_TRUE(num.is_negative());
    EXPECT_EQ(num.size(), 1);
    EXPECT_EQ(num[0], 12345);
}

TEST_F(BigIntTest, CopyConstructor) {
    BigInt num1("1234567890");
    BigInt num2(num1);
    EXPECT_EQ(num1, num2);
}

TEST_F(BigIntTest, MoveConstructor) {
    BigInt num1("1234567890");
    BigInt num2(std::move(num1));
    EXPECT_EQ(num2, BigInt("1234567890"));
    EXPECT_EQ(num1.size(), 1);
}


TEST_F(BigIntTest, CopyAssignment) {
    BigInt num1("1234567890");
    BigInt num2;
    num2 = num1;
    EXPECT_EQ(num1, num2);
}

TEST_F(BigIntTest, MoveAssignment) {
    BigInt num1("1234567890");
    BigInt num2;
    num2 = std::move(num1);
    EXPECT_EQ(num2, BigInt("1234567890"));
    EXPECT_EQ(num1.size(), 0);
}

TEST_F(BigIntTest, Addition) {
    BigInt num1("1234567890");
    BigInt num2("9876543210");
    BigInt result = num1 + num2;
    EXPECT_EQ(result, BigInt("11111111100"));
}

TEST_F(BigIntTest, Subtraction) {
    BigInt num1("9876543210");
    BigInt num2("1234567890");
    BigInt result = num1 - num2;
    EXPECT_EQ(result, BigInt("8641975320"));
}

TEST_F(BigIntTest, SubtractionWithNegative) {
    BigInt num1("1234567890");
    BigInt num2("-9876543210");
    BigInt result = num1 - num2;
    EXPECT_EQ(result, BigInt("11111111100"));
}

TEST_F(BigIntTest, Multiplication) {
    BigInt num1("123456");
    BigInt num2("654321");
    BigInt result = num1 * num2;
    EXPECT_EQ(result, BigInt("80779853376"));
}

TEST_F(BigIntTest, MultiplicationWithNegative) {
    BigInt num1("-123456");
    BigInt num2("654321");
    BigInt result = num1 * num2;
    EXPECT_EQ(result, BigInt("-80779853376"));
}

TEST_F(BigIntTest, Equality) {
    BigInt num1("1234567890");
    BigInt num2("1234567890");
    EXPECT_TRUE(num1 == num2);
}

TEST_F(BigIntTest, Inequality) {
    BigInt num1("1234567890");
    BigInt num2("9876543210");
    EXPECT_TRUE(num1 != num2);
}

TEST_F(BigIntTest, Abs) {
    BigInt num("-1234567890");
    BigInt result = num.abs();
    EXPECT_EQ(result, BigInt("1234567890"));
    EXPECT_FALSE(result.is_negative());
}

TEST_F(BigIntTest, IsEven) {
    BigInt num1("1234567890");
    BigInt num2("1234567891");
    EXPECT_TRUE(num1.is_even());
    EXPECT_FALSE(num2.is_even());
}

TEST_F(BigIntTest, MultiplicationWithBasePower) {
    BigInt num("123");
    BigInt base("100000"); 
    BigInt result = num * base * base; 
    EXPECT_EQ(result, BigInt("1230000000000"));
}

TEST_F(BigIntTest, OutputStream) {
    BigInt num("-1234567890");
    std::ostringstream oss;
    oss << num;
    EXPECT_EQ(oss.str(), "-1234567890");
}

TEST_F(BigIntTest, InputStream) {
    std::istringstream iss("1234567890");
    BigInt num;
    iss >> num;
    EXPECT_EQ(num, BigInt("1234567890"));
}

TEST_F(BigIntTest, InputStreamInvalid) {
    std::istringstream iss("abc123");
    BigInt num;
    iss >> num;
    EXPECT_TRUE(iss.fail());
}

TEST_F(BigIntTest, KaratsubaMultiplication) {
    BigInt num1("12345678901234567890");
    BigInt num2("98765432109876543210");
    BigInt result = BigInt::karatsuba_multiply(num1, num2);
    EXPECT_EQ(result, num1 * num2);
}

TEST_F(BigIntTest, DivisionByZero) {
    BigInt num("1234567890");
    BigInt zero("0");
    EXPECT_THROW(num / zero, std::invalid_argument);
}


TEST_F(BigIntTest, LargeNumbers) {
    std::string large(1000, '9');
    BigInt num(large);
    EXPECT_EQ(num.size(), (1000 + 4) / 5); 
}

TEST_F(BigIntTest, ZeroOperations) {
    BigInt zero("0");
    BigInt num("1234567890");
    EXPECT_EQ(num + zero, num);
    EXPECT_EQ(num - zero, num);
    EXPECT_EQ(num * zero, zero);
    EXPECT_THROW(zero / zero, std::invalid_argument);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}