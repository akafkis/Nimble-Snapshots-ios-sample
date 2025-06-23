#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CwlMachBadInstructionHandler.h"
#include "mach_excServer.h"

using namespace ::testing;

class TestCwlMachBadInstructionHandler : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test environment if needed
    }

    void TearDown() override {
        // Clean up test environment if needed
    }
};

TEST_F(TestCwlMachBadInstructionHandler, TestCatchMachExceptionRaise) {
    mach_port_t exception_port = MACH_PORT_NULL;
    mach_port_t thread = MACH_PORT_NULL;
    mach_port_t task = MACH_PORT_NULL;
    exception_type_t exception = EXC_BAD_INSTRUCTION;
    mach_exception_data_t code = {0, 0};
    mach_msg_type_number_t codeCnt = 0;

    EXPECT_CALL(BadInstructionException, receiveReply(_))
        .Times(1)
        .WillOnce(Return(KERN_SUCCESS));

    kern_return_t result = catch_mach_exception_raise(exception_port, thread, task, exception, code, codeCnt);
    ASSERT_EQ(result, KERN_SUCCESS);
}

TEST_F(TestCwlMachBadInstructionHandler, TestCatchMachExceptionRaiseState) {
    mach_port_t exception_port = MACH_PORT_NULL;
    exception_type_t exception = EXC_BAD_INSTRUCTION;
    mach_exception_data_t code = {0, 0};
    mach_msg_type_number_t codeCnt = 0;
    int flavor = 0;
    thread_state_t old_state = nullptr;
    mach_msg_type_number_t old_stateCnt = 0;
    thread_state_t new_state = nullptr;
    mach_msg_type_number_t new_stateCnt = 0;

    EXPECT_CALL(BadInstructionException, receiveReply(_))
        .Times(1)
        .WillOnce(Return(KERN_SUCCESS));

    kern_return_t result = catch_mach_exception_raise_state(exception_port, exception, code, codeCnt, &flavor, old_state, old_stateCnt, new_state, &new_stateCnt);
    ASSERT_EQ(result, KERN_SUCCESS);
}

TEST_F(TestCwlMachBadInstructionHandler, TestCatchMachExceptionRaiseStateIdentity) {
    mach_port_t exception_port = MACH_PORT_NULL;
    mach_port_t thread = MACH_PORT_NULL;
    mach_port_t task = MACH_PORT_NULL;
    exception_type_t exception = EXC_BAD_INSTRUCTION;
    mach_exception_data_t code = {0, 0};
    mach_msg_type_number_t codeCnt = 0;
    int flavor = 0;
    thread_state_t old_state = nullptr;
    mach_msg_type_number_t old_stateCnt = 0;
    thread_state_t new_state = nullptr;
    mach_msg_type_number_t new_stateCnt = 0;

    EXPECT_CALL(BadInstructionException, receiveReply(_))
        .Times(1)
        .WillOnce(Return(KERN_FAILURE));

    kern_return_t result = catch_mach_exception_raise_state_identity(exception_port, thread, task, exception, code, codeCnt, &flavor, old_state, old_stateCnt, new_state, &new_stateCnt);
    ASSERT_EQ(result, KERN_FAILURE);
}

TEST_F(TestCwlMachBadInstructionHandler, TestMachNdrRecord) {
    NDR_record_t ndr = mach_ndr_record();
    ASSERT_EQ(ndr, NDR_record);
}