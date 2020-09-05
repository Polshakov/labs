#ifndef TST_TESTDIVISIONBYZERO_H
#define TST_TESTDIVISIONBYZERO_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <IKeypad.h>
#include <ILatch.h>
#include <lockcontroller.h>

using namespace testing;

class MockKeypad : public IKeypad{
public:
    MOCK_METHOD(bool, isActive, (), (override));
    MOCK_METHOD(void, wait, (), (override));
    MOCK_METHOD(PasswordResponse, requestPassword, (), (override));
};

class MockLatch : public ILatch{
public:
    MOCK_METHOD(bool, isActive, (), (override));
    MOCK_METHOD(DoorStatus, open, (), (override));
    MOCK_METHOD(DoorStatus, close, (), (override));
    MOCK_METHOD(DoorStatus, getDoorStatus, (), (override));
};

class LockControllerFix : public Test{
public:
    MockKeypad keypad;
    MockLatch latch;
    LockController* lockcont;

    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override{
        lockcont = new LockController(&keypad, &latch);
    }
    void TearDown() override{
        delete lockcont;
    };
};


//test 1
TEST_F(LockControllerFix, wait){
    EXPECT_CALL(keypad, wait())
            .Times(1)
            .WillOnce(Return());

    lockcont->wait();
}

//test 2
TEST_F(LockControllerFix, doorClosed){
    EXPECT_CALL(latch, getDoorStatus())
            .Times(1)
            .WillOnce(Return(DoorStatus::CLOSE));

    bool result = lockcont->isDoorOpen();

    ASSERT_FALSE(result);
}

//test 3
TEST_F(LockControllerFix, doorOpen){
    EXPECT_CALL(latch, getDoorStatus())
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));

    bool result = lockcont->isDoorOpen();

    ASSERT_TRUE(result);
}

//test 4
TEST_F(LockControllerFix, lockWorksOpen){
    EXPECT_CALL(latch, open())
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));

    DoorStatus result = lockcont->unlockDoor();

    ASSERT_EQ(result, DoorStatus::OPEN);
}

//test 5
TEST_F(LockControllerFix, lockWorksClose){
    EXPECT_CALL(latch, close())
            .Times(1)
            .WillOnce(Return(DoorStatus::CLOSE));

    DoorStatus result = lockcont->lockDoor();

    ASSERT_EQ(result, DoorStatus::CLOSE);
}

//test 6
TEST_F(LockControllerFix, equipmentWorks){
    EXPECT_CALL(keypad, isActive())
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(latch, isActive())
            .Times(1)
            .WillOnce(Return(true));

    HardWareStatus result = lockcont->hardWareCheck();

    ASSERT_EQ(result, HardWareStatus::OK);
}

//test 7
TEST_F(LockControllerFix, equipmentDoesntWork){
    delete lockcont;
    lockcont = new LockController(nullptr, &latch);

    EXPECT_CALL(keypad, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(true));
    EXPECT_CALL(latch, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(true));

    HardWareStatus result = lockcont->hardWareCheck();

    ASSERT_EQ(result, HardWareStatus::ERROR);
}

//test 8
TEST_F(LockControllerFix, isLatchNotWork){
        EXPECT_CALL(keypad, isActive())
                .Times(AtLeast(0))
                .WillOnce(Return(true));
        EXPECT_CALL(latch, isActive())
                .Times(AtLeast(0))
                .WillOnce(Return(false));

        HardWareStatus result = lockcont->hardWareCheck();

        ASSERT_EQ(result, HardWareStatus::ERROR);
}

//test 9
TEST_F(LockControllerFix, passwordOK) {
    PasswordResponse passResp;

    passResp.password = "0000";
    passResp.status = PasswordResponse::Status::OK;
    EXPECT_CALL(keypad, requestPassword())
            .Times(1)
            .WillOnce(Return(passResp));

    bool result = lockcont->isCorrectPassword();

    ASSERT_TRUE(result);
}

//test 10
TEST_F(LockControllerFix, passwordWrong) {
    PasswordResponse passResp;

    passResp.password = "3562";
    passResp.status = PasswordResponse::Status::OK;

    EXPECT_CALL(keypad, requestPassword())
            .Times(1)
            .WillOnce(Return(passResp));

    bool result = lockcont->isCorrectPassword();

    ASSERT_FALSE(result);
}

//test 11
TEST_F(LockControllerFix, changePassword){
       PasswordResponse passResp1;
       passResp1.password = "0000";
       passResp1.status = PasswordResponse::Status::OK;

       PasswordResponse passResp2;
       passResp2.password = "3562";
       passResp2.status = PasswordResponse::Status::OK;

       PasswordResponse passResp3;
       passResp3.password = "3562";
       passResp3.status = PasswordResponse::Status::OK;

       EXPECT_CALL(keypad, requestPassword())
               .Times(3)
               .WillOnce(Return(passResp1))
               .WillOnce(Return(passResp2))
               .WillOnce(Return(passResp3));

       lockcont->resetPassword();
       bool result = lockcont->isCorrectPassword();

       ASSERT_TRUE(result);
}

//test 12
TEST_F(LockControllerFix, changePassword2){
        PasswordResponse passResp1;
        passResp1.password = "0000";
        passResp1.status = PasswordResponse::Status::OK;

        PasswordResponse passResp2;
        passResp2.password = "9876";
        passResp2.status = PasswordResponse::Status::OK;

        PasswordResponse passResp3;
        passResp3.password = "9876";
        passResp3.status = PasswordResponse::Status::OK;

        PasswordResponse passResp4;
        passResp4.password = "3562";
        passResp4.status = PasswordResponse::Status::OK;

        PasswordResponse passResp5;
        passResp5.password = "3562";
        passResp5.status = PasswordResponse::Status::OK;

        EXPECT_CALL(keypad, requestPassword())
                .Times(5)
                .WillOnce(Return(passResp1))
                .WillOnce(Return(passResp2))
                .WillOnce(Return(passResp3))
                .WillOnce(Return(passResp4))
                .WillOnce(Return(passResp5));

        lockcont->resetPassword();
        lockcont->resetPassword();
        bool result = lockcont->isCorrectPassword();

        ASSERT_TRUE(result);
}

#endif // TST_TESTDIVISIONBYZERO_H
