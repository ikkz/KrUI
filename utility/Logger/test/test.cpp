#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <Logger.h>

TEST(Logger, AddOutput)
{
    cl::Logger logger;
    EXPECT_TRUE(logger.add_output(std::cout));
    EXPECT_FALSE(logger.add_output(std::cout));
}

TEST(Logger, RemoveOutput)
{
    cl::Logger logger;
    std::ostringstream *poss = new std::ostringstream;
    std::ostringstream &oss = *poss;
    EXPECT_TRUE(logger.add_output(oss));
    EXPECT_FALSE(logger.add_output(oss));
    logger.set_loglevel(cl::Information);
    LOG(logger) << "success to add oss into logger";
    EXPECT_TRUE(logger.remove_output(oss));
    EXPECT_FALSE(logger.remove_output(oss));
    delete poss;
    // EXPECT_ANY_THROW(LOG(logger) << "expect throw");
    //it may not cause an exception, but it's actually wrong.
}

TEST(Logger, OperatorInsert)
{
    std::ostringstream oss1, oss2;
    cl::Logger logger;
    EXPECT_TRUE(logger.add_output(oss1));
    EXPECT_TRUE(logger.add_output(oss2));
    //oss1 and oss2 has the same str()
    logger.set_loglevel(cl::LogLevel::Information);
    LOG(logger) << "LogLevel::Information.";
    EXPECT_TRUE(oss1.str() == oss2.str());

    logger.set_loglevel(cl::LogLevel::Debug);
    LOG(logger) << "LogLevel::Debug.";
    EXPECT_TRUE(oss1.str() == oss2.str());

    logger.set_loglevel(cl::LogLevel::Warning);
    LOG(logger) << "LogLevel::Warning.";
    EXPECT_TRUE(oss1.str() == oss2.str());

    logger.set_loglevel(cl::LogLevel::Error);
    LOG(logger) << "LogLevel::Error.";
    EXPECT_TRUE(oss1.str() == oss2.str());

    logger.set_loglevel(cl::LogLevel::Unkonwn);
    LOG(logger) << "LogLevel::Unkonwn.";
    EXPECT_TRUE(oss1.str() == oss2.str());

    std::cout << "oss1:\n"
              << oss1.str();
    std::cout << "\noss2:\n"
              << oss2.str() << std::endl;
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
