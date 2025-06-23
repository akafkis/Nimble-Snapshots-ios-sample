#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ForgeriesFileManager.h"

using namespace ::testing;

class TestForgeriesFileManager : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test environment if needed
    }

    void TearDown() override {
        // Clean up test environment if needed
    }
};

TEST_F(TestForgeriesFileManager, TestWithFileStringMap) {
    NSDictionary<NSString *, id> *fileMap = @{
        @"/app/file.txt": @"Hello, World!",
        @"/docs/data.json": @{ @"key": @"value" }
    };
    ForgeriesFileManager *fileManager = [ForgeriesFileManager withFileStringMap:fileMap];

    ASSERT_EQ(fileManager.fileMap.count, 2);

    ForgeryFile *file1 = fileManager.fileMap[@"/app/file.txt"];
    ASSERT_EQ(file1.path, @"/app/file.txt");
    ASSERT_THAT(file1.data, ElementsAreArray({0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x2C, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21}));

    ForgeryFile *file2 = fileManager.fileMap[@"/docs/data.json"];
    ASSERT_EQ(file2.path, @"/docs/data.json");
    ASSERT_THAT(file2.data, ElementsAreArray({0x7B, 0x0A, 0x20, 0x20, 0x22, 0x6B, 0x65, 0x79, 0x22, 0x3A, 0x20, 0x22, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x22, 0x0A, 0x7D}));
}

TEST_F(TestForgeriesFileManager, TestFilesMatchingPath) {
    NSDictionary<NSString *, id> *fileMap = @{
        @"/app/file1.txt": @"Hello",
        @"/app/file2.txt": @"World",
        @"/docs/data.json": @{ @"key": @"value" }
    };
    ForgeriesFileManager *fileManager = [ForgeriesFileManager withFileStringMap:fileMap];

    NSArray<ForgeryFile *> *files = [fileManager filesMatchingPath:@"/app/file"];
    ASSERT_EQ(files.count, 2);
    ASSERT_EQ(files[0].path, @"/app/file1.txt");
    ASSERT_EQ(files[1].path, @"/app/file2.txt");
}

TEST_F(TestForgeriesFileManager, TestUrlsForFiles) {
    NSDictionary<NSString *, id> *fileMap = @{
        @"/app/file.txt": @"Hello, World!"
    };
    ForgeriesFileManager *fileManager = [ForgeriesFileManager withFileStringMap:fileMap];

    ForgeryFile *file = fileManager.fileMap[@"/app/file.txt"];
    NSArray<NSURL *> *urls = [fileManager urlsForFiles:@[file]];
    ASSERT_EQ(urls.count, 1);
    ASSERT_EQ(urls[0].path, @"/app/file.txt");
}

TEST_F(TestForgeriesFileManager, TestFileExistsAtPath) {
    NSDictionary<NSString *, id> *fileMap = @{
        @"/app/file.txt": @"Hello, World!"
    };
    ForgeriesFileManager *fileManager = [ForgeriesFileManager withFileStringMap:fileMap];

    ASSERT_TRUE([fileManager fileExistsAtPath:@"/app/file.txt"]);
    ASSERT_FALSE([fileManager fileExistsAtPath:@"/app/missing.txt"]);
}

TEST_F(TestForgeriesFileManager, TestContentsAtPath) {
    NSDictionary<NSString *, id> *fileMap = @{
        @"/app/file.txt": @"Hello, World!"
    };
    ForgeriesFileManager *fileManager = [ForgeriesFileManager withFileStringMap:fileMap];

    NSData *contents = [fileManager contentsAtPath:@"/app/file.txt"];
    ASSERT_THAT(contents, ElementsAreArray({0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x2C, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21}));
}