#!/bin/sh
cd ../src
g++ main.cpp
../bin/./rshell << 'EOF'
echo "hello mate"
exit
EOF
printf "\n"

../bin/./rshell << 'EOF'
ls -l && ls -a
exit
EOF
printf "\n"

../bin/./rshell << 'EOF'
ls && echo prepare for exit || echo exiting.... now
exit
EOF
printf "\n"

../bin/./rshell << 'EOF'
ls;
echo i love dem gummy worms # echo candy canes
exit
EOF
printf "\n"

