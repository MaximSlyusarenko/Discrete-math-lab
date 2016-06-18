while (<>) {
    print if /^(\w*)\1\W|\W(\w*)\1\W/
}
