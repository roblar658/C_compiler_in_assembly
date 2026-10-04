int g_a = 42;
int g_b = 58;
int g_arr[4];

int test_modify_globals() {
    g_a += 10; // 52
    g_b -= 8;  // 50
    return g_a + g_b; // 102
}

int test_global_array() {
    g_arr[0] = 1;
    g_arr[1] = 2;
    g_arr[2] = 3;
    g_arr[3] = 4;
    return g_arr[0] + g_arr[1] + g_arr[2] + g_arr[3]; // 10
}

int main() {
    if (g_a != 42) return 1;
    if (g_b != 58) return 2;
    if (test_modify_globals() != 102) return 3;
    if (test_global_array() != 10) return 4;
    return 0;
}
