extern int printf(char *fmt, int a, int b);

int test_str_index() {
    char *s = "Hello";
    if (s[0] != 72) return 1; // 'H'
    if (s[1] != 101) return 2; // 'e'
    if (s[4] != 111) return 3; // 'o'
    if (s[5] != 0) return 4;   // null terminator
    return 0;
}

int main() {
    if (test_str_index() != 0) return 1;

    // Call printf to verify C runtime linkage
    printf("Testing printf from our assembler C compiler! %d + %d = %d\n", 20, 22, 42);

    return 0;
}
