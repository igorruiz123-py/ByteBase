DIR="output/bin"

if test -d "$DIR"; then

    echo "[INFO] the directory 'output/bin' already exists."

else

    echo "[INFO] setting environment up..."
    mkdir -p $DIR
    echo "[OK] environment ready."

fi
