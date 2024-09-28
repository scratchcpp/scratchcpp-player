#include <QApplication>
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    a.setApplicationName("ScratchCPP Player");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
