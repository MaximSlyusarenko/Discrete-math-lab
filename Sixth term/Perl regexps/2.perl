while (<>) {
    print if /^cat\W|\Wcat\W/
}
