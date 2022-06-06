#! /bin/bash
git log | grep commit | awk '{print $2}'
