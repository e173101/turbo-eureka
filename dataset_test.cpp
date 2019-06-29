/**
 * test dataset
 * 
 * last update: 2019-06-29
 */

#include <gtest/gtest.h>
#include "dataset.h"
#include <unistd.h>

TEST(DATASET, flags)
{
    char cwd[100];
    getcwd(cwd, 100);
    string cwd_str(cwd);
    DATASET dataset(cwd_str + "/data/");
    vector<int> flags = {
        2051,
        10000,
        28,
        28,
        2049,
        10000,
        2051,
        60000,
        28,
        28,
        2049,
        60000};
    EXPECT_EQ(flags, dataset.flags);

    EXPECT_EQ(7, dataset.test_labels[0]);
    //draw a '7':
    for (int i = 0; i < 1; i++)
    {
        int col = 0;
        for (int j = 0; j < dataset.test_images[0].size(); j++)
        {
            if (0 == dataset.test_images[i][j])
                cout << ' ';
            else
                cout << '@';
            col++;
            if (28 == col)
            {
                col = 0;
                cout << endl;
            }
        }
        cout << endl;
    }

    
    EXPECT_EQ(5, dataset.train_labels[0]);
    
    //draw a '5':
    for (int i = 0; i < 1; i++)
    {
        int col = 0;
        for (int j = 0; j < dataset.train_images[0].size(); j++)
        {
            if (0 == dataset.train_images[i][j])
                cout << ' ';
            else
                cout << '@';
            col++;
            if (28 == col)
            {
                col = 0;
                cout << endl;
            }
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}