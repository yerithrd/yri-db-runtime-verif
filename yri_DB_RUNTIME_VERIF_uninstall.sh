#!/bin/sh
# @author: Pr. Prof. Dr. Xavier Noundou, YERITH R&D

# SHOWS THIS Makefile FILE COMMAND STRING IN THE
# CONSOLE AS THEY ARE EXECUTED.
set -x


sudo systemctl stop yri-db-runtime-verif

sudo apt -y --purge remove yri-db-runtime-verif

