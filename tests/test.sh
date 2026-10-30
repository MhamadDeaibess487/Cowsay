#!/bin/bash
set -euo pipefail
cd "$(dirname "$0")/.."
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
fail() { echo "FAIL: $*" >&2; exit 1; }
reject() {
    if "$@" >"$tmp/out" 2>"$tmp/err"; then fail "accepted: $*"; fi
    [[ -s $tmp/err ]] || fail "missing diagnostic: $*"
}
for app in newcow reading_cow wild_cow tamagoshi_cow; do
    ./"$app" --help >"$tmp/help"
    [[ $(cat "$tmp/help") == *Usage:* ]] || fail "help: $app"
    reject ./"$app" --unknown
done
./newcow >"$tmp/cow"
./newcow -e OO --tail 2 >"$tmp/cow"
[[ $(cat "$tmp/cow") == *'(OO)'* ]] || fail eyes
[[ $(wc -l <"$tmp/cow") == 7 ]] || fail tail
for value in -1 2x '' 999999999999999999999999; do reject ./newcow --tail "$value";done
reject ./newcow --tail
reject ./newcow -e x
reject ./newcow text
reject ./reading_cow
reject ./reading_cow "$tmp/missing"
reject ./reading_cow "$tmp" # fopen may succeed on a directory; fgetc must fail.
reject ./reading_cow readingcowTxt extra
: >"$tmp/empty"
./reading_cow --no-delay "$tmp/empty" >"$tmp/out"
[[ ! -s $tmp/out ]] || fail 'empty file'
printf 'ab c' >"$tmp/text"
./reading_cow --no-delay "$tmp/text" >"$tmp/out"
[[ $(wc -l <"$tmp/out") == 24 ]] || fail 'frame count'
[[ $(cat "$tmp/out") == *'"a"'* ]] || fail accumulation
printf '%8192s' '' | tr ' ' x >"$tmp/long"
./reading_cow --no-delay "$tmp/long" >/dev/null
# 1 MiB total, with short words: memory should depend on word size, not file size.
awk 'BEGIN { for (i=0;i<131072;i++) printf "bonjour " }' >"$tmp/large"
./reading_cow --no-delay "$tmp/large" >/dev/null
cp "$tmp/text" "$tmp/-text"
(cd "$tmp" && "$OLDPWD/reading_cow" --no-delay -- -text) >/dev/null
chmod 000 "$tmp/text"
if [[ ! -r $tmp/text ]]; then reject ./reading_cow --no-delay "$tmp/text"; else echo 'SKIP: permissions (privileged user)'; fi
chmod 600 "$tmp/text"
for at in 1 2 3; do
    reject env FAIL_AT="$at" ./tests/fail_alloc --no-delay "$tmp/long"
    [[ $(cat "$tmp/err") == *'mémoire insuffisante'* ]] || fail 'allocation diagnostic'
done
TERM=xterm ./tamagoshi_cow </dev/null >"$tmp/out" 2>"$tmp/err" && fail EOF
TERM=xterm ./tamagoshi_cow <<<stop >/dev/null
# Deterministic digestion kills the cow in two turns; invalid food is retried.
printf 'Alice\nstop\nnon\n\n \nx\n-1\n6\n0\n0\n' |
    TERM=xterm ./tests/fast_tamagoshi >"$tmp/game" 2>"$tmp/err"
[[ $(cat "$tmp/game") == *'Fin de partie'* ]] || fail game
[[ $(cat "$tmp/err") == *'Entrez un entier'* ]] || fail 'food validation'
printf '%100s\n' '' >"$tmp/input"
reject env TERM=xterm ./tests/fast_tamagoshi <"$tmp/input"
printf 'Alice\nstop\n%s\n' 'this-answer-is-too-long' >"$tmp/input"
reject env TERM=xterm ./tests/fast_tamagoshi <"$tmp/input"
for script in ./*.sh; do
    bash -n "$script"
    bash "$script" --help >"$tmp/help"
    reject bash "$script"
    reject bash "$script" 1 extra
done
for script in cow_*.sh crazy_cow.sh; do
    for value in -1 abc '1+1' 1000001 999999999999999999999; do reject bash "$script" "$value";done
done
# Isolate script formatting and sequences from optional cowsay/bc installations.
mkdir "$tmp/bin"
cat >"$tmp/bin/cowsay" <<'STUB'
#!/bin/bash
printf '%s\n' "$*"
STUB
cat >"$tmp/bin/sleep" <<'STUB'
#!/bin/bash
exit 0
STUB
chmod +x "$tmp/bin/"*
PATH="$tmp/bin:$PATH" bash cow_primaryschool.sh 003 >"$tmp/out"
[[ $(cat "$tmp/out") == *'La vache dit: 3'* ]] || fail counting
PATH="$tmp/bin:$PATH" bash cow_highschool.sh 3 >"$tmp/out"
[[ $(cat "$tmp/out") == *'Le carré de 3 est 9'* ]] || fail squares
PATH="$tmp/bin:$PATH" bash cow_college.sh 5 >"$tmp/out"
[[ $(cat "$tmp/out") == *'La vache dit : 5'* ]] || fail Fibonacci
PATH="$tmp/bin:$PATH" bash cow_university.sh 5 >"$tmp/out"
[[ $(cat "$tmp/out") == *'la vach dit : 5'* ]] || fail primes
if command -v bc >/dev/null; then
    PATH="$tmp/bin:$PATH" bash smart_cow.sh '2+3' >"$tmp/out"
    [[ $(cat "$tmp/out") == '2+3 = 5' ]] || fail calculator
    reject env PATH="$tmp/bin:$PATH" bash smart_cow.sh '1/0'
    reject env PATH="$tmp/bin:$PATH" bash smart_cow.sh '2+'
    PATH="$tmp/bin:$PATH" bash crazy_cow.sh 5 >"$tmp/out"
    [[ $(cat "$tmp/out") == *'de 5 est 101'* ]] || fail binary
else
    echo 'SKIP: calculator/binary conversion (bc unavailable)'
fi
mkdir "$tmp/empty-bin"
reject env PATH="$tmp/empty-bin" /bin/bash cow_primaryschool.sh 1
[[ $(cat "$tmp/err") == *'Dépendance manquante: cowsay'* ]] || fail 'missing cowsay'
reject env PATH="$tmp/bin" /bin/bash smart_cow.sh '2+3'
[[ $(cat "$tmp/err") == *'Dépendance manquante: bc'* ]] || fail 'missing bc'
echo 'All tests passed.'
