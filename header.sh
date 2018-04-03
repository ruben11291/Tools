###Author: Ruben Perez Pascual
###Email: ruben11291@gmail.com
###Github:ruben11291

#!/bin/bash

header="###Author: Ruben Perez Pascual\n###Email: ruben11291@gmail.com\n###Github:ruben11291\n"
for file in "$@"
do 
    sed -i -e "1i\
        $header" $file
done
