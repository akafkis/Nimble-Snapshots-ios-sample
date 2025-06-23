#import <XCTest/XCTest.h>
#import "ForgeriesApplication.h"

@interface TestForgeriesApplication : XCTestCase
@end

@implementation TestForgeriesApplication

- (void)testStatusBarHiddenGetSet {
    ForgeriesApplication *app = [[ForgeriesApplication alloc] init];
    XCTAssertFalse(app.isStatusBarHidden);

    app.statusBarHidden = YES;
    XCTAssertTrue(app.isStatusBarHidden);
    XCTAssertTrue(app.statusBarHidden);
}

- (void)testSetStatusBarHiddenWithAnimation {
    ForgeriesApplication *app = [[ForgeriesApplication alloc] init];
    [app setStatusBarHidden:YES withAnimation:UIStatusBarAnimationFade];
    XCTAssertTrue(app.isStatusBarHidden);
}

@end