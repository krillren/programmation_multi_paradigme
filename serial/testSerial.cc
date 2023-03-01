#include "Serial.h"
#include <fstream>
#include <iostream>
#include <gtest/gtest.h>

const char *t_filename = "Testing/Temporary/serial_test.bin";
const char *t_filename2 = "Testing/Temporary/serial_test2.bin";

std::byte data_sample[10] = {std::byte(0x00), std::byte(0x01), std::byte(0x02), std::byte(0x03), std::byte(0x04),
                             std::byte(0x05), std::byte(0x06), std::byte(0x07), std::byte(0x08), std::byte(0x09)};
std::size_t data_sample_size = 10;

void print_bytes(std::byte *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        std::cout << std::hex << (int) arr[i] << " ";
    }
    std::cout << std::endl;
}


/*
 * test OBinaryFile
 */


template<typename T>
void expect_equal(T *arr1, T *arr2, size_t size) {
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(arr1[i], arr2[i]);
    }
}

template<typename T>
void expect_to_be_in(T *arr1, size_t size, std::string file) {
    T buff[size];
    std::ifstream f(file);
    if (!f.is_open()) {
        std::cout << "failed to open file";
        exit(1);
    }

    f.read((char *) buff, size * sizeof(T));
    expect_equal(arr1, buff, size);
}


// test Obinaryfile move constructor
TEST(test_obinaryfile, move) {
    {
        serial::OBinaryFile f1(t_filename);
        serial::OBinaryFile f2 = std::move(f1); // Call the Constructor not the assignment operator
        serial::OBinaryFile f3(t_filename2);
        f3 = std::move(f2); // assignment operator

        f3.write(data_sample, data_sample_size);
    }
    expect_to_be_in(data_sample, data_sample_size, t_filename);

}

// test Obinaryfile move assignment
TEST(test_obinaryfile, move_assignment) {
    {
        serial::OBinaryFile f1(t_filename);
        serial::OBinaryFile f2(t_filename2);
        f2 = std::move(f1); // assignment operator

        f2.write(data_sample, data_sample_size);
    }
    expect_to_be_in(data_sample, data_sample_size, t_filename);
}

