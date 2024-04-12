void test_for()
{
  assert_true_rule(
      "rule test { \
        strings: \
          $a = \"ssi\" \
        condition: \
          for all i in (1..#a) : (@a[i] >= 2 and @a[i] <= 5) \
      }",
      "mississippi");

  assert_true_rule(
      "rule test { \
        strings: \
          $a = \"ssi\" \
          $b = \"mi\" \
        condition: \
          for all i in (1..#a) : ( for all j in (1..#b) : (@a[i] >= @b[j])) \
      }",
      "mississippi");

  assert_false_rule(
      "rule test { \
        strings: \
          $a = \"ssi\" \
        condition: \
          for all i in (1..#a) : (@a[i] == 5) \
      }",
      "mississippi");
}
