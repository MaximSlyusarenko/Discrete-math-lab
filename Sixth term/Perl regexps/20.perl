while (<>) {
    s/\(.+?\)/()/g;
    print;
}