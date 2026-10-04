int test_array_basic() {
    int arr[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        arr[i] = (i + 1) * 10;
    }
    int sum = 0;
    for (i = 0; i < 5; i = i + 1) {
        sum += arr[i];
    }
    // 10 + 20 + 30 + 40 + 50 = 150
    return sum;
}

int test_array_compound() {
    int arr[4];
    arr[0] = 5;
    arr[1] = 10;
    arr[2] = 15;
    arr[3] = 20;

    arr[0] += 5;  // 10
    arr[1] *= 2;  // 20
    arr[2] -= 5;  // 10
    arr[3] /= 2;  // 10

    return arr[0] + arr[1] + arr[2] + arr[3]; // 10 + 20 + 10 + 10 = 50
}

int main() {
    if (test_array_basic() != 150) return 1;
    if (test_array_compound() != 50) return 2;
    return 0;
}
