int test_basic_switch(int val) {
    int res = 0;
    switch (val) {
        case 1:
            res = 10;
            break;
        case 2:
            res = 20;
            break;
        case 3:
            res = 30;
            break;
        default:
            res = 99;
            break;
    }
    return res;
}

int test_fallthrough(int val) {
    int count = 0;
    switch (val) {
        case 1:
            count = count + 1;
        case 2:
            count = count + 2;
            break;
        case 3:
            count = count + 4;
            break;
        default:
            count = 100;
            break;
    }
    return count;
}

int main() {
    if (test_basic_switch(1) != 10) return 1;
    if (test_basic_switch(2) != 20) return 2;
    if (test_basic_switch(3) != 30) return 3;
    if (test_basic_switch(42) != 99) return 4;

    // Fallthrough: val=1 executes case 1 (+1) then case 2 (+2) -> 3
    if (test_fallthrough(1) != 3) return 5;
    // val=2 executes case 2 (+2) -> 2
    if (test_fallthrough(2) != 2) return 6;
    // val=3 executes case 3 (+4) -> 4
    if (test_fallthrough(3) != 4) return 7;

    return 0;
}
