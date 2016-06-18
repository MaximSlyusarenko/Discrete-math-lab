my @links = ();
 
while (<>) {
    push(@links, (/<a\s+href="(.*?)"\s*>/g));
}
     
foreach (@links) {
    s/^([^\/?#:]+:\/\/)?([^\/?#:]*)(.*)/$2/g;
}
         
my %answer = map {$_, 1} (@links);
         
foreach (sort keys %answer) {
    if (/^$/ or /^\./ or /\.\./) {
    } else {
        print "$_\n";
    }
}
