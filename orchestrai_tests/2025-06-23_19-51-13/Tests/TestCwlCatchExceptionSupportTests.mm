#import <XCTest/XCTest.h>
#import "CwlCatchException.h"

@interface TestCwlCatchExceptionSupport : XCTestCase
@end

@implementation TestCwlCatchExceptionSupport

- (void)testCatchExceptionOfKind {
    NSException *exception = catchExceptionOfKind([NSException class], ^{
        @throw [NSException exceptionWithName:NSInvalidArgumentException reason:@"Test exception" userInfo:nil];
    });
    XCTAssertNotNil(exception);
    XCTAssertTrue([exception isKindOfClass:[NSException class]]);
    XCTAssertEqualObjects(exception.name, NSInvalidArgumentException);
}

- (void)testCatchExceptionOfWrongKind {
    XCTAssertThrows(catchExceptionOfKind([NSRangeException class], ^{
        @throw [NSException exceptionWithName:NSInvalidArgumentException reason:@"Test exception" userInfo:nil];
    }));
}

@end