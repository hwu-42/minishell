#!/bin/bash

if [[ $- == *i* ]]; then
    echo "Running in interactive mode"
else
    echo "Running in non-interactive mode"
fi
