// Copyright 2021 NNTU-CS

#include <time.h>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <functional>

#include "gtest/gtest.h"

#define ARRSIZE1 100000
#define ARRSIZE2 200000

int countPairs1(int *arr, int len, int value);
int countPairs2(int *arr, int len, int value);
int countPairs3(int *arr, int len, int value);

void generateSorted(int *arr, int min, int max, int len) {
    int value = 0, j = 0;
    for (int i = 0; i < len; i++) {
        value = min + rand() % (max - min + 1);
        j = i - 1;
        while (j >= 0 && arr[j] > value) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = value;
    }
}

double measureTime(std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

std::vector<int> generateSortedVector(int size, int min = 0, int max = 1000) {
    std::vector<int> arr(size);
    int value, j;

    for (int i = 0; i < size; i++) {
        value = min + rand() % (max - min + 1);
        j = i - 1;

        while (j >= 0 && arr[j] > value) {
            if (j + 1 < size) arr[j + 1] = arr[j];
            j--;
        }
        if (j + 1 < size) arr[j + 1] = value;
    }
    return arr;
}

TEST(lab2, test1) {
    int *arr = new int[ARRSIZE1];
    generateSorted(arr, 0, 100, ARRSIZE1);
    int count1 = countPairs1(arr, ARRSIZE1, 50);
    int count2 = countPairs2(arr, ARRSIZE1, 50);
    int count3 = countPairs3(arr, ARRSIZE1, 50);
    EXPECT_TRUE((count1 == count2) && (count1 == count3) && (count2 == count3));
    delete[] arr;
}

TEST(lab2, test2) {
    int *arr = new int[ARRSIZE2];
    generateSorted(arr, 0, 100, ARRSIZE2);
    int count1 = countPairs1(arr, ARRSIZE2, 50);
    int count2 = countPairs2(arr, ARRSIZE2, 50);
    int count3 = countPairs3(arr, ARRSIZE2, 50);
    EXPECT_TRUE((count1 == count2) && (count1 == count3) && (count2 == count3));
    delete[] arr;
}

TEST(lab2, test3) {
    const int size = 20000;
    std::vector<int> arr = generateSortedVector(size, 0, 1000);
    int target = 500;

    int result1 = countPairs1(arr.data(), size, target);
    int result2 = countPairs2(arr.data(), size, target);
    int result3 = countPairs3(arr.data(), size, target);

    EXPECT_EQ(result1, result2)
        << "Results differ between countPairs1 and countPairs2";
    EXPECT_EQ(result2, result3)
        << "Results differ between countPairs2 and countPairs3";

    double t1 = measureTime([&]() {
        countPairs1(arr.data(), size, target);
    });
    double t2 = measureTime([&]() {
        countPairs2(arr.data(), size, target);
    });
    double t3 = measureTime([&]() {
        countPairs3(arr.data(), size, target);
    });

    bool condition1 = t1 > 1.5 * t2 && t1 > 1.5 * t3;
    EXPECT_TRUE(condition1)
        << "Time condition failed: t1 should be significantly larger than t2 and t3";

    bool condition2 = t2 < 2 * t3 || t3 < 2 * t2;
    const char* errorMsg = "Time condition failed: "
                       "t2 and t3 should be relatively close";
    EXPECT_TRUE(condition2) << errorMsg;
}
