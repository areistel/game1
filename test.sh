
#!/bin/bash

cd ./cmake/
make
if [ $? -eq 0 ]; then
    cd ..
    ./hot_engine
else
    echo FAIL
fi
