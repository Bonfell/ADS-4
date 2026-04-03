// Copyright 2021 NNTU-CS
#include <algorithm>
void binarySearchRange(int* arr, int len, int target, int& left, int& right) {
    left = -1;
    right = -1;
    int low = 0, high = len - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < target) {
            low = mid + 1;
        } else if (arr[mid] > target) {
            high = mid - 1;
        } else {
            left = mid;
            high = mid - 1;
        }
    }
    if (left == -1) return;
    low = 0;
    high = len - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < target) {
            low = mid + 1;
        } else if (arr[mid] > target) {
            high = mid - 1;
        } else {
            right = mid;
            low = mid + 1;
        }
    }
}
int countPairs1(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (arr[i] + arr[j] == value) {
                count++;
            }
        }
    }
    return count;
}
int countPairs2(int *arr, int len, int value) {
    int count = 0;
    int left = 0;
    int right = len - 1;
    while (left < right) {
        int currentSum = arr[left] + arr[right];
        if (currentSum == value) {
            if (arr[left] == arr[right]) {
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            } else {
                int leftCount = 1;
                while (left + 1 < right && arr[left] == arr[left + 1]) {
                    leftCount++;
            left++;
        }
                int rightCount = 1;
                while (right - 1 > left && arr[right] == arr[right - 1]) {
            rightCount++;
            right--;
        }
                count += leftCount * rightCount;
            }
            left++;
            right--;
        } else if (currentSum < value) {
            left++;
        } else {
            right--;
        }
    }
    return count;
}
int countPairs3(int *arr, int len, int value) {
    int total = 0;
    for (int i = 0; i < len; i++) {
        int complement = value - arr[i];
        if (complement < arr[i]) continue;
        int left, right;
        binarySearchRange(arr, len, complement, left, right);
        if (left != -1) {
            int start = std::max(left, i + 1);
            if (start <= right) {
                total += right - start + 1;
            }
        }
    }
    return total;
}
