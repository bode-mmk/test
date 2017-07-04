use utf8;
use Encode;

my $str = "あいうえお";

print $str;
print encode("utf8", $str),$/;
print encode("sjis", $str),$/;
