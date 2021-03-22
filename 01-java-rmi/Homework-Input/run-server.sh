#!/bin/sh

export CLASSPATH=.
# -Djava.rmi.dgc.leaseValue=500

java -Xss128m -Djava.rmi.server.hostname=$1 Server
