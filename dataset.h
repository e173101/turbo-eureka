/**
 * @brief: 获取四组数据：
 * train images + train labels + test images + test lables
 * last update: 2019-06-29
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class DATASET
{
public:
    DATASET(string path);
    vector<vector<unsigned char>> train_images;
    vector<int> train_labels;
    vector<vector<unsigned char>> test_images;
    vector<int> test_labels;

    vector<int> flags;  //just for test dataset

private:
    int reverseInt(int i);
    void readLabels(string filename, vector<int> &labels);
    void readImages(string filename, vector<vector<unsigned char>> &images);
};