int test_while() {
    int sum = 0;
    int i = 1;
    while (i <= 10) {
        sum = sum + i;
        i = i + 1;
    }
    return sum;
}

int test_for() {
    int sum = 0;
    int i;
    for (i = 0; i < 10; i = i + 1) {
        if (i == 5) {
            continue;
        }
        if (i == 8) {
            break;
        }
        sum = sum + i;
    }
    return sum;
}

int test_do_while() {
    int count = 0;
    int x = 1;
    do {
        count = count + 1;
        x = x * 2;
    } while (x < 16);
    return count;
}

int main() {
    if (test_while() != 55) {
        return 1;
    }
    if (test_for() != 23) {
        return 2;
    }
    if (test_do_while() != 4) {
        return 3;
    }
    return 0;
}
