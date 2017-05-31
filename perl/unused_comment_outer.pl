# warningはコピペで以下のような感じのものを食わせる
#
# 警告	C4100	'hoge': 引数は関数の本体部で 1 度も参照されません。	ProjectName	c:\hoge.cpp	1485
#
# もし表示形式を変えている場合は適当に配列の引数を変える

use warnings;
use strict;
use diagnostics;

if(@ARGV == 0){
  print $0," [warning_log_file_path] .",$/;
  exit(0);
}

my $warning_file_path = $ARGV[0];

open(WARNING_FILE, "<", $warning_file_path) or die print "warning file couldn't open.",$/;
my @file_data = <WARNING_FILE>;
close(WARNING_FILE);

for(@file_data){
  my @sp = split(/\s+/, $_);
  if(@sp < 2 || $sp[1] ne "C4100"){
    next;
  }
  $sp[2] =~ /'(.*)'/i;
  my $value_name = $1;        #変数名
  my $file_path = $sp[7];     #ファイルパス
  my $line_num = $sp[8];      #行数

  print $value_name, ":", $file_path, ":", $line_num, ":", $/;

  #open replace file
  open(REPLACE_FILE, "<", $file_path);
  my @data = <REPLACE_FILE>;
  close(REPLACE_FILE);
  $data[$line_num - 1] =~ s/$value_name/\/\* $value_name \*\//;

  #write tmp file
  my $tmp_file = $file_path . ".tmp";
  open(TMP_FILE, ">>", $tmp_file);
  foreach my $line (@data){
    print TMP_FILE $line;
  }
  close(TMP_FILE);

  #rename
  rename($file_path, $file_path.".old");
  rename($tmp_file, $file_path);
}
