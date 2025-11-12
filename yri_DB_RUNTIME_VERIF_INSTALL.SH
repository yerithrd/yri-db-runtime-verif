#!/bin/sh
# @author: Pr. Prof. Dr. Xavier Noundou, YERITH R&D

# SHOWS THIS Makefile FILE COMMAND STRING IN THE
# CONSOLE AS THEY ARE EXECUTED.
set -x


sudo gdebi -n yri-db-runtime-verif.deb

sudo systemctl daemon-reload