// test write
TEST(test_obinaryfile, write) {
    {
        serial::OBinaryFile f1(t_filename);
        f1.write(data_sample, data_sample_size);
    }
    expect_to_be_in(data_sample, data_sample_size, t_filename);
}
//test int8_t
TEST(test_obinaryfile, write_int8_t) {
    int8_t data = 0x01;
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    expect_to_be_in(&data, 1, t_filename);
}
//test int16_t
TEST(test_obinaryfile, write_int16_t) {
    int16_t data = 0x0102;
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    expect_to_be_in(&data, 1, t_filename);
}
//test int32_t
TEST(test_obinaryfile, write_int32_t) {
    int32_t data = 0x01020304;
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    expect_to_be_in(&data, 1, t_filename);
}
//test int64_t
TEST(test_obinaryfile, write_int64_t) {
    int64_t data = 0x0102030405060708;
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    expect_to_be_in(&data, 1, t_filename);
}
//test uint8_t
TEST(test_obinaryfile, write_uint8_t) {
    uint8_t data = 0x01;
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    expect_to_be_in(&data, 1, t_filename);
}
//test uint16_t
TEST(test_obinaryfile, write_uint16_t) {
    uint16_t data = 0x0102;
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    expect_to_be_in(&data, 1, t_filename);
}
//test uint32_t
TEST(test_obinaryfile, write_uint32_t) {
    uint32_t data = 0x01020304;
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    expect_to_be_in(&data, 1, t_filename);
}
//test uint64_t
TEST(test_obinaryfile, write_uint64_t) {
    uint64_t data = 0x0102030405060708;
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    expect_to_be_in(&data, 1, t_filename);
}
//test float
TEST(test_obinaryfile, write_float) {
    float data = 0.1;
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    expect_to_be_in(&data, 1, t_filename);
}
//test double
TEST(test_obinaryfile, write_double) {
    double data = 0.1;
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    expect_to_be_in(&data, 1, t_filename);
}
//test bool
TEST(test_obinaryfile, write_bool) {
    bool data = true;
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    expect_to_be_in(&data, 1, t_filename);
}
//test char
TEST(test_obinaryfile, write_char) {
    char data = 'a';
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    expect_to_be_in(&data, 1, t_filename);
}
//test string
TEST(test_obinaryfile, write_string) {
    std::string data = "coucou";
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    std::ifstream f(t_filename);
    if (!f.is_open()) {
        std::cout << "failed to open file";
        exit(1);
    }
    size_t size;

    std::string buff;
    f.read((char *) &size, sizeof(size_t));
    buff.resize(size);

    f >> buff;

    EXPECT_EQ(data, buff);
}
//test vector
TEST(test_obinaryfile, write_vector) {
    std::vector<int> data = {1, 2, 3, 4, 5};
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    std::ifstream f(t_filename);
    if (!f.is_open()) {
        std::cout << "failed to open file";
        exit(1);
    }
    size_t size;
    std::vector<int> result;
    f.read((char *) &size, sizeof(size_t));
    result.resize(size);

    f.read((char *) result.data(), static_cast<std::streamsize>(size * sizeof(int)));

    EXPECT_EQ(data, result);
}
//test map
TEST(test_obinaryfile, write_map) {
    std::map<int, int> data = {{1, 2},
                               {3, 4},
                               {5, 6}};
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    std::ifstream f(t_filename);
    if (!f.is_open()) {
        std::cout << "failed to open file";
        exit(1);
    }
    size_t size;
    std::map<int, int> result;
    f.read((char *) &size, sizeof(size_t));
    for (size_t i = 0; i < size; ++i) {
        int key;
        int value;
        f.read((char *) &key, sizeof(int));
        f.read((char *) &value, sizeof(int));
        result[key] = value;
    }

    EXPECT_EQ(data, result);
}
//test array
TEST(test_obinaryfile, write_array) {
    std::array data = {1, 2, 3, 4, 5};
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    std::ifstream f(t_filename);
    if (!f.is_open()) {
        std::cout << "failed to open file";
        exit(1);
    }
    size_t size;
    std::array result = {0, 0, 0, 0, 0};
    f.read((char *) &size, sizeof(size_t));

    f.read((char *) result.data(), static_cast<std::streamsize>(size * sizeof(int)));

    EXPECT_EQ(data, result);
}
//test set
TEST(test_obinaryfile, write_set) {
    std::set<int> data = {1, 2, 3, 4, 5};
    {
        serial::OBinaryFile f1(t_filename);
        f1 << data;
    }
    std::ifstream f(t_filename);
    if (!f.is_open()) {
        std::cout << "failed to open file";
        exit(1);
    }
    size_t size;
    std::set<int> result;
    f.read((char *) &size, sizeof(size_t));

    for (size_t i = 0; i < size; ++i) {
        int value;
        f.read((char *) &value, sizeof(int));
        result.insert(value);
    }

    EXPECT_EQ(data, result);
}






/*
 * test for IBinaryFile
 */
template<typename T>
void write_data(T *data,size_t size, std::string file) {
    std::ofstream f(file,std::ios::binary| std::ios::out);
    if (!f.is_open()) {
        std::cout << "failed to open file";
        exit(1);
    }
    f.write(reinterpret_cast<char*>(data), (std::streamsize)(size * sizeof(T)));
    f.close();
}

