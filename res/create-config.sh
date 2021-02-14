#!/bin/sh
CONFIG_FILE="/usr/share/nginx/html/config.toml"

echo "[auth]" >> $CONFIG_FILE
if [ ${AUTH_URL} ]
then
    echo "url = \"${AUTH_URL}\"" >> $CONFIG_FILE
fi

echo "[backend]" >> $CONFIG_FILE
if [ ${BACKEND_URL} ]
then
    echo "url = \"${BACKEND_URL}\"" >> $CONFIG_FILE
fi

echo "[scheduler]" >> $CONFIG_FILE
if [ ${SCHEDULER_URL} ]
then
    echo "url = \"${SCHEDULER_URL}\"" >> $CONFIG_FILE
fi
