#include <gtest/gtest.h>

extern "C" {
    #include "func.h"
    #include "array.h"
}

// TEST(ElementTest, CreateInt) {
//     Element* elem = create("int");
//     EXPECT_NE(elem, nullptr);
//     EXPECT_NE(elem->number, nullptr);
//     EXPECT_EQ(elem->size, sizeof(int));
//     if (elem->type_info && elem->type_info->destroy) {
//         elem->type_info->destroy(elem);
//     }
// }

// TEST(ElementTest, CreateFloat) {
//     Element* elem = create("float");
//     EXPECT_NE(elem, nullptr);
//     EXPECT_NE(elem->number, nullptr);
//     EXPECT_EQ(elem->size, sizeof(float));
//     if (elem->type_info && elem->type_info->destroy) {
//         elem->type_info->destroy(elem);
//     }
// }

TEST(ElementTest, )

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}