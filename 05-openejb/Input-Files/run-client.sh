#!/bin/sh
source setenv.sh

java -cp "$OPENEJB_HOME/lib/*:example.jar:." Main 42 # --search-only