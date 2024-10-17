#!/bin/bash

mvn clean compile package

java -jar target/ducky-jam.jar