while (<>) {
    print if /^\d+\W|\W\d+\W/
}
