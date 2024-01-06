  #!/bin/bash
set -euo pipefail
if [ "$#" -ge 1 ]; then
    COMPILER_CMD=("$@")
else
    COMPILER_CMD=($(./detect-compiler.sh))
fi

RUN_CMD=${RUN_CMD:-./compiled-test}

echo "Compilation command: ${COMPILER_CMD[@]}"
echo "Run command: $RUN_CMD"

FAIL=0
for tn in $(cat tests.txt); do
    tn=$(echo $tn)  # To remove \r from tests.txt on Windows

    # Uncomment the next line to run a single test
    #if ! [[ $tn =~ t1-01-* ]]; then continue; fi

    echo ===== $tn =====

    pushd test-data/$tn >/dev/null 2>&1
    rm *.out >/dev/null 2>&1 || true
    SOURCES="*.cpp mytest.cpp"
    if ! [ -f main.cpp ]; then
        SOURCES+=" mytest_main.cpp"
    fi
    SOURCES=$(echo $SOURCES | tr ' ' '\n' | sort | sed 's~^mytest~../../mytest~g')

    {
        # Prevent msys on Windows from converting Visual Studio's flags like /W4 to file paths
        # Redirect stderr to stdout so logs are not interleaved
        MSYS_NO_PATHCONV=1 MSYS2_ARG_CONV_EXCL="*" "${COMPILER_CMD[@]}" $SOURCES 2>&1 &&
        { $RUN_CMD >stdout.out 2>stderr.out; echo $? >exit.out; } &&
        diff /dev/null stdout.out &&
        diff stderr.{sol,out} &&
        diff -w exit.{sol,out} &&
        echo PASS;
    } || {
        echo -e "\033[31;1mFAIL\033[0m" &&
        FAIL=1;
    }
    popd >/dev/null 2>&1
done
if [[ "$FAIL" == "0" ]]; then
    echo -e "===== \033[32;1mALL PASS\033[0m ====="
else
    echo -e "===== \033[31;1mSOME FAIL\033[0m ====="
fi
exit $FAIL
