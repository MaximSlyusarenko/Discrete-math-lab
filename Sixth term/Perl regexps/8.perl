while (<>) {
    print if /\([^\)]*\b(\w)+\b[^\(]*\)/
}
