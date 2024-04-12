IDNSpoofChecker::IDNSpoofChecker() {
UErrorCode status = U_ZERO_ERROR;
checker_ = uspoof_open(&status);
if (U_FAILURE(status)) {
checker_ = nullptr;
return;
}

// At this point, USpoofChecker has all the checks enabled except
// for USPOOF_CHAR_LIMIT (USPOOF_{RESTRICTION_LEVEL, INVISIBLE,
// MIXED_SCRIPT_CONFUSABLE, WHOLE_SCRIPT_CONFUSABLE, MIXED_NUMBERS, ANY_CASE})
// This default configuration is adjusted below as necessary.

// Set the restriction level to high. It allows mixing Latin with one logical
// CJK script (+ COMMON and INHERITED), but does not allow any other script
// mixing (e.g. Latin + Cyrillic, Latin + Armenian, Cyrillic + Greek). Note
// that each of {Han + Bopomofo} for Chinese, {Hiragana, Katakana, Han} for
// Japanese, and {Hangul, Han} for Korean is treated as a single logical
// script.
// See http://www.unicode.org/reports/tr39/#Restriction_Level_Detection
uspoof_setRestrictionLevel(checker_, USPOOF_HIGHLY_RESTRICTIVE);

// Sets allowed characters in IDN labels and turns on USPOOF_CHAR_LIMIT.
SetAllowedUnicodeSet(&status);

// Enable the return of auxillary (non-error) information.
// We used to disable WHOLE_SCRIPT_CONFUSABLE check explicitly, but as of
// ICU 58.1, WSC is a no-op in a single string check API.
int32_t checks = uspoof_getChecks(checker_, &status) | USPOOF_AUX_INFO;
uspoof_setChecks(checker_, checks, &status);

// Four characters handled differently by IDNA 2003 and IDNA 2008. UTS46
// transitional processing treats them as IDNA 2003 does; maps U+00DF and
// U+03C2 and drops U+200[CD].
deviation_characters_ = icu::UnicodeSet(
UNICODE_STRING_SIMPLE("[\\u00df\\u03c2\\u200c\\u200d]"), status);
deviation_characters_.freeze();

// Latin letters outside ASCII. 'Script_Extensions=Latin' is not necessary
// because additional characters pulled in with scx=Latn are not included in
// the allowed set.
non_ascii_latin_letters_ =
icu::UnicodeSet(UNICODE_STRING_SIMPLE("[[:Latin:] - [a-zA-Z]]"), status);
non_ascii_latin_letters_.freeze();

// The following two sets are parts of |dangerous_patterns_|.
kana_letters_exceptions_ = icu::UnicodeSet(
UNICODE_STRING_SIMPLE("[\\u3078-\\u307a\\u30d8-\\u30da\\u30fb-\\u30fe]"),
status);
kana_letters_exceptions_.freeze();
combining_diacritics_exceptions_ =
icu::UnicodeSet(UNICODE_STRING_SIMPLE("[\\u0300-\\u0339]"), status);
combining_diacritics_exceptions_.freeze();

// These Cyrillic letters look like Latin. A domain label entirely made of
// these letters is blocked as a simplified whole-script-spoofable.
cyrillic_letters_latin_alike_ = icu::UnicodeSet(
icu::UnicodeString::fromUTF8("[асԁеһіјӏорԛѕԝхуъЬҽпгѵѡ]"), status);
cyrillic_letters_latin_alike_.freeze();

cyrillic_letters_ =
icu::UnicodeSet(UNICODE_STRING_SIMPLE("[[:Cyrl:]]"), status);
cyrillic_letters_.freeze();

DCHECK(U_SUCCESS(status));
// This set is used to determine whether or not to apply a slow
// transliteration to remove diacritics to a given hostname before the
// confusable skeleton calculation for comparison with top domain names. If
// it has any character outside the set, the expensive step will be skipped
// because it cannot match any of top domain names.
// The last ([\u0300-\u0339] is a shorthand for "[:Identifier_Status=Allowed:]
// & [:Script_Extensions=Inherited:] - [\\u200C\\u200D]". The latter is a
// subset of the former but it does not matter because hostnames with
// characters outside the latter set would be rejected in an earlier step.
lgc_letters_n_ascii_ = icu::UnicodeSet(
UNICODE_STRING_SIMPLE("[[:Latin:][:Greek:][:Cyrillic:][0-9\\u002e_"
"\\u002d][\\u0300-\\u0339]]"),
status);
lgc_letters_n_ascii_.freeze();

// Used for diacritics-removal before the skeleton calculation. Add
// "ł > l; ø > o; đ > d" that are not handled by "NFD; Nonspacing mark
// removal; NFC".
// TODO(jshin): Revisit "ł > l; ø > o" mapping.
UParseError parse_error;
diacritic_remover_.reset(icu::Transliterator::createFromRules(
UNICODE_STRING_SIMPLE("DropAcc"),
icu::UnicodeString::fromUTF8("::NFD; ::[:Nonspacing Mark:] Remove; ::NFC;"
" ł > l; ø > o; đ > d;"),
UTRANS_FORWARD, parse_error, status));

// Supplement the Unicode confusable list by the following mapping.
//   - {U+00FE (þ), U+03FC (ϼ), U+048F (ҏ)} => p
//   - {U+0127 (ħ), U+043D (н), U+045B (ћ), U+04A3 (ң), U+04A5 (ҥ),
  //      U+04C8 (ӈ), U+04CA (ӊ), U+0527 (ԧ), U+0529 (ԩ)} => h
//   - {U+0138 (ĸ), U+03BA (κ), U+043A (к), U+049B (қ), U+049D (ҝ),
//      U+049F (ҟ), U+04A1(ҡ), U+04C4 (ӄ), U+051F (ԟ)} => k
//   - {U+014B (ŋ), U+043F (п)} => n
  //   - {U+0167 (ŧ), U+0442 (т), U+04AD (ҭ)} => t
//   - {U+0185 (ƅ), U+044C (ь), U+048D (ҍ), U+0432 (в)} => b
//   - {U+03C9 (ω), U+0448 (ш), U+0449 (щ), U+0E1F (ฟ)} => w
//   - {U+043C (м), U+04CE (ӎ)} => m
//   - {U+0454 (є), U+04BD (ҽ), U+04BF (ҿ), U+1054 (ၔ)} => e
//   - U+0491 (ґ) => r
  //   - U+0493 (ғ) => f
//   - {U+04AB (ҫ), U+1004 (င)} => c
//   - U+04B1 (ұ) => y
//   - U+03C7 (χ), U+04B3 (ҳ), U+04FD (ӽ), U+04FF (ӿ) => x
//   - U+04CF (ӏ) => i (on Windows), l (elsewhere)
//   - U+0503 (ԃ) => d
//   - {U+050D (ԍ), U+100c (ဌ)} => g
//   - {U+0D1F (ട), U+0E23 (ร)} => s
//   - U+1042 (၂) => j
extra_confusable_mapper_.reset(icu::Transliterator::createFromRules(
UNICODE_STRING_SIMPLE("ExtraConf"),
      icu::UnicodeString::fromUTF8("[þϼҏ] > p; [ħнћңҥӈӊԧԩ] > h;"
                                   "[ĸκкқҝҟҡӄԟ] > k; [ŋп] > n; [ŧтҭ] > t;"
"[ƅьҍв] > b;  [ωшщฟ] > w; [мӎ] > m;"
                                   "[єҽҿၔ] > e; ґ > r; ғ > f; [ҫင] > c;"
"ұ > y; [χҳӽӿ] > x;"
#if defined(OS_WIN)
"ӏ > i;"
#else
"ӏ > l;"
#endif
                                   "ԃ  > d; [ԍဌ] > g; [ടร] > s; ၂ > j"),
UTRANS_FORWARD, parse_error, status));
DCHECK(U_SUCCESS(status))
<< "Spoofchecker initalization failed due to an error: "
<< u_errorName(status);
}
