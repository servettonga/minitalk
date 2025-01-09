#!/bin/bash

# Get server PID
SERVER_PID=$(pgrep server)

if [ -z "$SERVER_PID" ]; then
    echo "Server not running!"
    exit 1
fi

# Send file content to client
cat test_input.txt | while read line; do
    ./client $SERVER_PID "$line"
    sleep 0.1  # Small delay between messages
done
