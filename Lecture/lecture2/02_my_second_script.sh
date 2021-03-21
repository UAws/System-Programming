#!/bin/bash
touch my_third_script.sh
chmod +x my_third_script.sh
echo '#!/bin/bash' >> my_third_script.sh
echo "echo Hello World 2" >> my_third_script.sh
./my_third_script.sh
rm my_third_script.sh
