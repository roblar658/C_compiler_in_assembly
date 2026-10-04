int test_pointer_read() {
    int x = 42;
    int *p = &x;
    return *p;
}

int test_pointer_write() {
    int x = 10;
    int *p = &x;
    *p = 55;
    return x;
}

int test_pointer_compound() {
    int a = 100;
    int *p = &a;
    *p += 50;
    *p -= 20;
    return a;
}

int test_pointer_alias() {
    int val = 7;
    int *p1 = &val;
    int *p2 = &val;
    *p1 = 99;
    return *p2;
}

int main() {
    if (test_pointer_read() != 42) return 1;
    if (test_pointer_write() != 55) return 2;
    if (test_pointer_compound() != 130) return 3;
    if (test_pointer_alias() != 99) return 4;
    return 0;
}
