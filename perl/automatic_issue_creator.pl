use warnings;
use diagnostics;
use strict;
use Net::GitHub;
use Data::Dumper;
use Encode;
use utf8;
use Unicode::Escape qw(escape unescape);

# accesss tokenによってログイン
my $github = Net::GitHub->new(
  access_token => '',
  api_url => 'gitbucket_url'
);

my $issue = $github->issue;
$issue->set_default_user_repo('UserName','Hoge');
my @issues = $issue->repos_issues;

my $issue_result = $issue->create_issue({
    "title" => "Write title",
    "body" => "- Write content here.",
    "assignee" => "foo",
    "milestone" => 1,
    "labels" => [
      "recommend"
    ]
});