template<typename T>
void expect_to_read(T *data,size_t size, std::string file) {
    serial::IBinaryFile f1(file);
    T result[10];
    for(size_t i = 0; i < size; ++i) {
        f1 >> result[i];
        EXPECT_EQ(data[i], result[i]);
    }
}
//test move constructor
TEST(test_ibinaryfile, move_constructor) {
    int data = 1;
    write_data(&data, 1, t_filename);

    serial::IBinaryFile f1(t_filename);
    serial::IBinaryFile f2 = std::move(f1); // Call the Constructor not the assignment operator
    serial::IBinaryFile f3(t_filename2);
    f3 = std::move(f2); // assignment operator

    expect_to_read(&data,1, t_filename);
}
// test IBinaryfile move assignment
TEST(test_ibinaryfile, move_assignment) {
    int data = 1;
    write_data(&data, 1, t_filename);

    serial::IBinaryFile f1(t_filename);
    serial::IBinaryFile f2(t_filename2);
    f2 = std::move(f1); // assignment operator

    expect_to_read(&data,1,t_filename);
}

//test read
TEST(test_ibinaryfile, read) {
    int data = 1;
    write_data(&data, 1, t_filename);
    serial::IBinaryFile f1(t_filename);
    int result;
    f1.read((std::byte*)&result, sizeof(int));
    EXPECT_EQ(data, result);
}
//test int8_t
TEST(test_ibinaryfile, read_int8_t) {
    int8_t data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    write_data(data, 10, t_filename);
    expect_to_read(data,10, t_filename);
}

//test int16_t
TEST(test_ibinaryfile, read_int16_t) {
    int16_t data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    write_data(data, 10, t_filename);
    expect_to_read(data,10, t_filename);
}

//test int32_t
TEST(test_ibinaryfile, read_int32_t) {
    int32_t data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    write_data(data, 10, t_filename);
    expect_to_read(data,10, t_filename);
}

//test int64_t
TEST(test_ibinaryfile, read_int64_t) {
    int64_t data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    write_data(data, 10, t_filename);
    expect_to_read(data,10, t_filename);
}

//test uint8_t
TEST(test_ibinaryfile, read_uint8_t) {
    uint8_t data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    write_data(data, 10, t_filename);
    expect_to_read(data,10, t_filename);
}

//test uint16_t
TEST(test_ibinaryfile, read_uint16_t) {
    uint16_t data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    write_data(data, 10, t_filename);
    expect_to_read(data,10, t_filename);
}

//test uint32_t
TEST(test_ibinaryfile, read_uint32_t) {
    uint32_t data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    write_data(data, 10, t_filename);
    expect_to_read(data,10, t_filename);
}

//test uint64_t
TEST(test_ibinaryfile, read_uint64_t) {
    uint64_t data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    write_data(data, 10, t_filename);
    expect_to_read(data,10, t_filename);
}

//test float
TEST(test_ibinaryfile, read_float) {
    float data[10] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10};
    write_data(data, 10, t_filename);
    expect_to_read(data,10, t_filename);
}

//test double
TEST(test_ibinaryfile, read_double) {
    double data[10] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10};
    write_data(data, 10, t_filename);
    expect_to_read(data,10, t_filename);
}

//test bool
TEST(test_ibinaryfile, read_bool) {
    bool data[10] = {true, false, true, false, true, false, true, false, true, false};
    write_data(data, 10, t_filename);
    expect_to_read(data,10, t_filename);
}

