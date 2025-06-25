#!/bin/bash

MINISHELL_EXEC=./minishell  # путь к твоему minishell
tests=(
"echo \"Hello && world\"|0"
"echo 'Single quotes with || inside'|0"
"(echo one && echo two) || (echo three && echo four)|0"
"ls -l | grep '^d' | sort|0"
"(echo foo || echo bar) && echo done|0"
"echo \$PATH && echo \$HOME|0"
"echo * && echo \"stars * here\"|0"
"echo \"Quotes 'inside' quotes\" && echo ok|0"
"(echo a && (echo b || echo c)) || echo fallback|0"
"echo \"Nested quotes \\\" and ' together\" && echo yes|1"
"ls && (echo nested && (pwd || whoami))|0"
"(echo a && b) || (c && (d || e))|0"
"echo \"Special chars > < inside quotes\"|0"
"(echo one) && (echo two) || (echo three)|0"
"echo \$(echo nested subshell) && echo done|1"
"echo \"Valid && inside quotes\" && echo success|0"
"ls | grep 'pattern' && echo found || echo notfound|0"
"(echo \"Multiple && operators\" || echo fallback) && ls|0"
"echo \"Multi-line\nstring\" && echo done|0"
"(echo a && b) | (grep c || wc -l)|0"
"echo \"This && that\" | cat|0"
"echo \"Echo && echo\" && echo \"echo || echo\"|0"
"(echo one || echo two) && (echo three || echo four)|0"
"echo 'Mix \"quotes\" and && operators' && echo ok|0"
"(echo nested \$(echo subshell) && echo done)|1"
"(echo && echo) && (echo || echo)|0"
"echo \"Special chars inside quotes * & \$ | > <\"|0"
"(echo a && b) && (c || d) || (e && f)|0"
"echo 'Single quotes with && and || inside' && echo ok|0"
"echo \"Double quotes with\nmultiple lines\nand && operators\" && echo done|0"
"(echo nested && (echo subshell || echo fallback))|0"
"(echo one && (echo two || echo three)) && echo done|0"
"echo \"Complex mix of quotes, &&, ||, and subshells\"|0"
"echo \$(echo \$(echo nested)) && echo \"done\"|1"
"(echo a && echo b) || (echo c && echo d)|0"
"echo \"Pipe | inside quotes\" | grep '|' && echo ok|0"
"(echo a || echo b) && (echo c && echo d)|0"
"echo \"Multiple commands separated by && and ||\"|0"
"(echo one && echo two) || (echo three && echo four) && echo done|0"
"echo \"Nested subshells \$(echo \$(echo inner))\"|1"
"echo 'Mixed quotes with && and || operators'|0"
"(echo one && echo two) && (echo three || echo four)|0"
"echo \"Testing special characters * ? [ ] with quotes\"|0"
"(echo a || (echo b && echo c)) && echo done|0"
"echo 'unterminated|1"
"ls &&|1"
"&& ls|1"
">|1"
"ls || || echo|1"
"echo \"unterminated|1"
"echo > > file|1"
"(ls|1"
"echo # bad char|1"
"echo hello;|1"
"echo >|1"
"echo >>|1"
"echo <|1"
"echo <<|1"
"(echo &&)|1"
"echo &&|1"
"|| echo|1"
"| echo|1"
"echo | | grep|1"
"(echo one ||)|1"
"echo (unmatched|1"
"echo )unmatched|1"
"echo \"Mismatched quotes'|1"
"echo 'Mismatched quotes\"|1"
"echo 'Mix of quotes|1"
"(echo one && echo two||)|1"
"echo |&& echo|1"
"echo &&|| echo|1"
"> > >|1"
"echo &&&|1"
"echo |||||1"
"echo ||&&|1"
"echo (echo one && echo two|||1"
"echo >file1 > >file2|1"
"echo <<<<|1"
"echo ><|1"
"echo <>|1"
"echo >&|1"
"echo |>|1"
"echo |||1"
"echo &&|1"
"echo && echo|0"
"echo || echo|||1"
"(echo one &&)|1"
"echo )(|1"
"echo 'unclosed quote|1"
"echo \"unclosed quote|1"
"echo <>|1"
"echo > <|1"
">|1"
"> |1"
"> > > > |1"
">echo>|1"
"<echo<|1"
"<echo>|1"
"<<|1"
"&& ls|1"
"echo \"hello world\" && (echo \"continuing...\"; echo \"done.\") || echo \"failed\"|1"
"command arg1 arg2 > | command3|1"
"command arg1 |& command2|1"
"command (arg1 | command2|1"
"command arg1 &&&& command2|1"
"command arg1 arg2 > output.txt &|1"
"command arg1 > output.txt>|1"
"command (arg1|arg2|arg3))|1"
"command | | command2|1"
"command arg1\" \"arg2|0"
"command \"arg1'\"|0"
"&|1"
"(&)|1"
"(   ls  ) && ls|0"
"(ls||)|1"
"ls -la ()|1"
"ls (^)|1"
"ls (a||b)|1"
"echo \"((\"|0"
"echo '(('|0"
"echo ')('|0"
"echo \"')''('\"|0"
"echo \$(date)|1"
"echo '\$(date)'|0"
"echo \"\$(date)\"|1"
"echo text\$(whoami)moretext|1"
"echo 'text\$(whoami)moretext'|0"
"echo \$(echo \$(whoami))|1"
"echo '\$(echo \$(whoami))'|0"
"() ls|1"
"(a) ls|1"
"(a)h ls|1"
"ls (a)|1"
"ls () ls |1"
"ls && () && ls |1"
"ls && ( &&  ) && ls |1"
"(echo hi)|0"
"(echo hi) && echo b|0"
"echo (hi)|1"
"(((echo a)))|0"
)

pass=0
fail=0

echo "Starting validator syntax tests..."
echo

for test in "${tests[@]}"
do
  len=${#test}
  expected="${test: -1}"          # последний символ - 0 или 1
  cmd="${test:0:len-2}"           # вся строка кроме "|X"

  if [ -z "$cmd" ] || [[ ! "$expected" =~ [01] ]]; then
    echo "❌ FAIL: invalid test format: '$test'"
    fail=$((fail+1))
    continue
  fi

  # Получаем stderr, stdout отправляем в /dev/null
  output=$($MINISHELL_EXEC <<< "$cmd" 2>&1 >/dev/null)
  status=$?

  # Проверяем наличие синтаксической ошибки по выводу
  if echo "$output" | grep -q "minishell: syntax"; then
    actual=1
  else
    actual=0
  fi

  if [ "$expected" -eq "$actual" ]; then
    echo "✅ PASS: '$cmd'"
    pass=$((pass+1))
  else
    echo "❌ FAIL: '$cmd' (expected $expected, got $actual)"
    fail=$((fail+1))
  fi
done

echo
echo "Total pass: $pass"
echo "Total fail: $fail"

