//EXPECT_PTR_XX is needed by windows
//otherwise it throws a compile error while comparing 
//const and non const pointers with Assert::IsSame
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
#define EXPECT_PTR_EQ(x,y) XCTAssertEqual(x,y)
#define EXPECT_PTR_NE(x,y) XCTAssertNotEqual(x,y)
#define EXPECT_PTR_NULL(x) XCTAssertEqual(x,nullptr)
#define EXPECT_PTR_NOTNULL(x) XCTAssertNotEqual(x,nullptr)
#define FAIL() {XCTAssertTrue(false,"Assertion failed!");return;}
#define ASSERT_TRUE(X) if(!X){FAIL();}
#define ASSERT_FALSE(X) if(X){FAIL();}
#define ASSERT_EQ(x,y) if(x!=y){FAIL();}
#define ASSERT_PTR_EQ(x,y) if(x!=y){FAIL();}
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
#define EXPECT_NEAR(x,y,z) Assert::AreEqual(x,y,z)
#define EXPECT_TRUE(x) Assert::IsTrue(x)
#define EXPECT_FALSE(x) Assert::IsFalse(x)
#define EXPECT_EQ(x,y) Assert::AreEqual(x,y)
#define EXPECT_NE(x,y) Assert::AreNotEqual(x,y)
#define EXPECT_GT(x,y) Assert::IsTrue(x>y)
#define EXPECT_GE(x,y) Assert::IsTrue(x>=y)
#define EXPECT_LT(x,y) Assert::IsTrue(x<y)
#define EXPECT_LE(x,y) Assert::IsTrue(x<=y)
#define EXPECT_STREQ(x,y) Assert::AreEqual(strcmp(x,y),0)
#define EXPECT_PTR_EQ(x,y) Assert::IsTrue(x==y)
#define EXPECT_PTR_NE(x,y) Assert::IsFalse(x==y)
#define EXPECT_PTR_NULL(x) Assert::IsNull(x)
#define EXPECT_PTR_NOTNULL(x) Assert::IsNotNull(x)
#define FAIL() Assert::Fail()
#define ASSERT_TRUE(X) if(!X){FAIL();}
#define ASSERT_FALSE(X) if(X){FAIL();}
#define ASSERT_EQ(x,y) if(x!=y){FAIL();}
#define ASSERT_PTR_EQ(x,y) if(x!=y){FAIL();}
#define ASSERT_ANY_THROW(x) try{x;Assert::Fail();}catch(const char* m){}
#else
#define SPECTRE_TEST_INIT(CLASSNAME)
#define SPECTRE_TEST_END(CLASSNAME)
#define SPECTRE_TEST(SUITE_NAME,TEST_NAME) TEST(SUITE_NAME,TEST_NAME)
#define EXPECT_PTR_EQ(x,y) EXPECT_EQ(x,y)
#define EXPECT_PTR_NE(x,y) EXPECT_NE(x,y)
#define EXPECT_PTR_NULL(x) EXPECT_EQ(x,nullptr)
#define EXPECT_PTR_NOTNULL(x) EXPECT_NE(x,nullptr)
#define ASSERT_PTR_EQ(x,y) if(x!=y){FAIL();}
#endif

