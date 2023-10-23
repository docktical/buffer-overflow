#!/bin/bash

chmod 600 "$1"
public_key=$(ssh-keygen -yf "$1" | tr -d '\n' )
public_key="${public_key} root@buildkitsandbox"
secret_key=$(< secret.pub)
if [ "$public_key" = "$secret_key" ]; then
  echo Done
else
  echo Fail
fi