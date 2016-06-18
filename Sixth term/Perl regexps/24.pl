my @links = ();

while (<>) { 
    push(@links, (/<a\s+href="((http:\/\/|https:\/\/|ftp:\/\/)?(?!(http:\/\/|https:\/\/|ftp:\/\/|\.))+?.*?)"\s*>/g));
}

foreach (@links) {
    s/(http:\/\/|https:\/\/|ftp:\/\/)?([^\/?#:]*)(.*)/$2/g;
}

my %answer = map {$_, 1} (@links);

foreach (sort keys %answer) {
    if (/^$/) {
    } else {
        print "$_\n";
    }
}
