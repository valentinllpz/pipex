#!/usr/bin/env bash

echo "A long, long time ago the World was in an age of Chaos. In the middle of this chaos, in a little kingdom in the land of Hyrule, a legend was being handed down from generation to generation, the legend of the 'Triforce'; golden triangles possessing mystical powers." > infile
cp infile infile2
touch outfile
touch outfile2
./pipex infile "ls -l" "wc -l" outfile
< infile2 ls -l | wc -l > outfile2
if diff infile infile2 && diff outfile outfile2
then printf "Test 1: \033[92m[OK]\033[0m\n"
else printf "Test 1: \033[91m[KO]\033[0m\n"
fi
./pipex infile "grep al" "wc -w" outfile
< infile2 grep al | wc -w > outfile2
if diff infile infile2 && diff outfile outfile2
then printf "Test 2: \033[92m[OK]\033[0m\n"
else printf "Test 2: \033[91m[KO]\033[0m\n"
fi
./pipex infile "cat" "grep lol" outfile
< infile2 cat | grep lol > outfile2
if diff infile infile2 && diff outfile outfile2
then printf "Test 3: \033[92m[OK]\033[0m\n"
else printf "Test 3: \033[91m[KO]\033[0m\n"
fi
./pipex infile "cat" "grep Triforce" outfile
< infile2 cat | grep Triforce > outfile2
if diff infile infile2 && diff outfile outfile2
then printf "Test 4: \033[92m[OK]\033[0m\n"
else printf "Test 4: \033[91m[KO]\033[0m\n"
fi
./pipex infile "cat" "ls" outfile
< infile2 cat | ls > outfile2
if diff infile infile2 && diff outfile outfile2
then printf "Test 5: \033[92m[OK]\033[0m\n"
else printf "Test 5: \033[91m[KO]\033[0m\n"
fi
./pipex infile "echo test" "wc -l" outfile
< infile2 echo test | wc -l > outfile2
if diff infile infile2 && diff outfile outfile2
then printf "Test 6: \033[92m[OK]\033[0m\n"
else printf "Test 6: \033[91m[KO]\033[0m\n"
fi
./pipex infile "cd" "cd" outfile
< infile2 cd | cd > outfile2
if diff infile infile2 && diff outfile outfile2
then printf "Test 7: \033[92m[OK]\033[0m\n"
else printf "Test 7: \033[91m[KO]\033[0m\n"
fi
./pipex infile "cat" "cat" outfile
< infile2 cat | cat > outfile2
if diff infile infile2 && diff outfile outfile2
then printf "Test 8: \033[92m[OK]\033[0m\n"
else printf "Test 8: \033[91m[KO]\033[0m\n"
fi
./pipex infile "grep nope" "cat" outfile
< infile2 grep nope | cat > outfile2
if diff infile infile2 && diff outfile outfile2
then printf "Test 9: \033[92m[OK]\033[0m\n"
else printf "Test 9: \033[91m[KO]\033[0m\n"
fi
./pipex infile "echo test" "cat" outfile
< infile2 echo test | cat > outfile2
if diff infile infile2 && diff outfile outfile2
then printf "Test 10: \033[92m[OK]\033[0m\n"
else printf "Test 10: \033[91m[KO]\033[0m\n"
fi
rm -rf infile*
rm -rf outfile*