#!/usr/bin/env python2

##
# normalize data source
##

import sys
import re

re_whitespace = re.compile(r'[ \t]+[,|]?[ \t]*')
re_mail = re.compile(r'^[-+0-9a-zA-Z%_.]*@([-0-9A-Za-z]+\.)+[-0-9A-Za-z_]{2,}$')

def normalize(line):
    x = re_whitespace.split(line);
    if len(x) == 2:
        if re_mail.match(x[0]): return (x[0], x[1])
    if len(x) == 3:
        if re_mail.match(x[1]): return (x[1], x[2])
        if re_mail.match(x[2]): return (x[2], x[1])
    if len(x) == 4:
        if re_mail.match(x[2]): return (x[2], x[3])
        if re_mail.match(x[1]): return (x[1], x[3])
    if len(x) == 5:
        if re_mail.match(x[0]): return (x[0], x[4])
    x = line.split('|')
    if len(x) == 2:
        if re_mail.match(x[0]): return (x[0], x[1])
    x = line.split(',')
    if len(x) == 2:
        if re_mail.match(x[0]): return (x[0], x[1])
    if len(x) == 3:
        if re_mail.match(x[1]): return (x[1], x[2])
        if re_mail.match(x[2]): return (x[2], x[1])
    x = line.split('----')
    if len(x) == 2:
        if re_mail.match(x[0]): return (x[0], x[1])
    if len(x) >=3:
        if re_mail.match(x[0]): return (x[0], x[1])
        if re_mail.match(x[1]): return (x[1], x[0])
        if re_mail.match(x[2]): return (x[2], x[1])

while 1:
    line = sys.stdin.readline()
    if not line:
        break
    norm = normalize(line.rstrip());
    if norm:
        print "%s\t%s" % norm

