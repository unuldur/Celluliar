#include <QtTest>

// add necessary includes here
#include "../App/TreeUniverse.h"
class TestHashLife : public QObject
{
    Q_OBJECT

public:
    TestHashLife();
    ~TestHashLife();

private slots:
    void test_case1();
    void test_case2();
    void test_case3();
    void test_case4();
};

TestHashLife::TestHashLife()
{

}

TestHashLife::~TestHashLife()
{

}

void TestHashLife::test_case1()
{
    TreeUniverse tu;
    tu.setByte(0, 0);
    tu.setByte(1, 0);
    tu.setByte(0, 1);
    tu.setByte(1, 1);
    QVERIFY(tu.getByte(0, 0) == 1);
    QVERIFY(tu.getByte(0, 1) == 1);
    QVERIFY(tu.getByte(1, 0) == 1);
    QVERIFY(tu.getByte(1, 1) == 1);
    tu.runStep();
    QVERIFY(tu.getByte(0, 0) == 1);
    QVERIFY(tu.getByte(0, 1) == 1);
    QVERIFY(tu.getByte(1, 0) == 1);
    QVERIFY(tu.getByte(1, 1) == 1);
    TreeNode::initHash();
}


void TestHashLife::test_case4()
{
    TreeUniverse tu;
    tu.setByte(1000,1000);
    tu.setByte(1001, 1000);
    tu.setByte(1000, 1001);
    tu.setByte(1001, 1001);
    QVERIFY(tu.getByte(1000, 1000) == 1);
    QVERIFY(tu.getByte(1000, 1001) == 1);
    QVERIFY(tu.getByte(1001, 1000) == 1);
    QVERIFY(tu.getByte(1001, 1001) == 1);
    tu.runStep();
    QVERIFY(tu.getByte(1000, 1000) == 1);
    QVERIFY(tu.getByte(1000, 1001) == 1);
    QVERIFY(tu.getByte(1001, 1000) == 1);
    QVERIFY(tu.getByte(1001, 1001) == 1);
    TreeNode::initHash();
}

void TestHashLife::test_case2()
{
    TreeUniverse tu;
    tu.setByte(0, 0);
    tu.setByte(1, 0);
    tu.setByte(2, 0);
    QVERIFY(tu.getByte(0, 0) == 1);
    QVERIFY(tu.getByte(1, 0) == 1);
    QVERIFY(tu.getByte(2, 0) == 1);
    tu.runStep();
    QVERIFY(tu.getByte(0, 0) == 0);
    QVERIFY(tu.getByte(1, 0) == 1);
    QVERIFY(tu.getByte(2, 0) == 0);
    QVERIFY(tu.getByte(1, -1) == 1);
    QVERIFY(tu.getByte(1, 1) == 1);
    TreeNode::initHash();
}

void TestHashLife::test_case3()
{
    TreeUniverse tu;
    tu.setByte(0, 0);
    tu.setByte(1, 0);
    tu.setByte(2, 0);
    TreeNode::initHash();
}

QTEST_APPLESS_MAIN(TestHashLife)

#include "tst_testhashlife.moc"
