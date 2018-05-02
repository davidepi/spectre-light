#ifdef __XCODE__
#define SPECTRE_TEST_INIT(CLASSNAME) \
@interface CLASSNAME : XCTestCase  \
@end                               \
@implementation CLASSNAME
#define SPECTRE_TEST_END(CLASSNAME) @end
#define SPECTRE_TEST(SUITE_NAME,TEST_NAME) \
- (void)test_ ## SUITE_NAME ## _ ## TEST_NAME
#define EXPECT_NEAR(x,y,z) XCTAssertEqualWithAccuracy(x,y,z)
#define EXPECT_TRUE(x) XCTAssertTrue(x)
#define EXPECT_FALSE(x) XCTAssertFalse(x)
#define EXPECT_EQ(x,y) XCTAssertEqual(x,y)
#define EXPECT_NE(x,y) XCTAssertNotEqual(x,y)
#define EXPECT_GT(x,y) XCTAssertGreaterThan(x,y)
#define EXPECT_GE(x,y) XCTAssertGreaterThanOrEqual(x,y)
#define EXPECT_LT(x,y) XCTAssertLessThan(x,y)
#define EXPECT_LE(x,y) XCTAssertLessThanOrEqual(x,y)
#define EXPECT_STREQ(x,y) XCTAssertEqual(strcmp(x,y),0)
#define FAIL() {XCTAssertTrue(false);return;}
#define ASSERT_TRUE(X) if(!X){FAIL();}
#define ASSERT_FALSE(X) if(X){FAIL();}
#define ASSERT_EQ(x,y) if(x!=y){FAIL();}
#define ASSERT_ANY_THROW(x); try{x;XCTAssertTrue(false);}catch(const char* m){}
#elif defined(__VS__)
#define SPECTRE_TEST_INIT(CLASSNAME) \
using namespace Microsoft::VisualStudio::CppUnitTestFramework; \
namespace tests \
{ \
    TEST_CLASS( CLASSNAME )\
    { \
    public:
#define SPECTRE_TEST_END(CLASSNAME) };}
#define SPECTRE_TEST(SUITE_NAME,TEST_NAME) TEST_METHOD(TEST_NAME)
#define EXPECT_EQ(x,y) Assert::AreEqual(x,y)
#else
#define SPECTRE_TEST_INIT(CLASSNAME)
#define SPECTRE_TEST_END(CLASSNAME)
#define SPECTRE_TEST(SUITE_NAME,TEST_NAME) TEST(SUITE_NAME,TEST_NAME)
#endif

