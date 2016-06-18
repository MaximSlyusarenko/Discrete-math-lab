my $s = "";

while (my $line = <>) {
    $line =~ s/<.*?>//g; # tags
    $line =~ s/^(\s)*(\w)/$2/; # spaces at the beginning of non-empty line
    $line =~ s/(\s){2,}/$1/g; # two or more spaces in a row betwee words
    $s .= $line;
}

$s =~ s/(\s)*\b//; # beginning of the text
$s =~ s/(\s)*?\n/\n/g; # spaces before end of line
$s =~ s/(\n){3,}/\n\n/g; # many empty lines
$s =~ s/(\n)*\Z//; # empty lines at the end of text
print $s;
