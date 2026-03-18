DB="output/bin/db.bin"

if test -e $DB; then

    echo "[INFO] removing 'db.bin'..."
    rm -f $DB
    echo "[OK] 'db.bin' removed."

else 

    echo "[INFO] no such file of 'output/bin/db.bin' found."

fi