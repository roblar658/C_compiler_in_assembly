int g_side_effect = 0;

int side_effect_fn() {
    g_side_effect += 1;
    return 1;
}

int test_bitwise() {
    int a = 12; // 1100 in binary
    int b = 10; // 1010 in binary

    int and_res = a & b; // 1000 = 8
    int or_res  = a | b; // 1110 = 14
    int xor_res = a ^ b; // 0110 = 6
    int not_res = ~0;    // -1

    int shl_res = 1 << 4; // 16
    int shr_res = 32 >> 2; // 8

    if (and_res != 8) return 1;
    if (or_res != 14) return 2;
    if (xor_res != 6) return 3;
    if (not_res != -1) return 4;
    if (shl_res != 16) return 5;
    if (shr_res != 8) return 6;
    return 0;
}

int test_short_circuit() {
    g_side_effect = 0;

    // In 0 && side_effect_fn(), side_effect_fn MUST NOT be called!
    int res1 = (0 && side_effect_fn());
    if (res1 != 0) return 1;
    if (g_side_effect != 0) return 2; // side effect occurred!

    // In 1 || side_effect_fn(), side_effect_fn MUST NOT be called!
    int res2 = (1 || side_effect_fn());
    if (res2 != 1) return 3;
    if (g_side_effect != 0) return 4; // side effect occurred!

    // In 1 && side_effect_fn(), side_effect_fn MUST be called!
    int res3 = (1 && side_effect_fn());
    if (res3 != 1) return 5;
    if (g_side_effect != 1) return 6;

    return 0;
}

int test_ternary() {
    int x = 10;
    int y = 20;
    int max = (x > y) ? x : y;
    if (max != 20) return 1;

    int min = (x < y) ? x : y;
    if (min != 10) return 2;

    int sign = (x > 0) ? 1 : ((x < 0) ? -1 : 0);
    if (sign != 1) return 3;

    return 0;
}

int main() {
    if (test_bitwise() != 0) return 1;
    if (test_short_circuit() != 0) return 2;
    if (test_ternary() != 0) return 3;
    return 0;
}
