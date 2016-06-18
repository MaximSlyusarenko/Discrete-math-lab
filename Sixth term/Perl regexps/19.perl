while (<>) {
    s/\B0\b//g;
    print;
}
