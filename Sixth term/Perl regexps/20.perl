while (<>) {
    s/\(.+?\)/()/g;
    print;
}
