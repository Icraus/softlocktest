#include <QtTest>
#include <softcrypto.h>
// add necessary includes here

class TestCrypto : public QObject
{
    Q_OBJECT

public:
    TestCrypto();
    ~TestCrypto();

private slots:
    void testEncrpyt();
    void testDecrpyt();

};

TestCrypto::TestCrypto()
{

}

TestCrypto::~TestCrypto()
{

}

void TestCrypto::testEncrpyt()
{
    auto cryptoInstance = Crypto::getInstance();
    auto key = std::string("01234567890123456789012345678901");

    auto iv = std::string("0123456789012345");
    auto output = cryptoInstance.encrypt("Hello World", key, iv);
    auto dec = cryptoInstance.decrypt(output, key, iv);
    qDebug() << QString(dec.c_str()) << Qt::endl;
    QVERIFY("Hello World" ==  dec);

}

void TestCrypto::testDecrpyt()
{

}

QTEST_APPLESS_MAIN(TestCrypto)

#include "tst_testcrypto.moc"