//test char
TEST(test_ibinaryfile, read_char) {
    char data[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    write_data(data, 10, t_filename);
    expect_to_read(data,10, t_filename);
}

//test string
TEST(test_ibinaryfile, read_string) {
    std::string data = "coucou";
    {
        size_t size = data.size();
        std::ofstream f(t_filename, std::ios::binary);
        f.write((char*)&size, sizeof(size_t));
        f.write(data.c_str(), (std::streamsize)(size*sizeof(char)));
    }
    serial::IBinaryFile f1(t_filename);
    std::string result;
    f1 >> result;
    EXPECT_EQ(data, result);
}

//test vector
TEST(test_ibinaryfile, read_vector){
    std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    {
        size_t size = data.size();
        std::ofstream f(t_filename, std::ios::binary);
        f.write((char*)&size, sizeof(size_t));
        f.write((char*)data.data(), (std::streamsize)(size*sizeof(int)));
    }
    serial::IBinaryFile f1(t_filename);
    std::vector<int> result;
    f1 >> result;
    EXPECT_EQ(data, result);
}

//test map
TEST(test_ibinaryfile, read_map){
    std::map<int, int> data = {{1, 2},
                               {3, 4},
                               {5, 6}};
    {
        size_t size = data.size();
        std::ofstream f(t_filename, std::ios::binary);
        f.write((char*)&size, sizeof(size_t));
        for(auto& p : data){
            f.write((char*)&p.first, sizeof(int));
            f.write((char*)&p.second, sizeof(int));
        }
    }
    serial::IBinaryFile f1(t_filename);
    std::map<int, int> result;
    f1 >> result;
    EXPECT_EQ(data, result);
}

//test array
TEST(test_ibinaryfile, read_array){
    std::array<int,10> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    {
        size_t size = data.size();
        std::ofstream f(t_filename, std::ios::binary);
        f.write((char*)&size, sizeof(size_t));
        f.write((char*)data.data(), (std::streamsize)(size*sizeof(int)));
    }
    serial::IBinaryFile f1(t_filename);
    std::array<int,10> result{};
    f1 >> result;
    EXPECT_EQ(data, result);
}

//test set
TEST(test_ibinaryfile, read_set){
    std::set<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    {
        size_t size = data.size();
        std::ofstream f(t_filename, std::ios::binary);
        f.write((char*)&size, sizeof(size_t));
        for(auto& p : data){
            f.write((char*)&p, sizeof(int));
        }
    }
    serial::IBinaryFile f1(t_filename);
    std::set<int> result{};
    f1 >> result;
    EXPECT_EQ(data, result);
}


/*
 * test ObinaryFile/IBinaryFile
 */

template<typename T>
void test_read_write_value(T data,  const std::string& t_filename){
    {
        serial::OBinaryFile f(t_filename);
        f << data;
    }
    {
        serial::IBinaryFile f(t_filename);
        T result;
        f >> result;
        EXPECT_EQ(data, result);
    }
}

//test int8_t
TEST(test_iobinaryfile, read_write_int8_t) {
    int8_t data = 1;
    test_read_write_value(data, t_filename);
    data = -1;
    test_read_write_value(data, t_filename);
    data = INT8_MAX;
    test_read_write_value(data, t_filename);
    data = INT8_MIN;
    test_read_write_value(data, t_filename);
}

//test int16_t
TEST(test_iobinaryfile, read_write_int16_t) {
    int16_t data = 1;
    test_read_write_value(data, t_filename);
    data = -1;
    test_read_write_value(data, t_filename);
    data = INT16_MAX;
    test_read_write_value(data, t_filename);
    data = INT16_MIN;
    test_read_write_value(data, t_filename);
}

//test int32_t
TEST(test_iobinaryfile, read_write_int32_t) {
    int32_t data = 1;
    test_read_write_value(data, t_filename);
    data = -1;
    test_read_write_value(data, t_filename);
    data = INT32_MAX;
    test_read_write_value(data, t_filename);
    data = INT32_MIN;
    test_read_write_value(data, t_filename);
}

//test int64_t
TEST(test_iobinaryfile, read_write_int64_t) {
    int64_t data = 1;
    test_read_write_value(data, t_filename);
    data = -1;
    test_read_write_value(data, t_filename);
    data = INT64_MAX;
    test_read_write_value(data, t_filename);
    data = INT64_MIN;
    test_read_write_value(data, t_filename);
}

//test uint8_t
TEST(test_iobinaryfile, read_write_uint8_t) {
    uint8_t data = 1;
    test_read_write_value(data, t_filename);
    data = UINT8_MAX;
    test_read_write_value(data, t_filename);
}

//test uint16_t
TEST(test_iobinaryfile, read_write_uint16_t) {
    uint16_t data = 1;
    test_read_write_value(data, t_filename);
    data = UINT16_MAX;
    test_read_write_value(data, t_filename);
}

//test uint32_t
TEST(test_iobinaryfile, read_write_uint32_t) {
    uint32_t data = 1;
    test_read_write_value(data, t_filename);
    data = UINT32_MAX;
    test_read_write_value(data, t_filename);
}

//test uint64_t
TEST(test_iobinaryfile, read_write_uint64_t) {
    uint64_t data = 1;
    test_read_write_value(data, t_filename);
    data = UINT64_MAX;
    test_read_write_value(data, t_filename);
}

//test float
TEST(test_iobinaryfile, read_write_float) {
    float data = 1.0;
    test_read_write_value(data, t_filename);
    data = -1.0;
    test_read_write_value(data, t_filename);
    data = FLT_MAX;
    test_read_write_value(data, t_filename);
    data = FLT_MIN;
    test_read_write_value(data, t_filename);
}

//test double
TEST(test_iobinaryfile, read_write_double) {
    double data = 1.0;
    test_read_write_value(data, t_filename);
    data = -1.0;
    test_read_write_value(data, t_filename);
    data = DBL_MAX;
    test_read_write_value(data, t_filename);
    data = DBL_MIN;
    test_read_write_value(data, t_filename);
}

//test string
TEST(test_iobinaryfile, read_write_string) {
    std::string data = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";
    test_read_write_value(data, t_filename);
    data = "";
    test_read_write_value(data, t_filename);
}

//test vector full
TEST(test_iobinaryfile, read_write_vector_full) {
    std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    {
        serial::OBinaryFile f(t_filename);
        f << data;
    }
    {
        serial::IBinaryFile f(t_filename);
        std::vector<int> result;
        f >> result;
        EXPECT_EQ(data, result);
    }
}
//test vector empty
TEST(test_iobinaryfile, read_write_vector_empty) {
    std::vector<int> data;
    {
        serial::OBinaryFile f(t_filename);
        f << data;
    }
    {
        serial::IBinaryFile f(t_filename);
        std::vector<int> result;
        f >> result;
        EXPECT_EQ(data, result);
    }
}

//test map full
TEST(test_iobinaryfile, read_write_map_full) {
    std::map<int, int> data = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10} };
    {
        serial::OBinaryFile f(t_filename);
        f << data;
    }
    {
        serial::IBinaryFile f(t_filename);
        std::map<int, int> result;
        f >> result;
        EXPECT_EQ(data, result);
    }
}

