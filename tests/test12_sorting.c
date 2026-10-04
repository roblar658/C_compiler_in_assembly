int bubble_sort(int *arr, int n) {
    int i;
    int j;
    int temp;
    for (i = 0; i < n - 1; i = i + 1) {
        for (j = 0; j < n - i - 1; j = j + 1) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return 0;
}

int binary_search(int *arr, int n, int key) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key) {
            return mid;
        }
        if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    int numbers[8];
    numbers[0] = 64;
    numbers[1] = 34;
    numbers[2] = 25;
    numbers[3] = 12;
    numbers[4] = 22;
    numbers[5] = 11;
    numbers[6] = 90;
    numbers[7] = 5;

    bubble_sort(numbers, 8);

    // Expected: 5, 11, 12, 22, 25, 34, 64, 90
    if (numbers[0] != 5) return 1;
    if (numbers[1] != 11) return 2;
    if (numbers[2] != 12) return 3;
    if (numbers[3] != 22) return 4;
    if (numbers[4] != 25) return 5;
    if (numbers[5] != 34) return 6;
    if (numbers[6] != 64) return 7;
    if (numbers[7] != 90) return 8;

    // Binary search checks
    if (binary_search(numbers, 8, 25) != 4) return 9;
    if (binary_search(numbers, 8, 90) != 7) return 10;
    if (binary_search(numbers, 8, 5) != 0) return 11;
    if (binary_search(numbers, 8, 100) != -1) return 12;

    return 0;
}
