int main() {
    int x = 10;
    {
        int x = 5;
        print(x);
    }
    print(x);
    return 0;
}
