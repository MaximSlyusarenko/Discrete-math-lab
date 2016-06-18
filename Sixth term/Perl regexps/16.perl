while (<>) {
    s/(\b)(\w)(\w)/$1$3$2/g;
    print;
}
