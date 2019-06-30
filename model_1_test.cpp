#include <gtest/gtest.h>
#include <unistd.h>

#include "dataset.h"
#include "model_1.h"

using namespace std;

TEST(model, v1)
{
    char cwd[100];
    getcwd(cwd, 100);
    string cwd_str(cwd);
    DATASET dataset(cwd_str + "/data/");

    int bingo_cnt = 0;
    for (int i = 0; i < dataset.test_images.size(); i++)
        if (dataset.test_labels[i] == model_1(dataset.test_images[i].data()))
            bingo_cnt++;

    cout << "Correct count:" << bingo_cnt << endl;

    EXPECT_TRUE(0.5 < 1.0 * bingo_cnt / dataset.test_labels.size());
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}