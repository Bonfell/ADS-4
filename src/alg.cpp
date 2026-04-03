// Copyright 2021 NNTU-CS
#include <algorithm>
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
        int sum = arr[left] + arr[right];
        if (sum == value) {
            if (arr[left] == arr[right]) {
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            } else {
                int leftVal = arr[left];
                int rightVal = arr[right];
                int leftCount = 0;
                while (left < len && arr[left] == leftVal) {
                    leftCount++;
                    left++;
                }
                int rightCount = 0;
                while (right >= 0 && arr[right] == rightVal) {
                    rightCount++;
                    right--;
                }
                count += leftCount * rightCount;
            }
        } else if (sum < value) {
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
        int low = i + 1;
        int high = len - 1;
        int firstPos = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] < complement) {
                low = mid + 1;
            } else if (arr[mid] > complement) {
                high = mid - 1;
            } else {
                firstPos = mid;
                high = mid - 1;
            }
        }
        if (firstPos != -1) {
            low = firstPos;
            high = len - 1;
            int lastPos = firstPos;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (arr[mid] < complement) {
                    low = mid + 1;
                } else if (arr[mid] > complement) {
                    high = mid - 1;
                } else {
                    lastPos = mid;
                    low = mid + 1;
                }
            }
            total += lastPos - firstPos + 1;
        }
    }
    return total;
}
