#include "gmock/gmock.h"
#include <Mock/ResultManager.hpp>

using namespace ::testing;
using SUT = ::Mock::ResultManager;

TEST(ResultManagerTest, testTestSuccess) {
  SUT sut;
  sut.beginInit();
  sut.addString("expected");
  sut.endInit();
  sut.beginTest();
  sut.addString("expected");
  sut.endTest();

  ASSERT_THAT(sut.succeed(), Eq(true));
}

TEST(ResultManagerTest, testTestFailed) {
  SUT sut;
  sut.beginInit();
  sut.addString("expected");
  sut.endInit();
  sut.beginTest();
  sut.addString("result");
  sut.endTest();

  ASSERT_THAT(sut.succeed(), Eq(false));
}

TEST(ResultManagerTest, testWrongExpected) {
  SUT sut;
  sut.beginInit();
  sut.addString(":expected");
  sut.endInit();
  sut.beginTest();
  sut.addString("expected");
  sut.endTest();

  ASSERT_THAT(sut.succeed(), Eq(false));
}
