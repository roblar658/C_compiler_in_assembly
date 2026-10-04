struct Point {
    int x;
    int y;
};

struct Rect {
    int top;
    int left;
    int width;
    int height;
};

int test_struct_direct() {
    struct Point p;
    p.x = 15;
    p.y = 25;
    return p.x + p.y; // 40
}

int test_struct_pointer() {
    struct Point p;
    struct Point *ptr = &p;
    ptr->x = 100;
    ptr->y = 200;
    return ptr->x + ptr->y; // 300
}

int test_struct_compound() {
    struct Rect r;
    r.top = 10;
    r.left = 20;
    r.width = 30;
    r.height = 40;

    r.width += 10;  // 40
    r.height += 20; // 60

    return r.top + r.left + r.width + r.height; // 10 + 20 + 40 + 60 = 130
}

int main() {
    if (test_struct_direct() != 40) return 1;
    if (test_struct_pointer() != 300) return 2;
    if (test_struct_compound() != 130) return 3;
    return 0;
}
