#include "gtest/gtest.h"
#include <StringParser.h>

TEST(string_parser_suite, hasANumber_test) {
    StringParser p1("This is a string without any number.");
    StringParser p2("There are two hundred dogs in the kennel.");
    StringParser p3("My friend has more than two million in his account.");
    StringParser p4("Fly like a butterfly sting like a bee");
    StringParser p5("One dog is ok.");

    EXPECT_FALSE(p1.hasANumber());
    EXPECT_TRUE (p2.hasANumber());
    EXPECT_TRUE (p3.hasANumber());
    EXPECT_FALSE(p4.hasANumber());
    EXPECT_TRUE (p5.hasANumber());
}

TEST(string_parser_suite, negativeCasesSameString_test)
{
    StringParser p1("In these strings there are no word numbers");
    StringParser p2("Coronavirus is something a bit scary but has low mortality");
    StringParser p3("If I say can't touch this will you know what song I am referring to?");

    EXPECT_EQ (p1.getStringWithNumbers(), "In these strings there are no word numbers");
    EXPECT_EQ (p2.getStringWithNumbers(), "Coronavirus is something a bit scary but has low mortality");
    EXPECT_EQ (p3.getStringWithNumbers(), "If I say can't touch this will you know what song I am referring to?");
}

TEST(string_parser_suite, onesCases_test)
{
    StringParser p1("One one go");
    StringParser p2("Two dogs travel around the world");
    StringParser p3("There are five people in the queue.");
    StringParser p4("Last time I become the guy with fifty-two oranges that is in the math books.");
    StringParser p5("One nine should be translated to separated numbers");
    StringParser p6("four forty-four should also be translated to separated numbers");
    //StringParser p7("One and one go");

    EXPECT_EQ(p1.getStringWithNumbers(),"1 1 go");
    EXPECT_EQ(p2.getStringWithNumbers(),"2 dogs travel around the world");
    EXPECT_EQ(p3.getStringWithNumbers(),"There are 5 people in the queue.");
    EXPECT_EQ(p4.getStringWithNumbers(),"Last time I become the guy with 52 oranges that is in the math books.");
    EXPECT_EQ(p5.getStringWithNumbers(),"1 9 should be translated to separated numbers");
    EXPECT_EQ(p6.getStringWithNumbers(),"4 44 should also be translated to separated numbers");
    //EXPECT_EQ(p7.getStringWithNumbers(),"1 and 1 go");
}

TEST(string_parser_suite, teensCases_test)
{
    StringParser p1("Eleven");
    StringParser p2("I love to say nine eleven");
    StringParser p3("My little cousin is seventeen years old.");

    EXPECT_EQ(p1.getStringWithNumbers(),"11");
    EXPECT_EQ(p2.getStringWithNumbers(),"I love to say 9 11");
    EXPECT_EQ(p3.getStringWithNumbers(),"My little cousin is 17 years old.");
}

TEST(string_parser_suite, tensCases_test)
{
    StringParser p1("Eighty-nine");
    StringParser p2("My grandpa is ninety-two years old");
    StringParser p3("four eleven thirty-three");

    EXPECT_EQ(p1.getStringWithNumbers(),"89");
    EXPECT_EQ(p2.getStringWithNumbers(),"My grandpa is 92 years old");
    EXPECT_EQ(p3.getStringWithNumbers(),"4 11 33");
}

TEST(string_parser_suite, hundredCases_test)
{
    StringParser p1("seven hundred");
    StringParser p2("nine thousand and two");
    StringParser p3("twenty hundred and fifty-nine");
    StringParser p4("seven thousand four hundred and fifteen");
    StringParser p5("fifty million twenty thousand five hundred and twenty-four");
    StringParser p6("twelve thousand and forty-seven");
    StringParser p7("seven hundred million");
    StringParser p8("five million million");
    
    EXPECT_EQ(p1.getStringWithNumbers(),"700");
    EXPECT_EQ(p2.getStringWithNumbers(),"9002");
    EXPECT_EQ(p3.getStringWithNumbers(),"2059");
    EXPECT_EQ(p4.getStringWithNumbers(),"7415");
    EXPECT_EQ(p5.getStringWithNumbers(),"50020524");
    EXPECT_EQ(p6.getStringWithNumbers(),"12047");
    EXPECT_EQ(p7.getStringWithNumbers(), "700000000");
    EXPECT_EQ(p8.getStringWithNumbers(), "5000000 million");
}

