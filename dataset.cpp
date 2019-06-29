/**
 * @brief: read dataset
 * 把mnist的数据整只读到内存里
 * last update: 2019-06-29
 */

#include "dataset.h"

DATASET::DATASET(string path)
{
    readImages(path + "t10k-images-idx3-ubyte", test_images);
    readLabels(path + "t10k-labels-idx1-ubyte", test_labels);
    readImages(path + "train-images-idx3-ubyte", train_images);
    readLabels(path + "train-labels-idx1-ubyte", train_labels);
}

int DATASET::reverseInt(int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

void DATASET::readLabels(string filename, vector<int> &labels)
{
    ifstream file(filename, ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        file.read((char *)&magic_number, sizeof(magic_number));
        file.read((char *)&number_of_images, sizeof(number_of_images));
        magic_number = reverseInt(magic_number);
        number_of_images = reverseInt(number_of_images);

        flags.push_back(magic_number);
        flags.push_back(number_of_images);
        // cout << "magic number = " << magic_number << endl;
        // cout << "number of images = " << number_of_images << endl;

        for (int i = 0; i < number_of_images; i++)
        {
            unsigned char label = 0;
            file.read((char *)&label, sizeof(label));
            labels.push_back((unsigned char)label);
        }
    }
    else
        cout << "Can't open file: " << filename << endl;
}

void DATASET::readImages(string filename, vector<vector<unsigned char>> &images)
{
    ifstream file(filename, ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        unsigned char label;
        file.read((char *)&magic_number, sizeof(magic_number));
        file.read((char *)&number_of_images, sizeof(number_of_images));
        file.read((char *)&n_rows, sizeof(n_rows));
        file.read((char *)&n_cols, sizeof(n_cols));
        magic_number = reverseInt(magic_number);
        number_of_images = reverseInt(number_of_images);
        n_rows = reverseInt(n_rows);
        n_cols = reverseInt(n_cols);

        flags.push_back(magic_number);
        flags.push_back(number_of_images);
        flags.push_back(n_rows);
        flags.push_back(n_cols);
        // cout << "magic number = " << magic_number << endl;
        // cout << "number of images = " << number_of_images << endl;
        // cout << "rows = " << n_rows << endl;
        // cout << "cols = " << n_cols << endl;

        for (int i = 0; i < number_of_images; i++)
        {
            vector<unsigned char> tp;
            for (int r = 0; r < n_rows; r++)
            {
                for (int c = 0; c < n_cols; c++)
                {
                    unsigned char image = 0;
                    file.read((char *)&image, sizeof(image));
                    tp.push_back(image);
                }
            }
            images.push_back(tp);
        }
    }
    else
        cout << "Can't open file: " << filename << endl;
}