//test map empty
TEST(test_iobinaryfile, read_write_map_empty) {
    std::map<int, int> data;
    {
        serial::OBinaryFile f(t_filename);
        f << data;
    }
    {
        serial::IBinaryFile f(t_filename);
        std::map<int, int> result;
        f >> result;
        EXPECT_EQ(data, result);
    }
}

//test array full
TEST(test_iobinaryfile, read_write_array_full) {
    std::array<int, 10> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    {
        serial::OBinaryFile f(t_filename);
        f << data;
    }
    {
        serial::IBinaryFile f(t_filename);
        std::array<int, 10> result{};
        f >> result;
        EXPECT_EQ(data, result);
    }
}

//test array empty
TEST(test_iobinaryfile, read_write_array_empty) {
    std::array<int, 0> data;
    {
        serial::OBinaryFile f(t_filename);
        f << data;
    }
    {
        serial::IBinaryFile f(t_filename);
        std::array<int, 0> result{};
        f >> result;
        EXPECT_EQ(data, result);
    }
}

//test set full
TEST(test_iobinaryfile, read_write_set_full) {
    std::set<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    {
        serial::OBinaryFile f(t_filename);
        f << data;
    }
    {
        serial::IBinaryFile f(t_filename);
        std::set<int> result;
        f >> result;
        EXPECT_EQ(data, result);
    }
}


//test set empty
TEST(test_iobinaryfile, read_write_set_empty) {
    std::set<int> data;
    {
        serial::OBinaryFile f(t_filename);
        f << data;
    }
    {
        serial::IBinaryFile f(t_filename);
        std::set<int> result;
        f >> result;
        EXPECT_EQ(data, result);
    }
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
